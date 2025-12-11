/**
 * firmware/ledger/ledger_manager.c
 *
 * High-level ledger orchestration for Seed devices.
 * --------------------------------------------------
 * This module:
 *  - Owns the in-memory view of the ledger (balances + tx metadata)
 *  - Coordinates validation, application, and persistence of transactions
 *  - Exposes a small API for the rest of the firmware (UI, mesh, etc.)
 *
 * NOTE: This is “investor-ready” / prototype-level code:
 *  - Focuses on clarity and structure, not micro-optimizations
 *  - Many details are delegated to other modules (ledger_storage, validation, etc.)
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "ledger_manager.h"
#include "ledger_storage.h"        // on-flash storage read/write
#include "ledger_validation.h"     // balance checks, signature checks, etc.
#include "security_module.h"       // device keys, signatures
#include "timekeeping.h"           // monotonic time / logical clock
#include "crc16.h"                 // integrity checks for snapshots

/* --------------------------------------------------------------------------
 *  Internal types
 * --------------------------------------------------------------------------*/

/**
 * Simple in-memory representation of a transaction.
 * In the real implementation this should match the protocol / JSON schema.
 */
typedef struct {
    uint8_t  tx_id[LEDGER_TX_ID_LEN];     // unique transaction id (binary or hash)
    char     sender[LEDGER_ID_STR_LEN];
    char     receiver[LEDGER_ID_STR_LEN];
    int32_t  amount_cents;                // store in smallest currency unit
    uint32_t lamport;                     // logical clock from originating device
    char     device_id[LEDGER_ID_STR_LEN];
    uint8_t  prev_hash[LEDGER_HASH_LEN];  // optional: hash of previous tx / checkpoint
    uint8_t  signature[LEDGER_SIG_LEN];   // detached signature
    uint8_t  flags;                       // bit flags: pending / valid / invalid
} ledger_tx_t;

/**
 * Aggregate state of the ledger in RAM.
 * This is the “truth” that UI and mesh layer read from.
 */
typedef struct {
    uint32_t  last_applied_index;         // last applied tx index in storage
    uint32_t  logical_clock;              // local Lamport clock
    int64_t   cached_balance_cents;       // cached balance for this device_id
    bool      loaded;                     // has the ledger been loaded from flash?
} ledger_state_t;

/* Bit flags for ledger_tx_t.flags */
#define LEDGER_FLAG_PENDING   (1u << 0)
#define LEDGER_FLAG_VALID     (1u << 1)
#define LEDGER_FLAG_INVALID   (1u << 2)

/* --------------------------------------------------------------------------
 *  Static state
 * --------------------------------------------------------------------------*/

static ledger_state_t g_ledger_state;

/* --------------------------------------------------------------------------
 *  Local helpers
 * --------------------------------------------------------------------------*/

/**
 * Advance the logical clock safely and return the new value.
 * This keeps Lamport clocks monotonic per device.
 */
static uint32_t ledger_bump_clock(uint32_t external_clock_hint)
{
    if (external_clock_hint > g_ledger_state.logical_clock) {
        g_ledger_state.logical_clock = external_clock_hint;
    }
    g_ledger_state.logical_clock += 1;
    return g_ledger_state.logical_clock;
}

/**
 * Update cached balance based on a newly-applied transaction.
 * This is a micro-optimization so we don’t recompute from scratch on every query.
 */
static void ledger_update_cached_balance(const ledger_tx_t *tx,
                                         const char *my_device_id)
{
    if (strncmp(tx->sender, my_device_id, LEDGER_ID_STR_LEN) == 0) {
        g_ledger_state.cached_balance_cents -= tx->amount_cents;
    }
    if (strncmp(tx->receiver, my_device_id, LEDGER_ID_STR_LEN) == 0) {
        g_ledger_state.cached_balance_cents += tx->amount_cents;
    }
}

/* --------------------------------------------------------------------------
 *  Public API
 * --------------------------------------------------------------------------*/

