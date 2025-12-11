#ifndef LEDGER_VALIDATION_H
#define LEDGER_VALIDATION_H

#include <stdbool.h>
#include "ledger_manager.h"

bool ledger_validate_tx(const ledger_tx_t *tx);
bool ledger_check_double_spend(const ledger_tx_t *tx);

#endif
