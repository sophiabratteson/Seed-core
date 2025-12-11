#ifndef INPUT_BUTTONS_H
#define INPUT_BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BUTTON_NONE,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_SELECT,
    BUTTON_BACK
} button_event_t;

void buttons_init(void);
button_event_t buttons_read_event(void);

#endif