void ledger_init(void)
{
    memset(&g_ledger_state, 0, sizeof(g_ledger_state));

    // Load persisted metadata (last index, cached balance, logical clock)
    ledger_meta_t meta;
    if (ledger_storage_load_meta(&meta)) {
        g_ledger_state.last_applied_index   = meta.last_applied_index;
        g_ledger_state.logical_clock        = meta.logical_clock;
        g_ledger_state.cached_balance_cents = meta.cached_balance_cents;
        g_ledger_state.loaded               = true;
    } else {
        // Fresh device or corrupted meta → start from zero
        g_ledger_state.last_applied_index   = 0;
        g_ledger_state.logical_clock        = 0;
        g_ledger_state.cached_balance_cents = 0;
        g_ledger_state.loaded               = true;

        // Persist default meta immediately
        ledger_meta_t new_meta = {
            .last_applied_index   = 0,
            .logical_clock        = 0,
            .cached_balance_cents = 0
        };
        ledger_storage_store_meta(&new_meta);
    }
}

/**
 * Return the locally cached balance for this device.
 * NOTE: this is a single “owner” balance; multi-account support can extend this.
 */
int64_t ledger_get_cached_balance_cents(void)
{
    return g_ledger_state.cached_balance_cents;
}

/**
 * Build a new transaction object ready to be validated and stored.
 * The caller provides sender/receiver/amount; we attach clock + device id + signature.
 */
bool ledger_build_transaction(const char *sender,
                              const char *receiver,
                              int32_t amount_cents,
                              const char *device_id,
                              ledger_tx_t *out_tx)
{
    if (!sender || !receiver || !device_id || !out_tx) {
        return false;
    }
    if (amount_cents <= 0) {
        return false; // Seed does not support zero/negative transfers
    }

    memset(out_tx, 0, sizeof(*out_tx));

    // Generate transaction id (using security module / RNG / hash)
    if (!security_generate_tx_id(out_tx->tx_id, sizeof(out_tx->tx_id))) {
        return false;
    }

    // Copy identifiers
    strncpy(out_tx->sender,   sender,   LEDGER_ID_STR_LEN - 1);
    strncpy(out_tx->receiver, receiver, LEDGER_ID_STR_LEN - 1);
    strncpy(out_tx->device_id, device_id, LEDGER_ID_STR_LEN - 1);

    // Attach amount and Lamport clock
    out_tx->amount_cents = amount_cents;
    out_tx->lamport      = ledger_bump_clock(0);

    // Fetch previous hash / checkpoint from storage (optional chaining)
    ledger_storage_get_latest_hash(out_tx->prev_hash, sizeof(out_tx->prev_hash));

    // Sign transaction using the device’s private key
    if (!security_sign_transaction((const uint8_t *)out_tx,
                                   sizeof(*out_tx) - LEDGER_SIG_LEN,
                                   out_tx->signature,
                                   sizeof(out_tx->signature))) {
        return false;
    }

    // Mark pending until fully validated and persisted
    out_tx->flags = LEDGER_FLAG_PENDING;

    return true;
}

/**
 * Validate and apply a transaction:
 *  - signature check
 *  - basic format checks
 *  - balance / double-spend checks
 *  - persistence to flash
 *  - update of in-memory state
 */
ledger_apply_result_t ledger_apply_transaction(const ledger_tx_t *tx,
                                               const char *my_device_id)
{
    if (!tx || !my_device_id) {
        return LEDGER_APPLY_ERROR_FORMAT;
    }

    // 1. Signature and basic format validation
    if (!ledger_validation_check_signature(tx)) {
        return LEDGER_APPLY_INVALID_SIGNATURE;
    }
    if (!ledger_validation_check_format(tx)) {
        return LEDGER_APPLY_ERROR_FORMAT;
    }

    // 2. Replay / duplicate detection
    if (ledger_storage_transaction_exists(tx->tx_id)) {
        return LEDGER_APPLY_DUPLICATE;
    }

    // 3. Balance & double-spend checks (using a temporary simulated state)
    ledger_balance_ctx_t balance_ctx;
    ledger_storage_build_balance_context(&balance_ctx, tx->sender);

    if (!ledger_validation_check_sufficient_funds(&balance_ctx, tx->amount_cents)) {
        return LEDGER_APPLY_INSUFFICIENT_FUNDS;
    }

    // 4. Persist transaction to storage
    uint32_t new_index = 0;
    if (!ledger_storage_append_transaction(tx, &new_index)) {
        return LEDGER_APPLY_STORAGE_ERROR;
    }

    // 5. Update meta (index, clock, cached balance)
    g_ledger_state.last_applied_index = new_index;
    ledger_update_cached_balance(tx, my_device_id);

    ledger_meta_t meta = {
        .last_applied_index   = g_ledger_state.last_applied_index,
        .logical_clock        = g_ledger_state.logical_clock,
        .cached_balance_cents = g_ledger_state.cached_balance_cents
    };
    ledger_storage_store_meta(&meta);

    return LEDGER_APPLY_OK;
}

