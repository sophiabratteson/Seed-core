/*************************************************************
 * File: ledger_storage.c
 * Layer: Firmware → Ledger Engine → Storage
 * Description:
 *    Persistent storage engine for Seed’s offline-first ledger.
 *    Responsible for:
 *        - Storing, loading, and indexing ledger transactions
 *        - Flash-safe writes (append-only)
 *        - Checkpoint snapshots
 *        - CRC integrity validation
 *        - Secure erase operations
 *
 * NOTE:
 *    This file is hardware-agnostic. Hardware-specific flash I/O
 *    must be provided in storage_driver.c (HAL abstraction).
 *************************************************************/

#include "ledger_storage.h"
#include "storage_driver.h"
#include "crc16.h"
#include <string.h>

#define MAX_TX_RECORDS          2048
#define TX_RECORD_SIZE_BYTES    256       // fixed-size encoding
#define CHECKPOINT_INTERVAL     100       // snapshot every 100 writes

/**********************
 * INTERNAL STRUCTURES
 **********************/
typedef struct {
    uint8_t  data[TX_RECORD_SIZE_BYTES];
    uint16_t crc;
} tx_persist_record_t;

static uint32_t tx_count = 0;   // number of valid stored transactions

/*******************************************************
 *  INTERNAL HELPERS
 *******************************************************/

static void encode_transaction(const ledger_tx_t *tx, uint8_t *out)
{
    // Simple JSON-free binary encoding
    // Layout example:
    // [lamport(4)][amount(4)][sender(32)][receiver(32)][tx_id(36)][signature(64)][padding…]

    memset(out, 0, TX_RECORD_SIZE_BYTES);

    uint32_t offset = 0;

    memcpy(out + offset, &tx->lamport, sizeof(uint32_t));
    offset += 4;

    memcpy(out + offset, &tx->amount, sizeof(float));
    offset += 4;

    memcpy(out + offset, tx->sender, SENDER_ID_LEN);
    offset += SENDER_ID_LEN;

    memcpy(out + offset, tx->receiver, RECEIVER_ID_LEN);
    offset += RECEIVER_ID_LEN;

    memcpy(out + offset, tx->tx_id, TX_ID_LEN);
    offset += TX_ID_LEN;

    memcpy(out + offset, tx->signature, SIG_LEN);
}

static void decode_transaction(const uint8_t *in, ledger_tx_t *tx_out)
{
    uint32_t offset = 0;

    memcpy(&tx_out->lamport, in + offset, 4); offset += 4;
    memcpy(&tx_out->amount,  in + offset, 4); offset += 4;

    memcpy(tx_out->sender,   in + offset, SENDER_ID_LEN);   offset += SENDER_ID_LEN;
    memcpy(tx_out->receiver, in + offset, RECEIVER_ID_LEN); offset += RECEIVER_ID_LEN;
    memcpy(tx_out->tx_id,    in + offset, TX_ID_LEN);       offset += TX_ID_LEN;
    memcpy(tx_out->signature,in + offset, SIG_LEN);
}

static uint16_t compute_crc(const uint8_t *data)
{
    return crc16_compute(data, TX_RECORD_SIZE_BYTES);
}

/*******************************************************
 *  PUBLIC API IMPLEMENTATION
 *******************************************************/

bool ledger_storage_init(void)
{
    tx_count = storage_driver_scan_records(MAX_TX_RECORDS);
    return true;
}

bool ledger_storage_store_tx(const ledger_tx_t *tx)
{
    if (tx_count >= MAX_TX_RECORDS)
        return false;

    tx_persist_record_t record;
    encode_transaction(tx, record.data);
    record.crc = compute_crc(record.data);

    uint32_t address = tx_count * sizeof(tx_persist_record_t);

    if (!storage_driver_write(address, (uint8_t*)&record, sizeof(record)))
        return false;

    tx_count++;

    // Create periodic checkpoint
    if (tx_count % CHECKPOINT_INTERVAL == 0)
        ledger_storage_checkpoint();

    return true;
}

bool ledger_storage_load_tx(uint32_t index, ledger_tx_t *tx_out)
{
    if (index >= tx_count)
        return false;

    tx_persist_record_t record;
    uint32_t address = index * sizeof(tx_persist_record_t);

    if (!storage_driver_read(address, (uint8_t*)&record, sizeof(record)))
        return false;

    uint16_t calc_crc = compute_crc(record.data);
    if (calc_crc != record.crc)
        return false;  // corruption detected

    decode_transaction(record.data, tx_out);
    return true;
}

uint32_t ledger_storage_get_tx_count(void)
{
    return tx_count;
}

/*******************************************************
 * CHECKPOINT SYSTEM
 *******************************************************/

bool ledger_storage_checkpoint(void)
{
    ledger_checkpoint_t snapshot;

    // Build checkpoint metadata
    snapshot.tx_count  = tx_count;
    snapshot.lamport   = ledger_state_get_lamport();
    snapshot.group_bal = ledger_state_get_group_balances();

    return storage_driver_write_checkpoint((uint8_t*)&snapshot, sizeof(snapshot));
}

bool ledger_storage_restore_checkpoint(ledger_checkpoint_t *out)
{
    return storage_driver_read_checkpoint((uint8_t*)out, sizeof(*out));
}

/*******************************************************
 * SECURE ERASE CAPABILITIES
 *******************************************************/

bool ledger_storage_secure_erase(void)
{
    bool ok = storage_driver_secure_wipe_region(0, MAX_TX_RECORDS * sizeof(tx_persist_record_t));

    if (!ok) return false;

    tx_count = 0;
    return true;
}

/*******************************************************
 * DEBUG UTILITIES (OPTIONAL)
 *******************************************************/
void ledger_storage_debug_dump(void)
{
    ledger_tx_t tx;

    for (uint32_t i = 0; i < tx_count; i++) {
        if (ledger_storage_load_tx(i, &tx)) {
            printf("TX %lu | %s -> %s | %.2f | lamport=%u\n",
                (unsigned long)i,
                tx.sender,
                tx.receiver,
                tx.amount,
                tx.lamport
            );
        }
    }
}

/*************************************************************
 * END FILE: ledger_storage.c
 *************************************************************/
