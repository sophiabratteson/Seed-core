#ifndef LEDGER_MANAGER_H
#define LEDGER_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char tx_id[40];
    char sender[32];
    char receiver[32];
    float amount;
    uint32_t lamport;
    char device_id[16];
} ledger_tx_t;

void ledger_init(void);
bool ledger_apply_tx(const ledger_tx_t *tx);
void ledger_export(uint8_t *buffer, uint16_t *length_out);
bool ledger_import(const uint8_t *buffer, uint16_t length);
uint32_t ledger_get_balance(const char *user);

#endif
