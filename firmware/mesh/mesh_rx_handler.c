/**
 * ============================================================================
 *  File: mesh_rx_handler.c
 *  Description:
 *      Responsible for receiving, validating, decoding, and dispatching all
 *      inbound mesh packets. This is one of the MOST critical files in Seed’s
 *      offline-first mesh architecture because it ensures:
 *
 *          - No duplicate packets enter the system
 *          - No malformed packets cause crashes or corruption
 *          - No replayed packets undermine ledger security
 *          - All valid packets are routed to the ledger, sync engine, or
 *            application layer
 *          - Lamport clocks are updated safely
 *
 *      NOTE: This file does NOT decode ledger logic itself—only hands the
 *      packet to the ledger engine. This separation of concerns makes the
 *      system more secure and testable.
 *
 * ============================================================================
 */

#include "mesh_rx_handler.h"
#include "mesh_protocol.h"
#include "mesh_tx_queue.h"
#include "mesh_neighbor_table.h"
#include "../ledger/ledger_manager.h"
#include "../security/security_module.h"
#include "../utils/tiny_json_parser.h"
#include "../utils/timekeeping.h"

#define MAX_PACKET_SIZE    256
#define REPLAY_CACHE_SIZE  128
#define LAMPORT_UPDATE(x,y)  ((x) = ((x) > (y) ? (x) : (y)) + 1)

// ---------------------------------------------------------------------------
// GLOBAL STATE
// ---------------------------------------------------------------------------

static uint8_t replay_cache_index = 0;
static uint32_t replay_cache[REPLAY_CACHE_SIZE];   // stores packet hashes to prevent replay

// ---------------------------------------------------------------------------
// INTERNAL HELPERS
// ---------------------------------------------------------------------------

/**
 * Check if this packet hash was seen recently.
 */
static bool seen_recently(uint32_t hash)
{
    for (int i = 0; i < REPLAY_CACHE_SIZE; i++)
    {
        if (replay_cache[i] == hash)
            return true;
    }
    return false;
}

/**
 * Add a packet hash to replay cache.
 */
static void remember(uint32_t hash)
{
    replay_cache[replay_cache_index++] = hash;
    if (replay_cache_index >= REPLAY_CACHE_SIZE)
        replay_cache_index = 0;
}

/**
 * Compute a simple but stable hash of packet contents.
 * (Production version will use cryptographic hashing.)
 */
static uint32_t hash_packet(const uint8_t *data, uint16_t length)
{
    uint32_t h = 5381;
    for (int i = 0; i < length; i++)
        h = ((h << 5) + h) ^ data[i];
    return h;
}

// ---------------------------------------------------------------------------
// CORE PACKET PROCESSING
// ---------------------------------------------------------------------------

/**
 * Main entry point from radio ISR or radio driver.
 */
void mesh_handle_rx_packet(const uint8_t *data, uint16_t length, int8_t rssi)
{
    if (length == 0 || length > MAX_PACKET_SIZE)
    {
        // Ignore malformed size
        return;
    }

    // Step 1: hash + replay protection
    uint32_t packet_hash = hash_packet(data, length);

    if (seen_recently(packet_hash))
    {
        // Replay attempt OR redundant propagation
        return;
    }

    remember(packet_hash);

    // Step 2: Parse JSON packet
    mesh_packet_t packet;
    if (!mesh_protocol_parse(data, length, &packet))
    {
        // Malformed JSON or missing required fields
        return;
    }

    // Step 3: Validate signature (critical for financial safety)
    if (!security_verify_signature(packet.sender_id, packet.signature, data, length))
    {
        // Reject packet silently; security failure
        return;
    }

    // Step 4: Update neighbor table with RSSI info
    mesh_neighbor_update(packet.sender_id, rssi);

    // Step 5: Lamport clock update (offline-safe ordering)
    LAMPORT_UPDATE(global_lamport_clock, packet.lamport);

    // Step 6: Dispatch by message type
    switch (packet.type)
    {
        case MSG_TRANSACTION:
            ledger_handle_incoming_transaction(&packet.payload.transaction);
            break;

        case MSG_LEDGER_SYNC:
            ledger_handle_sync_block(&packet.payload.sync_block);
            break;

        case MSG_HEARTBEAT:
            // Heartbeat simply updates neighbor table; nothing else required
            break;

        case MSG_GROUP_SAVINGS:
            ledger_handle_group_savings(&packet.payload.group_savings);
            break;

        case MSG_TRUST_UPDATE:
            ledger_handle_trust_update(&packet.payload.trust_update);
            break;

        default:
            // Unknown message type; ignore for safety
            return;
    }

    // Step 7: (Optional) Re-broadcast in mesh if required by protocol
    //         Seed uses controlled gossip, not flooding.
    if (packet.ttl > 0)
    {
        packet.ttl -= 1;
        mesh_tx_queue_enqueue(&packet);
    }
}

// ---------------------------------------------------------------------------
// UNIT TEST HOOKS (ignored on device builds)
// ---------------------------------------------------------------------------

#ifdef UNIT_TEST
bool test_seen_recently(uint32_t h) { return seen_recently(h); }
void test_remember(uint32_t h) { remember(h); }
#endif
