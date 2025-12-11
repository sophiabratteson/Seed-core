# Enclosure Overview

This document describes the physical enclosure design for the Seed device.  
It outlines functional requirements, environmental needs, structural considerations, material options, ergonomics, manufacturability, and pathways from prototype housing to mass-production-ready casing.

---

# 1. Purpose of the Enclosure

The enclosure protects internal electronics, enables reliable long-term operation in difficult environments, and provides a user-friendly interface. It must:

- Safeguard the PCB, battery, display, secure chip, fingerprint sensor, LoRa radio, and buttons.
- Survive heat, dust, moisture, accidental drops, and rough handling.
- Enable energy-efficient operation and good antenna performance.
- Support low-literacy users with an intuitive, readable interface (via e-ink).
- Maintain a compact, durable form factor suitable for pockets, bags, and outdoor conditions.

The enclosure is not cosmetic — it is a *core functional component* of Seed’s reliability and trustworthiness.

---

# 2. Functional Requirements

## 2.1 Structural Requirements
- Rigid shell to prevent flexing that could damage PCB or battery.
- Internal mounting posts for PCB alignment.
- Cable routing channels for battery leads and antenna.
- Protection for port openings (charging, debug pads, etc.).
- Removable backplate (secured with tamper-evident screws) for battery access if needed.

## 2.2 Environmental Requirements
- Operates in **extreme heat** (35–55°C common in low-latency regions).
- Withstands dust, sand, and humidity (IP54 minimum target).
- Drop-resistant from 1–1.5 meters onto hard surfaces.
- UV-resistant if exposed to sunlight during charging.

## 2.3 Electrical Requirements
- Avoids RF interference by ensuring:
  - Antenna clearance from metal.
  - Non-metallic casing around RF cavity.
- Supports thermal dissipation from battery and secure element.

## 2.4 Usability Requirements
- Easy one-hand use.
- Buttons placed logically for navigation (up, down, confirm, back).
- Fingerprint sensor accessible and protected by recessed ring.
- E-ink display flush or slightly recessed to prevent scratches.

---

# 3. Design Goals

- **Extreme durability** suitable for humanitarian, rural, and disaster environments.
- **Low cost** for mass distribution.
- **Ease of assembly** in small or large manufacturing pipelines.
- **Repairability** in field settings where replacements are difficult.
- **Tamper resistance** around secure chip and storage area.

---

# 4. Recommended Materials

## 4.1 Prototype Housing
- 3D-printed **ABS** or **PETG** for durability and heat resistance.
- TPU gaskets for dust protection.
- Acrylic window for e-ink screen.

## 4.2 Mass-Production Housing
- Injection-molded **ABS/PC blend** (Polycarbonate + ABS):
  - Superior impact resistance.
  - Heat stability.
  - Manufacturable at scale.
- Optional soft-touch TPU outer shell for grip.
- Reinforced battery compartment for safety.

## 4.3 Environmental Seals
- Silicone or TPU gaskets for ports.
- Pressure-relief membrane to reduce condensation.

---

# 5. Internal Layout

- **Top section**: e-ink display, display driver board.
- **Center**: main PCB with LoRa radio, secure element, and MCU.
- **Side rail**: navigation buttons.
- **Bottom**: charging port (solar input or USB-C depending on prototype phase).
- **Back**: removable panel for battery (prototype only; final version may be sealed).
- **Antenna zone**: isolated region with non-conductive outer shell to maximize signal.

A clear airflow path must exist so battery heat does not accumulate near the MCU or secure chip.

---

# 6. Antenna Placement Considerations

Because LoRa’s performance depends heavily on placement:

- Antenna should be placed toward the **top edge** of the enclosure.
- No metal screws nearby.
- Minimum 2–3 mm clearance from inner walls.
- External stub antenna or internal wire antenna depending on region.

Incorrect placement reduces mesh reliability and lowers effective range.

---

# 7. Ergonomics & Industrial Design

- Slight convex back for comfortable grip.
- Textured sides for non-slip handling.
- Clearly distinguishable buttons (tactile feedback).
- Large contrast on e-ink UI for low-light visibility.

Optional features for future versions:
- Lanyard loop for field workers.
- Rubberized over-mold for rugged environments.

---

# 8. Security-Driven Physical Features

- Secure chip located under a reinforced cavity.
- Tamper-evident fasteners.
- Battery and storage components wrapped in resin or protected by break-detection switches (future).
- Emergency-wipe button hidden under a recessed area requiring deliberate action.

---

# 9. Prototype vs. Production Differences

| Feature | Prototype | Production |
|--------|-----------|------------|
| Material | 3D Print (ABS/PETG) | Injection-molded ABS/PC |
| Waterproofing | Basic (IP30) | Target IP54–IP67 |
| Assembly | Screws, open tolerances | Precision snap-fits + screws |
| Tamper resistance | Minimal | Reinforced secure chip cavity |
| Battery access | Removable backplate | Optional sealed design |
| Antenna | External or internal | Optimized internal cavity |

---

# 10. Manufacturing Roadmap

1. **Prototype 1 (3D-printed):** Evaluate fit, ergonomics, heat.
2. **Prototype 2 (Refined shell):** Add seals, antenna cavity, screw posts.
3. **Prototype 3 (Functional enclosure):** Field test for durability and comfort.
4. **DFM (Design for Manufacturing):** Prepare mold-ready CAD.
5. **Pilot injection molds:** Produce small run (100–300 units).
6. **Mass production:** Scale to 1k → 10k → 100k units.

---

# 11. Summary

The Seed enclosure is a critical part of the device’s reliability, usability, and security.  
It must withstand harsh conditions, remain intuitive for users of all literacy levels, and protect sensitive internal electronics including the secure chip and LoRa radio.

A well-designed enclosure ensures that Seed remains durable, trustworthy, and accessible across the environments where it is needed most.
