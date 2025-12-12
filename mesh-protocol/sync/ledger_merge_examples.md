# Ledger Merge Examples

This document provides concrete, step-by-step examples showing how Seed devices merge ledger data across a fully offline, decentralized mesh network. These examples demonstrate how deterministic rules ensure that all devices converge to the same ledger state, regardless of message order, connectivity gaps, or network topology.

The purpose of this file is to make the conflict resolution and merge logic tangible, auditable, and explainable to engineers, auditors, and investors.

---

## 1. Why Ledger Merge Examples Matter

Seed operates without:
- Central servers
- Reliable internet
- Global clocks
- Guaranteed message order

As a result, devices will frequently:
- Create transactions in parallel
- Receive updates in different sequences
- Sync after long offline periods

Ledger merge examples prove that Seed can still:
- Prevent double-spending
- Maintain consistency
- Recover from network fragmentation
- Scale safely without coordination

---

## 2. Canonical Merge Rules (Reminder)

All examples in this document assume the following deterministic merge rules:

1. Transactions are uniquely identified by `tx_id`.
2. All transactions are sorted globally by:
   - Lamport clock (ascending)
   - Device ID (alphabetical) as a tie-breaker
3. Transactions are applied in this global order.
4. Invalid transactions are marked and skipped, not deleted.
5. Duplicate transactions are ignored (idempotency).
6. No real-world timestamps are used.

These rules guarantee identical outcomes on all devices.

---

## 3. Example A: Simple Two-Device Sync

### Initial State

Device A ledger:
- TX_A1 (lamport: 1, device: A)
- TX_A2 (lamport: 2, device: A)

Device B ledger:
- TX_B1 (lamport: 1, device: B)

### Sync Event

Device A and Device B exchange ledgers.

### Combined Transaction Set

- TX_A1 (1, A)
- TX_B1 (1, B)
- TX_A2 (2, A)

### Sorted Global Order

1. TX_A1 (lamport 1, device A)
2. TX_B1 (lamport 1, device B)
3. TX_A2 (lamport 2, device A)

### Result

Both devices apply transactions in the same order and reach an identical ledger state.

---

## 4. Example B: Out-of-Order Arrival

### Initial State

Device A creates:
- TX_A1 (lamport: 1)
- TX_A2 (lamport: 2)

Device B receives TX_A2 first due to network delays.

### Device B Temporary State

- TX_A2 (pending, missing causal predecessor)

### Later Event

Device B receives TX_A1.

### Merge Behavior

- Device B reorders transactions based on lamport clock.
- TX_A1 is applied before TX_A2.
- TX_A2 transitions from pending to valid.

### Result

Arrival order does not affect final ledger order.

---

## 5. Example C: Parallel Spending Attempt

### Initial State

Device A balance: 10 units

Device A creates:
- TX_A1: send 7 units (lamport 5)

Device A later creates:
- TX_A2: send 6 units (lamport 6)

### Merge Order

1. TX_A1 applied → remaining balance: 3
2. TX_A2 applied → insufficient funds

### Resolution

- TX_A1: valid
- TX_A2: invalid (marked, not deleted)

### Result

Double-spending is prevented deterministically.

---

## 6. Example D: Identical Lamport Clock Collision

### Initial State

Device A creates:
- TX_A1 (lamport 10)

Device B creates:
- TX_B1 (lamport 10)

### Tie-Breaker Rule

Device IDs are compared alphabetically.

### Sorted Order

1. TX_A1 (device A)
2. TX_B1 (device B)

### Result

All devices apply the same ordering without ambiguity.

---

## 7. Example E: Long Offline Device Rejoining

### Scenario

Device C is offline for weeks and creates:
- TX_C1 (lamport 20)
- TX_C2 (lamport 21)
- TX_C3 (lamport 22)

Meanwhile, the network advances to lamport 100.

### Rejoin Event

Device C reconnects and broadcasts its transactions.

### Merge Behavior

- All transactions are merged into the global set.
- TX_C transactions are ordered correctly based on lamport values.
- No special reconciliation is required.

### Result

Offline history merges seamlessly.

---

## 8. Example F: Group Savings Rotation Conflict

### Scenario

Two devices submit updates for the same group savings round.

- TX_G1 (lamport 30, device B)
- TX_G2 (lamport 30, device C)

### Resolution

- Alphabetical device ID determines winner.
- Losing transaction is archived as a shadow record.

### Result

Group state remains consistent and auditable.

---

## 9. Example G: Duplicate Sync Events

### Scenario

Device A receives the same transaction set multiple times.

### Merge Behavior

- Existing `tx_id`s are ignored.
- No state changes occur.

### Result

Sync operations are safe to repeat.

---

## 10. Failure Recovery Example

### Scenario

A device crashes mid-sync after importing half of a transaction batch.

### Recovery

- On restart, device reloads last checkpoint.
- Re-imports full batch.
- Duplicate entries are ignored.

### Result

Ledger integrity is preserved.

---

## 11. Auditability and Transparency

Because all merge decisions are deterministic and reproducible:
- Auditors can replay the ledger from raw transactions
- Disputes can be resolved without trust in any single device
- Regulators can inspect merge logic without accessing private data

---

## 12. Summary

These examples demonstrate that Seed’s ledger merge system:
- Works without internet
- Handles real-world network failures
- Prevents fraud
- Scales naturally
- Produces identical results on all devices

Ledger merge behavior is predictable, verifiable, and resilient — forming the backbone of Seed’s offline financial system.
