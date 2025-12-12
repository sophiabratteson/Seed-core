# Conflict Resolution Rules

This document defines the deterministic conflict resolution rules used by the Seed mesh protocol. These rules ensure that all Seed devices converge on the same ledger state even when transactions are created offline, arrive out of order, or conflict with one another. No central authority, server, or real-time clock is required.

---

## 1. Purpose and Design Principles

The conflict resolution system is designed to:

- Guarantee eventual ledger consistency across all devices
- Prevent double-spending and replay attacks
- Support long offline periods and intermittent connectivity
- Operate without trusted servers or global timestamps
- Behave deterministically so all nodes reach identical outcomes

Every rule in this document prioritizes predictability, simplicity, and resilience in low-connectivity environments.

---

## 2. Core Conflict Resolution Model

Seed uses a **deterministic merge model** based on logical ordering rather than arrival order.

The system relies on:
- Lamport logical clocks
- Unique device identifiers
- Immutable transaction IDs
- Global deterministic sorting rules

Transactions are never deleted. Invalid or losing transactions are retained with an invalid status for auditability.

---

## 3. Lamport Logical Clock Rules

Each Seed device maintains a local Lamport counter.

Rules:
- The counter increments by 1 for every locally created transaction
- When receiving transactions, the device updates its counter to:
  max(local_clock, received_clock) + 1
- Lamport clocks represent causal ordering, not real time
- Higher Lamport values always represent later events

Lamport clocks allow fully offline ordering without synchronized clocks.

---

## 4. Deterministic Ordering Rules

All devices apply transactions in the same global order.

Sorting keys (in order):
1. Lamport clock (ascending)
2. Device ID (lexicographical order)
3. Transaction ID (lexicographical order, final tie-breaker)

This guarantees that every device produces the same ordered transaction list regardless of sync path or timing.

---

## 5. Transaction Uniqueness Rules

- Every transaction has a globally unique `tx_id`
- Duplicate `tx_id`s are ignored after first acceptance
- Re-importing the same transaction is idempotent
- Transactions are immutable once created

If two transactions share the same `tx_id` but differ in content, the transaction with the higher Lamport value is retained and the other is marked invalid.

---

## 6. Conflict Scenarios and Resolution Rules

### Scenario A: Double-Spend Attempt

If two transactions attempt to spend the same balance:

- Apply transactions in deterministic order
- The first valid transaction succeeds
- Subsequent conflicting transactions fail balance validation
- Failed transactions are marked invalid but preserved

---

### Scenario B: Simultaneous Transactions from Same Device

If two transactions from the same device have consecutive Lamport values:

- Both are applied in Lamport order
- No conflict exists unless balance or rule violations occur

---

### Scenario C: Offline Device Rejoins Network

When an offline device reconnects:

- All of its transactions are merged into the global pool
- Transactions are reordered using deterministic rules
- Invalid transactions are detected during reapplication
- No special reconciliation process is required

---

### Scenario D: Out-of-Order Transaction Arrival

Arrival order is ignored.

- Devices buffer transactions as needed
- Sorting and validation occur after merge
- Missing dependencies place transactions in a pending state until resolved

---

### Scenario E: Group or Trust-Score Conflicts

For group savings or trust-score updates:

- Each update includes a sequence index
- Conflicts at the same index are resolved by:
  - Higher Lamport clock
  - Device ID tie-breaker
- Losing updates are archived as shadow records

---

## 7. Transaction States

Each transaction exists in one of the following states:

- **Valid**: Applied successfully to the ledger
- **Pending**: Awaiting missing dependencies
- **Invalid**: Violates rules (double-spend, bad signature, etc.)
- **Orphaned**: Dependencies never resolved after timeout

State transitions are deterministic and auditable.

---

## 8. Ledger Merge Algorithm

When syncing with another node:

1. Collect all known transactions
2. Deduplicate by `tx_id`
3. Validate structure and signatures
4. Sort using deterministic ordering rules
5. Apply transactions sequentially
6. Mark invalid transactions as failed
7. Persist final ledger state

This algorithm guarantees convergence across the entire mesh.

---

## 9. Security Guarantees

The conflict resolution system ensures:

- No transaction reordering attacks
- No replay attacks
- No dependency manipulation
- No ledger divergence
- No trust in arrival order or peers

All outcomes are locally verifiable.

---

## 10. Failure Handling

- Devices may safely crash and restart
- Partial syncs do not corrupt state
- Conflicts are resolved on next merge
- Ledger integrity is preserved across power loss

---

## 11. Future Enhancements

Potential future upgrades include:

- Vector clocks for complex causal graphs
- Merkle-based ledger summaries
- Selective disclosure proofs
- Privacy-preserving conflict proofs

These enhancements do not alter the core deterministic model.

---

## 12. Summary

Seed’s conflict resolution rules allow a fully decentralized financial system to function without servers, internet, or clocks. By enforcing deterministic ordering, immutable transactions, and strict validation, every device independently arrives at the same ledger state—no matter how fragmented, delayed, or adversarial the network becomes.

This mechanism is the backbone of Seed’s offline-first financial infrastructure.
