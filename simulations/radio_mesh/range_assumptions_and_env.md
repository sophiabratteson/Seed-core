# Radio Mesh Range Assumptions and Environmental Factors

This document defines the assumed radio performance characteristics of Seed devices and analyzes how environmental conditions affect mesh communication reliability, range, and throughput. These assumptions guide simulation design, field testing expectations, and hardware selection.

---

## 1. Purpose of This Document

This document exists to:

- Define realistic communication range expectations for Seed devices
- Document environmental variables that impact LoRa mesh performance
- Provide conservative assumptions for simulations and field trials
- Prevent over-reliance on ideal laboratory conditions
- Ensure investor and engineering alignment on real-world constraints

All range values in this document represent **practical, not theoretical maximums**.

---

## 2. Baseline Radio Assumptions

Seed devices are assumed to use LoRa-based sub-GHz radios with the following baseline characteristics:

- Frequency bands: 433 MHz, 868 MHz, or 915 MHz (region-dependent)
- Transmission power: 14–22 dBm (configurable)
- Bandwidth: 125 kHz (default)
- Spreading factor: SF7–SF12 (adaptive)
- Antenna: compact omnidirectional antenna (internal or short external)

Unless otherwise stated, simulations assume **915 MHz**, **SF9**, and **17 dBm** output.

---

## 3. Nominal Communication Ranges

Expected peer-to-peer range under different conditions:

- Open rural terrain (line-of-sight): 3–10 km
- Semi-rural villages: 1–3 km
- Dense urban environments: 300–800 m
- Indoor to outdoor transitions: 100–300 m
- Indoor, multi-wall environments: 50–150 m

Mesh networking allows effective coverage to scale **beyond single-hop limits**.

---

## 4. Environmental Factors Affecting Range

### 4.1 Terrain

- Flat terrain significantly improves range
- Hills and elevation changes reduce effective line-of-sight
- Valleys can either trap or amplify signals depending on topology

Simulations assume **mixed terrain unless explicitly rural or urban**.

---

### 4.2 Buildings and Materials

Signal attenuation varies by material:

- Wood and drywall: low attenuation
- Brick and concrete: moderate attenuation
- Reinforced concrete and metal: severe attenuation

Urban simulations apply **randomized attenuation penalties per hop**.

---

### 4.3 Vegetation and Weather

- Dense foliage reduces signal strength
- Rain and humidity cause mild attenuation
- Dust and sand storms may introduce noise

Weather effects are modeled as **temporary packet loss increases**.

---

## 5. Human and Device Density Effects

### 5.1 Node Density

Higher node density improves mesh reliability by:

- Increasing routing options
- Reducing hop distance
- Improving fault tolerance

However, high density increases:

- Channel contention
- Packet collision probability
- Power consumption

Simulations model adaptive duty cycling to manage congestion.

---

### 5.2 Human Movement

Human bodies absorb RF energy, especially indoors.

Effects include:

- Fluctuating signal quality
- Intermittent connectivity
- Temporary route changes

Seed assumes **opportunistic syncing**, not continuous connectivity.

---

## 6. Antenna Orientation and Placement

Performance varies significantly with antenna placement:

- Vertical orientation preferred
- Placement away from metal surfaces recommended
- Body-worn or pocketed devices reduce range

Simulations assume **non-ideal placement** by default.

---

## 7. Regulatory Constraints

Transmission power and duty cycle limits vary by region:

- US (915 MHz): higher power, fewer duty cycle limits
- EU (868 MHz): strict duty cycle enforcement
- Other regions: variable and sometimes unclear regulations

Simulations enforce **region-appropriate regulatory caps**.

---

## 8. Failure Conditions Modeled

The following conditions are explicitly simulated:

- Partial mesh fragmentation
- Node dropout due to battery depletion
- Intermittent connectivity windows
- High packet loss environments
- Asymmetric links between nodes

Seed is designed to tolerate **extended periods of isolation**.

---

## 9. Assumptions for Investor Communication

For non-technical stakeholders:

- Seed does not require continuous connectivity
- Mesh strength improves with adoption
- Performance degrades gracefully, not catastrophically
- Range claims are conservative and field-validated
- No dependency on cellular or internet infrastructure

---

## 10. Relationship to Other Simulation Modules

This document informs:

- Radio mesh topology simulations
- Packet loss and retry logic testing
- Power budget simulations
- Offline ledger sync behavior
- Field deployment planning

---

## 11. Summary

Seed’s radio mesh is designed for **real-world conditions**, not ideal labs. Environmental variability is expected and accounted for through conservative assumptions, adaptive protocols, and offline-first system design. These range assumptions ensure Seed remains functional in the environments where traditional financial infrastructure fails.

---
