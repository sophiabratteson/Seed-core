/**
 * ============================================================================
 *  File: battery_sensor.c
 *  Description: Battery monitoring driver for Seed device
 *  Layer: Hardware Drivers
 *
 *  Purpose:
 *    - Provide accurate battery voltage and percentage readings.
 *    - Estimate remaining runtime based on usage profile.
 *    - Detect low-battery and unsafe conditions (over-discharge, overheating).
 *    - Supply power metrics to the power manager and UX layer.
 *
 *  Notes:
 *    - This is hardware-agnostic pseudocode designed to plug into any MCU ADC.
 *    - Final implementation will map to specific ADC pins + calibration curves.
 * ============================================================================
 */

#include "battery_sensor.h"
#include "power_config.h"
#include "safe_memory.h"
#include <stdint.h>
#include <stdbool.h>

/* ----------------------------------------------
   Hardware abstraction: ADC sampling interface
   (Implemented per-MCU in: platform_adc.c)
   ---------------------------------------------- */

extern uint16_t adc_read_raw(uint8_t channel);
extern float    adc_raw_to_voltage(uint16_t raw, float divider_ratio);

/* ----------------------------------------------
   Internal State
   ---------------------------------------------- */

static float last_voltage_mv     = 0.0f;
static uint8_t last_percentage   = 100;
static bool battery_initialized  = false;

/* Seed-specific thresholds (configurable via power_config.h) */
#define SEED_BATTERY_MIN_MV          3000    // Hard cutoff voltage
#define SEED_BATTERY_MAX_MV          4200    // Fully charged
#define SEED_BATTERY_LOW_MV          3300    // UX warning threshold
#define SEED_BATTERY_CRITICAL_MV     3100    // Force shutdown threshold

/* Voltage → percentage mapping table (approx. LiFePO4 / Li-Ion hybrid model) */
typedef struct {
    uint16_t mv;
    uint8_t  percent;
} battery_curve_t;

static const battery_curve_t BATTERY_CURVE[] = {
    {4200, 100},
    {4000,  90},
    {3800,  75},
    {3600,  50},
    {3400,  25},
    {3300,  10},
    {3100,   5},
    {3000,   0}
};

#define BATTERY_CURVE_SIZE (sizeof(BATTERY_CURVE)/sizeof(battery_curve_t))

/* ----------------------------------------------------------
   Helper: Convert millivolts to a 0–100% estimate
   ---------------------------------------------------------- */
static uint8_t estimate_percentage(uint16_t mv)
{
    for (int i = 0; i < BATTERY_CURVE_SIZE; i++) {
        if (mv >= BATTERY_CURVE[i].mv) {
            return BATTERY_CURVE[i].percent;
        }
    }
    return 0;
}

/* ----------------------------------------------------------
   Initialization
   ---------------------------------------------------------- */
void battery_sensor_init(void)
{
    battery_initialized = true;
}

/* ----------------------------------------------------------
   Read battery voltage (millivolts)
   ---------------------------------------------------------- */
float battery_get_voltage(void)
{
    if (!battery_initialized) {
        battery_sensor_init();
    }

    uint16_t raw = adc_read_raw(POWER_CONFIG_BATTERY_ADC_CHANNEL);
    float voltage = adc_raw_to_voltage(raw, POWER_CONFIG_DIVIDER_RATIO);

    last_voltage_mv = voltage * 1000.0f;
    return last_voltage_mv;
}

/* ----------------------------------------------------------
   Read battery percentage
   ---------------------------------------------------------- */
uint8_t battery_get_percentage(void)
{
    /* Uses last known voltage for stability */
    if (last_voltage_mv == 0) {
        battery_get_voltage();
    }

    last_percentage = estimate_percentage((uint16_t)last_voltage_mv);
    return last_percentage;
}

/* ----------------------------------------------------------
   Check for low-battery / critical states
   ---------------------------------------------------------- */
battery_status_t battery_get_status(void)
{
    if (last_voltage_mv == 0) {
        battery_get_voltage();
    }

    if (last_voltage_mv <= SEED_BATTERY_CRITICAL_MV) {
        return BATTERY_CRITICAL;
    }
    if (last_voltage_mv <= SEED_BATTERY_LOW_MV) {
        return BATTERY_LOW;
    }
    return BATTERY_NORMAL;
}

/* ----------------------------------------------------------
   Estimated runtime (very approximate)
   Future improvement: integrate discharge profile + usage mode
   ---------------------------------------------------------- */
uint16_t battery_estimate_minutes_remaining(void)
{
    /* Super-simple heuristic: assumes linear drain for prototype */
    uint8_t pct = battery_get_percentage();
    return (uint16_t)(pct * POWER_CONFIG_MINUTES_PER_PERCENT);
}

/* ----------------------------------------------------------
   Export telemetry for power manager + UX
   ---------------------------------------------------------- */
void battery_export_metrics(battery_metrics_t *out)
{
    if (!out) return;

    out->voltage_mv          = last_voltage_mv;
    out->percentage          = last_percentage;
    out->status              = battery_get_status();
    out->minutes_remaining   = battery_estimate_minutes_remaining();
}

/* ----------------------------------------------------------
   Safety hooks for shutdown
   ---------------------------------------------------------- */
bool battery_should_shutdown_immediately(void)
{
    return last_voltage_mv <= SEED_BATTERY_CRITICAL_MV;
}
