# Ledger Engine – Conflict Resolution

## Purpose

This document defines how the Seed ledger engine resolves conflicts that arise in a fully decentralized, offline-first financial system. Because Seed devices operate without continuous internet access or centralized servers, transactions may be created concurrently, arrive out of order, or partially overlap across devices. The conflict resolution logic ensures that all honest devices eventually converge on the same ledger state.

This system is designed to be deterministic, auditable, resilient to network disruptions, and resistant to malicious behavior.

---

## Design Goals

- Guarantee eventual ledger consistency across all devices
- Prevent double-spending and replay attacks
- Support long offline periods without data loss
- Operate without wall-clock time or trusted servers
- Ensure identical results across all devices given the same data
- Maintain transparency and auditability for users and regulators

---

## Core Principles

### Determinism
Every Seed device must reach the same ledger state when given the same set of transactions, regardless of order of arrival or network topology.

### Offline-First
All conflict resolution must function without reliance on real-time connectivity, trusted timestamps, or centralized coordination.

### Safety Over Liveness
In ambiguous cases, the system prioritizes preventing incorrect ledger states (e.g., double spending) even if some transactions are delayed or invalidated.

---

## Logical Time Model

### Lamport Logical Clocks

Each Seed device maintains a monotonically increasing logical clock:

- The clock increments for every locally created transaction
- Incoming transactions update the local clock if they contain a higher value
- Logical clocks establish a partial ordering of events without real timestamps

Logical clocks allow Seed to reason about ordering in environments where real time cannot be trusted or synchronized.

---

## Transaction Identity

Each transaction contains:

- A globally unique transaction ID (`tx_id`)
- The originating device ID
- A Lamport clock value
- Optional causal references to previous transactions
- A cryptographic signature

Transactions are immutable once created.

---

## Transaction States

Transactions exist in one of the following states:

- **Pending** – Valid format but missing required dependencies
- **Valid** – Fully verified and applied to the ledger
- **Invalid** – Violates ledger rules or fails cryptographic checks
- **Orphaned** – References missing ancestors after retry windows expire

State transitions are deterministic and reversible only through new valid transactions.

---

## Conflict Types and Resolution Rules

### 1. Duplicate Transaction IDs

If two transactions share the same `tx_id`:

- Compare Lamport clock values
- Retain the transaction with the higher clock
- If clocks are equal, compare device IDs lexicographically
- Discard the losing transaction

This scenario is rare and indicates either corruption or malicious behavior.

---

### 2. Double Spending

If two transactions attempt to spend the same balance:

- Sort transactions deterministically
- Apply in order
- The first valid transaction succeeds
- Subsequent transactions fail validation due to insufficient funds

No rollback occurs after application.

---

### 3. Out-of-Order Arrival

Transactions may arrive in any order due to offline syncing.

Resolution:

- Store all transactions
- Sort globally using deterministic ordering
- Re-apply ledger from a known checkpoint
- Reach identical final balances across devices

---

### 4. Concurrent Transactions from Same Device

If a device generates multiple transactions while offline:

- Each transaction carries increasing Lamport values
- Devices replay them in logical order
- Conflicts with other devices resolve deterministically

---

### 5. Group-Based Conflicts (Savings & Trust Scores)

Group updates include:

- Group ID
- Update sequence number
- Lamport clock

If two updates conflict:

- Higher Lamport value wins
- Losing update is archived but not applied
- Group state remains consistent across all nodes

---

## Deterministic Merge Algorithm

When syncing ledgers:

1. Collect all known transactions
2. Remove duplicates by `tx_id`
3. Verify signatures and data integrity
4. Sort transactions by:
   - Lamport clock (ascending)
   - Device ID (lexicographic)
5. Apply transactions sequentially
6. Mark failures as invalid
7. Save checkpoint state

This process guarantees convergence without coordination.

---

## Data Structures

### Transaction Object

```
{
  "tx_id": "string",
  "sender": "string",
  "receiver": "string",
  "amount": number,
  "lamport": number,
  "device_id": "string",
  "prev_tx_ids": ["string"],
  "signature": "string"
}
```

### Ledger State

- Transaction map keyed by `tx_id`
- Ordered transaction log
- Cached balances
- Checkpoint hashes

---

## Security Considerations

- Replay attacks prevented via Lamport ordering
- Tampered transactions fail signature checks
- Malicious reordering is ineffective due to deterministic sorting
- Ledger history is append-only and auditable

---

## Failure Handling

- Devices may temporarily diverge
- No permanent forks occur
- Missing data is resolved during later syncs
- Invalid transactions never affect balances

---

## Future Enhancements

- Vector clocks for richer causal modeling
- Merkle proofs for lightweight sync
- Zero-knowledge validation for privacy
- Trust-weighted conflict prioritization

---

## Summary

Seed’s ledger conflict resolution system enables secure, decentralized financial coordination without internet access or centralized control. By combining logical clocks, deterministic ordering, and strict validation rules, Seed ensures that every honest device independently reconstructs the same financial reality — even in the most disconnected environments.
