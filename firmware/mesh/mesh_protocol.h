#ifndef MESH_PROTOCOL_H
#define MESH_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_MESH_PACKET_SIZE 256

void mesh_protocol_init(void);
bool mesh_protocol_encode(uint8_t type, const uint8_t *payload, uint16_t payload_len, uint8_t *out_buf, uint16_t *out_len);
bool mesh_protocol_decode(const uint8_t *data, uint16_t len, uint8_t *type_out, uint8_t *payload_out, uint16_t *payload_len_out);

#endif
