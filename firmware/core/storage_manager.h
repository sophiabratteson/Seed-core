#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

bool storage_init(void);
bool storage_write(const char *key, const uint8_t *data, uint16_t length);
bool storage_read(const char *key, uint8_t *buffer, uint16_t buffer_len);
bool storage_delete(const char *key);

#endif
