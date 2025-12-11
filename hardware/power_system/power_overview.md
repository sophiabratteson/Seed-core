# Power System Overview

This document provides a comprehensive overview of the Seed device power subsystem, including its design goals, energy sources, storage components, regulation circuits, safety protections, and operational constraints. Because Seed is intended for deployment in low-infrastructure environments with unreliable access to electricity, the power system is one of the most critical hardware domains.

---

# 1. Power System Goals

Seed’s power architecture must support the following objectives:

- Operate reliably with no grid connection.
- Support continuous ledger functionality even during long periods without sunlight or external power.
- Maintain extremely low average power consumption to maximize battery life.
- Ensure safe charging and storage in harsh climates.
- Support multiple input sources, including solar and hand-crank generators.
- Provide stable voltage rails for LoRa radio bursts, secure chip operations, e-ink refresh cycles, and microcontroller processing.

---

# 2. Power Architecture Overview

Seed uses a multi-input hybrid power architecture consisting of:

- A primary LiFePO₄ battery for durability, longevity, and temperature stability.
- A solar input stage for passive daytime charging.
- A hand-crank generator interface for user-initiated emergency charging.
- A charge controller optimized for low-input charging currents.
- A step-up / step-down voltage regulation subsystem providing stable 3.3V and 1.8V rails.
- Dedicated safety and protection hardware to ensure user and device safety.

The system is designed to operate under extremely low power conditions and aggressively manage power draw using hardware sleep modes and duty cycling.

---

# 3. Energy Sources

## 3.1 Solar Panel Input
- Expected panel size: 0.5W–1.5W depending on final form factor.
- Typical voltage: 5–6V open circuit; regulated down by the charge controller.
- Supports trickle charging even in low-light environments.
- Enables fully passive operation for users who cannot actively generate power.

## 3.2 Hand-Crank Generator
- Alternating-current micro-generator input.
- Routed through a rectifier and smoothing capacitor before reaching the charge controller.
- Enables full autonomy even in environments without sunlight, such as indoor markets or rainy seasons.
- Provides immediate emergency power if the battery is depleted.

---

# 4. Energy Storage

## 4.1 LiFePO₄ Battery (Recommended Chemistry)
- High thermal stability; resists swelling or combustion.
- 2,000+ charge cycles, ideal for long-term field deployment.
- Performs well in temperatures from -20°C to +60°C.
- Stores enough energy for multiple days of low-duty operation.

## 4.2 Battery Protection Board (BMS)
Functions include:
- Over-charge protection.
- Over-discharge protection.
- Short-circuit protection.
- Temperature monitoring.
- Controlled discharge rates to protect cell longevity.

---

# 5. Power Regulation and Distribution

## 5.1 Voltage Regulation Rails
The Seed device requires:
- 3.3V rail for microcontroller, LoRa radio, memory, and logic.
- 1.8V rail (optional depending on secure element).
- Boost converter for stable output during low battery conditions.

## 5.2 Load Prioritization
Critical loads include:
- Secure element (short bursts).
- LoRa transmission (high current bursts).
- E-ink refresh cycles (moderate current spikes).
- MCU background tasks (ultra-low-power sleep the majority of the time).

Lower-priority loads can be suspended automatically when battery levels are low.

---

# 6. Power Budget Philosophy

Seed is engineered under a strict "offline-first, low-power-first" philosophy.

Typical consumption characteristics:
- MCU deep sleep: 2–10µA.
- LoRa receive window: ~10–12mA.
- LoRa transmit burst: 100–150mA peak (for milliseconds).
- E-ink full refresh: ~20–30mA momentary.
- Idle ledger operations: sub-milliwatt.

By aggressively minimizing radio and screen usage, Seed achieves multi-day or even multi-week runtime from a small LiFePO₄ cell.

---

# 7. Charging Architecture

Charge controller responsibilities:
- MPPT-like detection for maximizing solar efficiency.
- Automatic source switching between solar and hand-crank.
- Safe charging of LiFePO₄ chemistry at correct voltage and current levels.
- Temperature-aware charging curves.

Optional:
- LED charge indicator for user feedback.
- Low-battery warnings managed by firmware.

---

# 8. Power System Operating Modes

Seed firmware integrates multiple hardware-driven power modes:

## 8.1 Deep Sleep Mode
- MCU idle.
- Only real-time clock remains active.
- Wakes on button press, scheduled sync event, or power threshold interrupt.

## 8.2 Sync Window Mode
- Radio activated briefly to send or listen for ledger updates.
- Duration controlled by adaptive duty cycle algorithms.

## 8.3 Interaction Mode
- Buttons active.
- E-ink updates triggered.
- MCU handles ledger tasks and trust-score updates.

## 8.4 Emergency Mode
- Device enters minimal operation mode.
- Only essential functionality preserved.
- Activated when battery < critical threshold.

---

# 9. Safety and Compliance

The power subsystem must comply with:
- Temperature safety standards for battery handling.
- Short-circuit and over-voltage protections.
- IEC standards for consumer solar-charged electronics.
- Country-specific battery import regulations.

Design also includes hardware-level failsafes:
- Fuses or polymer resettable fuses.
- Input current limiting.
- Reverse-polarity protection.

---

# 10. Future Enhancements

Possible improvements for later hardware revisions:
- Integrated MPPT solar optimization for higher efficiency.
- Supercapacitor buffer for radio burst smoothing.
- Wireless (inductive) charging pad compatibility.
- Hot-swappable modular batteries.

---

# 11. Summary

Seed’s power system is engineered for resilience, modularity, and longevity in extremely low-infrastructure environments. By combining LiFePO₄ storage, solar trickle input, optional hand-crank charging, low-power firmware design, and robust safety protections, the device can operate autonomously for long periods without dependence on electrical grids. This makes Seed viable in rural communities, disaster zones, and emerging markets where traditional financial infrastructure cannot reliably function.
