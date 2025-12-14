# Simple Two-Node Ledger Simulation Walkthrough

This document provides a clear, step-by-step walkthrough of a minimal Seed ledger simulation involving two devices (nodes). The purpose is to demonstrate how Seed achieves offline-first financial synchronization without internet access, servers, or centralized coordination.

This walkthrough is intentionally simple and deterministic so that the underlying mechanics can be easily understood, validated, and extended.

---

## 1. Simulation Objective

The goals of this simulation are to:

- Demonstrate peer-to-peer transaction creation
- Show how independent devices maintain local ledgers
- Illustrate offline synchronization via transaction exchange
- Prove deterministic conflict resolution
- Validate eventual ledger convergence across nodes

This simulation models the smallest viable Seed network: two devices.

---

## 2. Entities Involved

### Node A
- Unique device ID: NODE_A
- Local ledger stored on device
- Can create transactions while offline

### Node B
- Unique device ID: NODE_B
- Independent local ledger
- Can receive, validate, and merge transactions

No central authority exists. Nodes do not share clocks, databases, or connectivity assumptions.

---

## 3. Initial State

At simulation start:

- Both Node A and Node B have:
  - Empty ledgers
  - Lamport clock initialized to 0
  - No knowledge of the other node’s transactions

Both nodes are fully offline.

---

## 4. Step 1: Transaction Creation on Node A

Node A creates two transactions while offline:

- Transaction A1:
  - Sender: Alice
  - Receiver: Bob
  - Amount: 5
  - Lamport clock: 1
- Transaction A2:
  - Sender: Alice
  - Receiver: Carol
  - Amount: 2
  - Lamport clock: 2
  - References A1 as a causal dependency

Node A’s ledger now contains:
- A1
- A2

Node B remains unaware of these transactions.

---

## 5. Step 2: Offline Transfer from Node A to Node B

Node A exports its transaction set as an outbox file.

This transfer represents any offline communication channel:
- USB drive
- SD card
- Bluetooth
- LoRa packet burst
- Physical transport (“sneakernet”)

Node B imports the outbox file.

---

## 6. Step 3: Ledger Import on Node B

Node B processes incoming transactions:

- Validates transaction format
- Checks signatures
- Confirms causal references
- Stores transactions locally

After import, Node B’s ledger contains:
- A1
- A2

Node B’s Lamport clock updates to the maximum seen value (2).

---

## 7. Step 4: Independent Transaction Creation on Node B

While still offline, Node B creates a new transaction:

- Transaction B1:
  - Sender: Bob
  - Receiver: Dave
  - Amount: 1.5
  - Lamport clock: 3

Node B’s ledger now contains:
- A1
- A2
- B1

Node A remains unaware of B1.

---

## 8. Step 5: Offline Transfer from Node B to Node A

Node B exports its ledger updates.

Node A imports the outbox file using the same offline mechanism.

---

## 9. Step 6: Deterministic Merge on Node A

Node A merges incoming transactions:

1. Collects all known transactions:
   - A1, A2 (local)
   - B1 (incoming)
2. Removes duplicates by transaction ID
3. Sorts transactions by:
   - Lamport clock (ascending)
   - Device ID (alphabetical tie-breaker)
4. Applies transactions in sorted order

Final global order:
1. A1 (lamport 1)
2. A2 (lamport 2)
3. B1 (lamport 3)

Node A and Node B now have identical ledgers.

---

## 10. Final State

Both nodes converge to the same ledger state:

- Identical transaction sets
- Identical ordering
- Identical balances
- No coordination or real-time communication required

This demonstrates eventual consistency.

---

## 11. Why This Matters for Seed

This simple walkthrough proves that:

- Seed does not require internet access
- Seed does not require banks or servers
- Devices can operate independently for long periods
- Synchronization is safe, deterministic, and auditable
- Financial state can propagate gradually across a mesh network

This behavior scales naturally from two nodes to thousands.

---

## 12. Extension Paths

This simulation can be extended to:

- Multi-hop mesh propagation
- Packet loss and retries
- Conflicting transactions
- Group savings pools
- Trust score evolution
- Power-aware sync schedules

All higher-level Seed behavior builds on this foundation.

---

## 13. Summary

The two-node ledger simulation is the minimal proof that Seed’s core promise works: financial coordination without connectivity. By relying on local state, deterministic ordering, and offline synchronization, Seed enables resilient economic systems in environments where traditional infrastructure fails.
