# Group Savings Message Specification

This document defines the Group Savings Message used in the Seed mesh protocol. Group savings messages enable fully offline, trust-based rotating savings groups (similar to ROSCAs) to function without internet access, centralized servers, or formal banking infrastructure.

These messages allow Seed devices to coordinate contributions, payouts, accountability, and transparency across a distributed mesh network.

---

## 1. Purpose

Group Savings Messages are used to:
- Coordinate recurring contributions among a defined group of users
- Track pooled balances and payout rotations
- Enforce accountability without central authority
- Synchronize group state across offline devices
- Provide auditability and dispute resolution

---

## 2. Design Principles

- Offline-first operation
- Deterministic merging across devices
- Minimal bandwidth usage
- Human-auditable records
- Tamper-resistant but community-governed
- No reliance on real-time clocks or internet

---

## 3. Group Savings Model

Each group savings instance includes:
- A fixed group identifier
- A defined list of participants
- A contribution amount per cycle
- A payout rotation order
- A cycle index that increments deterministically

All members independently track the same group state using shared rules.

---

## 4. Message Triggers

A Group Savings Message is generated when:
- A member makes a contribution
- A payout is executed
- A cycle advances
- A member misses or defaults on a contribution
- A dispute or correction is recorded

---

## 5. Message Structure

Group Savings Messages use a compact JSON-compatible structure:

{
  "message_type": "GROUP_SAVINGS_UPDATE",
  "group_id": "GROUP_8F2A91",
  "update_type": "CONTRIBUTION | PAYOUT | CYCLE_ADVANCE | DEFAULT | CORRECTION",
  "cycle_index": 12,
  "member_id": "DEVICE_A",
  "amount": 5.00,
  "lamport": 184,
  "device_id": "DEVICE_A",
  "prev_update_ids": ["UUID_1", "UUID_2"],
  "signature": "BASE64_SIGNATURE"
}

---

## 6. Field Definitions

- message_type  
  Fixed identifier used by mesh routers and parsers.

- group_id  
  Globally unique identifier for the savings group.

- update_type  
  Specifies the semantic meaning of the update.

- cycle_index  
  Logical cycle number for deterministic ordering.

- member_id  
  Device identity of the participant performing the action.

- amount  
  Contribution or payout amount.

- lamport  
  Logical timestamp used for ordering and conflict resolution.

- device_id  
  Originating Seed device identifier.

- prev_update_ids  
  Optional causal references to prior group updates.

- signature  
  Cryptographic signature validating authenticity.

---

## 7. Update Types

### CONTRIBUTION
Records a member’s contribution for the current cycle.

### PAYOUT
Records transfer of pooled funds to the designated recipient.

### CYCLE_ADVANCE
Indicates completion of a cycle and transition to the next.

### DEFAULT
Marks a missed or incomplete contribution.

### CORRECTION
Community-approved adjustment due to error or dispute.

---

## 8. Deterministic Application Rules

Devices apply group savings updates using the following order:
1. Sort by cycle_index
2. Sort by lamport timestamp
3. Sort by device_id alphabetically

This guarantees identical group state across all devices.

---

## 9. Conflict Handling

If conflicting updates occur:
- Higher lamport value wins
- If lamports tie, device_id ordering applies
- Losing updates are archived, not deleted
- Conflicts affect trust scores automatically

---

## 10. Partial Sync Tolerance

Devices may:
- Receive group updates out of order
- Miss cycles temporarily
- Rejoin after extended offline periods

Missing updates are marked as pending until resolved.

---

## 11. Security Properties

- All messages are signed
- Replay attacks are prevented via lamport ordering
- Invalid signatures are rejected
- Tampered updates never propagate

---

## 12. Privacy Considerations

- Group IDs do not encode personal identity
- Devices may use pseudonymous member IDs
- No centralized visibility of group membership
- Optional encrypted payload fields for sensitive data

---

## 13. Trust Score Integration

Group behavior directly impacts trust scores:
- Timely contributions increase score
- Defaults decrease score
- Dispute resolutions adjust score proportionally

Trust scoring remains local but converges via mesh sync.

---

## 14. Failure Scenarios

Handled failure cases include:
- Device loss mid-cycle
- Duplicate contribution messages
- Conflicting payout claims
- Long-term offline members

All are resolved without halting group operation.

---

## 15. Future Extensions

- Variable contribution amounts
- Emergency skips with group consent
- Cross-group federation
- Reputation-weighted payouts
- Zero-knowledge contribution proofs

---

## 16. Summary

Group Savings Messages enable Seed to replicate and improve traditional community savings systems using only offline devices and local trust. Through deterministic rules, cryptographic validation, and transparent state tracking, Seed allows financial cooperation to flourish even in the absence of infrastructure.

This mechanism is a core pillar of Seed’s economic resilience model.
