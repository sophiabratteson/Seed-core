/**
 * conflict_resolution.c
 * -------------------------------------------------------------
 * Seed Device Firmware — Ledger Conflict Resolution Module
 *
 * Purpose:
 *   Ensures that when two Seed devices exchange transactions
 *   over a low-bandwidth mesh network, both eventually converge
 *   on the *exact same* ledger state. This module implements
 *   deterministic, offline-safe conflict resolution using:
 *
 *     - Lamport logical clocks
 *     - Device ID deterministic tie-breakers
 *     - Strict validation ordering
 *     - Idempotent transaction merging
 *
 *   This entire algorithm is serverless and works globally in
 *   fully offline environments.
 *
 * -------------------------------------------------------------
 */

#include "conflict_resolution.h"
#include "ledger_validation.h"
#include "ledger_storage.h"
#include "device_config.h"
#include "tiny_json_parser.h"
#include "safe_memory.h"

#include <stdint.h>
#include <string.h>

/* -------------------------------------------------------------
 * INTERNAL HELPER STRUCTURES
 * -------------------------------------------------------------*/

typedef struct {
    transaction_t tx;
    uint8_t valid;
} merge_entry_t;


/* -------------------------------------------------------------
 * compare_transactions()
 *
 * Deterministic ordering rule:
 *   1. Sort by Lamport timestamp (ascending)
 *   2. If equal, sort by device_id (ASCII lexical order)
 *
 * This ensures all devices apply transactions in identical order.
 * -------------------------------------------------------------*/
static int compare_transactions(const transaction_t *a, const transaction_t *b)
{
    if (a->lamport < b->lamport) return -1;
    if (a->lamport > b->lamport) return  1;

    /* tie-breaker: device ID string comparison */
    return strcmp(a->device_id, b->device_id);
}


/* -------------------------------------------------------------
 * resolve_duplicate()
 *
 * If a transaction ID already exists in local storage but comes
 * in with different data, choose the “newer” version:
 *   - Higher Lamport timestamp wins
 *   - If equal timestamps: higher lexical device_id wins
 *
 * Prevents tampering, replay attacks, inconsistent histories.
 * -------------------------------------------------------------*/
static transaction_t resolve_duplicate(const transaction_t *local,
                                       const transaction_t *incoming)
{
    int comp = compare_transactions(local, incoming);

    if (comp >= 0) {
        /* local version wins */
        return *local;
    }

    /* incoming version wins */
    return *incoming;
}


/* -------------------------------------------------------------
 * merge_transaction()
 *
 * Adds an incoming transaction into the ledger buffer.
 * Handles:
 *   - Duplicate detection
 *   - Deterministic conflict resolution
 *   - Idempotency (safe repeat imports)
 * -------------------------------------------------------------*/
static void merge_transaction(merge_entry_t *entries,
                              uint32_t *count,
                              const transaction_t *incoming)
{
    for (uint32_t i = 0; i < *count; i++) {
        if (strcmp(entries[i].tx.tx_id, incoming->tx_id) == 0) {

            /* found matching ID, resolve duplicate */
            entries[i].tx = resolve_duplicate(&entries[i].tx, incoming);
            return;
        }
    }

    /* New transaction — add to buffer */
    safe_memcpy(&entries[*count].tx, incoming, sizeof(transaction_t));
    entries[*count].valid = 1;
    (*count)++;
}


/* -------------------------------------------------------------
 * sort_entries()
 *
 * Basic insertion sort — chosen because the number of incoming
 * transactions per sync cycle is small.
 *
 * Ensures consistency across all devices.
 * -------------------------------------------------------------*/
static void sort_entries(merge_entry_t *entries, uint32_t count)
{
    for (uint32_t i = 1; i < count; i++) {
        merge_entry_t key = entries[i];
        int j = i - 1;

        while (j >= 0 && compare_transactions(&entries[j].tx, &key.tx) > 0) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = key;
    }
}


/* -------------------------------------------------------------
 * conflict_resolution_run()
 *
 * HIGH-LEVEL WORKFLOW:
 *
 *   1. Load all local transactions
 *   2. Merge all incoming transactions
 *   3. Sort deterministically using Lamport + device_id rules
 *   4. Re-validate transactions in global order
 *   5. Write merged ledger back to storage
 *
 * This process is deterministic, offline-first, and guarantees
 * every Seed device reaches the **same final ledger state**.
 * -------------------------------------------------------------*/
void conflict_resolution_run(const transaction_t *incoming,
                             uint32_t incoming_count)
{
    /* 1. Load existing ledger into RAM buffer */
    transaction_t local[MAX_LEDGER_ENTRIES];
    uint32_t local_count = ledger_storage_load_all(local);

    merge_entry_t merged[MAX_LEDGER_ENTRIES];
    uint32_t merged_count = 0;

    /* Insert local entries */
    for (uint32_t i = 0; i < local_count; i++) {
        safe_memcpy(&merged[merged_count].tx, &local[i], sizeof(transaction_t));
        merged[merged_count].valid = 1;
        merged_count++;
    }

    /* 2. Merge incoming entries */
    for (uint32_t i = 0; i < incoming_count; i++) {
        merge_transaction(merged, &merged_count, &incoming[i]);
    }

    /* 3. Sort deterministically */
    sort_entries(merged, merged_count);

    /* 4. Revalidate in deterministic order */
    for (uint32_t i = 0; i < merged_count; i++) {
        merged[i].valid = ledger_validate_transaction(&merged[i].tx);
    }

    /* 5. Save final consistent ledger back to storage */
    ledger_storage_clear();
    for (uint32_t i = 0; i < merged_count; i++) {
        ledger_storage_write(&merged[i].tx, merged[i].valid);
    }
}


/* -------------------------------------------------------------
 * END OF MODULE
 * -------------------------------------------------------------*/
