# Radio System Overview

This document provides a comprehensive overview of the radio communication subsystem used in Seed devices. The radio stack is the foundation of Seed’s offline-first mesh networking model, enabling devices to synchronize financial data, broadcast trust-score updates, exchange group-savings messages, and maintain ledger consistency even in environments with no internet, no cell towers, and no existing infrastructure.  

Seed’s radio system is engineered to be low-power, long-range, resilient, and globally adaptable, making it suitable for underserved regions, disaster zones, refugee settlements, remote villages, and fragmented urban areas.

---

## 1. Radio System Goals

- Enable **device-to-device communication** without relying on infrastructure.  
- Support **multi-hop mesh networking**, extending coverage across entire communities.  
- Maintain **secure, authenticated communication** over untrusted public frequencies.  
- Minimize **energy usage** to support solar/hand-crank charging.  
- Support **small packet transmission** ideal for financial and ledger updates.  
- Comply with **regional radio frequency regulations** worldwide.  
- Remain **scalable**, supporting networks from 2 to 10,000+ devices.

---

## 2. Core Technology: LoRa / LoRa-Compatible Radios

Seed uses radios based on the Semtech SX1276/SX1262 LoRa chipsets or their equivalents. These provide:

- Long-range communication (1–10 km depending on terrain)  
- High penetration through foliage and buildings  
- Ultra-low power consumption  
- Narrowband modulation with configurable spreading factors  
- Support for both **simple broadcast** and **mesh-layer protocols** built on top

While LoRaWAN is a common protocol, Seed specifically uses **raw LoRa** to maintain independence from gateways and external infrastructure.

---

## 3. Frequency Bands and Global Support

Seed devices must comply with region-specific unlicensed frequency bands:

- **US / North America**: 902–928 MHz (902–915 preferred for mesh stability)  
- **EU / Africa / Middle East**: 863–870 MHz  
- **India / Southeast Asia**: 865–867 MHz  
- **Australia / New Zealand**: 915–928 MHz  

The device ships with regionally appropriate firmware + regulatory settings.

Each device enforces:

- Transmission power limits  
- Duty-cycle or listen-before-talk constraints  
- Channel hopping to reduce interference  

These measures ensure global deployability without violating local RF rules.

---

## 4. Communication Model

### 4.1 Packet Size and Messaging Philosophy
Seed uses extremely small, efficient packets (typically **20–60 bytes**) that carry:

- Ledger deltas  
- Transaction metadata  
- Trust-score updates  
- Group savings messages  
- Heartbeats or neighbor discovery pings  

This design makes radio usage fast, reliable, and power-efficient.

### 4.2 Transmission Modes Used by Seed

1. **Broadcast (one-to-many)**  
   - Default mode for ledger deltas and group announcements  
   - Helps devices naturally sync when encountered

2. **Directed (one-to-one)**  
   - Used for acknowledgments, retries, and targeted exchanges  
   - Improves reliability during high network load

3. **Gossip Propagation**  
   - Ensures eventual consistency without overwhelming the network  
   - Devices forward only *new* information

---

## 5. Mesh Networking Capabilities

Seed’s mesh layer (implemented above raw LoRa) supports:

### 5.1 Neighbor Discovery  
Devices periodically announce their presence, enabling:

- Local topology estimation  
- Multi-hop routing  
- Trust-score sharing  
- Group cluster formation  

### 5.2 Multi-Hop Forwarding  
Transactions can propagate across multiple devices until reaching entire communities.

### 5.3 Opportunistic Syncing  
Two devices passing each other can sync on the spot, allowing:

- Offline communities to reconnect  
- Ledger states to converge over time  

---

## 6. Range and Performance Expectations

Performance depends on the environment:

| Environment | Expected Range |
|------------|----------------|
| Open rural terrain | 5–10 km |
| Flat suburban | 2–4 km |
| Dense urban | 0.5–1.5 km |
| Indoors across walls | 0.2–0.5 km |

Mesh networks significantly extend this—dozens of nodes can cover entire villages or neighborhoods.

---

## 7. Power Optimization Techniques

- **High spreading factor only when needed**, reducing airtime  
- **Low-power listening windows**  
- **Adaptive transmission frequency** based on battery level  
- **Batching ledger updates** before transmission  
- **Waking the radio only for scheduled sync slots**  

Combined with the e-ink display and solar/hand-crank system, Seed can operate indefinitely with minimal energy.

---

## 8. Security in the Radio Layer

Although transmissions occur over open frequencies:

- Every packet is **signed** with a device’s private key  
- Payloads are **encrypted** using symmetric session keys  
- Seed prevents replay attacks using:  
  - Lamport clock increments  
  - Nonces / sequence IDs  
  - Duplicate packet filtering  
- The secure element chip stores all keys and never exposes them to main memory

This ensures confidentiality and authenticity even in hostile environments.

---

## 9. Hardware Integration

Seed’s radio subsystem includes:

- **Semtech SX1276 or SX1262 LoRa chipset**  
- **Matching antenna** tuned for the regional frequency  
- **RF shielding** to reduce interference  
- **Power amplifier** and **low-noise amplifier** depending on SKU  
- **Secure radio config stored in secure element**  

Many prototypes will use boards like:  
- LILYGO TTGO LoRa32 (ESP32 + SX1276)  
- RAK4600 (Nordic + LoRa)  
- Heltec WiFi LoRa modules  

Final hardware will be custom-designed for heat tolerance, ruggedness, and minimal power draw.

---

## 10. Future Improvements and Extensions

Seed’s radio system roadmap includes:

- **Adaptive mesh routing using trust scores**  
- **Compressed ledger deltas** for reduced airtime  
- **Directional antennas** for extended rural reach  
- **Frequency-aware congestion control**  
- **Hybrid BLE + LoRa pairing for localized sync**  
- **Satellite uplink modules for advanced deployments**  

---

## 11. Summary

The radio subsystem is the technological backbone of Seed’s offline financial network. It enables a fully infrastructure-independent mesh capable of powering financial access for communities without internet, electricity, or formal banking.  

By combining long-range LoRa radios, strict low-power design, cryptographic security, and intelligent mesh networking, Seed devices form a resilient, self-sustaining ecosystem that brings financial tools to the most underserved populations on Earth.
