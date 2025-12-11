// firmware/ledger/ledger_validation.c
//
// Purpose:
//   Core validation logic for Seed's offline-first ledger.
//   This module decides whether a transaction is:
//     - VALID          → can be applied to the ledger
//     - REJECTED       → permanently invalid (e.g., bad signature)
//     - PENDING        → needs more data (e.g., missing prior tx)
//     - SUSPICIOUS     → structurally valid but triggers risk flags
//
// Notes:
//   - This is architecture-level C (or C-like) code for investors/engineers.
//   - Types like SeedTransaction, LedgerState, and CryptoContext are defined
//     in shared headers (e.g., ledger_types.h, crypto.h, trust_score.h).
//   - The real embedded implementation will optimize memory, I/O, and crypto.
//

#include "ledger_validation.h"
#include "ledger_storage.h"
#include "crypto.h"
#include "trust_score.h"
#include "config.h"
#include "timekeeping.h"
#include "safe_memory.h"

// ---------------------------------------------------------
// ENUMS & CONSTANTS
// ---------------------------------------------------------

// Final classification for a transaction
typedef enum {
    TX_VALID = 0,
    TX_REJECTED,
    TX_PENDING,
    TX_SUSPICIOUS
} TxValidationStatus;

// High-level reason codes for logging / analytics
typedef enum {
    REASON_OK = 0,
    REASON_BAD_FORMAT,
    REASON_DUPLICATE_TX_ID,
    REASON_SIGNATURE_INVALID,
    REASON_INSUFFICIENT_FUNDS,
    REASON_MISSING_ANCESTOR,
    REASON_CLOCK_DRIFT,
    REASON_LIMIT_EXCEEDED,
    REASON_TRUST_SCORE_LOW,
    REASON_INTERNAL_ERROR
} TxValidationReason;

typedef struct {
    TxValidationStatus status;
    TxValidationReason reason;
} ValidationResult;

// Soft/business rules (tunable via config)
static const float MAX_SINGLE_TX_AMOUNT        = 500.0f;
static const float MAX_DAILY_SEND_AMOUNT       = 1000.0f;
static const int   MAX_MISSING_ANCESTORS       = 5;
static const int   MAX_CLOCK_DRIFT_STEPS       = 100000; // lamport units

// ---------------------------------------------------------
// INTERNAL HELPERS
// ---------------------------------------------------------

// Basic structural checks: required fields, ranges, etc.
static bool
check_format(const SeedTransaction *tx)
{
    if (tx == NULL) return false;
    if (tx->amount <= 0.0f) return false;

    // Basic string sanity (in real code we'd also enforce charset/length)
    if (tx->tx_id[0] == '\0') return false;
    if (tx->sender_id[0] == '\0') return false;
    if (tx->receiver_id[0] == '\0') return false;

    // Sender and receiver must not be the same for money movement
    if (safe_strcmp(tx->sender_id, tx->receiver_id) == 0) return false;

    return true;
}

// Detect duplicates / replays by checking if tx_id already exists.
static bool
check_duplicate(const LedgerState *state, const SeedTransaction *tx)
{
    if (!state || !tx) return false;

    const LedgerEntry *existing = ledger_storage_find_entry(state, tx->tx_id);
    return (existing != NULL);
}

// Validate digital signature using device's public key registry.
static bool
check_signature(const CryptoContext *crypto,
                const SeedTransaction *tx)
{
    if (!crypto || !tx) return false;

    const DevicePublicKey *pub =
        crypto_lookup_device_key(crypto, tx->device_id);

    if (pub == NULL) {
        // Unknown device key → treat as invalid
        return false;
    }

    return crypto_verify_signature(crypto, tx, pub);
}

// Ensure lamport clock is plausible and not wildly behind/ahead.
static bool
check_lamport_clock(const LedgerState *state,
                    const SeedTransaction *tx)
{
    if (!state || !tx) return false;

    uint64_t global_max = ledger_storage_get_max_lamport(state);
    // Allow some slack; fully strict behavior would reject anything below
    if (tx->lamport > global_max + MAX_CLOCK_DRIFT_STEPS) {
        return false;
    }
    return true;
}

// Check causal references (prev_tx_ids) exist or can be resolved.
static TxValidationReason
check_causal_ancestors(const LedgerState *state,
                       const SeedTransaction *tx)
{
    if (!state || !tx) return REASON_OK;

    int missing_count = 0;
    for (int i = 0; i < tx->prev_count; ++i) {
        const char *ref_id = tx->prev_tx_ids[i];
        if (!ref_id || ref_id[0] == '\0') continue;

        const LedgerEntry *e = ledger_storage_find_entry(state, ref_id);
        if (e == NULL) {
            missing_count++;
            if (missing_count > MAX_MISSING_ANCESTORS) {
                return REASON_MISSING_ANCESTOR;
            }
        }
    }
    // If some references are missing but under threshold:
    // we allow TX_PENDING at higher level.
    return (missing_count == 0) ? REASON_OK : REASON_MISSING_ANCESTOR;
}

// Calculate current spendable balance for a given account.
static bool
compute_balance(const LedgerState *state,
                const char *account_id,
                float *out_balance)
{
    if (!state || !account_id || !out_balance) return false;

    float balance = 0.0f;
    const LedgerCursor *cur = ledger_storage_cursor_begin(state);
    while (!ledger_storage_cursor_end(cur)) {
        const LedgerEntry *e = ledger_storage_cursor_get(cur);
        if (e->is_valid) {
            if (safe_strcmp(e->tx.sender_id, account_id) == 0) {
                balance -= e->tx.amount;
            }
            if (safe_strcmp(e->tx.receiver_id, account_id) == 0) {
                balance += e->tx.amount;
            }
        }
        ledger_storage_cursor_next(cur);
    }
    ledger_storage_cursor_free(cur);

    *out_balance = balance;
    return true;
}

