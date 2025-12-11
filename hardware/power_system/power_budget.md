# Power Budget

This document provides a detailed power budget analysis for the Seed device. Because Seed is designed for extremely low-resource environments, the power system must support offline operation, intermittent charging, and multi-day standby on minimal energy input. This file outlines estimated power consumption for every major subsystem, duty-cycle assumptions, and projected battery life under realistic usage models.

---

# 1. Objectives of the Power Budget

- Ensure Seed can operate for several days without sunlight or hand-cranking.
- Minimize power consumption of radio, display, sensors, and CPU.
- Provide predictable energy envelopes for firmware scheduling.
- Support low-power standby modes with instant wake.
- Validate that selected battery chemistry (LiFePO4) can support real-world duty cycles.
- Inform PCB power routing, regulator choices, and charging circuit design.

---

# 2. Hardware Components Considered

## Core components included in this power budget
- Microcontroller (ESP32 class or ARM Cortex-M series)
- LoRa radio module (SX1262 or SX1276)
- E-ink display (2.13 inch)
- Secure element chip
- Capacitive fingerprint sensor
- Battery management system (BMS)
- Sensors (basic battery monitor, optional temperature sensor)
- Hand-crank generator and solar input subsystem

---

# 3. Estimated Current Consumption per Component

These numbers are conservative estimates based on common components used in low-power IoT devices. Final measurements will occur after prototype assembly.

## Microcontroller (MCU)
- Active compute: 40–60 mA
- Light sleep: 1–2 mA
- Deep sleep: 20–80 µA

## LoRa Radio Transceiver
- Transmit (TX mode, 22 dBm): 120–140 mA
- Receive (RX mode): 12–14 mA
- Standby: 0.8–1.5 mA
- Sleep: 1–2 µA

## E-Ink Display (2.13")
- Page refresh: 25–40 mA for 400–500 ms
- Static display: 0 mA (no power required to maintain image)

## Secure Element (ATECC608 or similar)
- Active: 10–15 mA for short bursts
- Idle: < 150 µA

## Capacitive Fingerprint Sensor
- Active scan: 60–80 mA
- Idle/standby: 0.1–1 mA
- Deep sleep cutoff: < 20 µA (enabled between scans)

## Battery Management & Charging
- BMS overhead: 20–50 µA
- Solar charge controller (MPPT-style): 1–2 mA
- Hand-crank rectifier + storage: depends on load, typically 50–150 mA input

---

# 4. Typical Usage Duty Cycle

Seed is not a continuously online device. Its power profile is based on user-triggered bursts of activity.

## Daily usage assumptions
- 20 device unlocks (fingerprint)
- 10 ledger operations (creating or validating a transaction)
- 15 mesh sync events (short radio packet exchange)
- 5 display updates
- MCU deep sleep whenever idle
- Periodic heartbeat every 5 minutes (low power)

These assumptions generate a realistic model for rural markets with moderate transaction activity.

---

# 5. Energy Cost per Activity

## Unlock sequence (fingerprint + wake MCU)
- Fingerprint active 1 second: ~60 mA
- MCU active 1 second: ~50 mA
Total: ~110 mA for 1 second → 0.03 mAh per unlock

## Display refresh
- 30 mA for 0.5 s → 0.004 mAh per update

## LoRa transaction broadcast
- TX 140 mA for 200 ms → 0.008 mAh
- RX window 13 mA for 400 ms → 0.0015 mAh
Total: 0.0095 mAh per radio event

## Deep sleep baseline
- 50 µA average → 1.2 mAh per day

---

# 6. Daily Total Consumption Estimate

Using the duty cycle above:

- 20 unlocks → 0.6 mAh
- 10 transactions → 0.1 mAh
- 15 sync events → 0.14 mAh
- 5 display updates → 0.02 mAh
- Deep sleep baseline → 1.2 mAh
- Secure element operations → ~0.05 mAh
- System overhead (BMS, regulators) → ~3–5 mAh per day

## Total estimated daily consumption
