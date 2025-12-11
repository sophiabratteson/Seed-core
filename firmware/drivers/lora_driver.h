#ifndef LORA_DRIVER_H
#define LORA_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

void lora_init(void);
bool lora_send(const uint8_t *data, uint16_t len);
bool lora_receive(uint8_t *buffer, uint16_t *len_out);
void lora_set_frequency(uint32_t freq_hz);
void lora_set_power(uint8_t level);

#endif
