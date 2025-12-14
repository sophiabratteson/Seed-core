# Conflict Cases and Outcomes – Ledger Simulation

This document enumerates and analyzes the primary conflict scenarios that arise in Seed’s offline-first distributed ledger system. It explains how conflicts are detected, resolved, and validated during simulations to ensure deterministic convergence across all devices.

---

## Purpose of This Document

The goals of this simulation document are to:

- Enumerate realistic conflict scenarios expected in offline financial systems
- Demonstrate that Seed’s conflict resolution logic handles these scenarios safely
- Provide deterministic outcomes regardless of message order or connectivity
- Validate that the system prevents double-spending, replay attacks, and ledger divergence
- Support investor and auditor confidence through formalized reasoning

---

## Core Assumptions for Simulations

All simulations in this document assume:

- Devices operate fully offline for extended periods
- No centralized authority or server exists
- Devices synchronize opportunistically via mesh communication
- All devices follow the same deterministic merge rules
- Transactions are immutable once created
- Every device maintains its own local ledger copy

---

## Conflict Case 1: Duplicate Transaction Arrival

### Scenario
- Device A creates Transaction T1
- Device B receives T1 through the mesh
- Device C later receives T1 again via a different path

### Detection
- Transaction ID (tx_id) already exists in ledger

### Resolution
- Transaction is ignored
- Ledger remains unchanged

### Outcome
- Idempotent behavior preserved
- No duplication or double-counting

---

## Conflict Case 2: Simultaneous Transactions with Same Lamport Clock

### Scenario
- Device A and Device B both create transactions at Lamport time = 10
- Both transactions are valid and independent

### Detection
- Lamport timestamps are equal

### Resolution
- Compare device IDs lexicographically
- Lower device ID is applied first

### Outcome
- Deterministic ordering across all devices
- Ledger convergence guaranteed

---

## Conflict Case 3: Double-Spend Attempt (Same Sender)

### Scenario
- Device A creates Transaction T1 spending balance X
- Device A creates Transaction T2 spending the same balance X
- Both transactions propagate independently

### Detection
- When applying transactions sequentially, balance becomes insufficient

### Resolution
- Apply transactions in deterministic order
- First transaction succeeds
- Second transaction marked invalid

### Outcome
- No double-spending
- Full audit trail preserved

---

## Conflict Case 4: Out-of-Order Transaction Arrival

### Scenario
- Transaction T2 references T1 as a causal dependency
- Device receives T2 before T1

### Detection
- Missing causal reference detected via prev_tx_ids

### Resolution
- T2 placed into pending state
- T2 applied only after T1 arrives

### Outcome
- Causal consistency preserved
- Ledger correctness maintained

---

## Conflict Case 5: Long Offline Device Rejoining Network

### Scenario
- Device D operates offline for weeks
- Creates dozens of transactions
- Rejoins network with large backlog

### Detection
- Multiple unknown transactions received

### Resolution
- Transactions merged via global deterministic ordering
- Invalid transactions filtered during validation

### Outcome
- Seamless reintegration
- No special privileges or penalties required

---

## Conflict Case 6: Conflicting Group Savings Updates

### Scenario
- Two group members submit group updates concurrently
- Updates reference same group round index

### Detection
- Same group_id and same round number

### Resolution
- Higher Lamport timestamp wins
- Losing update archived but not applied

### Outcome
- Group fund integrity maintained
- Transparency preserved

---

## Conflict Case 7: Malicious Replay Attack

### Scenario
- Attacker rebroadcasts old valid transaction

### Detection
- tx_id already exists
- Lamport timestamp lower than current state

### Resolution
- Transaction ignored

### Outcome
- Replay attacks ineffective
- Ledger remains unchanged

---

## Conflict Case 8: Corrupted or Tampered Transaction

### Scenario
- Transaction arrives with modified payload

### Detection
- Signature verification fails
- Hash mismatch detected

### Resolution
- Transaction rejected
- Error logged locally

### Outcome
- Security boundary enforced
- No ledger contamination

---

## Conflict Case 9: Partial Sync Failure

### Scenario
- Device receives only a subset of transactions
- Sync interrupted due to power loss

### Detection
- Missing transaction gaps during validation

### Resolution
- Ledger remains in partially updated state
- Missing transactions requested during next sync

### Outcome
- Fault tolerance maintained
- No rollback required

---

## Simulation Metrics Tracked

During simulations, the following metrics are recorded:

- Ledger convergence time
- Number of rejected transactions
- Pending transaction queue depth
- Invalid transaction rate
- Power usage per sync cycle

---

## Simulation Success Criteria

A simulation run is considered successful if:

- All devices converge to identical ledger state
- No valid transaction is lost
- No invalid transaction is applied
- Deterministic ordering is preserved
- No manual intervention is required

---

## Summary

These conflict simulations demonstrate that Seed’s ledger architecture can safely handle the full spectrum of real-world offline financial conflicts. Through deterministic ordering, causal tracking, and strict validation, Seed ensures consistency, security, and resilience without relying on centralized infrastructure.

This simulation framework forms the foundation for field testing, hardware-in-the-loop testing, and future regulatory audits.