/**
 * Import a batch of transactions from mesh / USB / kiosk, reconcile, and apply.
 * This is the high-level "offline sync" entry point from the mesh stack.
 */
uint32_t ledger_import_batch(const ledger_tx_t *txs,
                             uint32_t count,
                             const char *my_device_id)
{
    if (!txs || count == 0 || !my_device_id) {
        return 0;
    }

    // 1. Pre-filter duplicates and obviously malformed txs
    //    (in a real implementation, we might also sort by lamport/device_id here).
    uint32_t applied = 0;

    for (uint32_t i = 0; i < count; i++) {
        const ledger_tx_t *tx = &txs[i];

        // Update local Lamport clock based on incoming tx
        ledger_bump_clock(tx->lamport);

        // Skip if already stored
        if (ledger_storage_transaction_exists(tx->tx_id)) {
            continue;
        }

        // Conflict resolution will be primarily handled by ordering rules
        // inside ledger_validation / mesh-protocol sync. For now, we just
        // run the normal apply path:
        ledger_apply_result_t res = ledger_apply_transaction(tx, my_device_id);
        if (res == LEDGER_APPLY_OK) {
            applied++;
        } else {
            // TODO: track invalid / orphaned txs for diagnostics
        }
    }

    return applied;
}

/**
 * Export a compact snapshot of the ledger for sync.
 * This might be all transactions, or a rolling window, depending on design.
 */
bool ledger_export_snapshot(uint8_t *buffer,
                            uint32_t buffer_size,
                            uint32_t *out_len)
{
    if (!buffer || !out_len) {
        return false;
    }

    // Delegate to storage module to serialize a snapshot range.
    // For now, we export the full ledger; later this can be incremental.
    uint32_t written = 0;
    if (!ledger_storage_stream_all(buffer, buffer_size, &written)) {
        return false;
    }

    // Append a CRC to detect corruption in transit
    uint16_t crc = crc16_compute(buffer, written);
    if (written + sizeof(crc) > buffer_size) {
        return false;
    }
    memcpy(buffer + written, &crc, sizeof(crc));
    written += sizeof(crc);

    *out_len = written;
    return true;
}

/**
 * Import a snapshot (e.g., from a kiosk, phone, or trusted Seed hub).
 * This is used for “fast sync” when a device has been offline for a long time.
 */
bool ledger_import_snapshot(const uint8_t *buffer,
                            uint32_t length,
                            const char *my_device_id)
{
    if (!buffer || length < sizeof(uint16_t) || !my_device_id) {
        return false;
    }

    // Verify CRC
    uint32_t data_len = length - sizeof(uint16_t);
    uint16_t expected_crc;
    memcpy(&expected_crc, buffer + data_len, sizeof(expected_crc));

    uint16_t actual_crc = crc16_compute(buffer, data_len);
    if (actual_crc != expected_crc) {
        return false; // corrupted snapshot
    }

    // Reset local ledger and reload from snapshot via storage layer
    if (!ledger_storage_replace_from_snapshot(buffer, data_len)) {
        return false;
    }

    // Rebuild meta & cached balance
    ledger_meta_t meta;
    if (!ledger_storage_load_meta(&meta)) {
        return false;
    }

    g_ledger_state.last_applied_index   = meta.last_applied_index;
    g_ledger_state.logical_clock        = meta.logical_clock;
    g_ledger_state.cached_balance_cents = meta.cached_balance_cents;
    g_ledger_state.loaded               = true;

    return true;
}
