# Radio Regulations Compliance Specification

## Purpose

This document defines how the Seed device complies with global radio frequency (RF) regulations. Because Seed operates as an offline, peer-to-peer mesh network using sub-GHz radio, regulatory compliance is essential for legal deployment, scalability, and investor readiness.

This specification ensures that Seed:
- Operates legally in all target regions
- Avoids interference with licensed spectrum users
- Can be certified for manufacturing and distribution
- Is adaptable to region-specific radio laws

---

## Regulatory Scope

Seed uses unlicensed Industrial, Scientific, and Medical (ISM) frequency bands and must comply with regional radio authorities including:

- **United States:** FCC (Federal Communications Commission)
- **European Union:** ETSI (European Telecommunications Standards Institute)
- **United Kingdom:** Ofcom
- **Canada:** ISED
- **Asia-Pacific:** MIC (Japan), SRRC (China), ACMA (Australia)
- **Global Reference:** ITU (International Telecommunication Union)

---

## Supported Frequency Bands

Seed is designed to support region-specific frequency variants:

- **902–928 MHz (US, Canada)**
- **868 MHz (EU, UK)**
- **433 MHz (optional low-data-rate regions)**
- **915 MHz (Asia-Pacific variants)**

Each Seed device is region-locked at provisioning time to prevent illegal transmission.

---

## Transmission Power Limits

Seed enforces strict transmission power caps at the firmware level:

- FCC (US): ≤ 1W EIRP (depending on modulation and hopping)
- ETSI (EU): ≤ 14 dBm EIRP (868 MHz band)
- Duty cycle restrictions enforced where required (e.g. 1% in EU)

Power levels are:
- Defined in firmware configuration
- Not user-adjustable
- Verified during factory testing

---

## Duty Cycle Compliance

To meet regional duty cycle rules, Seed implements:

- Transmission time tracking per device
- Adaptive backoff when limits are reached
- Queue-based message scheduling
- Prioritization of critical messages (ledger sync, security alerts)

This ensures compliance even in dense mesh deployments.

---

## Modulation and Bandwidth Controls

Seed uses LoRa modulation with configurable parameters:

- Spreading Factor (SF)
- Bandwidth (BW)
- Coding Rate (CR)

Firmware dynamically selects compliant parameters based on:
- Region
- Network density
- Power budget
- Environmental interference

Non-compliant combinations are blocked at compile time.

---

## Channel Access and Interference Avoidance

Seed implements multiple strategies to minimize interference:

- Listen-before-talk (where required)
- Randomized transmission offsets
- Mesh gossip protocols instead of flooding
- Low-duty beaconing

Seed does not rely on continuous broadcast modes.

---

## Antenna Compliance

Approved antenna designs must:
- Match regional frequency bands
- Meet gain limits
- Be tested as part of the full device (not modularly swapped)

Seed prohibits user-replaceable high-gain antennas to prevent regulatory violations.

---

## Certification Strategy

Seed follows a modular certification approach:

- Pre-certified radio modules where possible
- Full device certification for final hardware
- Separate SKUs per region if required

Target certifications include:
- FCC Part 15
- CE (RED Directive)
- UKCA
- IC (Canada)

---

## Manufacturing and Labeling Requirements

Each device includes:
- Regulatory ID markings
- Frequency band labeling
- Region designation
- Compliance statements

Packaging includes region-specific documentation.

---

## Firmware Safeguards

Seed firmware enforces compliance by:

- Hard-coded regional limits
- Disabled out-of-band transmission
- Locked RF parameters post-provisioning
- Secure boot preventing unauthorized firmware

Any attempt to bypass RF restrictions invalidates device operation.

---

## Testing and Validation

Compliance is verified through:

- RF chamber testing
- Field range testing
- Duty cycle stress testing
- Interference simulations

All test results are logged and archived.

---

## Risk Mitigation

Potential risks addressed:
- Accidental out-of-band transmission
- User-modified firmware
- Cross-border device transport

Mitigations include:
- Secure firmware
- Region locking
- Clear compliance documentation

---

## Future Expansion Considerations

As Seed scales:
- Additional frequency variants may be added
- Dynamic regional provisioning may be introduced
- Regulatory updates will be tracked continuously

---

## Summary

Seed’s radio system is designed from the ground up for global regulatory compliance. By combining hardware controls, firmware enforcement, and regional configuration, Seed can legally operate as a resilient, offline financial network across diverse environments without compromising safety or scalability.

This compliance framework enables confident manufacturing, distribution, and investment readiness.
