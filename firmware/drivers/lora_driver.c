/*
 * lora_driver.c
 * -----------------------------------------
 * Seed Device Firmware — LoRa Radio Driver
 *
 * Purpose:
 *   This module abstracts the LoRa radio hardware (SX1262/SX1276 class)
 *   so higher-level mesh components can send and receive packets
 *   without touching hardware registers directly.
 *
 * Design Goals:
 *   - Clean HAL (Hardware Abstraction Layer)
 *   - Reliable packet TX/RX for offline mesh sync
 *   - Low-power duty cycling
 *   - Region-compliant operation (US915 / EU868 etc.)
 *   - Hooks for encryption + signing (added in upper layers)
 *
 * NOTE:
 *   This is investor-ready demonstration firmware.
 *   Hardware-specific register values are stubbed and clearly marked.
 *   Final prototypes will replace these stubs with vendor SDK calls.
 */

#include "lora_driver.h"
#include "radio_config.h"
#include "security_config.h"
#include "power_config.h"
#include "../utils/timekeeping.h"
#include "../utils/crc16.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* -------------------------------------------------------
 *  Internal State
 * ------------------------------------------------------- */

static bool radio_initialized = false;

/* Buffer for incoming packets */
static uint8_t rx_buffer[LORA_MAX_PACKET_SIZE];
static uint16_t rx_size = 0;

/* -------------------------------------------------------
 *  Hardware-Level Stub Functions (to be replaced)
 * ------------------------------------------------------- */

static void hw_reset_radio()
{
    // TODO: Connect to SX1262/SX1276 RESET pin
}

static void hw_write_register(uint16_t reg, uint8_t value)
{
    // TODO: SPI write
}

static uint8_t hw_read_register(uint16_t reg)
{
    // TODO: SPI read
    return 0x00;
}

static void hw_send_payload(uint8_t *data, uint16_t len)
{
    // TODO: Hardware TX
}

static uint16_t hw_receive_payload(uint8_t *buffer)
{
    // TODO: Hardware RX
    return 0;
}

/* -------------------------------------------------------
 *  Initialization
 * ------------------------------------------------------- */

bool lora_init()
{
    hw_reset_radio();

    // Apply region-specific configs
    hw_write_register(REG_FREQUENCY, LORA_FREQUENCY);
    hw_write_register(REG_SPREADING_FACTOR, LORA_SF);
    hw_write_register(REG_BANDWIDTH, LORA_BW);
    hw_write_register(REG_CODING_RATE, LORA_CR);

    radio_initialized = true;
    return true;
}

/* -------------------------------------------------------
 *  CRC + Frame Assembly
 * ------------------------------------------------------- */

static uint16_t create_packet_crc(uint8_t *data, uint16_t len)
{
    return crc16_compute(data, len);
}

static uint16_t build_frame(uint8_t *out, const uint8_t *payload, uint16_t len)
{
    uint16_t total = 0;

    // Frame header
    out[total++] = FRAME_VERSION;
    out[total++] = FRAME_TYPE_DATA;

    // Payload length
    out[total++] = (uint8_t)(len & 0xFF);
    out[total++] = (uint8_t)((len >> 8) & 0xFF);

    // Payload
    memcpy(&out[total], payload, len);
    total += len;

    // CRC
    uint16_t crc = create_packet_crc(payload, len);
    out[total++] = (uint8_t)(crc & 0xFF);
    out[total++] = (uint8_t)((crc >> 8) & 0xFF);

    return total;
}

/* -------------------------------------------------------
 *  Public Send Function
 * ------------------------------------------------------- */

bool lora_send(uint8_t *data, uint16_t len)
{
    if (!radio_initialized) return false;
    if (len > LORA_MAX_PAYLOAD_SIZE) return false;

    uint8_t frame[LORA_MAX_PACKET_SIZE];
    uint16_t frame_len = build_frame(frame, data, len);

    hw_send_payload(frame, frame_len);

    return true;
}

/* -------------------------------------------------------
 *  Public Receive Function
 * ------------------------------------------------------- */

bool lora_receive(uint8_t *out, uint16_t *out_len)
{
    if (!radio_initialized) return false;

    rx_size = hw_receive_payload(rx_buffer);
    if (rx_size < MIN_FRAME_SIZE) return false;

    // Extract payload len
    uint16_t payload_len = rx_buffer[2] | (rx_buffer[3] << 8);

    if (payload_len > LORA_MAX_PAYLOAD_SIZE) return false;

    // Extract payload
    memcpy(out, &rx_buffer[4], payload_len);
    *out_len = payload_len;

    // Validate CRC
    uint16_t expected_crc = rx_buffer[4 + payload_len] |
                            (rx_buffer[5 + payload_len] << 8);

    uint16_t computed_crc = create_packet_crc(out, payload_len);

    return (expected_crc == computed_crc);
}

/* -------------------------------------------------------
 *  Power-Saving Logic
 * ------------------------------------------------------- */

void lora_sleep()
{
    // TODO: Put radio into low-power sleep mode
}

void lora_wake()
{
    // TODO: Reactivate radio
}

/* -------------------------------------------------------
 *  Diagnostics
 * ------------------------------------------------------- */

void lora_print_status()
{
    // TODO: Read hardware registers for debugging
}

/* -------------------------------------------------------
 *  End of File
 * ------------------------------------------------------- */
