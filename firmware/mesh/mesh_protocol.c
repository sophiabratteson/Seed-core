// firmware/mesh/mesh_protocol.c
//
// Core mesh protocol implementation for Seed devices.
// ---------------------------------------------------
// This module is responsible for:
//  - Defining on-air packet structure for the Seed mesh.
//  - Encoding/decoding headers and payloads.
//  - Attaching metadata (TTL, hop count, message type, IDs).
//  - Basic flooding / forwarding with power-aware limits.
//  - Invoking upper-layer handlers (ledger sync, group savings, trust-score updates).
//
// NOTE: This is an implementation skeleton meant to be “investor-ready”:
//  - The structure and comments are realistic for an embedded project.
//  - Many functions are stubs or simplified for clarity.
//  - Real hardware integration happens via radio_interface.c and other modules.

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "mesh_protocol.h"
#include "radio_interface.h"
#include "security_module.h"
#include "storage_manager.h"

// -----------------------------------------------------------------------------
// Mesh Protocol Constants
// -----------------------------------------------------------------------------

// Max on-air bytes per packet (LoRa link budget / regional compliance).
// This should stay conservative to maintain range and reliability.
#define MESH_MAX_PACKET_SIZE         128

// Maximum hop count (prevents infinite forwarding loops).
#define MESH_MAX_HOPS                8

// Time-to-Live for packets (in hops).
#define MESH_DEFAULT_TTL             5

// Simple replay cache size (number of recent message IDs cached).
#define MESH_REPLAY_CACHE_SIZE       32

// -----------------------------------------------------------------------------
// Message Types (must align with docs: mesh-protocol/message_types/*)
// -----------------------------------------------------------------------------

typedef enum {
    MESH_MSG_TRANSACTION       = 0x01, // Individual ledger transaction
    MESH_MSG_LEDGER_SYNC       = 0x02, // Bulk ledger fragment / snapshot
    MESH_MSG_HEARTBEAT         = 0x03, // Presence + health beacon
    MESH_MSG_GROUP_SAVINGS     = 0x04, // Savings-group contribution / payout
    MESH_MSG_TRUST_SCORE       = 0x05, // Trust score update / broadcast
    MESH_MSG_ERROR_REPORT      = 0x06  // Error / anomaly report
} mesh_msg_type_t;

// -----------------------------------------------------------------------------
// Basic Types
// -----------------------------------------------------------------------------

typedef uint16_t mesh_address_t;   // Short device address on mesh
typedef uint32_t mesh_msg_id_t;    // Logical message identifier (for replay protection)

// Mesh header placed at the beginning of every on-air packet.
// Keep this compact: LoRa has limited payload capacity.
typedef struct {
    mesh_msg_type_t type;     // Message type
    mesh_address_t  src;      // Source node
    mesh_address_t  dst;      // Destination node (0xFFFF = broadcast)
    uint8_t         ttl;      // Remaining hops
    uint8_t         hops;     // Hops already traversed
    mesh_msg_id_t   msg_id;   // Per-source unique identifier
} mesh_header_t;

// In-memory representation of a mesh packet (header + payload).
typedef struct {
    mesh_header_t header;
    uint8_t       payload[MESH_MAX_PACKET_SIZE - sizeof(mesh_header_t)];
    uint8_t       payload_len;
} mesh_packet_t;

// -----------------------------------------------------------------------------
// External Dependencies (provided by other modules)
// -----------------------------------------------------------------------------

// radio_interface.c must provide these:
extern bool radio_send_bytes(const uint8_t *data, uint8_t len);
extern void radio_set_receive_callback(void (*cb)(const uint8_t *data, uint8_t len));

// security_module.c must provide signing / verification:
extern bool security_sign_packet(uint8_t *data, uint8_t *len, uint8_t max_len);
extern bool security_verify_packet(const uint8_t *data, uint8_t len);

// storage_manager.c can be used to persist replay cache, metrics, etc.
// For now, we keep replay cache in RAM for simplicity.

// Upper-layer callbacks (implemented elsewhere, e.g., ledger_manager.c):
void mesh_on_transaction_message(const uint8_t *payload, uint8_t len);
void mesh_on_ledger_sync_message(const uint8_t *payload, uint8_t len);
void mesh_on_group_savings_message(const uint8_t *payload, uint8_t len);
void mesh_on_trust_score_message(const uint8_t *payload, uint8_t len);
void mesh_on_heartbeat_message(const uint8_t *payload, uint8_t len);

