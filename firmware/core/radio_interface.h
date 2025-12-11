#ifndef RADIO_INTERFACE_H
#define RADIO_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t *data;
    uint16_t length;
    uint8_t rssi;
} radio_packet_t;

void radio_init(void);
bool radio_send(const uint8_t *data, uint16_t length);
bool radio_receive(radio_packet_t *packet);
void radio_set_frequency(uint32_t freq_hz);
void radio_set_power(uint8_t power_level);

#endif
