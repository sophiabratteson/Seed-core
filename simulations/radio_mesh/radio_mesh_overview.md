# Radio Mesh Simulation Overview

This document defines how Seed simulates its radio mesh network to evaluate feasibility, performance, resilience, and scalability in fully offline environments. The goal of these simulations is to validate that Seed devices can reliably exchange financial data without internet, cellular service, or centralized infrastructure.

---

## 1. Purpose of Radio Mesh Simulations

Radio mesh simulations are used to:

- Validate that Seed devices can discover each other autonomously
- Measure communication reliability under real-world constraints
- Test ledger synchronization behavior across multi-hop networks
- Identify scalability limits and bottlenecks
- Evaluate energy usage tradeoffs in radio communication
- Stress-test the system under failure and adversarial conditions

These simulations guide hardware selection, firmware configuration, and protocol design before large-scale deployment.

---

## 2. Simulation Scope

The radio mesh simulation focuses on:

- Device-to-device LoRa communication
- Multi-hop routing behavior
- Packet loss and retry mechanisms
- Network partitioning and re-merging
- Power-aware transmission strategies
- Realistic environmental constraints

The simulation does not rely on internet connectivity or centralized servers.

---

## 3. Simulated Hardware Assumptions

The simulations assume devices with the following characteristics:

- LoRa radio (SX1276 or SX1262 class)
- Configurable transmission power (0–20 dBm)
- Adjustable spreading factor and bandwidth
- Omnidirectional antenna
- Limited memory and storage
- Battery-powered operation

These assumptions align with Seed’s intended production hardware.

---

## 4. Network Topology Models

The simulation supports multiple topology configurations:

### Single-Hop
- All devices are within direct radio range
- Used to establish baseline performance

### Multi-Hop Mesh
- Devices relay messages on behalf of others
- Used to test routing efficiency and convergence

### Sparse Mesh
- Devices are intermittently connected
- Used to simulate rural or disaster environments

### Dense Mesh
- Many devices in close proximity
- Used to evaluate congestion and collision handling

---

## 5. Message Types Simulated

The radio mesh simulation handles the following message categories:

- Transaction broadcasts
- Ledger synchronization packets
- Heartbeat and presence announcements
- Neighbor discovery beacons
- Trust score updates
- Group savings coordination messages
- Error and integrity reports

Each message type is modeled with realistic size and frequency constraints.

---

## 6. Transmission Model

Each simulated transmission includes:

- Payload size (bytes)
- Transmission power
- Spreading factor
- Data rate
- Time-on-air calculation
- Energy cost estimate

The model accounts for collisions, interference, and regulatory duty-cycle limits.

---

## 7. Packet Loss and Reliability

The simulation introduces probabilistic packet loss based on:

- Distance between devices
- Environmental noise
- Network congestion
- Battery state
- Antenna orientation variability

Retry logic and acknowledgment mechanisms are evaluated to ensure eventual message delivery without excessive power drain.

---

## 8. Routing Behavior

Routing simulations evaluate:

- Flooding-based dissemination
- Gossip-based propagation
- Hybrid adaptive routing
- Loop prevention mechanisms
- Path redundancy handling

The simulation measures how quickly information spreads and how much redundant traffic is generated.

---

## 9. Power Consumption Modeling

Each radio action consumes simulated energy based on:

- Transmission duration
- Reception time
- Idle listening
- Sleep cycles

Results are used to estimate battery lifetime under different usage profiles.

---

## 10. Failure Scenarios Simulated

The radio mesh simulation includes:

- Sudden device shutdown
- Battery depletion
- Radio interference spikes
- Network partitions
- Malicious or misbehaving nodes
- Environmental obstructions

Recovery behavior and convergence time are measured.

---

## 11. Metrics Collected

The simulation records:

- Message delivery success rate
- Average sync latency
- Network convergence time
- Energy consumed per transaction
- Number of hops per message
- Redundant packet overhead
- Failure recovery time

These metrics inform design tradeoffs and optimization priorities.

---

## 12. Outputs and Artifacts

Simulation outputs include:

- Network state timelines
- Energy usage graphs
- Delivery probability distributions
- Convergence visualizations
- Parameter sensitivity analyses

Results are stored for comparison across simulation runs.

---

## 13. Relationship to Other Simulations

This radio mesh simulation feeds into:

- Ledger synchronization simulations
- Power budget simulations
- Security threat simulations
- End-to-end integration scenarios

Together, these simulations validate Seed’s offline-first architecture.

---

## 14. Key Design Questions Addressed

- How far can Seed devices reliably communicate?
- How many devices can participate in a mesh?
- What configuration maximizes reliability per watt?
- How does the system behave when connectivity is intermittent?
- What tradeoffs exist between speed, reliability, and energy?

---

## 15. Summary

The radio mesh simulation is a foundational validation tool for Seed. It ensures that the system’s core promise—secure, decentralized financial coordination without internet—is technically viable at scale. By modeling real-world radio behavior and constraints, Seed can confidently progress from prototype to deployment.
