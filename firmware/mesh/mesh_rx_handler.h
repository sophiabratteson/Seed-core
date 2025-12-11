#ifndef MESH_RX_HANDLER_H
#define MESH_RX_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

void mesh_rx_handler_init(void);
void mesh_rx_handler_process(const uint8_t *data, uint16_t len);

#endif
