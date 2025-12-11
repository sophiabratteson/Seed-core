#ifndef CONFLICT_RESOLUTION_H
#define CONFLICT_RESOLUTION_H

#include <stdbool.h>
#include "ledger_manager.h"

bool conflict_resolve(const ledger_tx_t *a, const ledger_tx_t *b);
uint32_t conflict_compare(const ledger_tx_t *a, const ledger_tx_t *b);

#endif
