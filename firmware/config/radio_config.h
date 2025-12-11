/**
 * radio_config.h
 * ------------------------------------------------------------
 * Seed Device – Radio Configuration Header
 *
 * Defines all radio-layer constants, regional parameters,
 * default LoRa PHY configuration, airtime constraints, power
 * settings, and channel behavior for Seed's offline-first mesh.
 *
 * This file is investor-ready and engineered to look like a
 * production firmware architecture.
 *
 * ------------------------------------------------------------
 */

#ifndef RADIO_CONFIG_H
#define RADIO_CONFIG_H

/* ============================================================
 * 1. REGIONAL RADIO PARAMETERS
 * ============================================================
 * Seed devices must comply with local spectrum regulations.
 * The device chooses its region profile during provisioning.
 */

typedef enum {
    REGION_US_915,      // North America 902–928 MHz
    REGION_EU_868,      // Europe 863–870 MHz
    REGION_IN_865,      // India 865–867 MHz
    REGION_AU_915,      // Australia 915–928 MHz
    REGION_CUSTOM       // For pilots or restricted deployments
} radio_region_t;

/* ============================================================
 * 2. DEFAULT CHANNEL CONFIG FOR LORA MESH
 * ============================================================
 * Seed uses a small set of channels for:
 *  - Ledger sync packets
 *  - Transaction broadcasts
 *  - Device discovery
 *
 * These defaults can be overridden during provisioning.
 */

#define DEFAULT_TX_CHANNEL        0        // Channel index for sending
#define DEFAULT_RX_CHANNEL        0        // Channel index for receiving
#define MAX_MESH_CHANNELS         8

typedef struct {
    uint32_t frequency_hz;
    uint8_t  enabled;
} radio_channel_t;

/* ============================================================
 * 3. LORA PHY PARAMETERS (SX1276/SX1262 FAMILY)
 * ============================================================
 * Balanced for long-range, low-power, and offline-first mesh routing.
 */

#define LORA_BANDWIDTH_125KHZ     0
#define LORA_SPREADING_FACTOR     9        // SF9: long range + moderate latency
#define LORA_CODING_RATE          1        // CR 4/5
#define LORA_PREAMBLE_LENGTH      8
#define LORA_SYNC_WORD            0x12     // Private network sync word

/* ============================================================
 * 4. POWER & DUTY CYCLE BEHAVIOR
 * ============================================================
 * Actual RF output varies by regulatory region and chipset.
 */

#define TX_POWER_DBM_US           20       // Max legal for US915
#define TX_POWER_DBM_EU           14       // EU868 limit
#define TX_POWER_DBM_IN           20
#define TX_POWER_DBM_AU           20

// Duty cycle for EU868 (strictest region)
#define DUTY_CYCLE_LIMIT_PERCENT  1        // 1% transmit allowed

// Minimum time between transmissions (ms)
#define MIN_TX_INTERVAL_MS        3000

/* ============================================================
 * 5. PACKET SIZE LIMITS
 * ============================================================
 * LoRa is optimized for small packets.
 * Ledger sync sends multi-packet chunks when needed.
 */

#define MAX_PACKET_SIZE           240      // Safe for SF9, 125 kHz BW
#define MAX_FRAGMENT_COUNT        16       // Fragmented transmissions

/* ============================================================
 * 6. MESH NETWORKING FLAGS
 * ============================================================
 * Controls how devices route and forward packets.
 */

#define ENABLE_MESH_FORWARDING        1
#define MAX_HOP_COUNT                 6
#define ENABLE_NEIGHBOR_DISCOVERY     1
#define HEARTBEAT_INTERVAL_SECONDS    90

/* ============================================================
 * 7. RADIO TIMEOUTS & RETRIES
 * ============================================================
 */

#define RX_TIMEOUT_MS                 2000
#define TX_RETRY_COUNT                3
#define ACK_TIMEOUT_MS                1500
#define BACKOFF_BASE_MS               500

/* ============================================================
 * 8. STRUCT FOR FULL RADIO CONFIG
 * ============================================================
 * Used by firmware to configure hardware drivers.
 */

typedef struct {
    radio_region_t region;
    radio_channel_t channels[MAX_MESH_CHANNELS];
    uint8_t spreading_factor;
    uint8_t bandwidth;
    uint8_t coding_rate;
    uint8_t tx_power_dbm;
    uint8_t preamble_len;
    uint8_t sync_word;
    uint16_t min_tx_interval_ms;
    uint8_t enable_mesh_forwarding;
} radio_config_t;

/* ============================================================
 * 9. FUNCTION PROTOTYPES
 * ============================================================
 * Implemented in radio_interface.c
 */

radio_config_t radio_load_default_config(radio_region_t region);
void radio_apply_config(const radio_config_t *cfg);
void radio_set_channel(uint8_t channel_index);
void radio_set_power(uint8_t dbm);
void radio_set_spreading_factor(uint8_t sf);

#endif  // RADIO_CONFIG_H
