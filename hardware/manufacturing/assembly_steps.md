# Hardware Manufacturing – Assembly Steps

This document outlines the step-by-step manufacturing and assembly process for the Seed device. It is designed for prototype-to-pilot scale production (10–500 units) and can be expanded for mass manufacturing. The sequence ensures component integrity, electrical safety, quality control, and repeatability.

---

# 1. Pre-Assembly Preparation

## 1.1 Incoming Component Verification
- Validate quantity and condition of all critical components:
  - PCB panels
  - LoRa radio modules (SX1262/SX1276)
  - Secure element (ATECC608B or equivalent)
  - E-ink display modules
  - LiFePO4 battery cells
  - Solar + hand-crank charging modules
  - Power regulation ICs
  - Fingerprint sensor
  - Mechanical fasteners and enclosure parts
- Perform random sample electrical tests on critical ICs.
- Confirm all components meet supplier specifications.

## 1.2 ESD-Safe Workstation Setup
- Grounded assembly tables.
- ESD wristbands for all operators.
- ESD floor mats and humidity-controlled workspace (40–60%).

---

# 2. PCB Assembly Process

## 2.1 Solder Paste Application
- Use stainless steel stencil aligned to PCB.
- Apply lead-free solder paste (SAC305 recommended).
- Inspect under microscope for bridging or under-deposit.

## 2.2 Pick-and-Place Component Mounting
- Automated PnP or semi-manual placement for prototypes.
- Mount in the following recommended order:
  1. MCU + memory components
  2. Secure element chip
  3. Power management ICs
  4. LoRa radio module + RF routing components
  5. Passive components (resistors, capacitors, inductors)
  6. Connectors (battery, programming header)

## 2.3 Reflow Soldering
- Use lead-free reflow profile (peak 235–245°C).
- Inspect solder joints post-reflow.
- Rework any cold joints or bridges.

## 2.4 Through-Hole Soldering
- Attach antenna connector.
- Attach fingerprint sensor connector (if off-board).
- Hand-solder power switch and charging input.

---

# 3. Subsystem Integration

## 3.1 Battery Integration
- Spot-weld or connector-attach LiFePO4 cell.
- Add protective foam and thermal barrier.
- Connect battery leads to BMS input pads.

## 3.2 Display Mounting (E-Ink)
- Attach display using:
  - Double-sided adhesive frame, or
  - Standoffs and ribbon cable clamp.
- Route cable without bending past manufacturer limits.

## 3.3 Fingerprint Sensor Installation
- Align sensor with enclosure window.
- Use optical-grade adhesive or locking frame.
- Test quick fingerprint read using factory test firmware.

## 3.4 Antenna Attachment
- Mount internal or external antenna.
- Verify matching network soldered correctly.
- Perform RF continuity check.

---

# 4. Firmware Installation

## 4.1 Bootloader Flashing
- Connect via SWD/JTAG programmer.
- Flash secure bootloader + device identity provisioning.

## 4.2 Main Firmware Flashing
- Flash:
  - Mesh protocol stack
  - Ledger engine
  - User-interface firmware
  - Power management routines
- Verify firmware hash matches release manifest.

## 4.3 Secure Element Personalization
- Inject unique cryptographic keys.
- Lock configuration fuses to prevent tampering.
- Verify authentication challenge-response.

---

# 5. System Calibration

## 5.1 Power Calibration
- Measure idle current, transmit current, and sleep current.
- Verify solar and hand-crank charging efficiency.
- Validate battery cutoff and recovery thresholds.

## 5.2 Radio Calibration
- Calibrate RF output power (+14 to +22 dBm depending on region).
- Confirm frequency accuracy (< ±15 ppm).
- Run mesh-join and packet-exchange tests.

## 5.3 Display Calibration
- Ensure contrast and refresh rates match spec.
- Test partial-refresh (if supported).

## 5.4 Fingerprint Calibration
- Register test fingerprints.
- Validate latency (<300 ms target).
- Verify false reject and false accept rates.

---

# 6. Enclosure Assembly

## 6.1 Internal Mounting
- Place PCB assembly into enclosure base.
- Secure with low-profile screws.
- Add vibration-dampening pads.

## 6.2 Sealing and Gasket Application
- Install dust- and moisture-resistant gasket.
- Ensure alignment around display and fingerprint sensor.

## 6.3 Final Shell Closure
- Attach enclosure lid.
- Torque screws to specified limits.
- Add optional tamper-evident seal.

---

# 7. Final Quality Control

## 7.1 Functional Test Suite
- Power-on self-test (POST)
- Radio range test
- Mesh sync test
- Fingerprint scan test
- Storage write/read test
- Display refresh test

## 7.2 Environmental Stress Screening
- 5-cycle thermal test (0°C → 45°C)
- Vibration test (light duty)
- Drop test (1 m)

## 7.3 Compliance Verification
- RF compliance for target region
- Battery transport certification (UN38.3 for LiFePO4)

---

# 8. Packaging & Documentation

## 8.1 Device Packaging
- Anti-static bag
- Quick-start guide
- Warranty card
- USB power cable (if included)

## 8.2 Serialized Tracking
- Record device ID, secure-element public key, and batch number.
- Upload to internal manufacturing log.

---

# 9. Handoff to Field Deployment

- Ship pilot units to partner organizations.
- Provide firmware update instructions.
- Provide training materials for field agents.

---

# 10. Summary

The assembly process ensures each Seed device is:
- Electrically safe
- Mesh-network ready
- Securely provisioned with cryptographic identity
- Durable for low-resource environments
- Fully tested before deployment

This document is suitable for:
- Manufacturing partners  
- Hardware investors  
- Accelerator technical reviewers  
- Future scaling to mass production
