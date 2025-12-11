#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <stdint.h>

uint16_t battery_get_mv(void);
uint8_t battery_get_percentage(void);

#endif
