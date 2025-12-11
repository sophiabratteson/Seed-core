#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

void power_init(void);
void power_enter_low_power_mode(void);
void power_exit_low_power_mode(void);
uint16_t power_get_battery_level(void);
bool power_is_charging(void);

#endif
