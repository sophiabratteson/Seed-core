# Group Savings Synchronization Protocol

This document defines how Seed devices synchronize **group savings activity** across a fully offline, peer-to-peer mesh network. Group savings is a core financial primitive in Seed, enabling rotating savings, pooled funds, and community lending without relying on banks, servers, or continuous connectivity.

Because group savings involves **shared state across multiple devices**, synchronization must be deterministic, resilient to delays, and resistant to abuse or double-claiming.

---

## 1. Goals of Group Savings Sync

The group savings sync protocol is designed to:

- Maintain a consistent group savings state across all participating devices
- Allow members to contribute while offline
- Ensure only one member claims a payout per cycle
- Prevent double-spending or duplicate payouts
- Recover safely from long offline periods
- Converge to identical group balances on all devices

The protocol must function in environments with:
- No internet
- Intermittent power
- Asynchronous device encounters
- Untrusted physical environments

---

## 2. Group Savings Model Overview

Each group savings arrangement is modeled as a **deterministic state machine** shared across devices.

Core concepts:

- `group_id`: Unique identifier for the savings group
- `members`: List of participating device or user IDs
- `cycle_length`: Number of members / rounds
- `contribution_amount`: Fixed amount per cycle
- `current_cycle`: Index of the active payout round
- `payout_recipient`: Member designated to receive current cycle funds
- `total_balance`: Aggregate contributions accumulated for the cycle
- `status`: ACTIVE, COMPLETED, or TERMINATED

All group state transitions are recorded as **ledger transactions**, not mutable state.

---

## 3. Group Savings Transactions

Group savings activity is represented through explicit transaction types:

- `GROUP_CREATE`
- `GROUP_CONTRIBUTE`
- `GROUP_PAYOUT`
- `GROUP_CLOSE`

Each transaction includes:

{
“tx_id”: “…”,
“type”: “GROUP_CONTRIBUTE”,
“group_id”: “…”,
“member_id”: “…”,
“amount”: 5.0,
“cycle_index”: 3,
“lamport”: 42,
“device_id”: “NODE_A”,
“signature”: “…”
}

Transactions are immutable and validated independently on every device.

---

## 4. Offline Contribution Handling

Devices allow members to contribute while offline.

Rules:

- Contributions are recorded locally as pending transactions
- Pending contributions reference the current known `cycle_index`
- Devices do not require confirmation from other members to record contributions
- Contributions are broadcast during mesh encounters

When devices reconnect:

- Contributions are merged using deterministic ordering
- Duplicate contributions from the same member in the same cycle are rejected

---

## 5. Payout Synchronization Rules

Payouts require special handling because **only one payout is allowed per cycle**.

Rules:

- A payout transaction is only valid if:
  - All required contributions for the cycle are present
  - The payout recipient matches the deterministic cycle order
- If multiple payout attempts occur:
  - The payout with the highest lamport timestamp wins
  - Ties are resolved using device_id ordering
  - Losing payouts are marked INVALID

Payout transactions lock the cycle permanently.

---

## 6. Deterministic Cycle Ordering

The payout order is deterministic and known to all devices.

Methods include:
- Round-robin member order
- Pre-agreed rotation list
- Optional trust-score weighted ordering (future extension)

Because ordering is deterministic:
- Devices do not negotiate payout order
- Disputes are resolved automatically
- No central authority is required

---

## 7. Merge Algorithm for Group State

When two devices synchronize:

1. Collect all group-related transactions
2. Deduplicate by `tx_id`
3. Validate signatures and transaction structure
4. Sort transactions by:
   - lamport timestamp
   - device_id
5. Apply transactions sequentially:
   - Reject invalid contributions
   - Apply valid contributions
   - Apply exactly one payout per cycle
6. Recalculate derived group state

All devices performing these steps will reach the same group state.

---

## 8. Partial Sync and Recovery

Devices may encounter incomplete group histories.

Handling rules:

- Missing transactions cause dependent actions to remain pending
- Devices request missing group transactions opportunistically
- Orphaned group actions are retained for retry
- Group state is recalculated whenever new data arrives

This allows recovery after:
- Long device outages
- Lost encounters
- Temporary device failure

---

## 9. Security and Abuse Prevention

Protections include:

- Signature validation for every group transaction
- One-contribution-per-member-per-cycle rule
- Deterministic payout enforcement
- Immutable audit trail of all actions
- Rejection of forged or replayed group transactions

Malicious behavior cannot corrupt group state without majority collusion.

---

## 10. Failure Modes and Safeguards

Handled scenarios:

- Member goes offline mid-cycle
- Device is lost or stolen
- Multiple payout attempts
- Partial contribution sets
- Network partitions

Safeguards ensure:
- Funds are never duplicated
- Cycles never regress
- Group state remains recoverable

---

## 11. Relationship to Ledger and Trust Score

Group savings sync integrates with:

- Ledger engine: All actions are ledger transactions
- Trust score system:
  - Successful contributions increase trust
  - Missed contributions decrease trust
  - Early payouts improve reliability score

This creates economic incentives for good behavior.

---

## 12. Future Extensions

Planned enhancements:

- Variable contribution schedules
- Emergency skip or delay votes
- Cross-group pooling
- Privacy-preserving group balances
- Zero-knowledge contribution proofs

---

## 13. Summary

The group savings sync protocol enables community finance without banks, servers, or connectivity. By encoding all actions as deterministic ledger transactions and resolving conflicts automatically, Seed allows groups to save, rotate funds, and build trust—even in the most constrained environments.

This protocol is foundational to Seed’s mission of decentralized financial resilience.
