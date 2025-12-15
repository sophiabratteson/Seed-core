# Conflict Resolution Logic — Protocol Specification

This document defines the canonical conflict resolution rules for the Seed protocol. These rules ensure that all Seed devices—operating without centralized servers, clocks, or continuous connectivity—converge on the same ledger state despite delays, partitions, or adversarial conditions.

This file is part of the **protocol specification layer**, meaning it defines **what must happen**, not how individual firmware implementations achieve it.

---

## 1. Purpose and Scope

The conflict resolution logic exists to:

- Guarantee deterministic ledger convergence across all Seed devices
- Prevent double-spending and ledger divergence
- Enable safe offline-first operation
- Allow parallel transaction creation across disconnected nodes
- Remain resilient to malicious or faulty nodes

This logic applies to:

- Individual transactions
- Group savings updates
- Trust score updates
- Ledger synchronization events

---

## 2. Core Design Principles

The Seed protocol follows these non-negotiable principles:

- **Determinism**: Given the same transaction set, all devices produce the same ledger
- **Offline-first**: No reliance on real-time clocks or internet connectivity
- **Idempotence**: Reapplying the same transaction never changes state
- **Eventual consistency**: Devices converge over time, not instantly
- **Minimal trust**: Devices do not assume honest behavior from peers

---

## 3. Conflict Definition

A conflict occurs when:

- Two or more transactions compete for the same resources
- Transactions arrive in different orders on different devices
- Parallel updates modify the same logical state
- A device reconnects after long offline periods
- Malicious or malformed transactions are introduced

Conflicts are resolved **algorithmically**, never manually.

---

## 4. Logical Ordering Mechanism

Seed uses **Lamport Logical Clocks** combined with deterministic tie-breakers.

Each transaction includes:

- `lamport`: Monotonically increasing logical counter
- `device_id`: Globally unique device identifier
- `tx_id`: Unique transaction identifier

### Ordering Rule

Transactions are globally ordered by:

1. Lowest `lamport` value first
2. If equal, lexicographically smallest `device_id`
3. If still equal (extremely unlikely), lowest `tx_id`

This ordering is absolute and universal.

---

## 5. Transaction Validity Rules

Before application, each transaction is validated:

- Signature must be valid
- Data format must match protocol spec
- Causal dependencies (if any) must exist
- Sender must have sufficient balance or authority
- Transaction must not already be finalized

Invalid transactions are retained for audit but never applied.

---

## 6. Conflict Resolution Scenarios

### Scenario A: Double Spending

- Two transactions attempt to spend the same funds
- Apply in deterministic order
- First valid transaction succeeds
- Subsequent transaction fails due to insufficient balance

### Scenario B: Parallel Offline Transactions

- Devices create transactions independently
- On reconnection, all transactions are merged
- Ordering rules ensure identical replay order
- Ledger converges deterministically

### Scenario C: Simultaneous Group Savings Updates

- Updates include `group_id` and `update_index`
- If collision occurs:
  - Higher lamport wins
  - Loser is archived as shadow state

### Scenario D: Replay or Duplicate Transactions

- Duplicate `tx_id` detected
- Transaction ignored (idempotent behavior)

---

## 7. Ledger Merge Algorithm (Normative)

All implementations MUST perform the following steps:

1. Collect all known transactions
2. Remove duplicates by `tx_id`
3. Validate each transaction
4. Sort transactions using global ordering rules
5. Replay transactions sequentially
6. Reject invalid transactions during replay
7. Produce final ledger state
8. Store checkpoint hash

This algorithm MUST NOT depend on arrival order or timestamps.

---

## 8. Orphan and Pending Transactions

Transactions may enter temporary states:

- **Pending**: Awaiting missing causal dependencies
- **Orphaned**: Dependencies never satisfied after timeout
- **Invalid**: Failed validation

Pending transactions are retried during future syncs.

---

## 9. Security Considerations

Conflict resolution prevents:

- Ledger reordering attacks
- Replay attacks
- Fork creation
- Partial history injection

Malicious nodes cannot influence final state without controlling ordering rules, which are deterministic and universal.

---

## 10. Extensibility

Future versions MAY introduce:

- Vector clocks for richer causality
- Merkle-based state proofs
- Zero-knowledge transaction validation
- Trust-weighted prioritization (optional, non-default)

Backward compatibility must be preserved.

---

## 11. Protocol Guarantees

By following this specification, Seed guarantees:

- Identical ledger state across honest nodes
- Safe offline operation
- Predictable and auditable conflict handling
- No reliance on central authorities

This conflict resolution logic is foundational to Seed’s ability to operate as a global, decentralized financial system without internet access.

---
