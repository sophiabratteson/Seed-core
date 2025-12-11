/**
 * safe_memory.h
 * --------------------------------------------
 * Seed Device Firmware — Safe Memory Utilities
 *
 * Provides hardened wrappers around memory operations
 * to reduce the risk of buffer overflows, NULL pointer
 * dereferences, and unsafe memory access conditions.
 *
 * All functions return explicit status codes and perform
 * validation checks before executing underlying operations.
 *
 * These utilities are used across:
 *   - Ledger serialization/deserialization
 *   - Mesh packet encoding and decoding
 *   - Secure element communication
 *   - Storage persistence
 *
 * Designed for hostile / unstable environments where:
 *   - power may fail abruptly
 *   - memory corruption is possible
 *   - inputs may not be trusted
 */

#ifndef SAFE_MEMORY_H
#define SAFE_MEMORY_H

#include <stdint.h>
#include <stddef.h>

// --------------------------------------------
// Status Codes
// --------------------------------------------
typedef enum {
    SAFE_MEM_OK = 0,
    SAFE_MEM_ERR_NULL_PTR,
    SAFE_MEM_ERR_OUT_OF_RANGE,
    SAFE_MEM_ERR_COPY_FAILED,
    SAFE_MEM_ERR_ZERO_LENGTH
} safe_mem_status_t;

// --------------------------------------------
// Safe Copy
// --------------------------------------------

/**
 * Safely copies a block of memory.
 *
 * Parameters:
 *   dest  – destination buffer
 *   dsize – size of destination buffer
 *   src   – source buffer
 *   count – number of bytes to copy
 *
 * Returns:
 *   SAFE_MEM_OK on success, otherwise an error.
 */
safe_mem_status_t safe_mem_copy(
    void *dest,
    size_t dsize,
    const void *src,
    size_t count
);

// --------------------------------------------
// Safe Zero
// --------------------------------------------

/**
 * Securely zeroes a buffer using a volatile write
 * to prevent compiler optimization removal.
 *
 * Parameters:
 *   buf  – buffer pointer
 *   size – size in bytes
 *
 * Returns:
 *   SAFE_MEM_OK on success.
 */
safe_mem_status_t safe_mem_zero(void *buf, size_t size);

#endif // SAFE_MEMORY_H
