# Device Radio Specifications

This document defines the radio communication capabilities required for the Seed device. The radio subsystem is a core component enabling offline-first, peer-to-peer financial transactions across a mesh network without reliance on cellular networks, Wi-Fi, or centralized infrastructure.

---

## 1. Purpose and Design Goals

The radio system must:

- Enable long-range, low-power communication between Seed devices
- Operate reliably in low-connectivity and infrastructure-poor environments
- Support mesh networking with multi-hop routing
- Minimize power consumption to support solar and hand-crank charging
- Comply with regional radio regulations
- Provide secure transmission of financial data

---

## 2. Communication Technology Selection

### Primary Radio Technology
- **LoRa (Long Range Radio)**
  - Chosen for its long-range, low-power characteristics
  - Optimized for small packet transmission
  - Well-suited for intermittent, asynchronous communication

### Supported Chipsets
- Semtech SX1276 / SX1278
- Semtech SX1262 (preferred for newer revisions)
- Equivalent LoRa-compatible transceivers with proven field reliability

---

## 3. Frequency Bands

Seed devices must support regionally appropriate unlicensed ISM bands:

- **902–928 MHz** (US, Canada)
- **863–870 MHz** (Europe)
- **433 MHz** (optional, region-dependent)

Devices must be manufactured or configured per region to ensure regulatory compliance.

---

## 4. Transmission Characteristics

### Range
- Urban: 1–5 km (line-of-sight dependent)
- Rural / Open terrain: up to 10–15 km
- Mesh routing extends effective coverage beyond single-hop range

### Data Rate
- Typical payload size: 50–300 bytes
- Data rate optimized for reliability over throughput
- Adaptive spreading factor based on link quality

### Latency
- Not real-time
- Designed for eventual consistency rather than immediate confirmation
- Typical end-to-end sync latency: seconds to minutes depending on topology

---

## 5. Power Characteristics

- Transmit power: configurable up to regional legal limits
- Typical TX current: 120–150 mA (burst)
- Sleep current: < 5 µA
- Duty-cycled operation to preserve battery life
- Radio disabled entirely during idle periods

---

## 6. Antenna Specifications

- External or internal antenna support
- Impedance: 50 ohms
- Tuned per frequency band
- Optional diversity support for future revisions
- Mechanical design must protect antenna integrity in harsh environments

---

## 7. Mesh Networking Capabilities

The radio stack must support:

- Peer discovery
- Multi-hop message forwarding
- Store-and-forward delivery
- Opportunistic syncing when devices come into proximity
- Dynamic neighbor tables

Routing intelligence is handled at the mesh protocol layer, but radio hardware must support frequent state transitions and packet retransmissions.

---

## 8. Packet Handling

- Maximum packet size aligned with LoRa payload constraints
- Support for fragmentation and reassembly at higher layers
- CRC and checksum support at the radio level
- Hardware-level packet integrity verification

---

## 9. Security Requirements

- Encrypted payloads at higher protocol layers
- Radio hardware must not leak sensitive metadata
- Resistance to replay attacks through sequence numbers and logical clocks
- Compatibility with device identity and signature schemes

---

## 10. Environmental and Reliability Requirements

- Operating temperature: -20°C to +60°C
- Tolerant to dust, humidity, and vibration
- Stable performance under fluctuating power conditions
- Graceful degradation under interference

---

## 11. Regulatory Compliance

- FCC Part 15 (US)
- ETSI EN 300 220 (EU)
- Regional certification as required
- Firmware-configurable frequency and power limits

---

## 12. Future Expansion Considerations

- Support for alternative sub-GHz protocols if required
- Interoperability with community mesh networks
- Gateway compatibility for optional internet bridging
- Potential dual-radio designs in future hardware revisions

---

## 13. Summary

The Seed radio subsystem is designed to prioritize reliability, range, and energy efficiency over bandwidth. By leveraging LoRa-based mesh networking, Seed enables secure, decentralized financial communication in environments where traditional infrastructure does not exist. The radio system is foundational to Seed’s mission of financial inclusion and resilience.
