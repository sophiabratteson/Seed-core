# Factory Testing Checklist

This document defines the standardized factory testing process for Seed devices prior to shipment. The goal is to ensure every device meets functional, security, durability, and compliance requirements before entering the field. This checklist is designed for repeatability, auditability, and scale.

---

## 1. Purpose and Scope

- Validate hardware, firmware, and security integrity before deployment
- Detect manufacturing defects early
- Ensure consistent device behavior across production batches
- Establish traceable quality records for compliance and investor assurance

This checklist applies to **all Seed devices** produced at pilot scale and mass production scale.

---

## 2. Test Environment Setup

- Controlled indoor testing area
- ESD-safe workstation
- Calibrated power supplies and measurement tools
- Reference Seed device (known-good baseline)
- Secure provisioning terminal

Required tools:
- Multimeter
- Power analyzer
- RF signal tester or reference LoRa node
- USB flashing/debug cable
- Test firmware image (factory mode)

---

## 3. Incoming Visual Inspection

- Enclosure integrity (no cracks, warping, or loose seams)
- Buttons and input surfaces intact and responsive
- Display glass seated correctly
- Ports aligned and unobstructed
- No exposed wiring or solder bridges
- Serial number / QR code present and readable

Pass/Fail logged.

---

## 4. Power System Tests

### Battery
- Battery voltage within expected range
- Proper polarity and secure connection
- No swelling or overheating

### Charging
- USB charging initiates correctly
- Solar input detected (if applicable)
- Hand-crank input generates charge (if applicable)
- Charge controller reports correct state

### Power Consumption
- Idle current within specification
- Active radio transmission current within budget
- Sleep mode current below defined threshold

---

## 5. Boot and Firmware Integrity

- Device powers on successfully
- Secure boot completes without errors
- Firmware version matches production release
- Device enters factory test mode correctly
- No boot loops or crashes observed

---

## 6. Display and Input Tests

### E-Ink Display
- Screen refresh completes fully
- No ghosting or stuck pixels
- Text legible under normal lighting
- Refresh timing within spec

### Input
- Buttons register correct events
- No double-triggering or dead zones
- Long-press and short-press behavior validated

---

## 7. Security Component Verification

### Secure Element
- Secure chip detected and responsive
- Device identity key generated successfully
- Private keys non-exportable

### Fingerprint Sensor (if present)
- Sensor initializes correctly
- Enrollment process functions
- False-positive rate within acceptable range

---

## 8. Radio and Mesh Networking Tests

- LoRa radio initializes successfully
- Device broadcasts heartbeat message
- Device receives and decodes test packet
- RSSI and SNR within expected range
- Mesh neighbor discovery succeeds with reference node
- Transmission retries function as expected

---

## 9. Ledger and Storage Tests

- Internal storage initializes correctly
- Ledger file created and writable
- Test transaction successfully added
- Duplicate transaction handling verified
- Storage survives power cycle without corruption

---

## 10. Offline Sync Simulation

- Device generates outbound transaction
- Second device imports transaction successfully
- Ledger convergence confirmed
- Conflict resolution logic executes deterministically

---

## 11. Tamper and Fault Tests

- Sudden power loss does not corrupt storage
- Brown-out recovery successful
- Tamper detection flags trigger appropriately (if enabled)
- Emergency wipe mechanism responds correctly

---

## 12. Final Quality Gate

- All checklist items marked PASS
- Device serial number logged
- Firmware hash recorded
- Manufacturing batch ID recorded
- Tester ID and timestamp logged

Devices failing any critical test are routed to:
- Rework queue
- Component replacement
- Secure disposal (if unrecoverable)

---

## 13. Documentation and Traceability

For each device, store:
- Test checklist results
- Firmware version
- Hardware revision
- Unique device ID
- Date and location of testing

Records are retained for:
- Regulatory compliance
- Warranty support
- Post-deployment analysis
- Investor and audit review

---

## 14. Exit Criteria

A device is approved for shipment only if:
- 100% required tests pass
- No unresolved security warnings
- Power and radio metrics meet specification
- Ledger and sync behavior verified

---

## 15. Continuous Improvement

- Failure rates reviewed weekly
- Root-cause analysis conducted for recurring issues
- Checklist updated as hardware and firmware evolve
- Feedback loop maintained with manufacturing and engineering teams

---

**This factory testing checklist ensures Seed devices are secure, reliable, and ready for real-world deployment in low-connectivity environments.**
