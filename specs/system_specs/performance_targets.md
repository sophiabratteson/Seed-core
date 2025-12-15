# Performance Targets

This document defines the quantitative and qualitative performance targets for the Seed system. These targets guide hardware design, firmware optimization, mesh protocol behavior, and user experience expectations. They are intentionally ambitious but achievable for an offline-first, low-power, decentralized financial device.

---

## 1. Performance Philosophy

Seed prioritizes:

- Reliability over speed
- Deterministic behavior over throughput
- Offline resilience over real-time responsiveness
- Energy efficiency over computational intensity

Performance targets are designed to ensure Seed remains usable in low-resource environments while still supporting meaningful financial activity.

---

## 2. Transaction Performance Targets

### Transaction Creation
- Transaction creation latency: ≤ 250 ms
- Local validation time: ≤ 100 ms
- Signature generation time: ≤ 150 ms
- User confirmation feedback: ≤ 500 ms total

### Transaction Storage
- Write-to-secure-storage time: ≤ 200 ms
- Transaction durability guarantee: immediate after commit
- No transaction loss on sudden power failure

---

## 3. Ledger Performance Targets

### Ledger Size Handling
- Minimum supported ledger size: 100,000 transactions
- Target ledger size without degradation: 250,000 transactions
- Graceful degradation beyond target size via pruning and checkpointing

### Ledger Operations
- Ledger merge (1,000 transactions): ≤ 1 second
- Ledger validation pass: ≤ 2 seconds
- Deterministic reordering computation: ≤ 500 ms

---

## 4. Mesh Network Performance Targets

### Message Transmission
- Average message size: ≤ 512 bytes
- Maximum transaction message size: ≤ 1 KB
- Maximum sync batch size: ≤ 20 KB per exchange

### Delivery Reliability
- Successful delivery rate (ideal conditions): ≥ 95%
- Successful delivery rate (degraded conditions): ≥ 80%
- Automatic retry attempts: up to 5 per message

### Latency Expectations
- Single-hop message latency: 1–5 seconds
- Multi-hop propagation latency: ≤ 60 seconds typical
- Eventual delivery guarantee: yes (no hard real-time requirement)

---

## 5. Offline Sync Performance Targets

### Sync Efficiency
- Incremental sync preferred over full ledger transfer
- Sync session duration (typical): ≤ 30 seconds
- Sync session duration (large delta): ≤ 2 minutes

### Convergence
- Maximum sync cycles to convergence: ≤ 3
- Guaranteed deterministic convergence across all nodes

---

## 6. Power and Energy Performance Targets

### Power Consumption
- Idle (sleep): ≤ 50 µA
- Active (radio listening): ≤ 15 mA
- Active (radio transmit): ≤ 120 mA (short bursts only)

### Battery Life
- Minimum battery life (no solar): ≥ 7 days typical use
- Target battery life: ≥ 30 days with moderate use
- Emergency low-power mode: ≥ 14 days

### Charging
- Solar recharge viability: yes
- Hand-crank recharge usability: ≥ 1 transaction per minute of cranking

---

## 7. User Interface Performance Targets

### Display
- Screen refresh latency (e-ink): ≤ 1 second
- UI navigation response: ≤ 500 ms
- No UI blocking during background sync

### Input
- Button response time: ≤ 100 ms
- Fingerprint authentication time: ≤ 1 second
- Audio or haptic feedback latency: ≤ 200 ms

---

## 8. Security Performance Targets

### Cryptographic Operations
- Signature verification: ≤ 50 ms per transaction
- Encryption/decryption: ≤ 100 ms per message
- Secure boot time: ≤ 2 seconds

### Failure Handling
- Failed verification detection: immediate
- Replay attack detection: immediate
- Tamper event detection: ≤ 500 ms

---

## 9. Scalability Targets

- Supported concurrent nodes per local mesh: ≥ 100
- Supported regional network size (eventual): ≥ 100,000 devices
- No global coordination bottleneck
- No dependency on centralized infrastructure

---

## 10. Testing and Validation Targets

- All performance targets measurable via automated tests
- Performance regression threshold: ≤ 10% degradation
- Field test validation required for power and radio metrics

---

## 11. Investor Summary

Seed is engineered to function reliably under extreme constraints while still supporting real economic activity. These performance targets demonstrate that Seed is not designed as a laboratory experiment, but as a scalable, field-ready system capable of supporting millions of users in offline and low-infrastructure environments.

Performance is a core competitive advantage for Seed — not an afterthought.
