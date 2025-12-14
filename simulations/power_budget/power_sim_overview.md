# Power Budget Simulation Overview

This document defines how Seed models, simulates, and validates power usage across all operating modes. The power budget simulation ensures that Seed devices remain functional in low-resource environments, including areas with limited sunlight, irregular user activity, and intermittent mesh communication.

The goal of this simulation is to prove that Seed can operate sustainably without continuous grid power while supporting financial transactions, security features, and mesh networking.

---

## Objectives of the Power Budget Simulation

- Estimate realistic battery lifetime under different usage patterns.
- Identify power-heavy components and optimize their duty cycles.
- Validate feasibility of solar and hand-crank charging strategies.
- Ensure critical financial and security operations always remain powered.
- Provide quantitative evidence for investors and hardware partners.

---

## Device Power Domains Modeled

The simulation models power consumption across the following hardware domains:

- Microcontroller (MCU)
- LoRa radio transceiver
- E-ink display
- Secure element and fingerprint sensor
- Storage (flash / secure memory)
- Sensors and peripherals
- Power management circuitry

Each domain is modeled independently and combined into an overall power profile.

---

## Operating States

The simulation evaluates power usage across multiple operating states:

### Idle State
- Device is powered on but inactive.
- Radio is in low-power listen mode.
- Display is static (no refresh).
- Sensors are inactive.

### Active Transaction State
- User initiates a transaction.
- Fingerprint sensor activates.
- Ledger is updated.
- Radio transmits transaction data.

### Mesh Sync State
- Device exchanges ledger updates with nearby nodes.
- Radio operates in transmit and receive cycles.
- Conflict resolution logic executes.
- Storage writes occur.

### Training / Education State
- AI assistant provides guidance.
- Audio or display output is active.
- No radio transmission required.

### Emergency / Recovery State
- Device performs secure wipe or recovery operations.
- Secure element and storage are heavily utilized.
- Radio may broadcast emergency signals.

---

## Power Inputs Modeled

The simulation includes multiple power input sources:

### Battery
- Lithium Iron Phosphate (LiFePO4) battery
- Capacity modeled in mAh and Wh
- Charge and discharge efficiency included

### Solar Input
- Variable solar intensity profiles
- Day/night cycles
- Cloud cover and seasonal variability
- Panel efficiency degradation over time

### Hand-Crank Input
- Short-duration, high-current bursts
- User effort modeled as intermittent events
- Mechanical-to-electrical conversion losses included

---

## Simulation Assumptions

- Devices spend the majority of time in idle or low-power states.
- Transactions occur in short bursts.
- Mesh synchronization is opportunistic, not continuous.
- Display updates are infrequent.
- Security checks are lightweight except during authentication.

All assumptions are conservative to avoid overstating battery life.

---

## Metrics Tracked

The simulation outputs the following metrics:

- Average daily power consumption (mWh/day)
- Peak current draw during transmission
- Battery lifetime without recharge
- Battery lifetime with minimal solar input
- Required hand-crank usage frequency
- Power reserve margin for emergency operations

---

## Failure and Stress Scenarios

The simulation evaluates worst-case scenarios including:

- Extended periods without sunlight
- High transaction volume bursts
- Dense mesh environments with frequent syncs
- Battery degradation over time
- Partial hardware failure (e.g., solar panel loss)

Each scenario tests whether the device can maintain core financial functionality.

---

## Validation Strategy

Simulation results are validated through:

- Bench testing with real hardware components
- Field tests in low-connectivity environments
- Comparison against manufacturer power specifications
- Long-duration soak tests

Discrepancies between simulated and measured results are logged and iteratively refined.

---

## Outputs and Artifacts

The power simulation produces:

- Power usage tables per component
- Daily and weekly consumption graphs
- Battery lifetime estimates
- Recommended duty-cycle configurations
- Design constraints for firmware optimization

These outputs directly inform hardware design, firmware scheduling, and investor documentation.

---

## Investor Relevance

This simulation demonstrates that Seed:

- Can operate for weeks or months without grid power.
- Remains usable in extreme environments.
- Does not rely on continuous charging infrastructure.
- Is financially viable for deployment at scale.

The power budget simulation is a foundational proof point for Seed’s real-world feasibility.

---

## Summary

The power budget simulation ensures that Seed’s vision of an offline-first, financially inclusive device is technically and economically viable. By rigorously modeling energy usage and replenishment, Seed proves it can function reliably where traditional financial systems cannot.

This simulation directly supports hardware decisions, firmware design, field deployment planning, and investor confidence.
