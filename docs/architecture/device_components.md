# Seed Architecture: Device Components

This document describes every major hardware subsystem within the Seed device. Each section explains what the component is, why it exists, how it interfaces with other modules, and any constraints that guide its selection. This file serves as a reference for engineers evaluating feasibility, building prototypes, or preparing for manufacturing.

---

# 1. Core Processing Unit (MCU)

## Description
The MCU executes Seed's firmware, manages the mesh network stack, maintains the ledger, handles security operations, and controls the display and power-management systems.

## Candidate Components
- ESP32-S3 (Wi-Fi + BLE, dual-core, low power)
- nRF52840 (BLE + sub-GHz possibilities, ultra-low-power)
- STM32L4/L5 series (high reliability, very low power)

## Responsibilities
- Runs the ledger engine and transaction validation
- Executes AI micro-model for behavioral coaching
- Handles radio communication events
- Manages display refreshes for e-ink
- Coordinates secure element requests (signing, identity)
- Schedules sleep/wake cycles for ultra-low power usage

## Constraints
- Must run on minimal RAM
- Must support low-power modes
- Must tolerate high environmental variability
- Must support OTA firmware updates (optional future feature)

---

# 2. Radio and Mesh Networking Subsystem

## Description
This subsystem enables long-range, low-bandwidth communication between Seed devices without internet or cell service.

## Candidate Radio Modules
- Semtech SX1276/SX1262 (LoRa)
- RAK4600 or RAK3172 modules
- Ai-Thinker Ra-01 or Ra-02 modules

## Responsibilities
- Sends and receives small data packets
- Maintains peer discovery and neighbor table
- Synchronizes ledgers via gossip-based protocol
- Handles retries, acknowledgments, and timeouts

## Constraints
- Extremely low bitrate (ideal for micro-ledger packets only)
- Must comply with regional ISM band restrictions (868/915 MHz)
- Requires proper antenna tuning for real-world range

---

# 3. Power System

## Description
Seed uses a hybrid off-grid power design enabling use in locations without reliable electricity.

## Components
- LiFePO4 (LFP) rechargeable battery
- Solar panel (1–3 W depending on variant)
- Hand-crank generator input
- Charge controller (MPPT recommended)
- Battery protection circuitry (BMS)
- Power regulation (buck/boost converters)

## Responsibilities
- Provide safe and renewable power
- Support weeks of standby time
- Safely charge from inconsistent energy sources

## Constraints
- Battery must withstand high heat and physical handling
- Charging system must prevent overcurrent and overvoltage
- Device must be functional even at low battery levels

---

# 4. Display System (E-Ink)

## Description
The e-ink display provides ultra-low-power readability in sunlight and allows a simple, durable UI.

## Candidate Components
- 2.1"–2.9" black-and-white e-ink module (IL0373, UC8151 drivers)

## Responsibilities
- Render ledger summaries
- Show transaction details and confirmations
- Provide onboarding instructions and help messages

## Constraints
- Slow refresh rate (UI must be optimized)
- Must work in varying temperatures
- Must minimize redraws to save power

---

# 5. Secure Element / Cryptographic Module

## Description
A secure hardware enclave stores the device’s private keys, signs transactions, and ensures identity integrity.

## Candidate Components
- Microchip ATECC608B
- NXP EdgeLock SE050
- Infineon OPTIGA Trust M

## Responsibilities
- Sign transactions locally (no private keys exposed)
- Store secrets and trust score integrity keys
- Provide secure boot chain
- Help prevent device-level impersonation or tampering

## Constraints
- Must resist physical extraction
- Must be programmable in factory provisioning
- Must draw minimal power during cryptographic operations

---

# 6. Fingerprint / Biometric Authentication

## Description
A simple capacitive fingerprint module provides user authentication without requiring ID documents.

## Candidate Modules
- Generic capacitive fingerprint sensor
- FPC1020 series
- EgisTec modules

## Responsibilities
- Authenticate user offline
- Protect spending and access to ledger
- Trigger emergency “fake mode” or wipe sequence if needed

## Constraints
- Must operate reliably with dusty or sweaty hands
- Very low power standby mode required

---

# 7. Storage (Flash + Secure Backup)

## Description
Internal flash stores ledger state, user settings, trust score history, and AI personalization data.

## Components
- On-chip flash (MCU integrated)
- External SPI flash (2–8 MB typical)

## Responsibilities
- Store transaction history
- Store AI micro-model weights and behavior profiles
- Provide backup snapshots for rollback and recovery

## Constraints
- Writes must be minimized to extend flash lifespan
- Must be encrypted with secure element–generated keys

---

# 8. Input System (Buttons or Capacitive Controls)

## Description
Minimal input hardware keeps the device simple and durable.

## Components
- Up/down/select buttons
- Side slider for emergency mode activation
- Optional capacitive touch pads

## Responsibilities
- Navigate simple UI on e-ink
- Confirm or reject transactions
- Trigger SOS/fake ledger screen

## Constraints
- Should work while wearing gloves
- Must be robust and dust-resistant

---

# 9. Antenna System

## Description
The LoRa antenna determines real-world communication range.

## Candidate Components
- PCB trace antenna
- External whip antenna
- Ceramic antenna modules

## Responsibilities
- Enable long-range mesh communication
- Maintain stable packet transmission under mobility

## Constraints
- Must be tuned for correct ISM band
- Must avoid interference from battery and enclosure

---

# 10. Enclosure and Mechanical Design

## Description
The physical housing protects the device and affects durability, thermal behavior, and user experience.

## Considerations
- Reinforced plastic or composite materials
- Rubberized edges for drop protection
- Gasket sealing for dust and water resistance
- Easy-open design for repairability

## Constraints
- Must withstand heat, dust, and moisture
- Must survive repeated charging through solar and hand crank inputs
- Must accommodate varying component tolerances in mass production

---

# 11. Expansion and Future-Proofing

## Optional Future Additions
- Low-power microphone for voice-based interface
- Bluetooth pairing to partner devices
- Vibration motor for discrete alerts
- NFC for local peer-to-peer transfers

---

# 12. Internal Data Buses and Wiring

## Description
Defines how components talk to each other electrically.

## Interfaces
- I2C (sensors, secure element)
- SPI (e-ink, flash memory)
- UART (debugging, radio modules)
- GPIO (buttons, interrupts)

## Constraints
- Must minimize crosstalk and power leakage
- Must maintain clean routing on PCB layout

---

# 13. Summary Table (High-Level)

| Subsystem | Purpose | Example Components |
|----------|----------|--------------------|
| MCU | Core logic, mesh stack, ledger | ESP32-S3, STM32L5 |
| Radio | Offline communication | SX1276, RAK4600 |
| Power | Battery + solar + crank charging | LiFePO4 + BMS |
| Display | Ultra-low power UI | 2.9" E-Ink |
| Secure Element | Identity & cryptography | ATECC608B |
| Storage | Ledger + metadata | SPI flash |
| Biometrics | User authentication | Capacitive fingerprint |
| Inputs | UI control | Buttons/sliders |
| Enclosure | Protection | Ruggedized plastic |
| Antenna | Connectivity | Whip/PCB/ceramic |

---

# 14. Integration Notes

- The power subsystem must be tightly coupled with MCU sleep scheduling.
- Radio and secure element operations must coordinate for transaction signing.
- Display refreshes should be batched to minimize power draw.
- Firmware must include drivers for all components and operate under extreme power constraints.

---

# 15. Open Questions

- Should the device support replaceable batteries?
- Should e-ink be front-lit or unlit?
- Should antenna be internal or external?
- Should we add optional Bluetooth for provisioning?
