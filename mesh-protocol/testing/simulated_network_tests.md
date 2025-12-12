# Simulated Network Tests

This document defines how the Seed mesh protocol is tested using simulated network environments. These simulations are designed to validate correctness, resilience, security, and scalability before real-world hardware deployment. Simulated testing allows controlled experimentation across extreme and edge-case conditions that are difficult or expensive to reproduce physically.

---

## 1. Purpose of Simulated Network Testing

The goals of simulated network tests are to:

- Validate correctness of mesh protocol logic under varied conditions
- Ensure deterministic ledger convergence across devices
- Test resilience to packet loss, latency, and partial connectivity
- Evaluate power-saving behaviors and duty cycling
- Stress-test security mechanisms against adversarial conditions
- Identify failure modes before hardware field trials

Simulations act as a safety net before real-world pilots.

---

## 2. Simulation Environment Overview

Simulations are run using software-based node models that emulate Seed devices.

Each simulated node includes:
- Device identity (device_id)
- Logical clock (Lamport)
- Local ledger state
- Radio interface abstraction
- Power budget constraints
- Message queues and buffers

The environment controls:
- Network topology
- Link quality
- Transmission delays
- Packet loss rates
- Node mobility
- Node failure and recovery

---

## 3. Core Simulation Parameters

Simulated tests vary the following parameters:

- Node count (2 to 1,000+)
- Network topology (line, star, mesh, clustered)
- Transmission range overlap
- Packet loss rate (0%–60%)
- Message delay (milliseconds to hours)
- Node uptime/downtime cycles
- Power availability patterns

Each test run logs full protocol behavior for analysis.

---

## 4. Test Categories

### 4.1 Connectivity Tests

These tests verify that nodes can discover and communicate with neighbors.

Scenarios:
- Initial cold start discovery
- Dynamic join and leave events
- Network partition and reconnection
- Sparse vs dense node distributions

Expected outcomes:
- Stable neighbor tables
- No permanent isolation if paths exist
- Graceful handling of partitions

---

### 4.2 Ledger Synchronization Tests

These tests ensure ledger consistency across nodes.

Scenarios:
- Simultaneous transaction creation
- Delayed message propagation
- Offline node rejoining after long absence
- Partial ledger availability

Expected outcomes:
- Deterministic merge results
- No double-spending
- Eventual ledger convergence

---

### 4.3 Conflict Resolution Stress Tests

These tests intentionally induce conflicts.

Scenarios:
- Same sender creating conflicting transactions
- Concurrent group savings updates
- Competing trust score updates
- Lamport timestamp collisions

Expected outcomes:
- Deterministic conflict resolution
- Invalid transactions rejected consistently
- No divergence across nodes

---

### 4.4 Packet Loss and Retry Tests

These tests simulate unreliable radio conditions.

Scenarios:
- Random packet drops
- Burst loss events
- One-way message failures
- Corrupted payload injection

Expected outcomes:
- Retry logic functions correctly
- No infinite retry loops
- Eventual delivery or graceful failure

---

### 4.5 Power Constraint Simulations

These tests model limited energy availability.

Scenarios:
- Low battery nodes
- Aggressive sleep cycles
- Solar recharge variability
- Hand-crank recharge events

Expected outcomes:
- Reduced transmission rates under low power
- Preservation of critical state
- Recovery after power restoration

---

## 5. Adversarial and Abuse Scenarios

Simulations include malicious or faulty nodes.

Scenarios:
- Flooding attacks
- Replay attempts
- Malformed message injection
- Identity spoof attempts
- Trust score manipulation attempts

Expected outcomes:
- Attack detection
- Rate limiting enforcement
- Invalid messages discarded
- Honest nodes unaffected

---

## 6. Metrics Collected

Each simulation run records:

- Ledger convergence time
- Message delivery success rate
- Power consumption per node
- Conflict frequency
- Retry counts
- Invalid message rate
- Network throughput
- Node isolation duration

Metrics are used to guide protocol tuning.

---

## 7. Determinism Verification

A key requirement is deterministic behavior.

Method:
- Run identical simulations multiple times
- Shuffle message delivery order
- Compare final ledger states across runs

Expected result:
- All runs converge to identical ledger state

Any divergence is treated as a critical failure.

---

## 8. Failure Mode Analysis

Simulations intentionally trigger failures.

Examples:
- Node crashes mid-sync
- Storage corruption
- Clock reset events
- Incomplete message propagation

Expected behavior:
- Recovery without global reset
- No irreversible ledger corruption
- Graceful degradation

---

## 9. Tooling and Implementation

Simulations may be implemented using:
- Python-based node simulators
- Discrete event simulation frameworks
- Custom test harnesses
- Reproducible random seeds

All simulations are fully reproducible.

---

## 10. Transition to Physical Testing

Results from simulated tests directly inform:
- Radio parameter tuning
- Power budget assumptions
- Retry and backoff strategies
- Security hardening
- Field test planning

Simulation success is required before live hardware pilots.

---

## 11. Summary

Simulated network testing is a foundational validation layer for Seed. By exhaustively testing the mesh protocol under controlled but extreme conditions, Seed ensures reliability, security, and correctness before deployment in real-world, low-connectivity environments.

This approach minimizes risk, accelerates iteration, and builds confidence for investors, partners, and regulators.
