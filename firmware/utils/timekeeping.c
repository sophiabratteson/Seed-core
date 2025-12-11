#include "timekeeping.h"
#include <stdint.h>
#include <stdbool.h>

/*
 * Timekeeping Module
 * -------------------
 * This module provides Seed’s device-level timing infrastructure.
 * Because Seed devices operate offline and do NOT trust real-time clocks,
 * the timing layer focuses on:
 *   - Stable millisecond ticks from the MCU
 *   - Long-uptime counters for scheduling tasks
 *   - Timeout management for radio retries & mesh sync
 *   - Heartbeat interval generation
 *
 * No wall-clock time is used. Everything is monotonic.
 *
 * Hardware-specific tick sources (SysTick, RTC, Timer0, etc.)
 * must call timekeeping_tick_isr() every 1 millisecond.
 */

// ---------------------------------------------------------------------------
// Internal State
// ---------------------------------------------------------------------------

static volatile uint64_t g_millis = 0;          // Monotonic millisecond time
static volatile uint32_t g_seconds = 0;         // Derived seconds counter
static const uint32_t SECONDS_PER_TICK = 1000;  // 1000ms = 1s

// ---------------------------------------------------------------------------
// Interrupt-driven tick increment
// ---------------------------------------------------------------------------

/**
 * @brief Called from the hardware timer interrupt every 1ms.
 */
void timekeeping_tick_isr(void)
{
    g_millis++;

    // Convert milliseconds → seconds
    if (g_millis % SECONDS_PER_TICK == 0) {
        g_seconds++;
    }
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

/**
 * @brief Get time in milliseconds since boot.
 */
uint64_t timekeeping_millis(void)
{
    return g_millis;
}

/**
 * @brief Get time in seconds since boot.
 */
uint32_t timekeeping_seconds(void)
{
    return g_seconds;
}

/**
 * @brief Blocking delay. Not power-efficient, but simple.
 */
void timekeeping_delay_ms(uint32_t ms)
{
    uint64_t start = g_millis;
    while ((g_millis - start) < ms) {
        // busy-wait
        // On real hardware this should enter low-power idle mode.
    }
}

/**
 * @brief Check whether a timeout has expired.
 *
 * @param start     starting timestamp (in ms)
 * @param timeout   timeout duration (in ms)
 *
 * @return true if (now - start >= timeout)
 */
bool timekeeping_timeout_expired(uint64_t start, uint32_t timeout)
{
    uint64_t now = g_millis;
    return (now - start) >= timeout;
}

/**
 * @brief Compute elapsed time in milliseconds.
 */
uint32_t timekeeping_elapsed_ms(uint64_t since)
{
    return (uint32_t)(g_millis - since);
}

/**
 * @brief Generate a periodic event tick.
 *
 * Example:
 *    uint64_t next_ping = 0;
 *    if (timekeeping_periodic(&next_ping, 5000)) {
 *        // Do something every 5 seconds
 *    }
 *
 * @param next_timestamp pointer to the next scheduled trigger
 * @param period_ms periodic interval
 *
 * @return true when the event should fire
 */
bool timekeeping_periodic(uint64_t* next_timestamp, uint32_t period_ms)
{
    uint64_t now = g_millis;

    if (now >= *next_timestamp) {
        *next_timestamp = now + period_ms;
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------
// Optional diagnostics
// ---------------------------------------------------------------------------

#ifdef TIMEKEEPING_DEBUG
#include <stdio.h>

void timekeeping_debug_print(void)
{
    printf("[TIME] %llu ms | %u s\n",
           (unsigned long long)g_millis,
           g_seconds);
}
#endif
