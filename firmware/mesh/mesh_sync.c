/**
 * firmware/mesh/mesh_sync.c
 *
 * High-level mesh synchronization logic for Seed.
 *
 * This module is responsible for:
 *  - Periodically advertising a compact "ledger summary" to neighbors
 *  - Requesting missing ledger data from peers
 *  - Serving ledger data when peers ask for it
 *  - Driving a simple, deterministic sync state machine
 *
 * Design goals:
 *  - Offline-first: no central server, no real-time clock required
 *  - Low bandwidth: send small summaries and ranges, not entire history
 *  - Deterministic: any two devices given the same messages reach the same final ledger state
 *  - Hardware-friendly: simple C code, minimal dynamic allocation, small structs
 *
 * NOTE: This is reference firmware-style code meant for early prototypes
 * and investor / technical review. It will evolve as hardware and protocol
 * details are finalized.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "mesh_sync.h"
#include "mesh_protocol.h"
#include "ledger_manager.h"
#include "timekeeping.h"
#include "radio_interface.h"

// -----------------------------------------------------------------------------
// Configuration knobs
// -----------------------------------------------------------------------------

// How often to send a lightweight "I am alive + ledger summary" broadcast (ms)
#define MESH_HEARTBEAT_INTERVAL_MS      15_000U  // 15 seconds

// How often to initiate a sync check with at least one neighbor (ms)
#define MESH_SYNC_CHECK_INTERVAL_MS     60_000U  // 60 seconds

// Max number of outstanding sync requests we track at once
#define MESH_MAX_PENDING_SYNC           4U

// Maximum number of transaction IDs we will ask for in one request
#define MESH_MAX_TX_REQUEST_BATCH       32U

// -----------------------------------------------------------------------------
// Local types
// -----------------------------------------------------------------------------

/**
 * Small summary of our local ledger state.
 * This is designed to fit comfortably into a single mesh packet
 * and be cheap to compute on low-power hardware.
 */
typedef struct {
    uint32_t last_lamport;     // Highest Lamport clock we've seen
    uint32_t tx_count;         // Total number of transactions
    uint32_t ledger_hash;      // Lightweight hash over ledger checkpoint
} mesh_ledger_summary_t;

/**
 * Tracks an in-progress sync with a specific neighbor.
 */
typedef struct {
    bool     in_use;
    uint32_t neighbor_id;
    uint32_t last_request_time_ms;
    uint32_t next_expected_lamport;   // For range-based fetches
} mesh_pending_sync_t;

// -----------------------------------------------------------------------------
// Static state
// -----------------------------------------------------------------------------

static uint32_t           self_device_id        = 0;
static uint32_t           last_heartbeat_ms     = 0;
static uint32_t           last_sync_check_ms    = 0;
static mesh_pending_sync_t pending_sync[MESH_MAX_PENDING_SYNC];

// -----------------------------------------------------------------------------
// Forward declarations (internal helpers)
// -----------------------------------------------------------------------------

static void mesh_sync_send_heartbeat(void);
static void mesh_sync_handle_heartbeat(const mesh_packet_t *pkt);

static void mesh_sync_consider_peer_summary(uint32_t neighbor_id,
                                            const mesh_ledger_summary_t *remote);

static void mesh_sync_send_summary_request(uint32_t neighbor_id);
static void mesh_sync_send_tx_range_request(uint32_t neighbor_id,
                                            uint32_t from_lamport,
                                            uint32_t max_count);

static void mesh_sync_handle_summary(const mesh_packet_t *pkt);
static void mesh_sync_handle_tx_range_request(const mesh_packet_t *pkt);
static void mesh_sync_handle_tx_range_response(const mesh_packet_t *pkt);

static mesh_pending_sync_t *mesh_sync_get_or_alloc_slot(uint32_t neighbor_id);
static mesh_pending_sync_t *mesh_sync_find_slot(uint32_t neighbor_id);

// -----------------------------------------------------------------------------
// Public API
// -----------------------------------------------------------------------------

void mesh_sync_init(uint32_t device_id)
{
    self_device_id = device_id;
    last_heartbeat_ms  = timekeeping_millis();
    last_sync_check_ms = last_heartbeat_ms;

    memset(pending_sync, 0, sizeof(pending_sync));
}

