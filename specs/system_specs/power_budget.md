# Seed System Power Budget Specification

This document defines the complete power budget model for the Seed device. The power budget governs how Seed operates reliably in environments with no grid electricity, intermittent charging opportunities, extreme heat, and long idle periods. Power efficiency is a first-class system requirement and directly informs hardware selection, firmware design, user interaction patterns, and network behavior.

---

## 1. Power Budget Objectives

The Seed power system is designed to meet the following objectives:

- Operate continuously for multiple days without charging
- Function in off-grid environments with unreliable power access
- Support solar and manual (hand-crank) energy input
- Prioritize essential financial operations over non-critical tasks
- Prevent data loss during sudden power depletion
- Remain safe and stable in high-temperature environments

The power budget is structured to guarantee that core financial functions remain available even under severe power constraints.

---

## 2. Power Sources

Seed supports multiple complementary power inputs:

### Primary Energy Storage
- Lithium Iron Phosphate (LiFePO4) battery
- Selected for:
  - Thermal stability
  - Long cycle life
  - Non-flammability
  - Predictable discharge curves

### Energy Input Methods
- Solar panel input (low-wattage, passive charging)
- Manual hand-crank generator (user-initiated emergency charging)
- USB charging (for development, provisioning, and maintenance)

The system dynamically adapts its operating mode based on available energy sources.

---

## 3. Power Consumption Domains

Power usage is categorized into functional domains:

### Core System
- Microcontroller (MCU)
- Secure element
- Non-volatile storage

### Communication
- LoRa radio transmission
- LoRa radio reception
- Mesh discovery and sync operations

### User Interface
- E-ink display refresh
- Physical buttons
- Optional audio or haptic feedback

### Sensors and Security
- Fingerprint sensor
- Tamper detection circuitry

Each domain is independently power-managed.

---

## 4. Estimated Power Consumption by Component

The following values represent typical operational estimates:

### MCU
- Active: 20–40 mA
- Sleep: < 5 µA

### LoRa Radio
- Transmit (peak): 120–150 mA
- Receive: 10–15 mA
- Idle sleep: < 1 µA

### E-Ink Display
- Refresh: 15–30 mA (brief burst)
- Static display: 0 mA

### Secure Element
- Active cryptographic operation: < 10 mA
- Idle: negligible

### Fingerprint Sensor
- Active scan: 50–80 mA (short duration)
- Idle: near zero

The system design minimizes time spent in high-draw states.

---

## 5. Operating Modes and Power Profiles

Seed operates under distinct power modes:

### Active Mode
- User interacting
- Transactions being created or validated
- Radio transmissions enabled
- Highest short-term power draw

### Sync Mode
- Opportunistic mesh synchronization
- Controlled radio usage
- Duty-cycled to conserve energy

### Idle Mode
- Display static
- Radio asleep
- MCU in low-power state

### Emergency Low-Power Mode
- Triggered when battery falls below threshold
- Only critical operations allowed:
  - Viewing balance
  - Receiving funds
  - Secure data preservation
- Radio usage minimized or disabled

---

## 6. Duty Cycle Assumptions

Typical daily usage assumptions:

- 5–15 transactions per day
- 5–10 radio sync events
- Display refreshes only when state changes
- Majority of time spent in idle or deep sleep

These assumptions support multi-day operation on a single charge.

---

## 7. Power Management Strategies

Seed employs multiple strategies to reduce power consumption:

- Event-driven radio activation
- Aggressive sleep scheduling
- E-ink display usage instead of backlit screens
- Deferred background tasks
- Adaptive sync frequency based on battery level
- User-visible power warnings and suggestions

Firmware enforces strict energy accounting.

---

## 8. Power Safety and Protection

The power system includes:

- Over-charge protection
- Over-discharge protection
- Short-circuit protection
- Thermal monitoring
- Brownout detection

Critical data is written to non-volatile storage before shutdown.

---

## 9. Power Budget Constraints

The power budget imposes the following system constraints:

- No continuous radio listening
- No high-refresh displays
- No always-on sensors
- No background AI inference unless power surplus exists

All system features must degrade gracefully under low-power conditions.

---

## 10. Verification and Testing

Power budget validation includes:

- Idle current measurement
- Radio burst profiling
- Solar charging effectiveness tests
- Battery endurance simulations
- Field testing in low-sun and high-heat environments

Power metrics are logged during testing and compared against targets.

---

## 11. Summary

The Seed power budget enables secure, offline financial access in environments where traditional devices fail. By combining ultra-low-power hardware, adaptive firmware, and multiple charging options, Seed maintains essential financial functionality even under extreme power constraints.

Power efficiency is not an optimization — it is a foundational requirement of the Seed system
