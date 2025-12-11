#ifndef SECURITY_MODULE_H
#define SECURITY_MODULE_H

#include <stdint.h>
#include <stdbool.h>

void security_init(void);
bool security_generate_keypair(void);
bool security_sign(const uint8_t *msg, uint16_t len, uint8_t *sig_out);
bool security_verify(const uint8_t *msg, uint16_t len, const uint8_t *sig);
bool security_wipe_all_keys(void);

#endif
