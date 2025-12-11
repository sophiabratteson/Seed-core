# Bill of Materials (BOM) Overview

This document summarizes the complete Bill of Materials (BOM) required for the Seed prototype and guides the transition toward a manufacturable product. It outlines major subsystems, critical components, cost categories, vendor considerations, and scalability factors relevant to both engineering teams and investors.

Seed’s hardware architecture is intentionally designed to be low-cost, ultra-reliable, repairable, and optimized for low-connectivity environments. The BOM reflects modules that support long battery life, offline communication, security, and durability.

---

# 1. BOM Purpose and Philosophy

Seed is engineered for:
- Affordability in low-income regions
- Ruggedness in harsh environments
- Low power consumption
- Secure offline financial operations
- Long-term field sustainability

The BOM is structured to:
- Identify every major hardware subsystem
- Provide cost transparency for prototype vs. mass production
- Enable modular replacement and field repair
- Support certification and regulatory compliance

---

# 2. High-Level Component Categories

Seed’s BOM is grouped into the following categories:

- Core compute module (MCU + memory)
- Radio subsystem (LoRa + mesh networking)
- Display subsystem (e-ink low-power display)
- Power subsystem (battery, solar, hand-crank interface)
- Security subsystem (secure element, fingerprint sensor)
- I/O subsystem (buttons, audio prompts if applicable)
- Storage subsystem (flash, EEPROM)
- Mechanical enclosure components
- Supporting passives and PCB components

Each subsystem is detailed in separate BOM sections with cost ranges and recommended suppliers.

---

# 3. Core Compute Components

Seed’s compute subsystem includes:
- Primary microcontroller (MCU) with ultra-low-power modes
- Optional coprocessors for crypto acceleration
- Integrated or external memory (Flash, FRAM, EEPROM)

Prototype options:
- ESP32-S3, nRF52840, STM32L4 series
- External SPI flash (2 MB to 8 MB)
- Crystal oscillators and voltage regulators

Investor relevance:
- MCU choice determines power consumption, security capabilities, and firmware complexity.

---

# 4. Radio and Networking Components

To achieve long-range offline communication, Seed uses:
- Semtech LoRa transceiver (SX1262 or SX1276 family)
- Matching LoRa antenna (tuned to 868 MHz or 915 MHz depending on region)
- RF front-end matching network components

Key features:
- Long-range peer-to-peer communication
- Mesh synchronization without internet
- Ultra-low-power sleep/receive cycles

Investor relevance:
- Radio subsystem enables Seed's defining feature: financial services without connectivity infrastructure.

---

# 5. Display Components (E-Ink Subsystem)

Seed uses e-ink displays for:
- Minimal power drain (image persists without power)
- High sunlight readability
- Durability and simplicity

Prototype options:
- 2.13-inch or 2.9-inch Bi-stable e-ink display
- SPI display driver (IL3897 or similar)

Supporting components:
- Level shifters
- Display power regulator

Investor relevance:
- E-ink drastically improves battery life and usability in remote regions.

---

# 6. Power Subsystem Components

The power subsystem includes:
- LiFePO4 or Li-ion rechargeable battery
- Battery protection IC
- Charge controller (solar, hand-crank, or USB input)
- Voltage regulation chain (buck and LDO regulators)

Optional power harvesting components:
- Small solar panel (1–2 W)
- Hand-crank generator input module

Investor relevance:
- Long operating life with minimal infrastructure makes Seed usable in rural and disaster environments.

---

# 7. Security Subsystem Components

Security hardware includes:
- Secure element chip (ATECC608B or similar)
- Fingerprint sensor (capacitive)
- Tamper-detection mechanisms

Functions:
- Private key storage
- Encrypted communication
- User authentication
- Ledger integrity protection

Investor relevance:
- Hardware security is critical for trust, fraud-prevention, and regulatory compliance.

---

# 8. Storage and Memory Components

Typical items include:
- External SPI NOR flash for ledger storage
- FRAM for critical low-latency writes
- EEPROM for configuration data

Investor relevance:
- Sufficient storage ensures robust offline operation and recoverability.

---

# 9. Mechanical and Enclosure Components

Components include:
- Polycarbonate or ABS outer shell
- Internal support frame
- Shock padding
- Screen window
- Buttons or keypad elements
- Screws, seals, moisture-resistant lining

Investor relevance:
- Rugged construction extends device lifetime and reduces replacement cost.

---

# 10. PCB Components and Supporting Passives

Includes:
- PCB layers and materials
- Resistors, capacitors, diodes
- Power switches and MOSFETs
- Connectors (battery JST connector, programming header)
- Test pads for manufacturing

Investor relevance:
- PCB design efficiency directly affects final unit cost and manufacturability.

---

# 11. Prototype vs. Mass-Production BOM Considerations

Prototype costs are higher but allow rapid iteration.

Prototype efficiencies:
- Off-the-shelf modules
- Development boards
- Breakout PCBs

Mass-production efficiencies:
- Custom PCB integrating all subsystems
- Bulk component purchasing
- Optimized power and RF routing

Investor relevance:
- Demonstrates a realistic path from prototype to scalable production.

---

# 12. Cost-Level Summary (Estimated)

Prototype unit cost (per device):
- Low-end: 60–90 USD
- Mid-range: 90–130 USD
- High-end rugged prototype: 150–200 USD

Expected mass-production cost (per device at scale):
- Tier 1 (100k+ units): 18–35 USD
- Tier 2 (1M+ units): 12–25 USD

Drivers of cost reduction:
- PCB integration
- Component consolidation
- Volume purchasing
- Reduced mechanical complexity

---

# 13. Supplier Strategy

Recommended categories of suppliers:
- Semtech and RAK Wireless (radio subsystem)
- Waveshare and Good Display (e-ink)
- Microchip (secure elements)
- JLCPCB / PCBWay (manufacturing)
- AliExpress / LCSC (low-volume components)
- Mouser / DigiKey (high-quality sourcing)

Supplier selection considerations:
- Radio module certification
- Regional LoRa frequency compliance
- Export regulations for cryptographic hardware
- Battery transport rules

---

# 14. Risks and Mitigations

Risks:
- Component shortages (MCUs, LoRa chips)
- RF interference or regulatory limits
- Power subsystem inefficiencies
- Security vulnerabilities in hardware supply chain

Mitigations:
- Multiple approved vendor lists (AVL)
- Alternate chipsets for key subsystems
- Modular PCB sections for drop-in replacements
- Secure element authenticity checks

---

# 15. Summary

This BOM overview defines the full hardware structure of Seed and lays the foundation for detailed sourcing, cost optimization, and manufacturability planning. It enables investors and hardware partners to evaluate Seed’s feasibility, cost trajectory, and readiness for large-scale deployment.

Seed’s design philosophy ensures that even the earliest prototype logically evolves into a scalable, durable, secure device capable of supporting global offline financial access.
