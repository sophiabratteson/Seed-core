# Duty Cycle Assumptions

This document defines the duty cycle assumptions used in Seed power simulations. Duty cycle refers to how often and how long each hardware and software subsystem is active during normal device operation. These assumptions are critical for estimating battery life, solar viability, and long-term device reliability in off-grid environments.

---

## Purpose

The duty cycle model is used to:
- Estimate average and peak power consumption
- Compare power profiles across usage scenarios
- Validate feasibility of solar and hand-crank charging
- Identify dominant power consumers
- Inform firmware-level power optimization strategies

All power budget simulations reference the assumptions defined here.

---

## Device Operating States

Seed devices operate in the following high-level states:

- Deep Sleep
- Idle / Standby
- Active Interaction
- Radio Transmission
- Radio Reception
- Charging Mode
- Emergency / Recovery Mode

Each state has different power characteristics and expected time allocation.

---

## Baseline Usage Profile

The baseline profile represents a typical user in a low-connectivity environment such as a rural market or village.

### Daily Assumptions (24-hour period)

- Device powered on continuously
- User interactions spread throughout the day
- Radio activity clustered during peak interaction windows

---

## Subsystem Duty Cycles

### Microcontroller (MCU)

- Active processing: ~5% of time
- Idle / low-power mode: ~90% of time
- Deep sleep: ~5% of time

The MCU spends most of its time waiting for interrupts (button press, radio event, timer).

---

### E-Ink Display

- Screen refresh: ~20–40 refreshes per day
- Average refresh duration: <1 second
- Static display draw: 0 power between updates

Assumption:
- Display active <0.1% of total time
- Display does not meaningfully impact continuous power draw

---

### LoRa Radio

#### Transmission
- Short burst messages only
- Average transmission duration: 100–300 ms
- Daily transmissions: 20–100 messages

#### Reception
- Periodic listening windows
- Passive receive windows: 1–2 seconds per minute during active hours
- Reduced listening during overnight periods

Assumption:
- Radio TX: <0.5% duty cycle
- Radio RX: 2–5% duty cycle depending on mesh density

---

### Secure Element / Cryptography

- Active only during:
  - Transaction signing
  - Ledger verification
  - Key operations
- Each operation <50 ms

Assumption:
- Cryptographic operations <0.2% duty cycle

---

### Sensors and Inputs

#### Fingerprint Sensor
- Activated only during authentication
- Typical usage: 5–20 scans per day
- Active time per scan: <1 second

Assumption:
- <0.1% duty cycle

#### Buttons
- Event-driven
- Negligible power impact

---

### Storage (Flash / Secure Memory)

- Writes occur during:
  - Transaction creation
  - Ledger sync completion
  - Periodic checkpointing

Assumption:
- Storage active <0.3% of time

---

## Charging Duty Cycle

### Solar Charging

- Available 4–8 hours per day depending on region
- Charging occurs opportunistically
- Device may charge while operating

Assumption:
- Solar input offsets daily consumption under normal use

---

### Hand-Crank Charging

- Used intermittently during low-battery events
- Typical session: 1–5 minutes

Assumption:
- Not continuous
- Treated as emergency energy injection rather than baseline supply

---

## Emergency / Edge Case Scenarios

### High-Activity Market Day

- Increased transactions
- Higher radio usage
- More frequent screen refreshes

Assumption:
- Peak power draw may increase 2–3× temporarily
- Battery capacity sized to tolerate short-term spikes

---

### Long Offline Periods

- Minimal radio usage
- Device remains mostly idle
- Ledger accumulation local only

Assumption:
- Power consumption decreases significantly during isolation

---

## Summary Duty Cycle Table (Approximate)

- MCU Active: 5%
- Radio TX: 0.5%
- Radio RX: 2–5%
- Display Active: <0.1%
- Sensors: <0.1%
- Storage: <0.3%
- Idle / Sleep: ~89–92%

---

## Design Implications

- Battery capacity is driven primarily by idle draw, not peak usage
- LoRa receive windows are the dominant tunable power variable
- E-ink enables near-zero display overhead
- Aggressive sleep scheduling provides large efficiency gains
- Firmware optimization should prioritize radio scheduling logic

---

## Future Refinements

- Region-specific duty cycle profiles
- Adaptive duty cycling based on battery level
- Trust-score weighted radio participation
- Seasonal solar availability modeling
- Per-user behavioral power modeling

---

## Conclusion

These duty cycle assumptions demonstrate that Seed can operate continuously in off-grid environments with minimal energy input. By minimizing always-on components and using event-driven activation, the device achieves long operational lifetimes while maintaining reliable financial functionality.
