/**
 * ------------------------------------------------------------
 *  Seed Device Firmware
 *  File: power_config.h
 * ------------------------------------------------------------
 *
 *  Purpose:
 *      Centralized configuration file defining all power system
 *      parameters for the Seed offline-first financial device.
 *
 *  Audience:
 *      • Firmware engineers implementing power logic
 *      • Hardware engineers tuning battery + solar performance
 *      • Investors reviewing system-level energy design
 *
 *  Summary:
 *      This file establishes the tunable constants used by the
 *      power manager, including battery thresholds, charging
 *      profiles, power modes, brownout protection, and energy
 *      budgets for radio, display, and compute operations.
 *
 *  Design Principles:
 *      • Extremely low power consumption
 *      • Safe operation in high-temperature and low-resource environments
 *      • Predictable behavior during intermittent charging
 *      • Max uptime using solar + hand-crank inputs
 *
 * ------------------------------------------------------------
 */

#ifndef POWER_CONFIG_H
#define POWER_CONFIG_H

/*--------------------------------------------------------------
 * BATTERY PARAMETERS
 *------------------------------------------------------------*/

/**
 * Nominal voltage for LiFePO4 batteries (chosen for Seed due to
 * >2000 cycle life, thermal safety, and no risk of thermal runaway).
 */
#define BATTERY_NOMINAL_VOLTAGE       3.2f       // volts

/**
 * Safe voltage thresholds.
 * The device must NEVER operate below the cutoff threshold to
 * prevent deep discharge which permanently damages LiFePO4 cells.
 */
#define BATTERY_SHUTDOWN_THRESHOLD    2.8f       // volts
#define BATTERY_LOW_WARNING_LEVEL     3.0f       // volts
#define BATTERY_FULL_CHARGE_LEVEL     3.6f       // volts

/**
 * Battery capacity options (mAh).
 * Actual value chosen depends on manufacturing BOM.
 */
#define BATTERY_CAPACITY_MAH          1500       // typical prototype value

/*--------------------------------------------------------------
 * SOLAR + HAND-CRANK INPUT PARAMETERS
 *------------------------------------------------------------*/

/**
 * Expected input voltage range from small monocrystalline solar panels.
 */
#define SOLAR_INPUT_MIN_VOLTAGE       4.5f
#define SOLAR_INPUT_MAX_VOLTAGE       6.2f

/**
 * Hand-crank generator profile.
 * Produces variable output—firmware smooths via capacitor buffer +
 * buck converter.
 */
#define HANDCRANK_MIN_VOLTAGE         3.5f
#define HANDCRANK_MAX_VOLTAGE         12.0f
#define HANDCRANK_MAX_CURRENT_MA      500

/**
 * Charge controller behavior.
 * Seed uses a constant-current, constant-voltage (CC/CV) charging curve.
 */
#define CHARGE_CURRENT_LIMIT_MA       300
#define CHARGE_TERMINATION_CURRENT_MA 35

/*--------------------------------------------------------------
 * POWER MODES (ULTRA-LOW ENERGY DESIGN)
 *------------------------------------------------------------*/

/**
 * The device supports three power states:
 *
 * ACTIVE_MODE:
 *      – CPU awake
 *      – Radio allowed to transmit
 *      – E-ink refresh allowed
 *
 * IDLE_MODE:
 *      – CPU at low frequency
 *      – Radio disabled except for timed wake
 *
 * SLEEP_MODE:
 *      – CPU off except RTC
 *      – Radio off
 *      – E-ink display holds content with zero power
 */
#define POWER_MODE_ACTIVE             0
#define POWER_MODE_IDLE               1
#define POWER_MODE_SLEEP              2

/*--------------------------------------------------------------
 * LOAD PROFILES (ENERGY COST PER OPERATION)
 *------------------------------------------------------------*/

/** Radio transmit/receive cost model (LoRa SX1276/SX1262 typical values). */
#define RADIO_TX_CURRENT_MA           120   // at 20 dBm
#define RADIO_RX_CURRENT_MA           12
#define RADIO_WAKE_TIME_MS            6

/** E-ink refresh cost model. */
#define EINK_REFRESH_CURRENT_MA       26
#define EINK_REFRESH_TIME_MS          400

/** Microcontroller baseline current (depends on actual chipset). */
#define MCU_ACTIVE_CURRENT_MA         8
#define MCU_IDLE_CURRENT_MA           0.9
#define MCU_SLEEP_CURRENT_MA          0.05

/*--------------------------------------------------------------
 * POWER BUDGET TARGETS (PER DAY)
 *------------------------------------------------------------*/

/**
 * These values allow Seed to function with unreliable solar access.
 * Goals based on field research for energy-scarce regions.
 */
#define DAILY_POWER_BUDGET_MAH        35    // target consumption per day
#define DAILY_SOLAR_RECHARGE_TARGET   50    // expected solar input on cloudy days
#define HANDCRANK_RECHARGE_PER_MIN    12    // mAh per minute of cranking

/*--------------------------------------------------------------
 * TEMPERATURE SAFETY LIMITS
 *------------------------------------------------------------*/

#define TEMP_CHARGE_MIN_C             0
#define TEMP_CHARGE_MAX_C             45
#define TEMP_OPERATING_MIN_C         -20
#define TEMP_OPERATING_MAX_C          60

/*--------------------------------------------------------------
 * BROWNOUT + SAFETY LOGIC
 *------------------------------------------------------------*/

/**
 * Firmware should enter SAFE_MODE when voltage drops below this.
 * SAFE_MODE disables:
 *      – LoRa radio transmissions
 *      – E-ink refresh
 *      – Ledger writes
 * Only essential survival functions remain active.
 */
#define SAFE_MODE_THRESHOLD_VOLTAGE   2.95f

/**
 * Device automatically wakes only when:
 *      – Voltage recovers above SAFE_MODE_EXIT_VOLTAGE
 */
#define SAFE_MODE_EXIT_VOLTAGE        3.15f

/*--------------------------------------------------------------
 * CHECKPOINT + SYNC POWER GUARDS
 *------------------------------------------------------------*/

/**
 * Ledger sync is NOT permitted unless voltage >= SYNC_MIN_VOLTAGE.
 */
#define SYNC_MIN_VOLTAGE              3.25f

/**
 * Secure flash writes (ledger checkpointing) require good power headroom.
 */
#define CHECKPOINT_MIN_VOLTAGE        3.30f

/*--------------------------------------------------------------
 * FUTURE EXPANSION FLAGS
 *------------------------------------------------------------*/

#define ENABLE_SMART_POWER_SCALING    1   // adaptive duty cycling
#define ENABLE_SOLAR_PREDICTION       0   // ML-based forecast (future)
#define ENABLE_MISSION_MODE           1   // extends runtime by restricting UI

#endif // POWER_CONFIG_H
