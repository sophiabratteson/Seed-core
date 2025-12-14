# Radio Mesh Topology Scenarios

This document defines the network topology scenarios used to simulate, evaluate, and stress-test the Seed mesh communication layer. Because Seed operates in offline, infrastructure-free environments, the radio mesh must function across a wide range of physical layouts, population densities, and mobility patterns. These scenarios ensure the protocol remains reliable, energy-efficient, and resilient under real-world conditions.

---

## 1. Purpose of Topology Simulations

The topology simulations are designed to:

- Validate that Seed devices can form stable networks without centralized coordination.
- Measure message propagation reliability across different node arrangements.
- Identify failure modes caused by isolation, congestion, or node churn.
- Optimize routing, rebroadcast, and power-saving strategies.
- Ensure ledger convergence across sparse and dense deployments.

Each topology scenario models a realistic environment where Seed is expected to operate.

---

## 2. Topology Scenario Categories

Topology simulations are grouped into five primary categories:

- Sparse Linear Networks
- Dense Clustered Networks
- Mobile Opportunistic Networks
- Hub-and-Spoke Communities
- Partitioned and Reconnecting Networks

Each category focuses on different constraints and risks.

---

## 3. Sparse Linear Network

### Description
Nodes are arranged in a roughly linear formation with large distances between neighbors. Each node may only be within radio range of one or two others.

### Real-World Examples
- Rural villages along a road
- Refugee transit corridors
- Coastal fishing communities

### Characteristics
- Low node density
- High hop counts
- Increased latency
- High risk of temporary isolation

### Simulation Goals
- Verify multi-hop routing stability
- Measure message delivery success rate
- Evaluate retry and buffering behavior
- Test ledger sync across long propagation chains

---

## 4. Dense Clustered Network

### Description
Many Seed devices are located within close proximity, forming overlapping radio coverage zones.

### Real-World Examples
- Urban markets
- Refugee camps
- Community savings groups

### Characteristics
- High node density
- Multiple redundant paths
- Increased packet collisions
- Higher energy consumption risk

### Simulation Goals
- Evaluate flooding vs gossip efficiency
- Measure collision handling and backoff logic
- Test deduplication and idempotent processing
- Optimize power-saving duty cycles

---

## 5. Mobile Opportunistic Network

### Description
Nodes move in and out of range unpredictably. Connections are short-lived and intermittent.

### Real-World Examples
- Traveling merchants
- Nomadic communities
- Disaster response teams

### Characteristics
- Frequent topology changes
- Opportunistic syncing
- Unpredictable delays
- High reliance on store-and-forward logic

### Simulation Goals
- Validate offline-first sync robustness
- Test partial ledger exchanges
- Measure convergence time under mobility
- Ensure no data loss during transient links

---

## 6. Hub-and-Spoke Community

### Description
A small number of well-connected nodes act as hubs, while many peripheral nodes connect intermittently.

### Real-World Examples
- Community leaders
- NGO field offices
- Merchant aggregation points

### Characteristics
- Uneven connectivity
- Natural data aggregation points
- Risk of hub overload

### Simulation Goals
- Test load balancing strategies
- Measure hub failure impact
- Ensure no central dependency emerges
- Validate fairness in message propagation

---

## 7. Partitioned and Reconnecting Network

### Description
The mesh splits into isolated sub-networks that later reconnect and must reconcile state.

### Real-World Examples
- Natural disasters
- Power outages
- Seasonal migration

### Characteristics
- Temporary network partitions
- Independent transaction histories
- Large reconciliation events on reconnect

### Simulation Goals
- Stress-test conflict resolution logic
- Verify deterministic ledger convergence
- Measure reconciliation bandwidth costs
- Ensure no double-counting or replay

---

## 8. Metrics Tracked Across All Scenarios

Each topology simulation records:

- Message delivery success rate
- Average hop count
- Sync latency
- Energy consumption per node
- Ledger convergence time
- Packet collision frequency
- Orphan transaction resolution rate

These metrics inform protocol tuning and hardware configuration.

---

## 9. Failure Modes Observed

Topology simulations explicitly attempt to surface:

- Network collapse due to over-flooding
- Silent node isolation
- Excessive battery drain
- Ledger divergence
- Routing loops
- Malicious rebroadcast amplification

Observed failures are documented and fed back into protocol design.

---

## 10. Outputs and Artifacts

Each topology simulation produces:

- Network graphs over time
- Message propagation logs
- Energy usage estimates
- Ledger consistency reports
- Identified protocol weaknesses
- Recommended parameter adjustments

These outputs guide firmware and mesh protocol iteration.

---

## 11. Summary

Topology scenario simulations ensure Seed’s mesh network performs reliably across the most challenging real-world conditions. By validating behavior across sparse, dense, mobile, and partitioned environments, Seed achieves resilient, offline-first financial connectivity without relying on infrastructure, servers, or continuous power.

These simulations are foundational to Seed’s ability to operate at global scale in disconnected regions.
