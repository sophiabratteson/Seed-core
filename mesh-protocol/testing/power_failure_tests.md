# Power Failure Tests

This document defines how the Seed mesh protocol is tested against power loss, unexpected shutdowns, brownouts, and intermittent energy availability. Because Seed devices operate in off-grid, low-resource environments, power instability is treated as a first-class design constraint rather than an edge case.

The goal of these tests is to ensure that no financial data is lost, corrupted, duplicated, or misapplied when devices lose power at any point in their operation.

---

## 1. Objectives

The power failure test suite verifies that:

- Ledger state remains consistent across sudden power loss
- Transactions are never partially applied
- Device identity and cryptographic keys remain intact
- Mesh synchronization resumes safely after restart
- No double-spend or replay conditions are introduced
- Group savings and trust score mechanisms remain accurate
- Devices recover autonomously without user intervention

---

## 2. Power Failure Scenarios Covered

### 2.1 Sudden Power Loss During Idle State

Description:
- Device loses power while not actively sending or receiving data

Expected Behavior:
- Device reboots normally
- Ledger state loads correctly from secure storage
- No data loss occurs
- Device rejoins mesh using last known state

Test Method:
- Cut power during idle
- Restart device
- Compare ledger hash before and after restart

---

### 2.2 Power Loss During Transaction Creation

Description:
- Power is lost while a transaction is being created locally

Expected Behavior:
- Incomplete transaction is discarded
- No partial transaction is written to storage
- Ledger remains unchanged
- Lamport clock rolls forward safely

Test Method:
- Trigger transaction creation
- Interrupt power mid-operation
- Restart and inspect ledger

---

### 2.3 Power Loss During Ledger Write

Description:
- Power failure occurs while committing ledger updates to non-volatile memory

Expected Behavior:
- Atomic write guarantees either full commit or full rollback
- Ledger remains in last known valid state
- No corruption or undefined state

Test Method:
- Force power loss during storage write cycle
- Restart device
- Validate ledger integrity checksum

---

### 2.4 Power Loss During Mesh Transmission

Description:
- Device loses power while transmitting messages to neighbors

Expected Behavior:
- Outgoing messages are retried or safely dropped
- No duplicate transactions are created
- Receiving devices ignore incomplete messages

Test Method:
- Begin broadcast
- Remove power mid-transmission
- Verify downstream devices remain consistent

---

### 2.5 Power Loss During Mesh Reception

Description:
- Device loses power while receiving data from another node

Expected Behavior:
- Partial packets are discarded
- No partial state updates occur
- Sender eventually retries sync

Test Method:
- Interrupt power during receive
- Restart device
- Confirm no partial data applied

---

### 2.6 Power Loss During Conflict Resolution

Description:
- Device shuts down while resolving ledger conflicts

Expected Behavior:
- Conflict resolution restarts cleanly on reboot
- Deterministic ordering produces same final state
- No transaction is applied twice

Test Method:
- Introduce conflicting ledgers
- Interrupt power mid-merge
- Restart and re-run merge

---

### 2.7 Power Loss During Group Savings Update

Description:
- Device loses power while processing group savings contributions or payouts

Expected Behavior:
- Group state remains consistent
- Partial updates are rolled back
- Group balances and rotation order remain correct

Test Method:
- Initiate group update
- Cut power mid-operation
- Restart and validate group state

---

### 2.8 Power Loss During Trust Score Update

Description:
- Power loss occurs during trust score recalculation

Expected Behavior:
- Trust score updates are idempotent
- Partial calculations are discarded
- Scores recompute deterministically after restart

Test Method:
- Trigger trust update
- Interrupt power
- Restart and compare scores

---

## 3. Storage Safety Guarantees

Seed devices enforce the following guarantees:

- All ledger writes are atomic
- Temporary buffers are cleared on reboot
- Secure storage includes integrity checks
- Versioned checkpoints prevent rollback attacks
- Corrupted state automatically triggers recovery mode

---

## 4. Recovery Process After Power Loss

On reboot, the device performs:

1. Secure boot verification
2. Storage integrity validation
3. Ledger checksum verification
4. Rollback to last valid checkpoint if needed
5. Mesh rejoin handshake
6. Deferred sync retry with neighbors
7. Resume normal operation

This process requires no user input.

---

## 5. Repeated Failure Stress Testing

Description:
- Device is subjected to frequent power interruptions over extended periods

Goals:
- Validate long-term durability
- Ensure no cumulative ledger drift
- Confirm battery-safe behavior

Metrics:
- Successful reboot rate
- Ledger consistency rate
- Sync recovery success rate

---

## 6. Environmental Power Conditions

Tests are run under:

- Low battery voltage
- Brownout conditions
- Rapid power cycling
- Solar charging fluctuation
- Manual hand-crank interruption

---

## 7. Success Criteria

A power failure test passes if:

- Ledger hash matches pre-failure state or valid merged state
- No duplicate or missing transactions exist
- Device resumes mesh participation
- No manual repair is required
- No user-visible corruption occurs

---

## 8. Failure Classification

Failures are categorized as:

- Critical: Financial integrity compromised
- Major: Sync delayed but recoverable
- Minor: Temporary UI or timing issue
- Informational: Logging or metric anomaly

Only zero critical failures are acceptable.

---

## 9. Reporting and Audit Logs

Each test run records:

- Failure timestamp
- Power state at failure
- Recovery actions taken
- Ledger state before and after
- Hash comparison results

Logs are stored locally and optionally exported during sync.

---

## 10. Summary

Power failure resilience is fundamental to Seed’s design. These tests ensure that even in the most unstable energy environments, Seed devices preserve financial integrity, maintain trust, and continue operating as reliable nodes in a global offline-first financial mesh.

Seed is designed to fail safely, recover automatically, and never lose money.
