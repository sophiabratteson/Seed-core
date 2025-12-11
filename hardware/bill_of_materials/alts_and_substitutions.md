# Alternatives and Substitutions

This document outlines backup component options for the Seed device hardware bill of materials (BOM). Because Seed is designed for deployment in regions with volatile supply chains, it is critical to identify equivalent components that can replace primary parts without affecting device performance, safety, or compliance.

The objective is to guarantee manufacturability at scale and resilience against shortages, end-of-life components, or regional procurement constraints.

---

# 1. Philosophy Behind Substitutions

- Maintain functional equivalence even if exact components are unavailable.
- Ensure replacements meet minimum electrical, thermal, and safety specifications.
- Prioritize components with global availability or multiple suppliers.
- Allow tiered cost structures: standard, low-cost, and ruggedized options.
- Reduce single-supplier dependency wherever possible.

---

# 2. Core Component Categories With Alternatives

## 2.1 Microcontroller Unit (MCU)

### Primary Option
- ESP32-S3 or ESP32-C3 (integrated WiFi/BT but not required for Seed; chosen for cost and community support)

### Substitutions
- Nordic nRF52840  
  - Pros: ultra-low power, proven in mesh networks  
  - Cons: higher cost  
- STM32L4 series  
  - Pros: extremely low power consumption  
  - Cons: firmware tooling more complex  
- RP2040  
  - Pros: extremely cheap, available everywhere  
  - Cons: no built-in radios, requires external LoRa module

---

## 2.2 LoRa Radio Chipset (long-range mesh communication)

### Primary Option
- Semtech SX1276 / SX1262

### Substitutions
- HopeRF RFM95/96 modules  
- Murata CMWX1ZZABZ module (integrated MCU + LoRa)  
- Silicon Labs Sub-GHz radios (if Semtech availability is limited)

### Notes
- Replacement radio must match the regional frequency plan (433 / 868 / 915 MHz).
- Antenna tuning may require slight redesign for substitutions.

---

## 2.3 E-Ink Display

### Primary Option
- 2.13" e-ink monochrome low-power display

### Substitutions
- Waveshare 2.13" or 2.9" e-ink (same controller family)  
- GoodDisplay GDEH0213B72 or compatible models  
- Optional: memory-LCD display if e-ink supply is constrained  

### Notes
- Substituted display must support partial refresh and ultra-low idle power.

---

## 2.4 Secure Element (hardware security chip)

### Primary Option
- Microchip ATECC608B

### Substitutions
- Infineon OPTIGA Trust M  
- NXP SE050 series  
- STSAFE-A110  

### Notes
- All alternatives must support hardware-protected private key storage and ECC signing.

---

## 2.5 Fingerprint Sensor (optional for early MVP)

### Primary Option
- Capacitive fingerprint module (low-power)

### Substitutions
- Optical fingerprint modules  
- Local PIN-only fallback (no biometric module)  

### Notes
- Biometrics optional in MVP; full device can support modular authentication.

---

## 2.6 Power System Components

### Battery (LiFePO4 or Li-Po)

- Primary: 3.2V or 3.7V 500–1500 mAh cell  
- Alternatives:  
  - EEMB, A123, or Panasonic LiFePO4 cells  
  - Lithium-ion cylindrical cells (protected 14500 or 18650)  
  - NiMH rechargeable pack (rugged environments)

### Charging modules

- Primary: TP4056-based Li-Po charger or CN3058E for solar  
- Alternatives:  
  - BQ24074 (Texas Instruments)  
  - MCP73831 (Microchip)  

---

## 2.7 Solar Input Hardware

### Primary Option
- 5V small solar panel with onboard blocking diode

### Substitutions
- Voltaic Systems 6V rugged solar modules  
- Any 5–6V 0.5–1W panel with stable output  
- USB-powered external solar banks (offline systems)

---

## 2.8 Hand-Crank Generator (optional feature)

### Primary Option
- Compact DC dynamo with rectifier

### Substitutions
- Larger crank modules used in emergency radios  
- Dynamo-based commercial chargers  
- Pedal-powered station add-ons (community kiosks)

---

## 2.9 Enclosure Materials

### Primary Option
- ABS injection-molded shell

### Substitutions
- Polycarbonate (PC) for heat resistance  
- Nylon for ruggedness  
- Bamboo composite for local, sustainable production  
- 3D-printed prototypes (PLA/ABS/PETG)

---

# 3. Regional Substitution Guidance

- Africa: prioritize solar-friendly charging ICs and easily sourced Li-ion cells.  
- South Asia: ensure LoRa frequency compatibility (many regions use 865–867 MHz).  
- LATAM: plastic supply chains are strong; local injection molding feasible.  
- Middle East: heat-resistant enclosures recommended.

---

# 4. Cost-Tiered BOM Approaches

## Ultra-Low-Cost Build
- RP2040 MCU  
- RFM95 radio  
- No fingerprint sensor  
- Simple segment display instead of e-ink  

## Standard Build (recommended MVP)
- ESP32 or nRF52840  
- SX1276 radio  
- E-ink display  
- Secure element chip  

## Rugged Build
- LiFePO4 battery  
- Hardened enclosure  
- Weather-proof charging port  
- High-efficiency solar input  

---

# 5. Compatibility Considerations

When selecting substitutions:

- Electrical characteristics (voltage/current/power rails) must match.  
- SPI/I2C/UART protocols must be supported by the MCU.  
- Radio modules must match legal frequency bands.  
- Replaceable components must fit board footprint unless redesigning PCB.

---

# 6. Recommendations for MVP Procurement

To minimize delays:

- Choose components with at least **two global suppliers**.  
- Prefer modules with **existing libraries** (Arduino, ESP-IDF, Zephyr).  
- Skip biometric hardware for the first physical MVP to reduce complexity.  
- Avoid displays with exotic drivers — stay with well-supported models.

---

# 7. Summary

Alternative components ensure Seed can be produced reliably even in constrained environments. This substitutions matrix also reduces dependence on any single vendor, improves manufacturability, and strengthens Seed’s long-term resilience.

The BOM is intentionally flexible so local manufacturing partners across Africa, South Asia, and LATAM can build Seed devices using locally available components.
