# Antenna Design

This document explains the antenna requirements, selection criteria, placement considerations, and tuning strategy for Seed’s LoRa-based mesh networking system. Antenna performance is directly tied to communication range, reliability, power efficiency, and regulatory compliance. Because Seed must function in remote, low-connectivity environments, antenna quality is a critical hardware component.

---

# 1. Antenna Requirements

- Must operate in ISM bands that match regional regulations:
  - 868 MHz (EU, Africa, India)
  - 915 MHz (US, LATAM)
- Must be compatible with SX1262 or SX1276 LoRa chipsets.
- Must support long-range communication in rural and semi-obstructed environments.
- Must require minimal user interaction or repositioning.
- Must fit within a compact handheld enclosure without major performance loss.
- Must be low-cost, durable, and manufacturable at scale.

---

# 2. Supported Antenna Types

Seed can use the following antenna categories depending on prototype stage or manufacturing constraints.

## 2.1 External Whip Antenna (SMA or u.FL)
- Provides strongest signal and longest range.
- Easy to tune and replace.
- Ideal for early prototypes and testing.
- Not suitable for consumer enclosure unless integrated cleanly.

## 2.2 PCB Trace Antenna
- Printed directly onto the PCB.
- Lowest cost and simplest manufacturing.
- Small footprint.
- Requires careful layout and ground clearance.

## 2.3 Helical (Spring) Antenna
- Compact and durable.
- Moderate gain compared to whip antennas.
- Good for enclosed handheld devices.
- Works well when space is limited.

## 2.4 Flexible Printed (FPC) Antenna
- Thin and bendable.
- Can be placed on enclosure walls for better radiation pattern.
- Higher cost than PCB trace but better performance.

---

# 3. Recommended Antenna for Seed

For the final Seed consumer device:
- A PCB trace antenna is recommended for cost and manufacturability.
- An optional FPC antenna variant may be used in regions requiring greater range.
- Early prototypes should use an external SMA whip antenna for easy debugging.

---

# 4. Antenna Placement Guidelines

Proper placement is essential for maximizing mesh performance.

- Position the antenna as far away from metal components as possible.
- Maintain at least 10 mm clearance from battery, ground planes, and shielding cans.
- Place near the top edge of the device enclosure.
- Avoid routing digital signals directly under the antenna region.
- If using FPC antennas, keep them flush against plastic enclosure walls.
- Ensure user hands do not completely wrap around the antenna area during normal operation.

---

# 5. Impedance Matching and Tuning

LoRa antennas must be matched to 50 ohms for proper performance.

Steps:
1. Design feed line width to achieve 50 ohm characteristic impedance.
2. Include an antenna tuning network with:
   - Series inductor
   - Shunt capacitor pads
3. Use a VNA (Vector Network Analyzer) during prototyping to measure return loss (S11).
4. Adjust matching components until S11 < -10 dB at operating frequency.
5. Validate with over-the-air range tests.

Without tuning, range and sensitivity may drop by 30 to 50 percent.

---

# 6. Regulatory and Safety Considerations

- Ensure antenna gain does not exceed regional EIRP limits.
- Maintain compliance with:
  - FCC Part 15 (USA)
  - ETSI EN 300 220 (EU)
- Avoid hotspots in SAR testing by limiting output power where needed.
- Ensure antenna cannot be easily detached in ways that violate certification.

---

# 7. Environmental Requirements

To function in harsh conditions, antennas must withstand:
- High humidity
- Temperature swings
- Dust exposure
- Physical drops or shocks
- UV light (for external antennas on solar kiosks)

For handheld units:
- Use heat-resistant polycarbonate enclosure materials.
- Consider water-resistant adhesives or gaskets around FPC placement.

---

# 8. Integration With Radio Subsystem

Antenna performance ties into several other hardware modules:
- Radio interface (RF front-end)
- Power amplifier circuit
- Low-noise amplifier input protection
- RF filters
- PCB ground structure

Ensure that:
- RF traces are as short as possible.
- PCB provides a solid ground reference plane.
- Antenna feed is isolated from digital noise sources.

---

# 9. Antenna Testing Plan

A complete testing process includes:
- VNA sweep of return loss
- Range testing in different environments:
  - Urban (short-range)
  - Semi-rural (medium-range)
  - Open field (long-range)
- Orientation testing with rotation angles
- Multi-device mesh coverage mapping
- Battery impact analysis at different power levels

Data from this testing informs:
- Mesh protocol adjustments
- Transmission scheduling
- Power-saving strategies

---

# 10. Future Optimization Options

- Diversity antennas for improved reliability.
- MIMO-like redundancy for mesh density zones.
- Smart antennas for directional routing in high-traffic deployments.
- Tunable antennas for multi-region hardware SKUs.

---

# Summary

Antenna design is one of the highest-leverage components of Seed’s radio system. Proper selection, placement, and tuning directly influence mesh connectivity, range, battery life, and certification compliance. By optimizing antenna architecture early, Seed ensures a robust communication backbone for its offline-first financial network.
