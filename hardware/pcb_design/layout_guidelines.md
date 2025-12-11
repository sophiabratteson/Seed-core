# PCB Layout Guidelines for Seed Device

This document defines the required best-practice PCB layout guidelines for the Seed device. These rules ensure electrical reliability, manufacturability, radio performance, and long-term durability in harsh, low-infrastructure environments. The guidelines apply to all PCB revisions from prototype to mass-production.

---

# 1. Layout Objectives

- Ensure stable operation across extreme temperatures and inconsistent power availability.
- Optimize RF performance for long-range LoRa mesh communication.
- Protect sensitive circuits from noise, tampering, and power irregularities.
- Maintain manufacturability for small-batch and mass-production.
- Minimize power consumption and energy loss under low-power modes.
- Support modular hardware components such as the secure chip, e-ink display, and sensors.

---

# 2. PCB Stackup Requirements

- Use at least a 4-layer board for final production:
  - Layer 1: Signals + sensitive analog and security components.
  - Layer 2: Continuous ground plane (unbroken).
  - Layer 3: Power distribution and secondary routing.
  - Layer 4: Signals, mesh radio circuitry, external connectors.
- Maintain controlled impedance traces for RF and high-speed signals.
- Keep ground plane continuous with minimal splits to reduce EMI.

---

# 3. Grounding Guidelines

- The LoRa RF section requires a dedicated, uninterrupted ground region.
- The secure element (hardware encryption chip) must have a **separate ground island** connected at a single point to reduce leakage attack vectors.
- Decoupling capacitors must connect directly to ground with short traces.
- All mounting holes must be grounded for mechanical + ESD stability.

---

# 4. Power Distribution Routing

- Use wide traces from battery to main power regulation stages (recommended ≥ 40 mil).
- Place the power-management IC (PMIC) close to:
  - Battery connector
  - Solar/hand-crank input staging
  - Power protection circuitry
- Keep analog power (sensors, fingerprint module) isolated from RF + digital switching noise.
- Add test points along:
  - Battery input
  - 3.3 V regulated rail
  - Secure element VCC
  - LoRa PA (power amplifier) rail

---

# 5. Decoupling and Filtering Rules

- Every active IC requires at least:
  - One 0.1 µF ceramic capacitor at the power pin
  - One 1–10 µF bulk capacitor on the rail
- Secure chip requires low-noise filtering with ferrite bead isolation.
- LoRa transceiver requires a dedicated RF choke for power input stability.
- E-ink display driver should be decoupled with bulk capacitance to prevent state flicker.

---

# 6. RF Layout Rules (LoRa Antenna + Front End)

- Place the LoRa transceiver and matching network near the board edge.
- Antenna feedline must be:
  - 50 Ω impedance controlled
  - As short as possible
  - Free of 90° angles (use curves or 45° chamfers)
- Maintain a clear “RF keep-out zone”:
  - No ground pour directly under the antenna
  - No digital traces within 5–10 mm of the feedline
- Add ESD protection near antenna connector.

---

# 7. Secure Chip and Tamper-Resistance Layout

- Place secure element deep within PCB interior.
- Surround with copper pour tied to ground to reduce probing.
- Route all secure-chip traces on internal layers where possible.
- Minimize trace lengths for:
  - I²C/SPI communication lines
  - Power rails
  - Tamper-detection loop (if used)
- Add multiple vias to internal layers to prevent easy drilling attacks.

---

# 8. E-Ink Display Connector and Routing

- Use short, impedance-controlled traces for SPI/I²C signals.
- Backlight or charge-pump circuits must be isolated from RF paths.
- Place FPC connector near the board edge for easy enclosure integration.
- Add mechanical reinforcement pads around the connector to prevent detachment.

---

# 9. Fingerprint Sensor Routing

- Use shielded routing (grounded guard traces) to reduce noise and spoofing.
- Maintain consistent impedance for touch-signal lines.
- Avoid routing near:
  - LoRa PA section
  - Clock crystals
  - High-frequency power switching circuits
- Add ESD diodes for user-touch surfaces.

---

# 10. General Routing Rules

- Keep traces as short and direct as possible.
- Avoid via-in-pad for RF or sensitive analog areas.
- Maintain differential pair length-matching where applicable.
- Use 45° angles instead of 90° to reduce impedance reflections.
- Group related functional blocks logically:
  - Radio section
  - Secure chip
  - Power management
  - Sensor/Fingerprint module
  - E-ink display control

---

# 11. Thermal Considerations

- Add thermal relief vias near PMIC and charging circuits.
- Keep high-current components away from sensitive analog zones.
- Ensure LoRa PA has adequate copper pour for heat dissipation.

---

# 12. EMI/ESD Protection Strategy

- Use TVS diodes on:
  - USB/charging input
  - Antenna connector
  - User-touch points
- Add ferrite beads along power rails entering sensitive zones.
- Keep loops small and avoid large copper islands that may behave like antennas.

---

# 13. Manufacturing and Assembly Considerations

- Ensure components follow standard pick-and-place spacing.
- Avoid placing through-hole components near SMD placements.
- Include fiducial markers for machine vision alignment.
- Maintain consistent silkscreen labeling for test engineering:
  - Test points
  - Component values
  - Reference designators

---

# 14. Test Point Requirements

- Must include accessible test pads for:
  - Battery input
  - 3.3 V rail
  - RF feedline (probe-safe test pad)
  - Secure chip voltage rail
  - UART/debug interface
- Label all test points clearly on silkscreen.

---

# 15. Ruggedization Guidelines for Harsh Environments

- Use ENIG or hard-gold plating for improved corrosion resistance.
- Increase board thickness to ≥ 1.6 mm.
- Use conformal coating on:
  - Radio front end
  - Secure chip region
  - Power circuitry
- Add mechanical standoffs and shock-absorbing mounting holes for the enclosure.

---

# 16. Final Review Checklist

- Does the RF path meet impedance and clearance rules?
- Are all grounds continuous and properly stitched?
- Are decoupling caps placed directly at IC power pins?
- Is the secure element adequately shielded?
- Are sensor blocks isolated from high-frequency noise?
- Are test points accessible and labeled?
- Are all high-current traces sized correctly?
- Does the PCB meet regional RF compliance constraints?
- Does it support manufacturability for both low-volume and high-volume runs?

---

# Summary

These layout guidelines ensure that the Seed device is robust, secure, low-power, and high-performance under conditions where electricity, connectivity, and manufacturing consistency cannot be guaranteed. Following this document ensures the PCB can scale from prototype to mass-produced humanitarian infrastructure hardware, while maintaining Seed’s core promise: dependable financial access, anywhere in the world, without reliance on the internet.