/**
 * Called periodically from the main loop (e.g., every 500 ms).
 * Drives heartbeats and sync checks.
 */
void mesh_sync_tick(void)
{
    uint32_t now = timekeeping_millis();

    // 1) Periodic heartbeat broadcast
    if ((now - last_heartbeat_ms) >= MESH_HEARTBEAT_INTERVAL_MS) {
        mesh_sync_send_heartbeat();
        last_heartbeat_ms = now;
    }

    // 2) Periodically initiate a sync check with neighbors
    if ((now - last_sync_check_ms) >= MESH_SYNC_CHECK_INTERVAL_MS) {
        // For now we simply broadcast a "summary request" which
        // encourages neighbors to respond with their ledger summaries.
        mesh_sync_send_summary_request(MESH_BROADCAST_ID);
        last_sync_check_ms = now;
    }

    // 3) (Optional future extension): handle timeouts for pending syncs,
    // retry or prune old sync attempts, etc.
}

/**
 * Called by mesh_protocol when a mesh packet addressed to us arrives,
 * and it is classified as a "sync-related" message.
 */
void mesh_sync_on_packet(const mesh_packet_t *pkt)
{
    if (!pkt) return;

    switch (pkt->type) {
        case MESH_MSG_HEARTBEAT:
            mesh_sync_handle_heartbeat(pkt);
            break;

        case MESH_MSG_LEDGER_SUMMARY:
            mesh_sync_handle_summary(pkt);
            break;

        case MESH_MSG_TX_RANGE_REQUEST:
            mesh_sync_handle_tx_range_request(pkt);
            break;

        case MESH_MSG_TX_RANGE_RESPONSE:
            mesh_sync_handle_tx_range_response(pkt);
            break;

        default:
            // Not a sync message; ignore or log
            break;
    }
}

// -----------------------------------------------------------------------------
// Internal helpers - heartbeat & summaries
// -----------------------------------------------------------------------------

/**
 * Build and broadcast a heartbeat that includes a compact ledger summary.
 */
static void mesh_sync_send_heartbeat(void)
{
    mesh_ledger_summary_t summary = {0};
    ledger_get_summary(&summary.last_lamport,
                       &summary.tx_count,
                       &summary.ledger_hash);

    mesh_packet_t pkt;
    memset(&pkt, 0, sizeof(pkt));
    pkt.type       = MESH_MSG_HEARTBEAT;
    pkt.src_id     = self_device_id;
    pkt.dest_id    = MESH_BROADCAST_ID;
    pkt.payload_len = sizeof(summary);

    memcpy(pkt.payload, &summary, sizeof(summary));

    radio_send_packet(&pkt);
}

/**
 * Process a heartbeat from another device.
 * We use the included summary only as a "hint" — the real work
 * happens when we exchange full summaries and range requests.
 */
static void mesh_sync_handle_heartbeat(const mesh_packet_t *pkt)
{
    if (!pkt) return;
    if (pkt->payload_len != sizeof(mesh_ledger_summary_t)) {
        // Malformed or older version; ignore gracefully
        return;
    }

    mesh_ledger_summary_t remote;
    memcpy(&remote, pkt->payload, sizeof(remote));

    mesh_sync_consider_peer_summary(pkt->src_id, &remote);
}

/**
 * Ask whether we should try to sync with this peer based on their summary.
 * For now, we use a very simple rule:
 *  - If their last_lamport or tx_count is greater than ours, we probably
 *    are missing transactions and should fetch.
 */
static void mesh_sync_consider_peer_summary(uint32_t neighbor_id,
                                            const mesh_ledger_summary_t *remote)
{
    mesh_ledger_summary_t local;
    ledger_get_summary(&local.last_lamport,
                       &local.tx_count,
                       &local.ledger_hash);

    bool remote_has_newer =
        (remote->last_lamport > local.last_lamport) ||
        (remote->tx_count     > local.tx_count);

    if (!remote_has_newer) {
        // We are as up-to-date or newer; no action needed.
        return;
    }

    // Allocate / get a sync slot for this neighbor and request a range.
    mesh_pending_sync_t *slot = mesh_sync_get_or_alloc_slot(neighbor_id);
    if (!slot) {
        // No free slots; we may log this and try later.
        return;
    }

    slot->next_expected_lamport = local.last_lamport + 1;
    slot->last_request_time_ms  = timekeeping_millis();

    mesh_sync_send_tx_range_request(neighbor_id,
                                    slot->next_expected_lamport,
                                    MESH_MAX_TX_REQUEST_BATCH);
}

