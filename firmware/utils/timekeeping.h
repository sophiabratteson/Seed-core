/**
 * timekeeping.h
 * --------------------------------------------
 * Seed Device Firmware — Timekeeping Utilities
 *
 * The Seed device operates in offline-first environments,
 * meaning there is no reliable absolute time source.
 *
 * Instead of real timestamps, Seed uses:
 *   - Lamport logical clocks for ordering events
 *   - Monotonic device tick counters
 *   - Low-power timers for scheduling sync tasks
 *
 * These functions provide:
 *   - safe access to logical clocks
 *   - increment operations tied to transaction creation
 *   - resync utilities after reboot or brownout
 */

#ifndef TIMEKEEPING_H
#define TIMEKEEPING_H

#include <stdint.h>

// --------------------------------------------
// Logical Clock
// --------------------------------------------

/**
 * Initializes the logical clock system.
 * Should be called at boot.
 */
void tk_init_clock(void);

/**
 * Increments the Lamport clock and returns the new value.
 * Called every time a new transaction is created.
 */
uint32_t tk_increment_clock(void);

/**
 * Updates logical clock after receiving a remote timestamp.
 *
 * Parameters:
 *   remote_clock – Lamport timestamp from another device
 *
 * Returns:
 *   updated local clock value
 */
uint32_t tk_update_from_remote(uint32_t remote_clock);

/**
 * Returns the current Lamport clock value.
 */
uint32_t tk_get_clock(void);

// --------------------------------------------
// Monotonic System Tick
// --------------------------------------------

/**
 * Returns a low-resolution monotonic tick counter
 * used for:
 *   - retry intervals
 *   - sync scheduling
 *   - power-saving sleep durations
 */
uint32_t tk_get_monotonic_tick(void);

/**
 * Advances the monotonic tick safely.
 * Should be tied to a hardware timer interrupt.
 */
void tk_tick_isr(void);

#endif // TIMEKEEPING_H
