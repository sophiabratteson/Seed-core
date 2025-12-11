# Prototyping Plan

This document outlines the step-by-step plan for developing Seed’s hardware prototype from early breadboard experiments to a production-ready alpha device. The goal is to validate the electronics, enclosure ergonomics, power system behavior, and manufacturability before mass production.

## 1. Objectives of the Prototype Phase

- Validate all critical hardware systems under real-world conditions.
- Test LoRa mesh communication reliability and range.
- Confirm solar, hand-crank, and battery power performance.
- Evaluate e-ink readability and UI responsiveness.
- Verify fingerprint sensor accuracy and durability.
- Establish a repeatable assembly process.
- Identify early failures before scaling to mass production.

## 2. Prototype Stages

### Stage 1: Breadboard Prototype (Weeks 1–4)
- Assemble core electronic components on a breadboard.
- Integrate MCU board (e.g. ESP32 + SX127x).
- Connect LoRa radio module and antenna.
- Attach e-ink display breakout and test refresh cycles.
- Add battery, solar panel, and charging circuitry.
- Flash test firmware for:
  - Radio send/receive loops
  - Basic LED/print debugging
  - Local ledger storage
- Validate basic functions:
  - Device boots
  - Radio transmits
  - Storage writes persist
  - Power system charges and discharges predictably

### Stage 2: Alpha Prototype PCB (Weeks 4–8)
- Convert breadboard wiring to a first printed circuit board (PCB).
- Route clean traces for radio, power, and display.
- Add connectors for battery, solar, buttons, fingerprint sensor.
- Produce 5–10 boards from a low-volume manufacturer.
- Assemble by hand or via prototype assembly services.
- Flash firmware and test:
  - Power stability under load
  - Radio range in open-air and indoor settings
  - E-ink UI updates
  - Data persistence across power cycles

### Stage 3: Beta Prototype Device (Weeks 8–12)
- Design the first enclosed form factor.
- Use SLA or MJF 3D printing for enclosure fabrication.
- Integrate components into a full handheld device.
- Validate real-world performance including:
  - Drop tolerance
  - Heat exposure
  - Battery longevity under typical usage
  - Solar input viability in low-light environments
  - Mesh sync reliability in groups of 3–10 devices
- Collect feedback from early field testers.

### Stage 4: Pre-production Prototype (Weeks 12–16)
- Move from hand-assembled boards to small-scale manufacturing.
- Produce 20–50 units for pilot testing.
- Apply small design optimizations:
  - Improved button layout
  - Better antenna tuning
  - Reinforced enclosure
  - Reduced power leakage
- Confirm the design meets manufacturing standards.

## 3. Required Materials and Suppliers

### Electronics
- LoRa radio modules (SX1276/SX1262)
- ESP32 or equivalent microcontroller
- E-ink display modules
- LiFePO4 or Li-ion batteries
- Solar input regulators
- Fingerprint sensor module
- Secure element chip (ATECC608 or similar)

### Enclosure
- SLA resin prints for early validation
- Injection-mold test for later-stage prototypes

### Tools and Services
- Soldering equipment
- Oscilloscope and multimeter
- Prototype PCB manufacturers (JLCPCB, PCBWay)
- Assembly services for small batches
- 3D printing services (Shapeways, Xometry)

## 4. Prototype Testing Checklist

### Electrical Testing
- Current draw at idle, active mesh sync, and display refresh.
- Charging behavior from solar, USB, and hand-crank.
- Radio frequency integrity and antenna matching.

### Functional Testing
- Mesh communication between 2–10 devices.
- Ledger sync correctness and consistency.
- Fingerprint sensor reliability.

### Environmental Testing
- Device behavior in heat and humidity.
- Drop tests at various heights.
- Water resistance testing for splash protection.

### User Experience Testing
- E-ink readability in sun and shade.
- Ergonomics of buttons and shape.
- Ease of charging and maintaining device.

## 5. Risks and Mitigations

### Risk: Radio interference or poor mesh performance
- Mitigation: Adjust spreading factor, bandwidth, antenna design.

### Risk: Battery failure in hot climates
- Mitigation: Use LiFePO4 chemistry for heat tolerance.

### Risk: E-ink refresh lag
- Mitigation: Cache UI states and minimize updates.

### Risk: Manufacturing variability
- Mitigation: Build test jigs and repeatable QC procedures.

## 6. Success Criteria

- Device powers on reliably and runs for multiple days on a single charge.
- Mesh communication succeeds with high reliability across many nodes.
- Ledger sync merges consistently across devices.
- Hardware survives rough field use.
- Assembly process can be scaled to 100+ units with predictable outcomes.

## 7. Transition to Mass Production

Once the pre-production prototype passes testing, next steps include:

- Final PCB revision for manufacturability.
- Selection of mass-production partners.
- Tooling for injection-molded enclosure.
- Finalization of bill of materials (BOM).
- Long-term reliability and safety certification processes.

The prototyping plan ensures Seed evolves from a functioning early prototype to a robust, mass-producible device ready for real-world deployment.