// -----------------------------------------------------------------------------
// Internal helpers - summary + range messages
// -----------------------------------------------------------------------------

/**
 * Broadcast a request for ledger summaries from peers.
 * This is very cheap and used periodically to discover who has new data.
 */
static void mesh_sync_send_summary_request(uint32_t neighbor_id)
{
    mesh_packet_t pkt;
    memset(&pkt, 0, sizeof(pkt));

    pkt.type        = MESH_MSG_LEDGER_SUMMARY_REQUEST;
    pkt.src_id      = self_device_id;
    pkt.dest_id     = neighbor_id;  // could be broadcast or specific

    pkt.payload_len = 0; // no body needed

    radio_send_packet(&pkt);
}

/**
 * Send a request for "transactions with Lamport >= from_lamport"
 * up to max_count. The peer is free to return fewer.
 */
static void mesh_sync_send_tx_range_request(uint32_t neighbor_id,
                                            uint32_t from_lamport,
                                            uint32_t max_count)
{
    mesh_tx_range_request_t req;
    req.from_lamport = from_lamport;
    req.max_count    = max_count;

    mesh_packet_t pkt;
    memset(&pkt, 0, sizeof(pkt));

    pkt.type        = MESH_MSG_TX_RANGE_REQUEST;
    pkt.src_id      = self_device_id;
    pkt.dest_id     = neighbor_id;
    pkt.payload_len = sizeof(req);

    memcpy(pkt.payload, &req, sizeof(req));

    radio_send_packet(&pkt);
}

/**
 * Handle a peer asking us for our ledger summary.
 */
static void mesh_sync_handle_summary(const mesh_packet_t *pkt)
{
    if (!pkt) return;

    if (pkt->type == MESH_MSG_LEDGER_SUMMARY_REQUEST) {
        // Respond with our summary
        mesh_ledger_summary_t summary = {0};
        ledger_get_summary(&summary.last_lamport,
                           &summary.tx_count,
                           &summary.ledger_hash);

        mesh_packet_t out;
        memset(&out, 0, sizeof(out));

        out.type        = MESH_MSG_LEDGER_SUMMARY;
        out.src_id      = self_device_id;
        out.dest_id     = pkt->src_id;
        out.payload_len = sizeof(summary);

        memcpy(out.payload, &summary, sizeof(summary));
        radio_send_packet(&out);
    }
    else if (pkt->type == MESH_MSG_LEDGER_SUMMARY) {
        if (pkt->payload_len != sizeof(mesh_ledger_summary_t)) {
            return;
        }

        mesh_ledger_summary_t remote;
        memcpy(&remote, pkt->payload, sizeof(remote));
        mesh_sync_consider_peer_summary(pkt->src_id, &remote);
    }
}

// -----------------------------------------------------------------------------
// Internal helpers - range request / response
// -----------------------------------------------------------------------------

/**
 * Peer asks us: "give me up to max_count transactions with Lamport >= from_lamport".
 */
static void mesh_sync_handle_tx_range_request(const mesh_packet_t *pkt)
{
    if (!pkt) return;
    if (pkt->payload_len != sizeof(mesh_tx_range_request_t)) {
        return;
    }

    mesh_tx_range_request_t req;
    memcpy(&req, pkt->payload, sizeof(req));

    // Ask ledger_manager for a compact batch of transactions
    mesh_tx_range_response_t resp;
    memset(&resp, 0, sizeof(resp));

    resp.from_lamport = req.from_lamport;
    resp.tx_count     = ledger_get_tx_batch(req.from_lamport,
                                            req.max_count,
                                            resp.txs,
                                            MESH_MAX_TX_IN_RESPONSE);

    mesh_packet_t out;
    memset(&out, 0, sizeof(out));

    out.type        = MESH_MSG_TX_RANGE_RESPONSE;
    out.src_id      = self_device_id;
    out.dest_id     = pkt->src_id;
    out.payload_len = sizeof(resp.from_lamport) +
                      sizeof(resp.tx_count) +
                      resp.tx_count * sizeof(mesh_tx_summary_t);

    memcpy(out.payload, &resp, out.payload_len);

    radio_send_packet(&out);
}

