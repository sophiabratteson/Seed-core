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
- Each device maintains its own increasing counter.
- Every new transaction increments the counter.
- A higher clock value always represents a "later" event.
- Logical clocks work offline because they do not rely on real timestamps.

## Causal References
- Each transaction may include references to previous transaction IDs.
- These references show causal relationships such as "this transaction depends on the previous one."
- Devices use causal graphs to detect missing transactions or broken chains.

## Deterministic Tie-Breaker
- If two transactions have the same lamport clock value:
  - The transaction is chosen based on comparing device IDs alphabetically.
  - This ensures all devices merge in the same way.

## Idempotent Application
- Importing the same transaction multiple times does not change ledger state.
- Devices always check if a transaction already exists before adding it.

---

# 3. Transaction States

Seed nodes categorize transactions into the following states:

- Pending: Known but not yet validated due to missing causal ancestors.
- Valid: Fully accepted into the ledger.
- Invalid: Violates rules such as insufficient balance or tampered signature.
- Orphaned: Transaction references cannot be satisfied even after retries.

Pending and orphan states allow devices to sync gradually in low-connectivity environments.

---

# 4. Conflict Scenarios and Resolution Rules

## Scenario A: Same transaction ID but different content
- This should not normally happen since tx_id is generated uniquely.
- If it does occur:
  - Compare lamport timestamps.
  - Keep the version with the higher lamport value.
  - If equal, use device ID alphabetical ordering.
  - Reject the other version.

## Scenario B: Two valid transactions from the same sender spending the same funds
- Apply transactions in deterministic order:
  - Higher lamport wins.
  - If ties remain, use device ID ordering.
- The losing transaction is marked invalid due to insufficient balance.

## Scenario C: Transactions arrive in different orders on different devices
- Reorder transactions globally by:
  - First: lamport clock
  - Second: device ID
- All devices eventually converge to the same sorted order.

## Scenario D: A device is offline and creates many transactions
- All transactions accumulate locally.
- When the device reconnects:
  - Its transactions merge into the global ledger based on lamport and device ID.
  - Conflicts are resolved automatically using deterministic rules.

## Scenario E: Group savings or trust-score updates collide
- Group-based updates include a group_id and update index.
- If two updates share the same index:
  - The update with the higher lamport value is applied.
  - The other becomes a shadow entry and is archived for audit.

---

# 5. Deterministic Ledger Merge Algorithm

The ledger merge algorithm guarantees identical final outputs across devices.

Steps:

1. Collect all known transactions from both devices.
2. Discard duplicates (same tx_id).
3. Validate signatures and data format.
4. Sort transactions by:
   - lamport clock value (ascending)
   - device_id (alphabetical)
5. Apply transactions in this global order.
6. If a transaction violates rules:
   - Mark it invalid.
   - Continue processing the rest.
7. Output the final ledger state and checkpoints.

This algorithm never relies on real time or arrival order.

---

# 6. Example Merge Case

Device A transactions:
- A1 (lamport 1)
- A2 (lamport 2)

Device B transactions:
- B1 (lamport 1)
- B2 (lamport 3)

Merged order:
1. A1 (lamport 1, device A < device B)
2. B1 (lamport 1, device B)
3. A2 (lamport 2)
4. B2 (lamport 3)

All Seed devices will apply transactions in this exact order and produce identical results.

---

# 7. Data Structures Required

## Transaction
```
{
  "tx_id": "...",
  "sender": "...",
  "receiver": "...",
  "amount": 5.0,
  "lamport": 12,
  "device_id": "NODE_A",
  "prev_tx_ids": ["..."],
  "signature": "..."
}
```

## Ledger
- A map keyed by tx_id.
- Stores validity state.
- Supports deterministic sorting and merging.

---

# 8. Sync and Reconciliation Workflow

1. Device broadcasts or transfers its outbox.
2. Other devices import incoming transactions.
3. Devices merge transactions using deterministic rules.
4. Devices recalculate ledger validity.
5. Devices checkpoint new state to secure storage.
6. Devices propagate updated ledger back to the mesh network.

This loop continues until all nodes converge.

---

# 9. Security Considerations

- All transactions must be signed using per-device private keys.
- Replay attacks prevented by:
  - Incrementing lamport clocks
  - Recognizing duplicate tx_ids
- Malicious nodes cannot reorder history due to deterministic sort rules.
- Tampered transactions fail signature validation.

---

# 10. Future Extensions

- Vector clocks for multi-party causal chains.
- Merkle-tree proofs for lightweight syncing.
- Zero-knowledge validation for private transaction fields.
- Trust-score weighted conflict resolution for group savings.

---

# 11. Summary

Seed's conflict resolution logic allows a global financial system to function without internet, without servers, and without synchronized clocks. By using deterministic ordering rules, lamport timestamps, and strict validation, every device in the network can independently reconstruct the same ledger, regardless of connection quality or environment.

Seed remains consistent, secure, and resilient even in the most challenging conditions.
