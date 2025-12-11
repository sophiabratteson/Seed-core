#ifndef CAPACITIVE_FINGERPRINT_H
#define CAPACITIVE_FINGERPRINT_H

#include <stdint.h>
#include <stdbool.h>

void fingerprint_init(void);
bool fingerprint_authenticate(uint8_t *user_id_out);
bool fingerprint_enroll(uint8_t user_id);

#endif
