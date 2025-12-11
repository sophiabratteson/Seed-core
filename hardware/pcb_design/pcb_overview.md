# PCB Overview

This document provides a high-level technical and strategic overview of the Seed PCB (Printed Circuit Board). The PCB serves as the physical backbone that integrates Seed’s low-power computing core, radio system, security hardware, power subsystem, sensors, and user interface into a rugged, ultra-reliable offline financial device. The PCB design emphasizes manufacturability, thermal stability, repairability, and long-term field durability in low-resource environments.

---

## 1. Design Goals

- Minimize power consumption for operation in low-energy environments.
- Ensure reliable operation without dependence on mobile networks or internet.
- Support long-range mesh communication using LoRa-based radios.
- Provide strong hardware security through an onboard secure element.
- Maintain compatibility with e-ink displays for readability and battery longevity.
- Be manufacturable at low cost and scalable to mass production.
- Tolerate heat, dust, humidity, and physical stress common in developing regions.
- Prioritize repairability, modularity, and straightforward diagnostics.

---

## 2. PCB Form Factor and Layout Strategy

- Single-board layout optimized for small handheld enclosure.
- Dimensions defined around the display footprint plus battery cavity.
- Component placement prioritizes thermal isolation for battery and radio modules.
- Radio section positioned at top edge for maximum antenna clearance.
- Secure element and MCU placed centrally to reduce trace length and EMI.
- Power subsystem grouped on one edge for efficient routing and minimal noise.
- Test pads exposed on backside for manufacturing diagnostics.

---

## 3. Core System Components

### Microcontroller Unit
- Ultra-low-power MCU (example: ESP32-C3 or ARM Cortex-M0+/M4-class device).
- Integrates CPU, RAM, flash, and hardware cryptography acceleration.
- Supports deep sleep modes for ultra-long battery life.

### LoRa Radio Module
- SX1262 or SX1276-based transceiver.
- Integrated low-noise amplifier and power amplifier for long-range performance.
- Connected to external or PCB trace antenna for optimized mesh communication.

### Secure Element Chip
- Hardware enclave for cryptographic keys, signatures, and identity storage.
- Provides tamper detection and protection for sensitive ledger data.
- Ensures Seed devices cannot be cloned or impersonated.

### E-Ink Display Connector
- 24-pin or 32-pin FPC connector depending on display selection.
- Supports partial refresh, grayscale modes, and low-power updates.

### Capacitive Fingerprint Sensor Interface
- UART or SPI connection depending on module.
- Isolated ground reference for clean sensor performance.

### Buttons and Input Hardware
- Haptic feedback buttons or sealed membrane tact switches.
- Debounce filtering done in firmware with noise-aware routing.

---

## 4. Power Subsystem Layout

- LiFePO4 or Li-ion battery connector with built-in protection.
- Solar input stage with MPPT-compatible charging IC.
- Hand-crank input port routed through rectifier and charge controller.
- 3.3V buck/boost regulator optimized for ultra-low dropout.
- Power rails isolated per subsystem:
  - MCU rail
  - Radio rail
  - Display rail
  - Secure element rail

---

## 5. PCB Layer Stackup

- 4-layer board recommended for EMI performance and clean routing.
- Layer breakdown:
  - Top: Components and high-speed signals.
  - Inner 1: Ground plane.
  - Inner 2: Power distribution and sensitive traces.
  - Bottom: Secondary routing and diagnostics.

This structure supports:
- Stable RF performance.
- Reduced interference on cryptographic operations.
- Cleaner display voltages.

---

## 6. EMI and RF Considerations

- Controlled impedance traces for antenna feedline.
- Ground fencing around radio section.
- Clear no-copper zones under antenna.
- Separation between radio and high-current charging circuits.
- Decoupling capacitors placed directly adjacent to radio IC pins.

---

## 7. Security-Related Hardware Layout

- Secure chip traces isolated from general MCU I/O to reduce tamper risk.
- Short traces to prevent side-channel attacks.
- Independent power filtering for secure element.
- Tamper switch or conductive mesh pads optional for future revisions.

---

## 8. Manufacturability and Assembly

- All surface-mount technology (SMT) components positioned on top layer for low-cost assembly.
- Passive components standardized to reduce sourcing complexity.
- Large test pads for:
  - Power rail measurement
  - UART debugging
  - SWD/JTAG programming
- Designed for reflow soldering consistency.
- Clear silkscreen labeling for field repair.

---

## 9. Environmental Durability Features

- Conformal coating recommended for tropical regions.
- High-temperature components chosen for equatorial climates.
- Shielding can added over radio and secure element.
- Reinforced mounting points for enclosure vibration tolerance.

---

## 10. Future PCB Expansion Options

- Additional sensor footprints (temperature, accelerometer, NFC).
- Expansion port for peripheral modules.
- Alternate radio footprints (Sub-GHz + 2.4GHz hybrid).
- Lower-cost "Lite" PCB for mass adoption deployments.
- High-capacity “Pro” version for enterprise and NGO partners.

---

## 11. Summary

This PCB is engineered as an ultra-resilient offline financial device optimized for harsh environments and long-term deployment. Its design integrates low power, strong security, reliable mesh communication, and manufacturability in a compact, durable form factor. The PCB serves as the foundation for Seed’s broader mission: enabling financial access for billions without reliance on traditional infrastructure.
