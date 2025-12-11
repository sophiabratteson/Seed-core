#ifndef MESH_TX_QUEUE_H
#define MESH_TX_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

void mesh_tx_queue_init(void);
bool mesh_tx_queue_enqueue(const uint8_t *data, uint16_t len);
bool mesh_tx_queue_dequeue(uint8_t *buffer, uint16_t *len_out);

#endif
