#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

// ================================================================
//  Seed Device Firmware - Global Configuration Header
//  This file defines all compile-time configuration parameters
//  for a Seed hardware device.
//
//  Every module in firmware/core, firmware/mesh, firmware/ledger,
//  firmware/drivers, and firmware/security depends on this file.
//
//  INVESTOR-READY VERSION (Hardware-agnostic, Production-style)
// ================================================================


// ---------------------------------------------------------------
// DEVICE IDENTITY
// ---------------------------------------------------------------
#define DEVICE_ID_MAX_LEN        16
#define DEVICE_SERIAL_NUMBER     "SEED-PROTOTYPE-01"

// Device type: DEV, FIELD_TEST, PRODUCTION
#define DEVICE_MODE              0   // 0 = Dev, 1 = Field-Test, 2 = Production


// ---------------------------------------------------------------
// RADIO CONFIGURATION (LoRa SX1276/SX1262 family)
// ---------------------------------------------------------------

// Choose based on region radio compliance
// 0 = US915, 1 = EU868, 2 = AS923, 3 = IN865
#define REGION_CODE              0

#if REGION_CODE == 0
    #define LORA_FREQUENCY_HZ    915000000UL
#elif REGION_CODE == 1
    #define LORA_FREQUENCY_HZ    868000000UL
#elif REGION_CODE == 2
    #define LORA_FREQUENCY_HZ    923000000UL
#elif REGION_CODE == 3
    #define LORA_FREQUENCY_HZ    865000000UL
#endif

// Radio spreading factor (defines range vs speed)
#define LORA_SPREADING_FACTOR    7
#define LORA_BANDWIDTH_HZ        125000
#define LORA_CODING_RATE         5

// TX Power (adjust based on battery + heat + local RF laws)
#define LORA_TX_POWER_DBM        17

// Mesh network parameters
#define MESH_HEARTBEAT_INTERVAL_MS   15000
#define MESH_MAX_NEIGHBORS           32
#define MESH_MAX_TTL                 5


// ---------------------------------------------------------------
// POWER SYSTEM SETTINGS
// ---------------------------------------------------------------
#define BATTERY_CAPACITY_MAH         1500
#define POWER_SAVE_MODE_ENABLED      1     // 1 = enable deep sleep
#define IDLE_SLEEP_TIMEOUT_MS        30000
#define MIN_BATTERY_BEFORE_TX_MV     3300

// For hand-crank + solar input (prototype mode)
#define ALLOW_LOW_VOLTAGE_BOOT       1


// ---------------------------------------------------------------
// STORAGE CONFIGURATION
// ---------------------------------------------------------------

// Size of ledger storage in flash/EEPROM
#define MAX_TRANSACTIONS_STORED      4096
#define MAX_TX_SIZE_BYTES            256

// File naming convention for block storage
#define LEDGER_FILE_NAME             "ledger.dat"
#define CHECKPOINT_FILE_NAME         "checkpoint.dat"

#define SECURE_STORAGE_ENABLED       1


// ---------------------------------------------------------------
// SECURITY & CRYPTOGRAPHY
// ---------------------------------------------------------------

// Placeholder for secure element (real keys live in hardware)
#define DEVICE_PUBLIC_KEY_PLACEHOLDER    "PUBKEY_PLACEHOLDER"
#define DEVICE_PRIVATE_KEY_PLACEHOLDER   "PRIVKEY_PLACEHOLDER"

// Enable signature checks
#define ENABLE_MESSAGE_SIGNING       1
#define ENABLE_LEDGER_HASHING        1

// Hash algorithm (0=SHA256, 1=BLAKE2s)
#define HASH_ALGO                    0


// ---------------------------------------------------------------
// FEATURE FLAGS
// Toggle major Seed features for firmware footprint + testing
// ---------------------------------------------------------------

// Ledger engine
#define FEATURE_LEDGER_VALIDATION        1
#define FEATURE_CONFLICT_RESOLUTION      1

// Trust score updates
#define FEATURE_TRUST_SCORE              1

// Group savings (rotational lending)
#define FEATURE_GROUP_SAVINGS            1

// Local AI assistant (prototype stub)
#define FEATURE_LOCAL_AI                 0

// Emergency wipe mode
#define FEATURE_EMERGENCY_WIPE           1


// ---------------------------------------------------------------
// UI / PERIPHERAL SETTINGS
// ---------------------------------------------------------------
#define EINK_REFRESH_MS                  1200
#define FINGERPRINT_SENSOR_ENABLED       1
#define LED_STATUS_INDICATOR_ENABLED     1
#define BUTTON_DEBOUNCE_MS               50


// ---------------------------------------------------------------
// BUILD VALIDATION (compile-time checks)
// ---------------------------------------------------------------
#if MAX_TRANSACTIONS_STORED < 100
#error "MAX_TRANSACTIONS_STORED is too small for ledger stability."
#endif

#if LORA_TX_POWER_DBM > 20
#error "TX power exceeds safe or legal limits."
#endif


#endif // DEVICE_CONFIG_H
