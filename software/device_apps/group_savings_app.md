# Group Savings Application

## Purpose

The Group Savings Application enables users to collectively save money, rotate access to pooled funds, and build financial trust without requiring banks, internet connectivity, or centralized administrators. This application digitizes informal savings groups (e.g., ROSCAs, savings circles, village banks) directly on Seed devices.

---

## Core Objectives

- Enable peer-managed group savings without centralized control
- Operate fully offline with deterministic synchronization
- Enforce transparency, accountability, and fairness
- Support low-literacy and non-smartphone users
- Integrate trust score incentives and penalties

---

## Group Model Overview

Each group is defined by:

- A unique `group_id`
- A fixed set of members (device identities)
- A contribution amount
- A contribution interval (e.g., weekly)
- A payout rotation order
- A lifecycle state

Groups exist independently of any single device and are synchronized across the mesh network.

---

## Group Lifecycle States

- Proposed  
  Group parameters defined, awaiting member confirmations

- Active  
  Contributions ongoing, payouts rotating

- Paused  
  Temporarily halted due to disputes or missing members

- Completed  
  All members have received payouts

- Dissolved  
  Group terminated early (with full audit history preserved)

---

## User Actions Supported

- Create a new group
- Join or reject a group invitation
- Make scheduled contributions
- View group balance and history
- Receive a payout
- Vote to pause or dissolve a group
- Report missed payments or disputes

All actions generate signed group events stored in the ledger.

---

## Data Structures

### Group Definition

```
{
  "group_id": "GROUP_123",
  "members": ["NODE_A", "NODE_B", "NODE_C"],
  "contribution_amount": 1.0,
  "interval_days": 7,
  "payout_order": ["NODE_A", "NODE_B", "NODE_C"],
  "current_round": 0,
  "state": "ACTIVE"
}
```

### Group Event

```
{
  "event_id": "UUID",
  "group_id": "GROUP_123",
  "type": "CONTRIBUTION | PAYOUT | PAUSE | DISSOLVE",
  "actor_device": "NODE_A",
  "amount": 1.0,
  "lamport": 42,
  "signature": "SIG",
  "timestamp_hint": "OPTIONAL"
}
```

---

## Contribution Logic

- Contributions are expected at fixed intervals
- Each contribution is validated against:
  - Group membership
  - Correct amount
  - Contribution window
- Missed contributions are recorded explicitly
- Partial contributions are rejected

---

## Payout Logic

- Exactly one member receives payout per round
- Payout eligibility determined by rotation order
- Payout occurs only when:
  - All required contributions for the round are present
  - No unresolved disputes exist
- Payout events are final and irreversible

---

## Trust Score Integration

- On-time contributions increase trust score
- Missed or late payments decrease trust score
- Group reputation affects:
  - Eligibility to join future groups
  - Priority in group formation
- Chronic abuse leads to group-level sanctions

---

## Conflict Resolution Rules

- Group events are ordered using:
  - Lamport timestamp
  - Device ID tie-breaker
- Duplicate events are ignored (idempotent)
- Conflicting state transitions favor:
  - Higher lamport value
  - Majority-confirmed group actions
- Disputed events are preserved but marked inactive

---

## Offline-First Synchronization

- Group events sync through mesh messages
- Devices reconcile group state deterministically
- Missing events place group in pending state
- Full convergence occurs once all events propagate

No real-time coordination is required.

---

## Security Considerations

- All group events are digitally signed
- Only members may submit group actions
- Payouts cannot be spoofed or reordered
- Ledger preserves full audit trail
- Malicious devices cannot fabricate group history

---

## User Interface Principles

- Simple step-by-step prompts
- Icon-based status indicators
- Audio prompts for low-literacy users
- Clear group progress visualization
- Explicit warnings for missed payments

---

## Failure Modes and Recovery

- If a device is lost:
  - Group state recoverable from mesh
- If a member drops out:
  - Group may pause or dissolve by vote
- If synchronization is delayed:
  - Events queue locally until sync resumes

---

## Metrics Tracked

- Group completion rate
- Missed contribution frequency
- Average trust score change per group
- Group lifetime duration
- Dispute occurrence rate

---

## Future Extensions

- Variable contribution amounts
- Emergency group withdrawals
- Cross-group trust aggregation
- Inter-group lending
- NGO-backed group guarantees

---

## Summary

The Group Savings Application transforms informal financial cooperation into a secure, transparent, and offline-capable system. By embedding trust, accountability, and deterministic synchronization directly into Seed devices, users gain access to collective financial tools previously unavailable without banks or internet infrastructure.
