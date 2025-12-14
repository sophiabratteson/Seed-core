# Ledger Simulation Overview

This document describes the purpose, scope, assumptions, and structure of the **Seed Ledger Simulation**. The ledger simulation is a non-hardware, software-only environment used to validate Seed’s offline-first financial logic before deployment to real devices. It is designed to test correctness, convergence, and resilience of the ledger under realistic edge conditions.

---

## 1. Purpose of the Ledger Simulation

The ledger simulation exists to answer one core question:

**Can independent Seed devices, operating without internet or central servers, always converge on the same correct financial state?**

Specifically, the simulation is used to:
- Validate deterministic conflict resolution logic
- Test offline-first synchronization behavior
- Model multi-device transaction creation
- Explore failure, delay, and recovery scenarios
- Demonstrate correctness to investors, researchers, and regulators
- Reduce hardware risk by validating logic early

The simulation acts as a *truth laboratory* for Seed’s financial core.

---

## 2. What the Ledger Simulation Is (and Is Not)

### What it *is*:
- A logical model of Seed’s ledger behavior
- A multi-node environment where devices act independently
- A reproducible, deterministic test harness
- A substitute for early hardware testing

### What it *is not*:
- A performance benchmark
- A UI or end-user product
- A replacement for real radio testing
- A blockchain or proof-of-work system

---

## 3. Simulation Scope

The ledger simulation models the following components:

- Device identities
- Local ledger state
- Transaction creation
- Logical time (Lamport clocks)
- Conflict resolution
- Offline sync events
- Ledger convergence

It intentionally excludes:
- Cryptographic implementation details
- Real radio stack behavior
- Hardware power constraints
- User interface logic

---

## 4. Core Assumptions

The simulation operates under these assumptions:

- Each device has a unique device ID
- Devices may be offline indefinitely
- Transactions may arrive out of order
- Devices never share a global clock
- Devices may see partial histories
- No central authority exists

These assumptions mirror the real-world conditions Seed is designed for.

---

## 5. Simulated Device Model

Each simulated device includes:

- `device_id`: globally unique identifier
- `ledger`: local transaction store
- `lamport_clock`: logical event counter
- `outbox`: transactions available for sync
- `inbox`: newly received transactions

Devices behave autonomously and never “ask permission” from others.

---

## 6. Transaction Lifecycle in Simulation

Each transaction passes through these stages:

1. Created locally by a device
2. Assigned a Lamport timestamp
3. Added to local ledger
4. Exported during sync opportunity
5. Imported by peer devices
6. Sorted deterministically
7. Validated against ledger rules
8. Accepted or rejected
9. Checkpointed into stable state

The simulation ensures each step is observable and auditable.

---

## 7. Ledger Merge Logic (High-Level)

When two devices sync:

1. Combine both transaction sets
2. Remove duplicates by `tx_id`
3. Validate data structure
4. Sort transactions by:
   - Lamport timestamp (ascending)
   - Device ID (tie-breaker)
5. Apply transactions sequentially
6. Mark invalid transactions without halting
7. Persist final ledger state

This process guarantees convergence regardless of arrival order.

---

## 8. Conflict Scenarios Tested

The simulation explicitly tests:

- Double-spend attempts
- Parallel transactions from same account
- Delayed sync after long offline periods
- Repeated transaction imports
- Partial ledger visibility
- Group savings conflicts
- Trust score collisions

Each scenario must result in identical final ledger states across devices.

---

## 9. Determinism Guarantee

A critical design requirement:

> **Given the same set of transactions, all Seed devices must produce the exact same ledger state.**

The simulation enforces this by:
- Eliminating real-time dependencies
- Avoiding randomness
- Using strict ordering rules
- Ensuring idempotent transaction application

This property is foundational to Seed’s trust model.

---

## 10. Outputs of the Simulation

The ledger simulation produces:

- Final ledger states per device
- Transaction ordering logs
- Conflict resolution traces
- Invalid transaction reports
- Sync convergence confirmation

These outputs are used for:
- Investor demos
- Technical validation
- Academic review
- Architecture confidence

---

## 11. Relationship to Other Simulations

This ledger simulation integrates conceptually with:

- Radio mesh simulations
- Power budget simulations
- User behavior simulations
- Security threat simulations

However, it remains intentionally isolated to ensure clarity and correctness of the financial core.

---

## 12. Future Extensions

Planned enhancements include:

- Merkle-based state compression
- Vector clock experimentation
- Probabilistic packet loss modeling
- Large-scale (100+ node) simulations
- Regulatory audit-mode simulation
- Visualization of ledger convergence

---

## 13. Investor Relevance

For investors, this simulation demonstrates:

- Seed’s technical seriousness
- Offline-first feasibility
- Risk mitigation before hardware spend
- Deterministic financial correctness
- Scalability of logic without infrastructure

It proves that Seed is not a concept — it is an engineered system.

---

## 14. Summary

The ledger simulation is the **foundation of Seed’s credibility**. It validates that a decentralized, offline, serverless financial system can function reliably under extreme constraints. Everything else in Seed — hardware, radio, UI, AI — builds on this core.

If the ledger simulation works, Seed works.
