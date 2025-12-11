/**
 * mesh_neighbor_table.c
 *
 * Seed Device Firmware — Mesh Networking Layer
 *
 * Purpose:
 *   Maintain a lightweight, power-efficient table of nearby Seed devices.
 *   Each neighbor entry stores last-heard time, signal quality, and
 *   routing-relevant metadata. This enables:
 *      - Multi-hop mesh routing
 *      - Gossip-based ledger sync
 *      - Energy-aware transmission scheduling
 *      - Trust-score-weighted propagation (future enhancement)
 *
 * Notes for Investors:
 *   - This module enables Seed devices to form a self-healing network
 *     without internet, cell towers, or infrastructure.
 *   - The design is optimized for low power, small memory usage, and
 *     intermittent connectivity.
 */

#include "mesh_neighbor_table.h"
#include "timekeeping.h"
#include "radio_interface.h"
#include <string.h>

#define MAX_NEIGHBORS       32
#define NEIGHBOR_TIMEOUT_MS 300000   // 5 minutes
#define RSSI_SMOOTH_FACTOR  0.2f     // exponential smoothing

// -------------------------------------------------------------
// Data Structure
// -------------------------------------------------------------

static neighbor_entry_t neighbor_table[MAX_NEIGHBORS];

// -------------------------------------------------------------
// Internal Helpers
// -------------------------------------------------------------

static int find_free_slot() {
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (!neighbor_table[i].active) {
            return i;
        }
    }
    return -1;
}

static int find_neighbor(const char *id) {
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (neighbor_table[i].active &&
            strcmp(neighbor_table[i].device_id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// -------------------------------------------------------------
// Initialization
// -------------------------------------------------------------

void neighbor_table_init() {
    memset(neighbor_table, 0, sizeof(neighbor_table));
}

// -------------------------------------------------------------
// Add or Update Neighbor Entry
// -------------------------------------------------------------

void neighbor_table_heard_from(const char *device_id, int rssi) {
    int idx = find_neighbor(device_id);

    // Case 1: Existing neighbor → update RSSI and timestamp
    if (idx >= 0) {
        neighbor_entry_t *n = &neighbor_table[idx];
        n->last_heard_ms = timekeeping_millis();

        // Smooth RSSI changes to avoid jitter in noisy radio environments
        n->rssi = (int)(n->rssi * (1.0f - RSSI_SMOOTH_FACTOR)
                        + rssi * RSSI_SMOOTH_FACTOR);

        n->link_quality = radio_compute_link_quality(n->rssi);  
        return;
    }

    // Case 2: New neighbor → add if space available
    int free_slot = find_free_slot();
    if (free_slot >= 0) {
        neighbor_entry_t *n = &neighbor_table[free_slot];

        strncpy(n->device_id, device_id, DEVICE_ID_MAX);
        n->last_heard_ms = timekeeping_millis();
        n->rssi = rssi;
        n->link_quality = radio_compute_link_quality(rssi);
        n->active = 1;
    }
    // Else: Table full — future improvement: evict weakest entry
}

// -------------------------------------------------------------
// Cleanup Stale Neighbors
// -------------------------------------------------------------

void neighbor_table_prune() {
    uint32_t now = timekeeping_millis();

    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (neighbor_table[i].active &&
            (now - neighbor_table[i].last_heard_ms > NEIGHBOR_TIMEOUT_MS)) {

            neighbor_table[i].active = 0;
        }
    }
}

// -------------------------------------------------------------
// Query Functions
// -------------------------------------------------------------

int neighbor_table_count() {
    int count = 0;
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (neighbor_table[i].active) count++;
    }
    return count;
}

neighbor_entry_t *neighbor_table_get(int index) {
    if (index < 0 || index >= MAX_NEIGHBORS) return NULL;
    if (!neighbor_table[index].active) return NULL;
    return &neighbor_table[index];
}

neighbor_entry_t *neighbor_table_best_link() {
    neighbor_entry_t *best = NULL;
    int best_lq = -1;

    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (neighbor_table[i].active &&
            neighbor_table[i].link_quality > best_lq) {

            best = &neighbor_table[i];
            best_lq = neighbor_table[i].link_quality;
        }
    }

    return best;
}

// -------------------------------------------------------------
// Debug Print (Optional)
// -------------------------------------------------------------

#ifdef ENABLE_DEBUG
#include <stdio.h>

void neighbor_table_debug_print() {
    printf("---- Neighbor Table ----\n");
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        if (neighbor_table[i].active) {
            printf("ID: %s | RSSI: %d | LQ: %d | Last seen: %lu ms\n",
                   neighbor_table[i].device_id,
                   neighbor_table[i].rssi,
                   neighbor_table[i].link_quality,
                   neighbor_table[i].last_heard_ms);
        }
    }
    printf("-------------------------\n");
}
#endif
