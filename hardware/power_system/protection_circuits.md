# Protection Circuits

This document describes the electrical protection systems required to ensure Seed devices remain safe, durable, and reliable in harsh, low-infrastructure environments. Protection circuits prevent battery hazards, component failure, data corruption, and user-facing safety issues. The design emphasizes resilience, simplicity, and low power consumption.

---

# 1. Objectives of Protection Circuits

- Prevent battery over-voltage, under-voltage, over-current, and thermal damage.
- Protect internal electronics from power surges or unstable generation sources such as hand cranks and low-quality solar panels.
- Reduce risk of fire or catastrophic failure.
- Provide safe shutdown and data protection during brownouts or sudden power loss.
- Ensure device longevity across extreme temperatures and rough handling.
- Maintain user safety even in environments with unreliable power systems.

---

# 2. Protection Requirements

Seed devices operate in communities with limited electrical infrastructure. This creates specific requirements:

## 2.1 Safe charging from solar and hand-crank generators
- Incoming power sources can fluctuate rapidly.
- Solar panels may spike under changing shadows; hand cranks produce irregular voltage.
- Protection modules must stabilize voltage before reaching the battery or internal electronics.

## 2.2 Safe battery handling
- LiFePO4 batteries are chosen for thermal and chemical stability.
- They still require protection against over-charging, deep discharge, and short circuits.

## 2.3 Safe operating environment
- Many users will keep devices in pockets, exposed to the sun, or store them in non-climate-controlled homes.
- Circuitry must withstand temperature swings without failure.

## 2.4 Data integrity during power loss
- The ledger must not become corrupted due to sudden shutdown.
- The system needs brownout detection and a graceful fallback state.

---

# 3. Recommended Protection Components

## 3.1 Battery Protection IC
These chips provide multiple safety layers:
- Over-charge cutoff
- Over-discharge cutoff
- Short circuit protection
- Thermal monitoring
- Current limiting

Common IC families:
- DW01A style protection IC (if using smaller cells)
- Integrated LiFePO4 battery protection modules with BMS boards

## 3.2 Dedicated Charging Controller
A charging controller ensures the battery receives regulated current, even from unstable sources.

Features:
- Constant-current / constant-voltage charging profile
- Automatic charge termination
- Temperature-aware charging
- Input current limiting

Suggested types:
- LiFePO4-specific charging ICs (for correct charging curve)
- Modules compatible with solar input (MPPT or pseudo-MPPT)

## 3.3 Surge Protection and Input Filtering
Protection against unpredictable power input.

Components:
- TVS diodes on power input lines
- Input capacitor banks to smooth unstable voltage
- Series MOSFET for reverse polarity protection
- Over-voltage buck or buck-boost converter

## 3.4 Over-Current Protection (OCP)
Prevents damage if the device experiences a short or overload.

Options:
- Polyfuse (self-resetting fuse)
- Fast-acting electronic fuse (e-fuse)
- Current-sense resistor paired with system shutdown logic

## 3.5 Thermal Management Features
- Ambient temperature sensor tied to charging logic
- Battery internal temperature monitoring
- Charge cutoff below 0°C or above safe thresholds
- Automatic system throttle in high heat

## 3.6 Reverse Polarity Protection
Prevents damage if wires from solar panels or hand cranks are connected incorrectly.

Possible methods:
- Schottky diode (simple, low cost)
- MOSFET-based ideal diode (more efficient, less voltage drop)

---

# 4. Protection Logic Flow

1. Input source (solar or crank) connects to input filtering stage.
2. Surge protection absorbs voltage spikes.
3. Buck or buck-boost regulator stabilizes voltage.
4. Charging controller regulates current into the battery.
5. Battery Protection IC monitors:
   - Over-charge
   - Over-discharge
   - Over-current
   - Temperature
6. Device power rail passes through:
   - Reverse polarity protection
   - Over-current fuse or e-fuse
7. Power manager firmware reads system voltages and performs:
   - Brownout detection
   - Safe shutdown routines
   - Ledger checkpointing before cutoff

---

# 5. Firmware Integration With Protection Circuits

To maintain data integrity and prevent hardware damage, firmware integrates with the protection system:

- Poll battery voltage and temperature periodically.
- Trigger write-ahead ledger checkpoint if voltage drops below threshold.
- Halt radio transmission during under-voltage states.
- Disable charging during extreme temperature conditions.
- Enter low-power mode when the battery is critically low.
- Provide warnings or icons on the e-ink display if unsafe conditions occur.

---

# 6. Testing and Validation Requirements

Protection circuits must undergo rigorous testing:

## 6.1 Electrical tests
- Over-voltage injection tests
- Reverse polarity tests
- Short-circuit simulation
- Battery deep-discharge cycling
- Load step response tests

## 6.2 Environmental tests
- High-temperature idle tests
- Low-temperature stop-charge tests
- Humidity and dust exposure
- Shock and vibration testing

## 6.3 User interaction tests
- Accidental wire misconnection
- Unsafe or unstable charging source use
- Rapid power cycling

---

# 7. Failure Modes and Mitigation

## Input power spikes
- Mitigation: TVS diodes, buck regulators.

## Over-charging
- Mitigation: battery IC cutoff logic, firmware disable-charge command.

## Deep discharge
- Mitigation: battery protection IC prevents operation below safe voltage.

## Overheat during charge
- Mitigation: temperature-aware charging controller.

## Battery swelling or degradation
- Mitigation: firmware usage logs and cycle count indicators.

## Sudden power loss causing ledger corruption
- Mitigation: brownout detect and checkpointing logic.

---

# 8. Future Enhancements

- Optional supercapacitor buffer for safer shutdown.
- More advanced MPPT charging for high-efficiency solar collection.
- Tamper detection baked into power subsystem.
- Smart BMS with encrypted communication between protection chip and MCU.
- System health analytics to predict battery replacement needs.

---

# 9. Summary

Robust protection circuits are essential for Seed devices to operate reliably in low-infrastructure environments. By combining hardware-level safety, firmware controls, and fail-safe power paths, the Seed device can withstand electrical hazards, maintain data integrity, and ensure a long, safe operational life for users who rely on it as a primary financial tool.