// -----------------------------------------------------------------------------
// Module State
// -----------------------------------------------------------------------------

static mesh_address_t g_local_address   = 0;
static mesh_msg_id_t  g_next_msg_id     = 1;

// Very simple replay cache; in production we might make this
// a ring buffer persisted to flash, with timestamp/TTL.
static mesh_msg_id_t  g_replay_cache[MESH_REPLAY_CACHE_SIZE];
static uint8_t        g_replay_cache_head = 0;

// Forward declaration of internal handlers:
static void mesh_radio_rx_callback(const uint8_t *data, uint8_t len);
static bool mesh_is_duplicate(mesh_msg_id_t msg_id);
static void mesh_record_seen(mesh_msg_id_t msg_id);
static void mesh_handle_incoming_packet(mesh_packet_t *pkt);
static void mesh_forward_packet(mesh_packet_t *pkt);

// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

void mesh_init(mesh_address_t local_addr)
{
    g_local_address = local_addr;
    g_next_msg_id   = 1;

    // Clear replay cache
    for (uint8_t i = 0; i < MESH_REPLAY_CACHE_SIZE; i++) {
        g_replay_cache[i] = 0;
    }
    g_replay_cache_head = 0;

    // Register radio receive callback so all incoming packets pass through here.
    radio_set_receive_callback(mesh_radio_rx_callback);
}

// -----------------------------------------------------------------------------
// Public Send APIs (for higher-level modules)
// -----------------------------------------------------------------------------

// Generic send helper
static bool mesh_send_internal(mesh_msg_type_t type,
                               mesh_address_t dst,
                               const uint8_t *payload,
                               uint8_t payload_len)
{
    if (payload_len > (MESH_MAX_PACKET_SIZE - sizeof(mesh_header_t))) {
        return false; // too large
    }

    mesh_packet_t pkt;
    pkt.header.type  = type;
    pkt.header.src   = g_local_address;
    pkt.header.dst   = dst;
    pkt.header.ttl   = MESH_DEFAULT_TTL;
    pkt.header.hops  = 0;
    pkt.header.msg_id = g_next_msg_id++;

    pkt.payload_len = payload_len;
    if (payload_len > 0 && payload != NULL) {
        memcpy(pkt.payload, payload, payload_len);
    }

    // Serialize header + payload into raw buffer
    uint8_t buffer[MESH_MAX_PACKET_SIZE];
    uint8_t len = 0;

    memcpy(&buffer[len], &pkt.header, sizeof(mesh_header_t));
    len += sizeof(mesh_header_t);
    memcpy(&buffer[len], pkt.payload, pkt.payload_len);
    len += pkt.payload_len;

    // Sign packet for authenticity/integrity
    if (!security_sign_packet(buffer, &len, MESH_MAX_PACKET_SIZE)) {
        return false;
    }

    // Send over radio
    return radio_send_bytes(buffer, len);
}

bool mesh_send_transaction_broadcast(const uint8_t *payload, uint8_t len)
{
    return mesh_send_internal(MESH_MSG_TRANSACTION, 0xFFFF, payload, len);
}

bool mesh_send_ledger_sync(mesh_address_t dst,
                           const uint8_t *payload,
                           uint8_t len)
{
    return mesh_send_internal(MESH_MSG_LEDGER_SYNC, dst, payload, len);
}

bool mesh_send_group_savings_update(const uint8_t *payload, uint8_t len)
{
    return mesh_send_internal(MESH_MSG_GROUP_SAVINGS, 0xFFFF, payload, len);
}

bool mesh_send_trust_score_update(const uint8_t *payload, uint8_t len)
{
    return mesh_send_internal(MESH_MSG_TRUST_SCORE, 0xFFFF, payload, len);
}

bool mesh_send_heartbeat(void)
{
    uint8_t dummy = 0;
    return mesh_send_internal(MESH_MSG_HEARTBEAT, 0xFFFF, &dummy, 0);
}

// -----------------------------------------------------------------------------
// Radio Receive Path
// -----------------------------------------------------------------------------

