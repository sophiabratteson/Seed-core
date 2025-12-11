# Power Traces and Grounding Guidelines

This document defines the required PCB design rules for Seed’s power-distribution network, grounding strategy, noise-reduction practices, and reliability considerations for operating in low-infrastructure, high-temperature, and electrically noisy environments. These requirements apply to both prototype and production revisions of the Seed device.

---

## 1. Goals of Power and Ground Design

- Ensure stable and clean power delivery to all components.
- Protect the device from voltage dips during radio transmission bursts.
- Minimize noise coupling into sensitive analog circuits (battery sensing, fingerprint sensor).
- Achieve safe thermal performance without active cooling.
- Reduce EMI (electromagnetic interference) to comply with regional radio regulations.
- Enable safe operation using solar, hand-crank, battery, and USB-powered configurations.

---

## 2. Power Domains Overview

Seed uses multiple isolated or semi-isolated power domains:

- Battery domain (LiFePO4 or Li-ion).
- Charging domain (solar + hand-crank + optional USB).
- 3.3V regulated domain (MCU, LoRa radio, secure element).
- 1.8V or auxiliary domain (optional sensors).
- High-current burst domain (LoRa TX stage).

Each domain must be routed with clear separation and proper filtering to avoid cross-domain interference.

---

## 3. Power Trace Width Requirements

To ensure low resistance and safe thermal performance:

### Battery Traces
- Width: 40–60 mil recommended.
- Keep as short as possible.
- Avoid vias if possible; if needed, use multiple vias in parallel.

### 3.3V Regulated Rails
- Width: 20–30 mil recommended.
- Central distribution spine should be thick, with branches thinner.

### Radio PA (Power Amplifier) Burst Lines
LoRa transmit bursts produce rapid current spikes.

- Width: 30–40 mil minimum.
- Use local decoupling close to radio module pins.

### Input From Solar / Hand-Crank Charger
- Width: 40 mil minimum.
- Place transient protection and reverse-polarity circuitry near the connector.

---

## 4. Decoupling and Power Filtering

Every IC must have local decoupling.

### MCU
- 0.1 µF ceramic capacitor placed within 2–3 mm of each power pin.
- 4.7–10 µF bulk capacitor nearby.

### LoRa Radio
- 0.1 µF per power pin.
- 10 µF bulk capacitor.
- 47–100 µF low-ESR cap recommended for TX burst compensation.

### Secure Element Chip
- 0.1 µF ceramic.
- 1 µF bulk cap.

### Fingerprint Sensor
- Follow manufacturer guidelines; typically 1–10 µF local decoupling.

Power filtering:
- Use π-filter (C–L–C) on noisy rails if necessary.
- Place ferrite bead between radio domain and MCU domain.

---

## 5. Grounding Strategy

A stable ground plane is critical for both digital and RF performance.

### Solid Ground Plane
- Use uninterrupted ground plane on Layer 2 (for 4-layer boards).
- Avoid ground plane fragmentation around antennas.

### Star Ground Reference
- High-current domains (battery, PA) should join ground at a single reference point.
- Prevents ground noise from spreading to sensitive circuits.

### Via Stitching
- Stitch ground vias around:
  - Radio module perimeter.
  - Power regulators.
  - E-ink display interface flex connector.
- Recommended spacing: 2–3 mm between vias.

---

## 6. Radio Grounding Considerations

LoRa modules require careful grounding for proper RF behavior.

- Keep ground plane solid under the radio but remove copper under the antenna region.
- Place several ground vias near the RF matching network.
- Maintain controlled-impedance 50-ohm trace for antenna feedline.

---

## 7. Protection and Safety Components

Include the following protection circuits:

- Reverse polarity protection on battery input.
- TVS diode for surge suppression on charging input.
- Over-current protection fuse (resettable polyfuse).
- ESD protection diodes near user-accessible ports.

---

## 8. Thermal and Current Handling Guidelines

### LoRa TX Heating
- Provide thermal relief using copper pours connected to radio ground.
- If using SX1262 high-power variant, ensure PA heat spreads over ground plane.

### Battery Charging Heat
- Keep charger IC away from thermally sensitive components.
- Add thermal vias under the charger IC pad.

---

## 9. Noise Isolation and Signal Integrity

- Keep analog sensor traces away from LoRa high-current paths.
- Maintain separation between:
  - Radio traces
  - Fingerprint sensor signals
  - Secure element communication lines (I²C/SPI)

Recommended spacing:
- Minimum 20 mil between noisy power sections and analog lines.

Place ground guard traces around:
- Secure chip lines.
- Fingerprint sensing lines.

---

## 10. Recommended 2-Layer vs 4-Layer Approach

### Prototyping (2-Layer PCB)
- Possible but requires careful manual placement.
- Ground plane discontinuities may reduce radio performance.

### Production (4-Layer PCB)
- Layer stack suggestion:
  - Layer 1: Signals + power
  - Layer 2: Solid ground
  - Layer 3: Power distribution + secondary signals
  - Layer 4: Signals / I/O

Using 4 layers significantly improves:
- RF stability
- Noise immunity
- Thermal dissipation

---

## 11. Testing and Verification Plan

Before finalizing each PCB revision:

- Perform IR camera scan during LoRa TX for hot spots.
- Measure voltage ripple on 3.3V rail with oscilloscope.
- Validate antenna SWR (Standing Wave Ratio) to avoid power reflection.
- Stress test with worst-case duty cycle (continuous TX).
- Validate battery sag behavior at low temperatures.

---

## 12. Summary

Proper power and grounding design is essential to Seed’s operational reliability in harsh, low-infrastructure environments. These guidelines ensure stable power delivery, strong RF performance, noise isolation, and compliance with safety standards. Following this design framework allows Seed devices to remain functional even under heavy load, extreme temperatures, and unpredictable charging sources.
