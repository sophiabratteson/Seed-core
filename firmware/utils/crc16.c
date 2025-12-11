/**
 * -------------------------------------------------------------
 *  Seed Device Firmware
 *  File: crc16.c
 *  Purpose: CRC-16/CCITT-FALSE checksum implementation
 * -------------------------------------------------------------
 *
 *  Why CRC?
 *  --------
 *  Seed devices operate in extremely low-connectivity, noisy
 *  radio environments. Every packet, ledger delta, and sync
 *  message must include a lightweight integrity check.
 *
 *  CRC-16 is:
 *   - Fast enough for low-power MCUs
 *   - Strong enough to detect burst errors
 *   - Standardized across many mesh and radio protocols
 *
 *  This module is used by:
 *     firmware/mesh/packet_format
 *     firmware/mesh/mesh_protocol
 *     firmware/storage_manager
 *     firmware/security_module
 *
 *  Parameters (CRC-16/CCITT-FALSE)
 *  -------------------------------
 *    Polynomial: 0x1021
 *    Initial value: 0xFFFF
 *    XOR output: 0x0000
 *    Input reflected: No
 *    Output reflected: No
 *
 *  Example expected outputs:
 *    CRC16("123456789") → 0x29B1
 *
 * -------------------------------------------------------------
 */

#include "crc16.h"

/**
 * Computes CRC-16/CCITT-FALSE over a buffer.
 *
 * @param data    Pointer to the input byte array
 * @param length  Number of bytes to process
 * @return        16-bit CRC checksum
 */
uint16_t crc16_compute(const uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;

    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)data[i] << 8;

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }

    return crc & 0xFFFF;
}

/**
 * Incremental CRC update for streaming data (e.g., radio packets,
 * chunked ledger sync payloads).
 *
 * @param crc     Previous CRC state
 * @param byte    Next byte to incorporate
 * @return        Updated CRC
 */
uint16_t crc16_update(uint16_t crc, uint8_t byte)
{
    crc ^= (uint16_t)byte << 8;

    for (uint8_t bit = 0; bit < 8; bit++)
    {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc <<= 1;
    }

    return crc & 0xFFFF;
}

/**
 * Convenience function to verify a CRC against expected value.
 *
 * @param data      Input bytes
 * @param length    Number of bytes
 * @param expected  Expected CRC result
 * @return          1 if valid, 0 if mismatch
 */
uint8_t crc16_verify(const uint8_t *data, uint16_t length, uint16_t expected)
{
    return (crc16_compute(data, length) == expected) ? 1 : 0;
}
