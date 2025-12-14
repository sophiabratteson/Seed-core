# Scalability Limits — Radio Mesh Simulation

This document defines the practical and theoretical scalability limits of Seed’s radio mesh network. It explains how the network behaves as the number of devices increases, what constraints emerge, and how Seed is designed to remain functional and reliable under growth without centralized infrastructure.

---

## 1. Purpose of This Document

- Define how many devices a Seed mesh can support under different conditions.
- Identify limiting factors (radio, power, memory, time).
- Establish realistic deployment expectations for pilots and early rollouts.
- Inform protocol design decisions that preserve usability at scale.
- Provide investor clarity on growth boundaries and mitigation strategies.

---

## 2. Definitions

- **Node**: A Seed device participating in the mesh.
- **Neighborhood**: Set of nodes within direct radio range.
- **Hop**: One relay step between two nodes.
- **Mesh Density**: Number of nodes per square kilometer.
- **Throughput**: Amount of data successfully delivered per unit time.
- **Convergence Time**: Time required for all reachable nodes to reach consistent state.

---

## 3. Core Scalability Constraints

### 3.1 Radio Airtime

- LoRa radios are airtime-limited, not bandwidth-rich.
- Regulatory duty cycle limits (e.g., 1% in many regions) cap total transmissions.
- As node count increases:
  - Collision probability rises.
  - Latency increases.
  - Broadcast storms become possible without mitigation.

**Implication**: Mesh must minimize unnecessary transmissions.

---

### 3.2 Packet Size Constraints

- Typical LoRa payloads range from ~50 to ~250 bytes.
- Larger messages increase airtime exponentially.
- Seed uses:
  - Compact binary serialization.
  - Incremental sync messages.
  - Delta-based ledger exchange.

**Implication**: Message design directly affects scalability.

---

### 3.3 Power Budget

- Each transmission consumes significant energy.
- Battery-powered nodes cannot sustain frequent broadcasts.
- Dense meshes drain devices faster due to overhearing traffic.

**Implication**: Power-aware routing and duty cycling are mandatory.

---

### 3.4 Memory and Storage

- Devices have finite flash and RAM.
- Ledger growth is bounded by:
  - Checkpointing.
  - Pruning invalid or expired transactions.
  - Archival snapshots.

**Implication**: Unlimited growth is prevented by design.

---

### 3.5 Time-to-Convergence

- In large meshes, full convergence may take hours or days.
- Seed prioritizes:
  - Eventual consistency.
  - Local correctness over global immediacy.

**Implication**: System remains usable without full sync.

---

## 4. Scaling Scenarios

### 4.1 Small Mesh (2–10 Nodes)

- Direct peer-to-peer communication.
- Near-instant sync.
- Minimal collisions.
- Ideal for:
  - Small villages.
  - Family groups.
  - Pilot testing.

---

### 4.2 Medium Mesh (10–100 Nodes)

- Multi-hop routing emerges.
- Gossip-based sync preferred over flooding.
- Sync occurs opportunistically.

Mitigations:
- Probabilistic rebroadcast.
- Time-randomized transmissions.
- Neighbor prioritization.

---

### 4.3 Large Mesh (100–1,000 Nodes)

- Full mesh flooding is infeasible.
- Nodes form implicit clusters.
- Not all nodes directly exchange data.

Mitigations:
- Local convergence with eventual global merge.
- Trusted relay nodes (not centralized).
- Checkpoint summaries instead of full ledgers.

---

### 4.4 Very Large Mesh (1,000+ Nodes)

- Treated as federated meshes.
- Occasional bridge nodes move data between regions.
- Physical mobility (people, vehicles) aids propagation.

Seed does **not** assume:
- Continuous connectivity.
- Real-time global awareness.

---

## 5. Protocol-Level Scalability Controls

### 5.1 Gossip-Based Dissemination

- Nodes randomly select peers to exchange summaries.
- Reduces broadcast amplification.
- Scales logarithmically rather than linearly.

---

### 5.2 Summary-First Sync

- Nodes exchange compact ledger summaries first.
- Only missing data is requested.
- Prevents redundant transfers.

---

### 5.3 Backoff and Rate Limiting

- Adaptive transmission delays based on network density.
- Randomized wait windows reduce collisions.
- Hard caps on sync frequency.

---

### 5.4 Role Differentiation

- Some nodes naturally act as:
  - High-uptime relays.
  - Community hubs.
- No node is required or privileged.
- Roles emerge organically.

---

## 6. Failure Modes at Scale

### 6.1 Broadcast Storms

Mitigation:
- TTL (time-to-live) on messages.
- Rebroadcast probability decay.

---

### 6.2 Ledger Bloat

Mitigation:
- Periodic checkpoints.
- Archival pruning.
- State compression.

---

### 6.3 Energy Collapse

Mitigation:
- Duty cycle enforcement.
- Power-aware routing.
- Solar/hand-crank recharging.

---

## 7. Scalability Metrics Tracked in Simulation

- Max sustainable node count per square kilometer.
- Average sync latency vs. node count.
- Packet collision rate.
- Battery drain per node.
- Convergence probability over time.

These metrics guide protocol tuning before field deployment.

---

## 8. Design Philosophy on Scalability

Seed is designed around **human-scale finance**, not high-frequency trading.

Key principles:
- Offline-first.
- Eventual consistency.
- Local autonomy.
- No single point of failure.
- Graceful degradation.

Scalability is achieved through **restraint**, not raw throughput.

---

## 9. Investor Summary

- Seed does not require global real-time consensus.
- The mesh scales through decentralization and locality.
- Growth increases reach, not fragility.
- Limits are known, modeled, and intentionally designed around.

This makes Seed viable in environments where traditional systems fail—and scalable enough to grow responsibly without centralized infrastructure.

---

## 10. Open Questions and Future Work

- Optimal cluster sizing heuristics.
- Adaptive trust-weighted routing.
- Cross-mesh bridging policies.
- Field validation under extreme density.

These areas are actively explored in ongoing simulations and pilots.