/**
 * Peer has sent us a batch of transactions for the requested Lamport range.
 */
static void mesh_sync_handle_tx_range_response(const mesh_packet_t *pkt)
{
    if (!pkt) return;
    if (pkt->payload_len < (sizeof(uint32_t) * 2)) {
        return; // too small
    }

    mesh_tx_range_response_t resp;
    memset(&resp, 0, sizeof(resp));

    // We trust mesh_protocol to define resp packing, but for clarity:
    memcpy(&resp.from_lamport, pkt->payload, sizeof(uint32_t));
    memcpy(&resp.tx_count,
           pkt->payload + sizeof(uint32_t),
           sizeof(uint32_t));

    if (resp.tx_count > MESH_MAX_TX_IN_RESPONSE) {
        resp.tx_count = MESH_MAX_TX_IN_RESPONSE; // safety clamp
    }

    size_t tx_bytes = resp.tx_count * sizeof(mesh_tx_summary_t);
    if (pkt->payload_len < (sizeof(uint32_t) * 2 + tx_bytes)) {
        // malformed; ignore
        return;
    }

    memcpy(resp.txs,
           pkt->payload + sizeof(uint32_t) * 2,
           tx_bytes);

    // Import into local ledger
    for (uint32_t i = 0; i < resp.tx_count; ++i) {
        ledger_import_tx_summary(&resp.txs[i]);
    }

    // Update sync slot
    mesh_pending_sync_t *slot = mesh_sync_find_slot(pkt->src_id);
    if (!slot) {
        // We didn't know we were syncing with this peer, but that's fine.
        return;
    }

    if (resp.tx_count == 0) {
        // No more txs in this range; sync is probably done.
        slot->in_use = false;
        return;
    }

    // Advance expected lamport and request next batch if needed.
    uint32_t highest_lamport = resp.txs[resp.tx_count - 1].lamport;

    mesh_ledger_summary_t local;
    ledger_get_summary(&local.last_lamport,
                       &local.tx_count,
                       &local.ledger_hash);

    if (highest_lamport < local.last_lamport) {
        // There might be more we don't have; ask again.
        slot->next_expected_lamport = highest_lamport + 1;
        slot->last_request_time_ms  = timekeeping_millis();

        mesh_sync_send_tx_range_request(pkt->src_id,
                                        slot->next_expected_lamport,
                                        MESH_MAX_TX_REQUEST_BATCH);
    } else {
        // We are fully caught up with this peer.
        slot->in_use = false;
    }
}

// -----------------------------------------------------------------------------
// Internal helpers - pending sync slots
// -----------------------------------------------------------------------------

static mesh_pending_sync_t *mesh_sync_get_or_alloc_slot(uint32_t neighbor_id)
{
    mesh_pending_sync_t *free_slot = NULL;

    for (uint32_t i = 0; i < MESH_MAX_PENDING_SYNC; ++i) {
        if (pending_sync[i].in_use &&
            pending_sync[i].neighbor_id == neighbor_id) {
            return &pending_sync[i]; // already tracking this neighbor
        }
        if (!pending_sync[i].in_use && !free_slot) {
            free_slot = &pending_sync[i];
        }
    }

    if (free_slot) {
        free_slot->in_use   = true;
        free_slot->neighbor_id = neighbor_id;
        free_slot->last_request_time_ms = 0;
        free_slot->next_expected_lamport = 0;
    }

    return free_slot;
}

static mesh_pending_sync_t *mesh_sync_find_slot(uint32_t neighbor_id)
{
    for (uint32_t i = 0; i < MESH_MAX_PENDING_SYNC; ++i) {
        if (pending_sync[i].in_use &&
            pending_sync[i].neighbor_id == neighbor_id) {
            return &pending_sync[i];
        }
    }
    return NULL;
}
