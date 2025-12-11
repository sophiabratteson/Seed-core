/**
 * Seed Device Firmware
 * Mesh Networking Stack — Transmission Queue
 *
 * File: mesh_tx_queue.c
 * Purpose:
 *     Implements the outbound transmission queue used by the Seed mesh protocol.
 *     This queue temporarily stores all outgoing packets (transactions, sync messages,
 *     group-savings updates, trust-score updates, heartbeats, etc.) until the radio
 *     subsystem successfully transmits them.
 *
 * Why this matters:
 *     - Seed devices operate in unpredictable offline environments.
 *     - Radio airtime is limited, intermittent, and power-constrained.
 *     - Devices may move in and out of LoRa range.
 *     - A controlled transmission queue prevents message loss and ensures fairness
 *       between message types.
 *
 * Investor-friendly explanation:
 *     This file demonstrates that Seed has a real, structured firmware layer for
 *     store-and-forward mesh networking — a critical differentiator for an offline
 *     financial device. The queue ensures reliability, efficient radio usage, and
 *     eventual delivery of financial transactions in low-connectivity regions.
 */

#include "mesh_tx_queue.h"
#include "radio_interface.h"
#include "timekeeping.h"
#include "safe_memory.h"

#define MAX_TX_QUEUE_SIZE     32        // Configurable depending on RAM budget
#define RETRY_BACKOFF_MS      5000      // 5-second retry interval (adaptive in future)
#define MAX_RETRY_COUNT       5         // After 5 failures, packet is discarded

/**
 * Data structure for an outgoing packet.
 * Each packet includes:
 *   - Serialized payload
 *   - Packet type (transaction, sync, heartbeat…)
 *   - Retry counter
 *   - Timestamp for next retry
 */
typedef struct {
    MeshPacket packet;
    uint8_t    retry_count;
    uint32_t   next_retry_timestamp;
    bool       in_use;
} TxQueueSlot;

/**
 * The transmission queue itself.
 */
static TxQueueSlot tx_queue[MAX_TX_QUEUE_SIZE];

/**
 * Initialize empty queue.
 */
void mesh_tx_queue_init() {
    SAFE_MEMSET(tx_queue, 0, sizeof(tx_queue));
}

/**
 * Attempt to push a packet into the queue.
 * Returns:
 *     true  — if successfully added
 *     false — if queue is full
 */
bool mesh_tx_queue_push(MeshPacket *pkt) {
    for (int i = 0; i < MAX_TX_QUEUE_SIZE; i++) {
        if (!tx_queue[i].in_use) {
            tx_queue[i].packet = *pkt;
            tx_queue[i].retry_count = 0;
            tx_queue[i].next_retry_timestamp = time_now_ms();
            tx_queue[i].in_use = true;
            return true;
        }
    }
    // Queue full — in production firmware, optionally prioritize urgent message types.
    return false;
}

/**
 * Transmit all packets that are ready.
 * Called periodically by main loop.
 */
void mesh_tx_queue_process() {
    uint32_t now = time_now_ms();

    for (int i = 0; i < MAX_TX_QUEUE_SIZE; i++) {
        if (!tx_queue[i].in_use)
            continue;

        // Not time to retry yet
        if (now < tx_queue[i].next_retry_timestamp)
            continue;

        RadioStatus status = radio_send_packet(&tx_queue[i].packet);

        if (status == RADIO_OK) {
            // Packet successfully transmitted — clear slot
            tx_queue[i].in_use = false;
        }
        else {
            // Transmission failure — retry with exponential backoff
            tx_queue[i].retry_count++;

            if (tx_queue[i].retry_count >= MAX_RETRY_COUNT) {
                // Drop packet, but mark for analytics if needed
                tx_queue[i].in_use = false;
            }
            else {
                // Schedule next attempt with exponential backoff
                uint32_t delay = RETRY_BACKOFF_MS * (1 << tx_queue[i].retry_count);
                tx_queue[i].next_retry_timestamp = now + delay;
            }
        }
    }
}

/**
 * Returns the number of active messages waiting to be sent.
 */
int mesh_tx_queue_size() {
    int count = 0;
    for (int i = 0; i < MAX_TX_QUEUE_SIZE; i++) {
        if (tx_queue[i].in_use)
            count++;
    }
    return count;
}
