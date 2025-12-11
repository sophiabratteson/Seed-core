// firmware/core/power_manager.c
//
// High-level power management logic for Seed device.
// - Tracks battery level and charging state
// - Chooses power state (ACTIVE / IDLE / DEEP_SLEEP / CHARGING / FAULT)
// - Coordinates with radio + display + CPU sleep
// - Designed to be called regularly from main_loop.c

#include <stdint.h>
#include <stdbool.h>

// ---- Dependencies (implemented in other modules) --------------------

// timekeeping.c
extern uint32_t tk_millis(void);              // returns ms since boot

// battery_sensor.c
extern uint16_t battery_read_mv(void);        // battery voltage in millivolts
extern bool     battery_is_charging(void);    // true if charging (e.g. solar / crank)
extern bool     battery_is_present(void);     // basic sanity check

// lora_driver.c
extern void lora_enter_sleep(void);
extern void lora_wake(void);

// e_ink_display.c
extern void e_ink_enter_sleep(void);
extern void e_ink_wake(void);

// power_config.h (configure thresholds + timing)
#define PM_BATT_GOOD_MV          3700u  // > 3.7V = good
#define PM_BATT_LOW_MV           3400u  // between 3.4V and 3.7V = caution
#define PM_BATT_CRITICAL_MV      3200u  // < 3.2V = deep sleep ASAP

#define PM_IDLE_TIMEOUT_MS       30000u // 30s of inactivity → IDLE
#define PM_DEEP_SLEEP_DELAY_MS   300000u// 5min in IDLE/LOW → DEEP_SLEEP

#define PM_RADIO_BURST_MAX_MS    5000u  // allow short radio bursts up to 5s

// --------------------------------------------------------------------

typedef enum {
    POWER_STATE_ACTIVE = 0,
    POWER_STATE_IDLE,
    POWER_STATE_DEEP_SLEEP,
    POWER_STATE_CHARGING,
    POWER_STATE_FAULT
} power_state_t;

typedef struct {
    uint16_t battery_mv;
    uint8_t  battery_pct;
    bool     charging;
    power_state_t state;
    uint32_t last_state_change_ms;
    uint32_t last_activity_ms;
    bool     radio_burst_requested;
    uint32_t radio_burst_end_ms;
} power_status_t;

static power_status_t g_power;

// ---- Internal helpers -----------------------------------------------

static uint8_t pm_estimate_pct(uint16_t mv)
{
    // Very rough linear mapping for Li-ion/LiFePO4-like behavior
    if (mv <= PM_BATT_CRITICAL_MV) return 0;
    if (mv >= PM_BATT_GOOD_MV)     return 100;

    uint16_t span_mv = PM_BATT_GOOD_MV - PM_BATT_CRITICAL_MV;
    uint16_t rel_mv  = mv - PM_BATT_CRITICAL_MV;
    return (uint8_t)((rel_mv * 100u) / span_mv);
}

static void pm_update_battery(void)
{
    g_power.battery_mv   = battery_read_mv();
    g_power.battery_pct  = pm_estimate_pct(g_power.battery_mv);
    g_power.charging     = battery_is_charging();
}

static void pm_set_state(power_state_t new_state)
{
    if (g_power.state == new_state) return;

    g_power.state = new_state;
    g_power.last_state_change_ms = tk_millis();

    switch (new_state) {
        case POWER_STATE_ACTIVE:
            lora_wake();
            e_ink_wake();
            break;
        case POWER_STATE_IDLE:
            // Radio + display can go to low power; CPU still running
            lora_enter_sleep();
            // e-ink can stay as-is; it already holds image without power
            break;
        case POWER_STATE_DEEP_SLEEP:
            // Put everything we can to sleep
            lora_enter_sleep();
            e_ink_enter_sleep();
            // CPU would enter deep sleep in main_loop.c
            break;
        case POWER_STATE_CHARGING:
            // Allow more generous activity while charging
            lora_enter_sleep(); // can be woken when needed
            break;
        case POWER_STATE_FAULT:
        default:
            // Minimal safe state
            lora_enter_sleep();
            e_ink_enter_sleep();
            break;
    }
}

static void pm_decide_state(void)
{
    uint32_t now = tk_millis();

    // Battery / hardware sanity
    if (!battery_is_present()) {
        pm_set_state(POWER_STATE_FAULT);
        return;
    }

    // Critical battery → DEEP_SLEEP no matter what
    if (g_power.battery_mv <= PM_BATT_CRITICAL_MV) {
        pm_set_state(POWER_STATE_DEEP_SLEEP);
        return;
    }

    // If charging, prefer CHARGING state
    if (g_power.charging) {
        pm_set_state(POWER_STATE_CHARGING);
        return;
    }

    // If radio burst requested, we must be ACTIVE
    if (g_power.radio_burst_requested && now < g_power.radio_burst_end_ms) {
        pm_set_state(POWER_STATE_ACTIVE);
        return;
    } else {
        g_power.radio_burst_requested = false;
    }

    // Idle / sleep logic based on activity + battery level
    uint32_t since_activity = now - g_power.last_activity_ms;

    if (since_activity < PM_IDLE_TIMEOUT_MS) {
        pm_set_state(POWER_STATE_ACTIVE);
        return;
    }

    // After idle timeout, drop to IDLE
    if (since_activity < PM_DEEP_SLEEP_DELAY_MS &&
        g_power.battery_mv > PM_BATT_LOW_MV) {
        pm_set_state(POWER_STATE_IDLE);
        return;
    }

    // If we've been idle a long time or battery is low → DEEP_SLEEP
    pm_set_state(POWER_STATE_DEEP_SLEEP);
}

// ---- Public API -----------------------------------------------------

void power_init(void)
{
    uint32_t now = tk_millis();
    g_power.battery_mv           = 0;
    g_power.battery_pct          = 0;
    g_power.charging             = false;
    g_power.state                = POWER_STATE_ACTIVE;
    g_power.last_state_change_ms = now;
    g_power.last_activity_ms     = now;
    g_power.radio_burst_requested= false;
    g_power.radio_burst_end_ms   = now;

    pm_update_battery();
    pm_decide_state();
}

// Call this regularly from the main loop (e.g. every 500–1000 ms)
void power_update(void)
{
    pm_update_battery();
    pm_decide_state();
}

// Mark that some user / system activity happened (button press, transaction, etc.)
void power_mark_activity(void)
{
    g_power.last_activity_ms = tk_millis();

    // Being active cancels any "deep sleep soon" plan
    if (g_power.state == POWER_STATE_IDLE ||
        g_power.state == POWER_STATE_DEEP_SLEEP) {
        pm_set_state(POWER_STATE_ACTIVE);
    }
}

// Request a short radio "on" window for sending/receiving
bool power_request_radio_burst(uint32_t duration_ms)
{
    if (duration_ms > PM_RADIO_BURST_MAX_MS) {
        duration_ms = PM_RADIO_BURST_MAX_MS;
    }

    // If battery is critically low, deny
    if (g_power.battery_mv <= PM_BATT_CRITICAL_MV) {
        return false;
    }

    uint32_t now = tk_millis();
    g_power.radio_burst_requested = true;
    g_power.radio_burst_end_ms    = now + duration_ms;
    pm_set_state(POWER_STATE_ACTIVE);
    return true;
}

// Simple query helpers

power_state_t power_get_state(void)
{
    return g_power.state;
}

uint16_t power_get_battery_mv(void)
{
    return g_power.battery_mv;
}

uint8_t power_get_battery_pct(void)
{
    return g_power.battery_pct;
}

bool power_is_charging(void)
{
    return g_power.charging;
}
