/**
 * radio_interface.c
 * ---------------------------------------------------------
 * Seed Device Firmware — Radio Interface Layer
 *
 * Purpose:
 *   - Provides a hardware-abstracted interface for LoRa-based
 *     mesh communication.
 *   - Handles radio initialization, configuration, TX/RX
 *     operations, power-optimized modes, and basic integrity
 *     checks.
 *
 * Design Goals:
 *   - Offline-first mesh communication with no dependency
 *     on internet or infrastructure.
 *   - Ultra-low power consumption for long runtimes.
 *   - Deterministic, small packet formats for financial
 *     ledger sync.
 *   - Secure transmission with pre-validated keys handled
 *     by the secure element (not implemented here).
 *
 * NOTE:
 *   This is a prototype-grade scaffold. The hardware-specific
 *   driver hooks (SPI writes, interrupts, registers) must be
 *   implemented when the SX1262/SX1276 board arrives.
 * ---------------------------------------------------------
 */

#include "radio_interface.h"
#include "radio_config.h"
#include "device_config.h"
#include "crc16.h"
#include <string.h>
#include <stdio.h>

// ---------------------------------------------------------------------------
// Internal Static State
// ---------------------------------------------------------------------------
static bool radio_initialized = false;
static radio_status_t last_status = RADIO_STATUS_IDLE;

// ---------------------------------------------------------------------------
// Hardware Abstractions (to be implemented with real board)
// ---------------------------------------------------------------------------

static void hw_reset_radio()
{
    // TODO: toggle reset pin for SX1262/SX1276
}

static void hw_radio_write_register(uint16_t reg, uint8_t value)
{
    // TODO: implement SPI write
}

static uint8_t hw_radio_read_register(uint16_t reg)
{
    // TODO: implement SPI read
    return 0;
}

static void hw_radio_send_raw(uint8_t *data, uint16_t len)
{
    // TODO: push bytes into radio FIFO and trigger TX
}

static uint16_t hw_radio_receive_raw(uint8_t *buffer, uint16_t max_len)
{
    // TODO: read bytes from radio RX FIFO
    return 0;
}

// ---------------------------------------------------------------------------
// Radio Initialization
// ---------------------------------------------------------------------------

radio_status_t radio_init()
{
    hw_reset_radio();

    // Apply radio configuration constants
    hw_radio_write_register(REG_FREQ_MSB, RADIO_FREQ_MSB);
    hw_radio_write_register(REG_FREQ_MID, RADIO_FREQ_MID);
    hw_radio_write_register(REG_FREQ_LSB, RADIO_FREQ_LSB);

    hw_radio_write_register(REG_SPREADING_FACTOR, RADIO_SF);
    hw_radio_write_register(REG_BANDWIDTH, RADIO_BW);
    hw_radio_write_register(REG_CODING_RATE, RADIO_CR);

    hw_radio_write_register(REG_OUTPUT_POWER, RADIO_TX_POWER);

    radio_initialized = true;
    last_status = RADIO_STATUS_IDLE;

    return RADIO_STATUS_OK;
}

// ---------------------------------------------------------------------------
// Packet Structure
// ---------------------------------------------------------------------------
/*
   Seed Radio Packet Format (≤ 250 bytes)
   --------------------------------------
   | Byte(s) | Field            |
   |---------|------------------|
   |   0     | Protocol version |
   |   1     | Message type     |
   |  2–3    | Payload length   |
   |  4–n    | Payload data     |
   | n+1,n+2 | CRC16 checksum   |

   Design Considerations:
   - Small packet size → reliable in lossy mesh networks.
   - CRC16 ensures integrity even before signature validation.
   - Message types include:
        MSG_LEDGER_SYNC
        MSG_TX_BROADCAST
        MSG_GROUP_SAVINGS_UPDATE
        MSG_TRUST_SCORE_UPDATE
        MSG_HEARTBEAT
*/

#define PROTOCOL_VERSION 1

// ---------------------------------------------------------------------------
// Build Packet
// ---------------------------------------------------------------------------

static uint16_t build_packet(
    uint8_t msg_type,
    uint8_t *payload,
    uint16_t payload_len,
    uint8_t *out_buffer)
{
    out_buffer[0] = PROTOCOL_VERSION;
    out_buffer[1] = msg_type;

    out_buffer[2] = (payload_len >> 8) & 0xFF;
    out_buffer[3] = (payload_len & 0xFF);

    memcpy(&out_buffer[4], payload, payload_len);

    uint16_t crc = crc16_compute(out_buffer, payload_len + 4);
    out_buffer[4 + payload_len]     = (crc >> 8) & 0xFF;
    out_buffer[5 + payload_len]     = (crc & 0xFF);

    return payload_len + 6;
}

// ---------------------------------------------------------------------------
// Transmit
// ---------------------------------------------------------------------------

radio_status_t radio_send(uint8_t msg_type, uint8_t *data, uint16_t len)
{
    if (!radio_initialized)
        return RADIO_ERR_NOT_INITIALIZED;

    uint8_t packet[MAX_RADIO_PACKET_SIZE];
    uint16_t packet_len = build_packet(msg_type, data, len, packet);

    hw_radio_send_raw(packet, packet_len);
    last_status = RADIO_STATUS_TX;

    return RADIO_STATUS_OK;
}

// ---------------------------------------------------------------------------
// Receive
// ---------------------------------------------------------------------------

radio_status_t radio_receive(radio_packet_t *out_packet)
{
    if (!radio_initialized)
        return RADIO_ERR_NOT_INITIALIZED;

    uint8_t buffer[MAX_RADIO_PACKET_SIZE];
    uint16_t len = hw_radio_receive_raw(buffer, MAX_RADIO_PACKET_SIZE);

    if (len < 6)
        return RADIO_ERR_BAD_PACKET;

    uint8_t version = buffer[0];
    uint8_t type    = buffer[1];
    uint16_t plen   = (buffer[2] << 8) | buffer[3];

    if (plen + 6 != len)
        return RADIO_ERR_BAD_LENGTH;

    uint16_t received_crc = (buffer[len-2] << 8) | buffer[len-1];
    uint16_t computed_crc = crc16_compute(buffer, len-2);

    if (received_crc != computed_crc)
        return RADIO_ERR_CRC_MISMATCH;

    out_packet->version = version;
    out_packet->msg_type = type;
    out_packet->payload_len = plen;
    memcpy(out_packet->payload, &buffer[4], plen);

    last_status = RADIO_STATUS_RX;
    return RADIO_STATUS_OK;
}

// ---------------------------------------------------------------------------
// Power Management Hooks
// ---------------------------------------------------------------------------

void radio_sleep()
{
    // TODO: Put radio into low-power sleep mode
    last_status = RADIO_STATUS_SLEEP;
}

void radio_wake()
{
    // TODO: Wake radio from sleep mode
    last_status = RADIO_STATUS_IDLE;
}

// ---------------------------------------------------------------------------
// Status Query
// ---------------------------------------------------------------------------

radio_status_t radio_get_status()
{
    return last_status;
}
