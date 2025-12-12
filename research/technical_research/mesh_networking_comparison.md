# Mesh Networking Comparison

This document compares existing mesh networking technologies and approaches relevant to Seed’s offline-first, low-power, decentralized financial system. The goal is to evaluate tradeoffs across range, power consumption, reliability, scalability, security, and suitability for financial transactions in low-connectivity environments.

---

## 1. Purpose of This Comparison

Seed depends on a mesh network that must:

- Operate without internet or cellular infrastructure
- Function reliably with intermittent connectivity
- Consume extremely low power
- Support secure transmission of financial transactions
- Scale from small villages to regional networks
- Be deployable on inexpensive hardware

This document evaluates common mesh networking options against those requirements.

---

## 2. Evaluation Criteria

Each mesh approach is evaluated across the following dimensions:

- Range: Typical communication distance between nodes
- Power Consumption: Suitability for battery, solar, or hand-crank power
- Throughput: Ability to handle transaction data (not media)
- Latency: Acceptable delay for offline-first sync
- Scalability: Performance as node count increases
- Security Model: Built-in or extensible security features
- Hardware Cost: Approximate device cost implications
- Suitability for Seed: Overall alignment with Seed’s goals

---

## 3. Mesh Networking Approaches Compared

### 3.1 LoRa Mesh (Custom / Seed-Specific)

Description:
A custom mesh protocol built on LoRa radio technology (e.g., SX1276, SX1262), optimized for low-bandwidth financial data and offline operation.

Characteristics:
- Range: 1–15 km (environment dependent)
- Power: Extremely low (ideal for solar and hand-crank)
- Throughput: Low (sufficient for transactions, not media)
- Latency: Variable but acceptable for offline sync
- Scalability: High with proper gossip/flood controls
- Security: Application-layer encryption and signing
- Hardware Cost: Low
- Suitability for Seed: Excellent

Pros:
- Designed specifically for offline-first use
- Works in rural and infrastructure-poor areas
- Very low power consumption
- Long-range communication
- Regulatory support in many regions

Cons:
- Low data rates
- Requires custom protocol design
- Not suitable for real-time applications

---

### 3.2 Meshtastic (LoRa-Based)

Description:
An open-source LoRa mesh firmware designed primarily for messaging and location sharing.

Characteristics:
- Range: 1–10 km
- Power: Low
- Throughput: Low
- Latency: Moderate
- Scalability: Moderate
- Security: Basic encryption
- Hardware Cost: Low
- Suitability for Seed: Partial

Pros:
- Proven LoRa mesh implementation
- Active community
- Works on common LoRa dev boards

Cons:
- Optimized for chat, not ledgers
- Limited support for deterministic conflict resolution
- Less control over protocol internals

---

### 3.3 Bluetooth Mesh

Description:
Mesh networking built on Bluetooth Low Energy (BLE).

Characteristics:
- Range: 10–100 meters per hop
- Power: Low to moderate
- Throughput: Moderate
- Latency: Low
- Scalability: Limited by hop count
- Security: Strong device-level encryption
- Hardware Cost: Low
- Suitability for Seed: Poor

Pros:
- Widely supported on consumer devices
- Low latency

Cons:
- Extremely short range
- Not viable for rural or village-scale networks
- Requires dense device distribution

---

### 3.4 Wi-Fi Mesh

Description:
Mesh networking using Wi-Fi radios.

Characteristics:
- Range: 50–200 meters per hop
- Power: High
- Throughput: High
- Latency: Low
- Scalability: Moderate
- Security: Strong
- Hardware Cost: Moderate
- Suitability for Seed: Poor

Pros:
- High bandwidth
- Mature security standards

Cons:
- High power consumption
- Short range compared to LoRa
- Not suitable for off-grid environments

---

### 3.5 Cellular Ad-Hoc / Delay-Tolerant Networks (DTN)

Description:
Systems that store-and-forward data using opportunistic connections (e.g., phones syncing when in range).

Characteristics:
- Range: Opportunistic
- Power: Device-dependent
- Throughput: High when available
- Latency: Unpredictable
- Scalability: Moderate
- Security: Depends on implementation
- Hardware Cost: High
- Suitability for Seed: Limited

Pros:
- Can move large data volumes
- Works opportunistically

Cons:
- Depends on smartphones or infrastructure
- Not suitable for primary financial system
- Inconsistent availability

---

## 4. Comparative Summary Table (Qualitative)

- Best Range: LoRa Mesh
- Lowest Power: LoRa Mesh
- Best for Offline Finance: LoRa Mesh
- Easiest to Prototype Quickly: Meshtastic
- Best Consumer Support: Bluetooth Mesh
- Highest Bandwidth: Wi-Fi Mesh

---

## 5. Why Seed Chooses a Custom LoRa Mesh

Seed’s requirements are fundamentally different from consumer messaging or networking products:

- Transactions must converge deterministically
- Data volumes are small but critical
- Devices must run for days or weeks without charging
- Infrastructure cannot be assumed
- Security must be embedded at the protocol level

A custom LoRa-based mesh allows Seed to:

- Design transaction-aware routing
- Optimize power usage for financial workloads
- Embed trust scores and group savings logic
- Maintain ledger consistency without servers
- Operate independently of any telecom provider

---

## 6. Future Hybrid Approaches

Seed may later support hybrid networking modes:

- LoRa mesh as the primary transport
- Opportunistic Wi-Fi or phone sync when available
- Gateway nodes for optional internet bridging

These extensions do not replace the core mesh, but enhance reach when conditions allow.

---

## 7. Conclusion

Among all evaluated mesh networking approaches, a custom LoRa-based mesh protocol is the only option that fully satisfies Seed’s requirements for range, power efficiency, security, and offline-first financial operation.

This choice enables Seed to function where traditional networks cannot, supporting resilient, community-driven economic systems at global scale.
