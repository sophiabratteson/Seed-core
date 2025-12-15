# Power Consumption Test Specification

This document defines how Seed devices are tested to verify power efficiency, battery longevity, and reliability across real-world usage scenarios. Power performance is a critical success factor for Seed, as the device is designed to operate in environments with limited or intermittent access to electricity.

---

## 1. Objectives

The goals of power consumption testing are to:

- Validate that Seed devices meet minimum battery life targets
- Ensure safe operation under low-power and high-demand conditions
- Measure power usage across all device modes
- Confirm compatibility with solar and hand-crank charging inputs
- Identify firmware or hardware optimizations for power efficiency

---

## 2. Power Architecture Under Test

Power tests apply to the full device power stack, including:

- LiFePO4 battery system
- Power management integrated circuit (PMIC)
- Solar charging input
- Hand-crank charging input
- E-ink display
- LoRa radio module
- Secure element and fingerprint sensor
- Microcontroller unit (MCU)
- Non-volatile storage

---

## 3. Test Environments

Power tests are conducted under the following conditions:

### Environmental Conditions
- Ambient temperatures: 0°C, 25°C, 45°C
- Indoor and outdoor testing
- Static and mobile usage scenarios

### Power States
- Fully charged battery
- Mid-charge battery
- Low battery threshold
- Battery recovery after depletion

---

## 4. Device Operating Modes Tested

Each operating mode is tested independently and in combination:

- Idle (screen static, radio listening)
- Transaction creation
- Ledger synchronization
- Mesh message relay
- Group savings updates
- Trust score calculation
- AI assistant interaction
- Secure authentication (fingerprint scan)
- Emergency wipe mode
- Firmware update mode
- Deep sleep / power-saving mode

---

## 5. Test Methodology

### Measurement Tools
- Inline current meters
- Battery fuel gauge readings
- Internal PMIC telemetry
- External logging equipment where available

### Procedure
1. Fully charge device
2. Initialize test mode
3. Execute defined operation
4. Measure current draw (mA) and voltage (V)
5. Record duration and total energy consumption
6. Repeat across temperature and battery states
7. Aggregate results across multiple devices

---

## 6. Power Budget Metrics

The following metrics are recorded and evaluated:

- Average current draw per operation
- Peak current draw
- Energy per transaction (mWh)
- Energy per sync event
- Idle drain per hour
- Standby drain per day
- Battery life projection (days/months)
- Charge efficiency (solar and hand-crank)

---

## 7. Battery Lifetime Testing

Battery lifetime is evaluated using:

- Continuous usage simulations
- Intermittent usage simulations
- Worst-case stress scenarios
- Long-term idle storage tests
- Repeated charge/discharge cycles

Battery degradation is tracked over time to estimate usable lifespan.

---

## 8. Charging Input Validation

### Solar Input Tests
- Charging rate under full sun, partial sun, and shade
- Recovery time from low battery
- Solar-only sustained operation feasibility

### Hand-Crank Input Tests
- Energy generated per minute of cranking
- Minimum crank duration for critical operations
- User fatigue impact modeling

---

## 9. Failure and Edge Case Testing

Power resilience is tested under:

- Sudden power loss
- Brownout conditions
- Partial charge interruptions
- Faulty charging input
- Over-temperature conditions
- Repeated low-battery resets

Device behavior must remain safe and data-consistent.

---

## 10. Acceptance Criteria

The device passes power consumption testing if:

- Battery life meets or exceeds design targets
- No data corruption occurs during power loss
- Charging systems operate safely and efficiently
- Thermal limits are not exceeded
- Power usage remains within defined budgets
- Device recovers cleanly from low-power states

---

## 11. Reporting and Documentation

Test results are documented with:

- Raw measurement logs
- Aggregated summaries
- Charts and trend analysis
- Identified optimizations
- Firmware tuning recommendations

Reports are stored alongside hardware and firmware versions tested.

---

## 12. Investor and Field Readiness Summary

Power consumption testing ensures Seed devices are:

- Economically viable at scale
- Practical for low-infrastructure regions
- Durable under real-world conditions
- Capable of long-term autonomous operation

Efficient power usage directly supports Seed’s mission of enabling financial access anywhere, without dependence on constant electricity or internet connectivity.