// This is called by radio_interface.c when raw bytes are received.
static void mesh_radio_rx_callback(const uint8_t *data, uint8_t len)
{
    if (len < sizeof(mesh_header_t)) {
        return; // too short to be valid
    }

    // Verify signature (this also protects against many forms of tampering).
    if (!security_verify_packet(data, len)) {
        return;
    }

    mesh_packet_t pkt;
    memcpy(&pkt.header, data, sizeof(mesh_header_t));
    pkt.payload_len = (uint8_t)(len - sizeof(mesh_header_t));

    if (pkt.payload_len > 0) {
        memcpy(pkt.payload, data + sizeof(mesh_header_t), pkt.payload_len);
    }

    mesh_handle_incoming_packet(&pkt);
}

// -----------------------------------------------------------------------------
// Core Incoming Handler
// -----------------------------------------------------------------------------

static void mesh_handle_incoming_packet(mesh_packet_t *pkt)
{
    // Drop if TTL exhausted
    if (pkt->header.ttl == 0 || pkt->header.hops >= MESH_MAX_HOPS) {
        return;
    }

    // Replay protection
    if (mesh_is_duplicate(pkt->header.msg_id)) {
        return; // we've seen this message already
    }
    mesh_record_seen(pkt->header.msg_id);

    bool is_for_me   = (pkt->header.dst == g_local_address);
    bool is_broadcast = (pkt->header.dst == 0xFFFF);

    // Deliver to upper-layer handlers if it's ours or broadcast
    if (is_for_me || is_broadcast) {
        switch (pkt->header.type) {
            case MESH_MSG_TRANSACTION:
                mesh_on_transaction_message(pkt->payload, pkt->payload_len);
                break;
            case MESH_MSG_LEDGER_SYNC:
                mesh_on_ledger_sync_message(pkt->payload, pkt->payload_len);
                break;
            case MESH_MSG_GROUP_SAVINGS:
                mesh_on_group_savings_message(pkt->payload, pkt->payload_len);
                break;
            case MESH_MSG_TRUST_SCORE:
                mesh_on_trust_score_message(pkt->payload, pkt->payload_len);
                break;
            case MESH_MSG_HEARTBEAT:
                mesh_on_heartbeat_message(pkt->payload, pkt->payload_len);
                break;
            case MESH_MSG_ERROR_REPORT:
                // For future use: send to diagnostics/logging.
                break;
            default:
                // Unknown message type; ignore or log.
                break;
        }
    }

    // Forward if still has TTL and we are not the original source.
    if (!is_for_me && pkt->header.ttl > 0) {
        mesh_forward_packet(pkt);
    }
}

// -----------------------------------------------------------------------------
// Forwarding Logic (Simple Flooding)
// -----------------------------------------------------------------------------

static void mesh_forward_packet(mesh_packet_t *pkt)
{
    // Decrement TTL and increment hops for the forwarded packet
    pkt->header.ttl--;
    pkt->header.hops++;

    // Re-serialize and re-sign.
    uint8_t buffer[MESH_MAX_PACKET_SIZE];
    uint8_t len = 0;

    memcpy(&buffer[len], &pkt->header, sizeof(mesh_header_t));
    len += sizeof(mesh_header_t);
    memcpy(&buffer[len], pkt->payload, pkt->payload_len);
    len += pkt->payload_len;

    if (!security_sign_packet(buffer, &len, MESH_MAX_PACKET_SIZE)) {
        return;
    }

    (void)radio_send_bytes(buffer, len);
}

// -----------------------------------------------------------------------------
// Replay Cache Helpers
// -----------------------------------------------------------------------------

static bool mesh_is_duplicate(mesh_msg_id_t msg_id)
{
    for (uint8_t i = 0; i < MESH_REPLAY_CACHE_SIZE; i++) {
        if (g_replay_cache[i] == msg_id) {
            return true;
        }
    }
    return false;
}

static void mesh_record_seen(mesh_msg_id_t msg_id)
{
    g_replay_cache[g_replay_cache_head] = msg_id;
    g_replay_cache_head++;
    if (g_replay_cache_head >= MESH_REPLAY_CACHE_SIZE) {
        g_replay_cache_head = 0;
    }
}

// -----------------------------------------------------------------------------
// Optional Periodic Processing Hook
// -----------------------------------------------------------------------------

// In a real firmware, this could be invoked from the main loop at regular
// intervals to emit heartbeats, adjust power settings, etc.
void mesh_periodic_tick(void)
{
    // Example: send a heartbeat periodically (placeholder)
    // In production this would be gated by timers and duty-cycle limits.
    // mesh_send_heartbeat();
}
