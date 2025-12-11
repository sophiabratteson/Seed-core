#ifndef MESH_NEIGHBOR_TABLE_H
#define MESH_NEIGHBOR_TABLE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t id[8];
    uint32_t last_seen_timestamp;
    int8_t rssi;
} mesh_neighbor_t;

void neighbor_table_init(void);
void neighbor_table_update(const uint8_t *id, int8_t rssi);
uint8_t neighbor_table_count(void);

#endif
