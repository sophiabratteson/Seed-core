#ifndef LEDGER_STORAGE_H
#define LEDGER_STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "ledger_manager.h"

void ledger_storage_init(void);
bool ledger_storage_write(const ledger_tx_t *tx);
bool ledger_storage_load_all(void (*callback)(const ledger_tx_t *tx));

#endif
