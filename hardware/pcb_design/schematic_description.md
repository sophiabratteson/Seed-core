# Schematic Description

This document provides a detailed, high-level description of the Seed device schematic. It explains the major electrical subsystems, how they interconnect, and why each component is chosen. This description is written to support hardware design, investor diligence, and early manufacturing planning.

---

# 1. Overview of the Electronics Architecture

The Seed device schematic is built around four major subsystems:

- Processing Core (MCU or SoC)
- Radio + Mesh Communication System
- Power Management + Energy Harvesting
- Secure Storage + Sensor Subsystems

All components interconnect via a combination of SPI, I2C, GPIO, and power rails. The architecture is optimized for extremely low power consumption, offline-first operation, durability, and support for a mesh financial ledger.

---

# 2. Processing Core

The Seed device uses a low-power microcontroller capable of real-time radio operation and local ledger computation.

## MCU Block Connections
- SPI bus shared with:
  - LoRa Radio Module (SX1262/SX1276)
  - Secure Element Chip (ATECC608 or equivalent)
- I2C bus shared with:
  - Battery Fuel Gauge
  - Environmental sensors (if included)
- Digital GPIO:
  - Input buttons
  - Fingerprint sensor interrupt
  - E-Ink busy/ready signals
- PWM/Timer:
  - Optional haptic motor
- UART:
  - Debug/programming port

The MCU is placed centrally to minimize trace length and reduce noise on high-speed buses.

---

# 3. Radio + Mesh Communication Subsystem

The LoRa transceiver is the core of Seed’s offline mesh.

## Radio Module (SX1262/SX1276)
- SPI bus to MCU
- DIO0/DIO1 interrupt pins to MCU for packet events
- RF output routed through:
  - Low-pass filter or matching network
  - External antenna connector (U.FL or SMA)
- Power rail connected through radio_enable MOSFET for duty-cycling

## Antenna System
- 50-ohm controlled-impedance RF trace
- Ground stitching vias surrounding antenna feed line
- Antenna tuning components (capacitors/inductors) for regional frequencies (433/868/915 MHz)

---

# 4. E-Ink Display Interface

The E-Ink module connects directly to the MCU via SPI.

## Display Signals
- SPI_CLK, SPI_MOSI, SPI_MISO (shared bus)
- CS (Chip Select)
- DC (Data/Command Select)
- RESET
- BUSY (status pin)

## Power Control
- Separate 3.3V rail, optionally switched using a load switch
- Capacitor bank to stabilize E-Ink refresh current

The E-Ink panel is intentionally low power, consuming energy only during updates.

---

# 5. Secure Element + Authentication

A dedicated hardware security module ensures that each Seed device is cryptographically unique.

## Secure Element Connections
- I2C SDA/SCL to MCU
- Power rail filtered with ferrite bead
- Optional tamper-detection GPIO lines
- Private key stored internally (never readable)

This component handles:
- Message signing
- Device identity keys
- Ledger integrity verification

---

# 6. Fingerprint Sensor Interface

The capacitive fingerprint reader connects as follows:

- UART or SPI communication to MCU
- Interrupt pin (finger detected)
- 3.3V power rail with local decoupling capacitors

The schematic includes:
- ESD protection diodes for the sensor ring
- Shielding recommendations for analog signal stability

---

# 7. Power System

The power section manages solar input, hand-crank charging, and battery protection.

## Battery
- LiFePO4 cell connected through:
  - Protection IC (overcharge/overdischarge)
  - Fuel gauge via I2C
- JST connector for modularity

## Charging Inputs
- Solar panel input through MPPT or simple DC-DC charger
- Hand-crank input through:
  - Bridge rectifier
  - Input capacitor smoothing
  - DC-DC boost converter

## Regulators
- 3.3V buck/boost LDO powering:
  - MCU
  - Radio
  - E-Ink display
  - Sensors
- Sleep-mode power domain for ultra-low consumption

---

# 8. Memory and Storage

Seed uses a combination of MCU flash and optional external storage.

## External Storage (optional)
- SPI Flash chip
- Write-protected region for firmware
- Dedicated area for offline ledger checkpoints

Decoupling capacitors placed close to VCC/GND pins per datasheet.

---

# 9. Input Buttons

Buttons are wired simply:

- GPIO with pull-up resistor (internal or external)
- ESD protection diode array
- Debounce capacitor (or debounced in firmware)

This supports navigation in the UI and emergency actions.

---

# 10. Connectors and Programming Interfaces

## SWD / JTAG Header
- For MCU flashing and debugging
- Usually a 5-pin or 10-pin header footprint

## USB-C (optional)
- For charging
- For firmware updates
- Includes CC resistors for USB configuration

USB data lines include:
- ESD diodes
- Controlled trace routing

---

# 11. Grounding and Noise Management

The schematic enforces good RF and digital integrity practices:

- Separate analog/digital grounds if needed
- Ground pour under the MCU except under RF sections
- RF keep-out area under antenna
- Multiple decoupling caps near every IC (0.1 µF + 1 µF)

This improves mesh range and device reliability.

---

# 12. System-Level Schematic Flow

The schematic shows the following block flow:

1. Power system generates stable 3.3V.
2. MCU receives power and boots secure firmware.
3. Secure Element initializes identity keys.
4. MCU communicates via SPI to:
   - LoRa radio for mesh operations
   - E-Ink display for UI updates
5. Fingerprint sensor authenticates user input.
6. Ledger stored in MCU flash or external memory.
7. Radio exchanges packets with nearby devices.
8. All blocks follow low-power design to maximize battery life.

---

# 13. Notes for PCB Layout Handoff

The schematic includes:
- Footprints for each component
- Reference designators (U1, U2, C5, R10, etc.)
- Power domains clearly labeled
- Firmware-related pins exposed for programming
- Test points for:
  - Battery rail
  - 3.3V rail
  - RF output
  - Debug UART

This schematic forms the basis for PCB layout and prototype manufacturing.

---

# 14. Summary

This schematic provides a complete electrical architecture for the Seed offline financial device. It balances stability, security, low cost, and low energy consumption while enabling long-range mesh communication. Every component in the schematic is chosen to support Seed’s overarching goals: trust, accessibility, and resilience in environments with unreliable or nonexistent infrastructure.
