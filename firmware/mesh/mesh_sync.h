#ifndef MESH_SYNC_H
#define MESH_SYNC_H

#include <stdint.h>
#include <stdbool.h>

void mesh_sync_init(void);
void mesh_sync_push_ledger_delta(void);
void mesh_sync_receive_packet(const uint8_t *data, uint16_t len);
void mesh_sync_tick(void);

#endif
