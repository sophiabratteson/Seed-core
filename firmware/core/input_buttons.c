#ifndef INPUT_BUTTONS_H
#define INPUT_BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_SELECT,
    BUTTON_BACK
} button_id_t;

typedef enum {
    BUTTON_SHORT_PRESS,
    BUTTON_LONG_PRESS
} button_event_type_t;

typedef void (*button_event_callback_t)(button_id_t id, button_event_type_t type);

void buttons_init(button_event_callback_t cb);
void buttons_update(void);
bool buttons_check_wake_event(void);

#endif
/**
 * input_buttons.c
 *
 * Seed Device Firmware
 * ----------------------------------------
 * Handles all physical button input:
 *  - debouncing
 *  - event classification (short press, long press, hold)
 *  - forwarding input events to the UI/application layer
 *  - optional wake-from-sleep triggers
 *
 * This module is intentionally hardware-abstracted so it can run on
 * different Seed prototypes (breadboard → PCB).
 */

#include "input_buttons.h"
#include "timekeeping.h"
#include "safe_memory.h"
#include "power_manager.h"
#include <stdint.h>
#include <stdbool.h>

/* -----------------------------
   CONFIGURATION CONSTANTS
------------------------------*/

// GPIO pin assignments (placeholder — update per PCB)
#define BTN_UP_PIN        2
#define BTN_DOWN_PIN      3
#define BTN_SELECT_PIN    4
#define BTN_BACK_PIN      5

// debounce window (ms)
#define DEBOUNCE_MS       40

// long-press recognition threshold (ms)
#define LONG_PRESS_MS     600

/* -----------------------------
   INTERNAL STATE STRUCTURE
------------------------------*/

typedef struct {
    bool     stable_state;      // last stable reading (true = pressed)
    bool     raw_state;         // most recent read from GPIO
    uint32_t last_change_ms;    // time of last transition
    uint32_t press_start_ms;    // time when button was pressed
} button_state_t;

// state for each button
static button_state_t btn_up;
static button_state_t btn_down;
static button_state_t btn_select;
static button_state_t btn_back;

// callback pointer
static button_event_callback_t registered_callback = NULL;

/* -----------------------------
   HARDWARE ABSTRACTION LAYER
   (to be implemented per board)
------------------------------*/

static bool read_gpio(uint8_t pin)
{
    /**
     * TODO: Replace with actual hardware read.
     * Return true if button is currently pressed.
     */
    return false;
}

/* -----------------------------
   INITIALIZATION
------------------------------*/

void buttons_init(button_event_callback_t cb)
{
    registered_callback = cb;

    // Initialize all button states
    button_state_t initial = {0};
    btn_up = initial;
    btn_down = initial;
    btn_select = initial;
    btn_back = initial;
}

/* -----------------------------
   HELPER: PROCESS A SINGLE BUTTON
------------------------------*/

static void process_button(button_state_t *btn,
                           uint8_t pin,
                           button_id_t id,
                           uint32_t now)
{
    bool reading = read_gpio(pin);

    // Detect raw change
    if (reading != btn->raw_state) {
        btn->raw_state = reading;
        btn->last_change_ms = now;
    }

    // Debounce: only accept state change if stable for DEBOUNCE_MS
    if ((now - btn->last_change_ms) < DEBOUNCE_MS) return;

    // If stable and changed → process
    if (reading != btn->stable_state) {
        btn->stable_state = reading;

        if (reading) {
            // button pressed
            btn->press_start_ms = now;
        } else {
            // button released → classify event
            uint32_t duration = now - btn->press_start_ms;
            button_event_type_t type =
                (duration >= LONG_PRESS_MS) ? BUTTON_LONG_PRESS : BUTTON_SHORT_PRESS;

            if (registered_callback) {
                registered_callback(id, type);
            }
        }
    }
}

/* -----------------------------
   MAIN UPDATE LOOP
   (called from main_loop tick)
------------------------------*/

void buttons_update(void)
{
    uint32_t now = timekeeping_ms();

    process_button(&btn_up,     BTN_UP_PIN,     BUTTON_UP,     now);
    process_button(&btn_down,   BTN_DOWN_PIN,   BUTTON_DOWN,   now);
    process_button(&btn_select, BTN_SELECT_PIN, BUTTON_SELECT, now);
    process_button(&btn_back,   BTN_BACK_PIN,   BUTTON_BACK,   now);
}

/* -----------------------------
   OPTIONAL: WAKE HANDLERS
------------------------------*/

bool buttons_check_wake_event(void)
{
    /**
     * If any button is pressed while device is sleeping,
     * this function returns true so power manager can wake up.
     */
    if (read_gpio(BTN_UP_PIN))     return true;
    if (read_gpio(BTN_DOWN_PIN))   return true;
    if (read_gpio(BTN_SELECT_PIN)) return true;
    if (read_gpio(BTN_BACK_PIN))   return true;

    return false;
}
