/**
 * safe_memory.c
 * -----------------------------------------
 * Seed Device Firmware — Secure Memory Utilities
 *
 * This module provides hardened memory operations for
 * embedded environments where crashes, corruption, or
 * adversarial tampering must be prevented.
 *
 * Features:
 *  - Bounds-checked memory copy/set
 *  - Secure memory wipe for sensitive data
 *  - Pointer null-check helpers
 *  - Optional compile-time hardening modes
 *
 * These functions help ensure firmware reliability
 * on ultra-low-power offline devices operating in
 * unpredictable field environments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "safe_memory.h"

// ------------------------------------------------------------
// Internal Helper: Validate pointers + lengths
// ------------------------------------------------------------
static int safe_mem_validate(const void *dst, const void *src, size_t len)
{
    if (dst == NULL || src == NULL) return -1;   // null pointer
    if (len == 0) return -2;                     // invalid length
    return 0;
}

// ------------------------------------------------------------
// Safe Memory Copy (bounds-checked)
// ------------------------------------------------------------
int safe_memcpy(void *dst, size_t dst_size,
                const void *src, size_t src_size,
                size_t len)
{
    if (safe_mem_validate(dst, src, len) != 0)
        return -1;

    // Ensure we never read or write out of bounds
    if (len > dst_size || len > src_size)
        return -2;

    memcpy(dst, src, len);
    return 0;
}

// ------------------------------------------------------------
// Safe Memory Set
// ------------------------------------------------------------
int safe_memset(void *dst, size_t dst_size, uint8_t value, size_t len)
{
    if (dst == NULL || len == 0) return -1;
    if (len > dst_size) return -2;

    memset(dst, value, len);
    return 0;
}

// ------------------------------------------------------------
// Secure Zero (for wiping sensitive data — keys, PINs)
// ------------------------------------------------------------
void secure_zero(void *ptr, size_t len)
{
    if (!ptr || len == 0) return;

#if defined(__GNUC__)
    // Prevent compiler from optimizing away the wipe
    __asm__ __volatile__ ("" : : : "memory");
#endif

    volatile uint8_t *p = (volatile uint8_t *)ptr;
    while (len--) *p++ = 0;
}

// ------------------------------------------------------------
// Safe Compare — constant time (prevents timing attacks)
// ------------------------------------------------------------
int safe_memcmp_consttime(const void *a, const void *b, size_t len)
{
    if (a == NULL || b == NULL) return -1;

    const uint8_t *pa = (const uint8_t *)a;
    const uint8_t *pb = (const uint8_t *)b;

    uint8_t diff = 0;
    for (size_t i = 0; i < len; i++)
        diff |= (pa[i] ^ pb[i]);

    return diff; // 0 = match, non-zero = mismatch
}

// ------------------------------------------------------------
// Pointer Safety Checks (Optional helper utilities)
// ------------------------------------------------------------
int is_null(const void *ptr)
{
    return (ptr == NULL);
}

int is_aligned(const void *ptr, size_t alignment)
{
    return ((uintptr_t)ptr % alignment == 0);
}

// ------------------------------------------------------------
// Hardened Allocator Hooks (Optional — for future expansion)
// ------------------------------------------------------------
#ifdef SEED_ENABLE_MEMORY_TRACE
#include <stdio.h>

void mem_trace(const char *msg, size_t size)
{
    printf("[MEM TRACE] %s (%lu bytes)\n", msg, (unsigned long)size);
}
#endif
