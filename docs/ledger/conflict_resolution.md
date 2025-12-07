# Conflict Resolution Logic

This document explains how Seed devices maintain a consistent ledger across a fully distributed, offline-first mesh network. Because devices do not rely on a central server, transactions may arrive at different times, in different orders, or in conflicting states. The conflict resolution logic ensures that every device eventually converges on the same ledger state.

---

# 1. Goals of Conflict Resolution

- Ensure all devices eventually reach consistent ledger state.
- Prevent double-spending or replaying old transactions.
- Enable synchronization even when devices have been offline for long periods.
- Allow safe merging of transaction histories created in parallel.
- Maintain deterministic behavior so all devices reach identical results.

---

# 2. Core Concepts

## Lamport Logical Clocks
- Each device maintains an increasing counter.
- Every new transaction increments this counter.
- A higher lamport clock value always represents a “later” event.
- Logical clocks work completely offline without real timestamps.

## Causal References
- Transactions may include references to earlier transaction IDs.
- These references form local causal chains.
- Devices can detect missing ancestors or incomplete sequences.
- Helps maintain order even when receiving out-of-order data.

## Deterministic Tie-Breaker
Used when two transactions share the same lamport timestamp:

1. Compare device IDs alphabetically.
2. The transaction from the lexicographically “smaller” device ID is considered earlier.

This ensures **every device merges transactions in a globally deterministic way**.

## Idempotent Application
- Re-importing the same transaction has no effect.
- Prevents ledger corruption when multiple neighbors broadcast the same data.

---

# 3. Transaction States

Seed devices categorize every transaction into one of four states:

- **Pending** — Transaction seen but not yet valid due to missing ancestors.
- **Valid** — Fully accepted and applied to the ledger.
- **Invalid** — Violates signatures, balance rules, or other validation checks.
- **Orphaned** — Causal references cannot be recovered after repeated attempts.

Pending and orphan states allow devices to function in unstable mesh environments.

---

# 4. Conflict Scenarios & Resolution Rules

## Scenario A: Same transaction ID but different content
Normally impossible, but if tampering or corruption occurs:

1. Compare lamport values — higher wins.
2. If equal, compare device IDs — alphabetical winner wins.
3. Discard the other version.

## Scenario B: Double-spending from the same sender
Two transactions might spend the same funds:

- Determine global order using lamport + device ID.
- Apply the earlier transaction.
- The later transaction becomes **invalid** due to insufficient balance.

## Scenario C: Different arrival orders across devices
Because devices sync in different environments:

- Global ordering is recomputed using:
  - lamport (ascending)
  - device_id (alphabetical)
- All devices eventually converge to the same order.

## Scenario D: Device offline for long periods
Offline device creates many local transactions:

- When reconnected:
  - Transactions merge into global ledger based on deterministic rules.
  - No internet or coordinated clock is required.

## Scenario E: Group savings or trust-score collisions
Group-based updates carry a **group_id** and **update index**.

If two updates target the same index:

1. The update with higher lamport wins.
2. The loser becomes a shadow entry (audit-only).

---

# 5. Deterministic Ledger Merge Algorithm

The deterministic merge rules guarantee identical ledgers on all Seed devices.

### Steps:

1. Collect all known transactions (local + remote).
2. Remove duplicates by tx_id.
3. Validate signatures and structural format.
4. Sort transactions by:
   1. lamport clock
   2. device ID
5. Apply each transaction in order.
6. If validation fails:
   - Mark as invalid.
7. Write updated ledger to secure storage.
8. Share updated ledger state back to mesh when possible.

**No real timestamps. No central server. No internet.**

---

# 6. Example Merge Case

### Device A creates:
- A1 (lamport 1)
- A2 (lamport 2)

### Device B creates:
- B1 (lamport 1)
- B2 (lamport 3)

### Global sorted order:
1. **A1** (lamport 1, device A < B)
2. **B1** (lamport 1)
3. **A2** (lamport 2)
4. **B2** (lamport 3)

Every Seed device will apply these in the exact same order.

---

# 7. Data Structures Required

## Transaction Structure
```
{
  "tx_id": "uuid",
  "sender": "user_id",
  "receiver": "user_id",
  "amount": 5.0,
  "lamport": 12,
  "device_id": "NODE_A",
  "prev_tx_ids": ["..."],
  "signature": "digital_signature_here"
}
```

## Ledger Structure
- A map keyed by `tx_id`.
- Stores full transaction objects.
- Tracks validation state.
- Supports deterministic sorting and merging.

---

# 8. Sync & Reconciliation Workflow

1. Device broadcasts or transfers its outbox.
2. Receiving device imports all incoming transactions.
3. Devices merge both datasets using global ordering.
4. Ledger re-validates all transactions.
5. New ledger state is saved to secure storage.
6. Devices propagate updated state to neighbors.

This loop repeats until full convergence.

---

# 9. Security Considerations

- All transactions must be cryptographically signed.
- Replay attacks prevented via:
  - Unique tx_ids
  - Lamport increments
- Malicious nodes cannot reorder history:
  - Sorting rules are deterministic
- Tampered transactions fail signature checks.
- Out-of-order or delayed sync does not compromise correctness.

---

# 10. Future Extensions

- **Vector clocks** for richer multi-device causality.
- **Merkle proofs** to sync only small deltas.
- **Zero-knowledge proofs** for private transactions.
- **Trust-score-aware conflict rules** for community-managed savings groups.

---

# 11. Summary

Seed's conflict resolution system enables a financial ledger to operate **fully offline**, **fully distributed**, and **fully deterministic**. By combining lamport logical clocks, causal references, and strict validation rules, every Seed device independently constructs the same ledger state—even under extreme network limitations.

This makes Seed reliable, tamper-resistant, and capable of scaling across millions of users without centralized infrastructure.
