# Offline Sync Scenarios

This document defines the offline synchronization scenarios used to validate Seed’s distributed ledger behavior. These simulations model how Seed devices exchange, reconcile, and converge ledger state without relying on internet connectivity, centralized servers, or real-time coordination.

The purpose of these scenarios is to prove that Seed functions reliably under real-world conditions such as intermittent contact, delayed synchronization, device isolation, and asymmetric connectivity.

---

## Purpose of Offline Sync Simulations

Offline sync simulations are designed to:

- Validate that ledger convergence occurs without centralized control
- Ensure transactions created offline are preserved and merged correctly
- Demonstrate deterministic behavior across devices
- Identify edge cases where conflicts or inconsistencies may arise
- Stress-test Seed’s conflict resolution and reconciliation logic

These simulations are software-based models used before and alongside hardware testing.

---

## Core Assumptions

All offline sync scenarios assume the following conditions:

- Devices operate without internet access
- Devices may be offline for extended periods (hours, days, or weeks)
- Devices exchange data opportunistically (mesh radio, physical transfer, or intermittent gateway)
- Devices maintain their own local ledger and logical clock
- No device is considered authoritative over another

---

## Scenario 1: Two Devices, Intermittent Contact

### Description
Two Seed devices operate independently and meet periodically to synchronize.

### Setup
- Device A and Device B start with identical empty ledgers
- Both devices create transactions independently while offline
- Devices meet intermittently and exchange outboxes

### Expected Behavior
- All transactions are exchanged during sync
- Devices merge ledgers deterministically
- Final ledger state is identical on both devices
- Transaction order is based on Lamport clock and device ID

### Key Validation Points
- No transactions are lost
- No duplicates are created
- Ledger convergence occurs after contact

---

## Scenario 2: Multi-Hop Propagation Through Mesh

### Description
Transactions propagate through a mesh network where devices do not all meet directly.

### Setup
- Device A meets Device B
- Device B later meets Device C
- Device A never directly meets Device C

### Expected Behavior
- Transactions from Device A reach Device C via Device B
- Device C eventually converges to the same ledger state
- No assumption of direct connectivity is required

### Key Validation Points
- Store-and-forward behavior works
- Partial connectivity does not break convergence
- Devices act as passive relays without trust assumptions

---

## Scenario 3: Long-Term Offline Device Rejoining Network

### Description
A device operates offline for an extended period before rejoining the network.

### Setup
- Device A remains offline for weeks
- Network continues evolving with new transactions
- Device A later reconnects via one or more peers

### Expected Behavior
- Device A imports all missing transactions
- Device A’s locally created transactions are merged into the global ledger
- Conflicts are resolved deterministically
- Device A reaches the same ledger state as the network

### Key Validation Points
- Ledger history reconciliation works at scale
- Offline duration does not break sync logic
- No manual intervention is required

---

## Scenario 4: Simultaneous Conflicting Transactions

### Description
Two devices create conflicting transactions while offline.

### Setup
- Device A and Device B both attempt to spend the same balance
- Transactions are created independently
- Devices later synchronize

### Expected Behavior
- Transactions are ordered deterministically
- One transaction succeeds
- The conflicting transaction is marked invalid
- All devices reach the same conclusion

### Key Validation Points
- Double-spend prevention works
- No ambiguity exists after merge
- Deterministic rules eliminate forks

---

## Scenario 5: Partial Sync and Interrupted Transfers

### Description
A sync operation is interrupted before completion.

### Setup
- Device A begins syncing with Device B
- Transfer is interrupted mid-exchange
- Devices later reconnect

### Expected Behavior
- Partial data does not corrupt ledger state
- Duplicate imports are safely ignored
- Remaining transactions sync on next contact

### Key Validation Points
- Idempotent import logic works
- Interrupted syncs do not cause ledger damage
- Recovery is automatic

---

## Scenario 6: Physical Transfer (“Sneakernet”) Sync

### Description
Devices exchange ledger data via physical media.

### Setup
- Device A exports ledger snapshot to storage (e.g., USB, SD card)
- File is physically transported to Device B
- Device B imports snapshot

### Expected Behavior
- Ledger merges identically to radio-based sync
- Transport medium does not affect outcome
- No network assumptions exist

### Key Validation Points
- Sync protocol is transport-agnostic
- Offline-first design is validated

---

## Scenario 7: Group Savings Synchronization

### Description
Group savings contributions occur across multiple offline devices.

### Setup
- Group members contribute at different times
- Devices sync asynchronously
- Group pot updates propagate gradually

### Expected Behavior
- Contributions aggregate correctly
- Rotation order is preserved
- Conflicting updates are resolved deterministically

### Key Validation Points
- Group state consistency
- Fairness in rotation logic
- Auditability of group ledger

---

## Scenario 8: Trust Score Updates During Offline Operation

### Description
Trust score updates occur while devices are offline.

### Setup
- Devices update trust scores based on local interactions
- Devices later synchronize

### Expected Behavior
- Trust score updates merge deterministically
- No double-counting occurs
- Scores converge across devices

### Key Validation Points
- Trust score monotonicity
- Replay prevention
- Fair aggregation logic

---

## Metrics Collected During Simulations

Each offline sync simulation records:

- Time to convergence
- Number of sync rounds required
- Number of conflicts detected
- Number of invalid transactions
- Ledger size growth over time
- Memory and storage usage

---

## Failure Modes Observed

Offline sync simulations are used to identify:

- Ledger bloat risks
- Sync starvation scenarios
- Repeated invalid transaction spam
- Edge cases requiring protocol tuning

Findings from these simulations directly inform protocol and firmware improvements.

---

## Outputs and Artifacts

Each simulation produces:

- Input transaction sets
- Merge logs
- Final ledger snapshots
- Conflict resolution traces
- Deterministic ordering proofs

These artifacts are stored for auditing, debugging, and investor validation.

---

## Summary

Offline sync scenarios demonstrate that Seed’s ledger system remains reliable, deterministic, and secure even under extreme connectivity constraints. These simulations prove that Seed can operate as a global financial system without requiring internet access, centralized infrastructure, or continuous availability.

Offline-first synchronization is not an edge case in Seed — it is the core design principle.