// Check that sender has enough funds and respects basic limits.
static TxValidationReason
check_funds_and_limits(const LedgerState *state,
                       const SeedTransaction *tx)
{
    float balance = 0.0f;
    if (!compute_balance(state, tx->sender_id, &balance)) {
        return REASON_INTERNAL_ERROR;
    }

    if (tx->amount > balance) {
        return REASON_INSUFFICIENT_FUNDS;
    }

    if (tx->amount > MAX_SINGLE_TX_AMOUNT) {
        return REASON_LIMIT_EXCEEDED;
    }

    // Daily send cap (simplified; real code would consider timestamps)
    float daily_sent = ledger_storage_sum_daily_sent(state, tx->sender_id);
    if (daily_sent + tx->amount > MAX_DAILY_SEND_AMOUNT) {
        return REASON_LIMIT_EXCEEDED;
    }

    return REASON_OK;
}

// Trust-score based risk gating. Does NOT necessarily reject, can mark suspicious.
static TxValidationReason
check_trust_score(const TrustScoreContext *ts,
                  const SeedTransaction *tx,
                  bool *out_suspicious)
{
    if (!ts || !tx || !out_suspicious) return REASON_INTERNAL_ERROR;

    *out_suspicious = false;

    float score = trust_score_get(ts, tx->sender_id);
    if (score < TRUST_SCORE_HARD_REJECT) {
        return REASON_TRUST_SCORE_LOW;
    }

    if (score < TRUST_SCORE_SOFT_THRESHOLD) {
        *out_suspicious = true;
    }

    return REASON_OK;
}

// ---------------------------------------------------------
// PUBLIC ENTRY POINT
// ---------------------------------------------------------

bool
ledger_validate_transaction(const LedgerState       *state,
                            const CryptoContext     *crypto,
                            const TrustScoreContext *trust_ctx,
                            const SeedTransaction   *tx,
                            ValidationResult        *out_result)
{
    if (!out_result) return false;
    out_result->status = TX_REJECTED;
    out_result->reason = REASON_INTERNAL_ERROR;

    if (!state || !crypto || !trust_ctx || !tx) {
        return false;
    }

    // 1) Structural / format checks
    if (!check_format(tx)) {
        out_result->status = TX_REJECTED;
        out_result->reason = REASON_BAD_FORMAT;
        return true;
    }

    // 2) Duplicate / replay protection
    if (check_duplicate(state, tx)) {
        out_result->status = TX_REJECTED;
        out_result->reason = REASON_DUPLICATE_TX_ID;
        return true;
    }

    // 3) Signature / authenticity
    if (!check_signature(crypto, tx)) {
        out_result->status = TX_REJECTED;
        out_result->reason = REASON_SIGNATURE_INVALID;
        return true;
    }

    // 4) Lamport clock sanity
    if (!check_lamport_clock(state, tx)) {
        out_result->status = TX_REJECTED;
        out_result->reason = REASON_CLOCK_DRIFT;
        return true;
    }

    // 5) Causal ancestry checks
    TxValidationReason causality_reason = check_causal_ancestors(state, tx);
    if (causality_reason == REASON_MISSING_ANCESTOR) {
        // Missing ancestors but under threshold → PENDING
        out_result->status = TX_PENDING;
        out_result->reason = REASON_MISSING_ANCESTOR;
        return true;
    }

    // 6) Balance and limits
    TxValidationReason funds_reason = check_funds_and_limits(state, tx);
    if (funds_reason != REASON_OK) {
        out_result->status = TX_REJECTED;
        out_result->reason = funds_reason;
        return true;
    }

    // 7) Trust score / risk checks
    bool suspicious = false;
    TxValidationReason trust_reason = check_trust_score(trust_ctx, tx, &suspicious);
    if (trust_reason == REASON_TRUST_SCORE_LOW) {
        out_result->status = TX_REJECTED;
        out_result->reason = trust_reason;
        return true;
    }
    if (trust_reason == REASON_INTERNAL_ERROR) {
        out_result->status = TX_REJECTED;
        out_result->reason = trust_reason;
        return true;
    }

    // If we reached here, transaction is structurally valid & funded.
    if (suspicious) {
        out_result->status = TX_SUSPICIOUS;
        out_result->reason = REASON_OK;
    } else {
        out_result->status = TX_VALID;
        out_result->reason = REASON_OK;
    }

    return true;
}

// ---------------------------------------------------------
// HIGH-LEVEL LEDGER APPLY ENTRY
// ---------------------------------------------------------

bool
ledger_try_apply_transaction(LedgerState             *state,
                             const CryptoContext     *crypto,
                             const TrustScoreContext *trust_ctx,
                             const SeedTransaction   *tx)
{
    ValidationResult vr;
    if (!ledger_validate_transaction(state, crypto, trust_ctx, tx, &vr)) {
        return false;
    }

    switch (vr.status) {
        case TX_VALID:
        case TX_SUSPICIOUS:
            // Store transaction with status; upper layers may flag suspicious.
            if (!ledger_storage_append(state, tx, (vr.status == TX_SUSPICIOUS))) {
                return false;
            }
            return true;

        case TX_PENDING:
            // Store in a pending pool; reconciliation logic will retry later
            return ledger_storage_append_pending(state, tx);

        case TX_REJECTED:
        default:
            // Optionally log for audit; do not modify ledger state
            ledger_storage_log_rejected(tx, vr.reason);
            return false;
    }
}
