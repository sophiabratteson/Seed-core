# Hardware Prototype Plan

## Overview
This document outlines the plan for building the first hardware prototype of the Seed device. The goal of this phase is not to achieve final industrial design, but to validate core technical assumptions: offline communication, local ledger operations, low-power display, secure identity, and modular expandability. The prototype is intended to guide early engineering decisions and de-risk the system before progressing to custom PCBs or enclosure manufacturing.

## Objectives
- Validate that two Seed devices can communicate offline using LoRa.
- Demonstrate the mesh-based ledger synchronization workflow.
- Test e-ink display functionality with minimal power consumption.
- Evaluate security components including secure element and fingerprint sensor.
- Measure power draw across realistic usage cycles.
- Verify radios can communicate across expected rural and village-scale distances.
- Produce an engineering reference for future PCB development.

## Prototype Architecture
### Core modules included in the prototype
- Microcontroller module (ESP32-S3, ESP32, or nRF52 family depending on availability).
- LoRa radio module (SX1262 or SX1276).
- Small e-ink display module for UI.
- LiPo or LiFePO4 battery + charging circuit.
- Optional solar or hand-crank input for power evaluation.
- Secure element dev board for key storage.
- Optional fingerprint sensor module.
- Breadboard or perfboard for early wiring.

### What will not be included in this prototype
- Full enclosure design.
- Optimized antenna tuning.
- Ruggedization or heat-resistant materials.
- Power-optimized PCB.
- Full UX/UI software stack.

These features will be addressed in the second and third hardware prototype cycles.

## Prototype Components and Justification
### Microcontroller
- Purpose: Runs ledger engine, handles radio communication, UI logic.
- Requirements: Low power, multiple sleep modes, secure boot support, enough RAM for local ledger.
- Candidates: ESP32-S3 DevKit, LILYGO LoRa32, RAK WisBlock base modules.

### Radio Module (LoRa)
- Purpose: Enables long-range, low-bandwidth, offline communication.
- Requirements: Support for ISM bands (868/915 MHz), proven mesh behavior, adjustable spreading factors.
- Candidates: SX1262, SX1276 modules, LILYGO LoRa32 built-in radios.

### Display (E-Ink)
- Purpose: Zero-power static display suitable for low-energy environments.
- Requirements: 2.13–2.9 inch panel, partial refresh support.
- Candidates: Waveshare e-ink modules, Heltec Vision boards.

### Power System
- Purpose: Validate power longevity and recharge strategies.
- Elements: LiPo/LiFePO4 battery, solar panel, hand-crank generator, BMS charge controller.
- Key tasks: Measure runtime, test survival in heat, assess charge rates.

### Security Hardware
- Secure element: ATECC608 or equivalent.
- Biometric sensor: Capacitive fingerprint module for local authentication.
- Purpose: Validate integration with ledger signing and user identity.

### Optional Sensors
- Environmental sensors for future features (temperature, motion, tamper-detection).

## Build Phases
### Phase 1: Bench-top Prototype
- Assemble microcontroller, radio, display, and battery on breadboard.
- Verify continuous power flow and radio communication.
- Run basic send/receive test between two devices.
- Confirm display updates and sleep mode behavior.

### Phase 2: Functional Prototype
- Integrate secure element and fingerprint sensor.
- Add basic UI workflow (unlock device, show balance, send transaction).
- Validate mesh sync across two or more devices.
- Measure power usage in different states.

### Phase 3: Field Prototype
- Move components onto perfboard for durability.
- Add temporary 3D-printed or laser-cut case.
- Conduct outdoor mesh tests, distance tests, and power stress tests.
- Record performance metrics for engineering review.

## Testing Plan
### Communication Testing
- Range tests in open field, rural areas, and indoor block scenarios.
- Packet loss rates under various spreading factors.
- Multi-device broadcasting tests to simulate group savings.

### Ledger and Sync Testing
- Validate deterministic ordering and conflict resolution.
- Test offline creation of transactions and delayed syncing.
- Add controlled conflict cases to ensure stability.

### Power Testing
- Battery runtime under typical daily workload.
- Solar-only recharge test.
- Sleep current measurement.

### Security Testing
- Validate signature generation using secure element.
- Test device unlock with fingerprint.
- Evaluate tamper detection behavior.

## Risks and Mitigations
### Risk: Radio range insufficient in dense environments
Mitigation: Adjust antenna design, use higher spreading factors, test alternate chipsets.

### Risk: Power consumption too high
Mitigation: Optimize sleep cycles, reduce display refresh frequency, evaluate alternative MCUs.

### Risk: Secure element integration complexity
Mitigation: Use established dev boards with sample libraries before PCB integration.

### Risk: E-ink display latency
Mitigation: Use partial refresh or simpler UI animations.

### Risk: Thermal issues in hot regions
Mitigation: Shift from LiPo to LiFePO4, add vent design in next enclosure version.

## Success Criteria
- Two prototype devices can sync ledgers offline without error.
- Mesh networking works over at least 200–400 meters in open field.
- Display remains readable in sunlight and requires minimal power.
- Battery lasts for 3–7 days under realistic use.
- Secure signing and authentication function reliably.
- Prototype reveals clear next steps for PCB design.

## Deliverables
- Fully assembled hardware prototypes (2–3 units).
- Performance data: range, power usage, sync latency.
- Engineering notes for PCB Version 1.
- Recommendations for enclosure ergonomics.
- Updated risk assessment based on prototype results.
