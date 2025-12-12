# Trust Score Update Message Specification

This document defines the Trust Score Update Message used in the Seed mesh protocol. This message allows Seed devices to propagate changes to user trust scores across a fully offline, peer-to-peer mesh network while maintaining determinism, auditability, and resistance to manipulation.

---

## 1. Purpose

Trust Score Update Messages communicate changes to a user's trust score resulting from financial behavior, group participation, repayments, or protocol-defined events.

The message enables:
- Offline propagation of trust updates
- Deterministic trust score convergence across devices
- Transparent auditability of trust changes
- Protection against replay and manipulation attacks

---

## 2. Design Goals

- Offline-first operation
- Deterministic merging across all devices
- Minimal bandwidth usage
- Strong integrity and authenticity guarantees
- Resistance to trust inflation or spoofing
- Support for gradual convergence in low-connectivity environments

---

## 3. When This Message Is Generated

A Trust Score Update Message is generated when:
- A user repays a loan on time
- A user defaults or misses a payment
- A user contributes consistently to group savings
- A group votes to update a member’s trust standing
- A protocol-defined milestone or penalty is triggered

Trust score changes are **event-driven**, not time-based.

---

## 4. Message Structure

### Trust Score Update Message (JSON)

{
“message_type”: “TRUST_SCORE_UPDATE”,
“update_id”: “uuid”,
“subject_id”: “USER_ID”,
“delta”: 3,
“new_score”: 72,
“reason_code”: “GROUP_SAVINGS_CONTRIBUTION”,
“group_id”: “GROUP_ABC”,
“lamport”: 128,
“origin_device_id”: “DEVICE_XYZ”,
“prev_update_ids”: [“uuid1”, “uuid2”],
“timestamp_hint”: null,
“signature”: “BASE64_SIGNATURE”
}

---

## 5. Field Definitions

- `message_type`
  - Constant identifier: `"TRUST_SCORE_UPDATE"`

- `update_id`
  - Unique identifier for this update event

- `subject_id`
  - Identifier of the user whose trust score is affected

- `delta`
  - Signed integer representing the change in trust score

- `new_score`
  - Resulting trust score after applying delta

- `reason_code`
  - Enum describing why the update occurred
  - Examples:
    - `LOAN_REPAYMENT_ON_TIME`
    - `MISSED_PAYMENT`
    - `GROUP_SAVINGS_CONTRIBUTION`
    - `GROUP_DEFAULT`
    - `MANUAL_GROUP_ADJUSTMENT`

- `group_id`
  - Optional
  - Present if update is related to a group mechanism

- `lamport`
  - Logical timestamp used for deterministic ordering

- `origin_device_id`
  - Device that generated the update

- `prev_update_ids`
  - References to prior trust updates for causal ordering

- `timestamp_hint`
  - Optional human-readable timestamp
  - Not used for ordering or validation

- `signature`
  - Cryptographic signature of the message contents

---

## 6. Validation Rules

A Trust Score Update Message is valid only if:
- The signature verifies against the subject or group authority
- The `lamport` value is greater than previously seen updates
- The `new_score` matches `previous_score + delta`
- The update references valid prior updates when required
- The update complies with protocol-defined score bounds

Invalid updates are discarded but logged for audit.

---

## 7. Deterministic Merge Rules

When multiple updates are received:

1. Deduplicate by `update_id`
2. Sort updates by:
   - `lamport` (ascending)
   - `origin_device_id` (alphabetical)
3. Apply updates sequentially
4. If conflicting updates exist:
   - Higher lamport update prevails
   - Ties resolved via device ID ordering
5. All devices converge on identical trust scores

---

## 8. Conflict Scenarios

### Simultaneous Updates
- Two devices issue updates with same lamport
- Device ID ordering resolves conflict deterministically

### Offline Burst Updates
- Device accumulates updates offline
- Updates are merged sequentially upon reconnection

### Malicious Inflation Attempt
- Invalid signature or inconsistent delta
- Update rejected automatically

---

## 9. Storage and Persistence

- Trust updates are stored in:
  - Append-only trust update log
  - Indexed by subject_id and lamport
- Periodic checkpoints store:
  - Current trust score
  - Last applied update_id
- Historical updates retained for auditability

---

## 10. Privacy Considerations

- Trust updates contain no personal identifiers
- Subject IDs are pseudonymous
- Group-related updates disclose only group IDs
- Updates propagate without internet connectivity

---

## 11. Security Considerations

- All updates must be signed
- Replay attacks prevented via lamport tracking
- Devices reject updates that violate monotonic score rules
- Tamper detection flags suspicious update patterns

---

## 12. Bandwidth Characteristics

- Small payload size (< 512 bytes)
- Suitable for LoRa and low-power mesh transport
- Batched updates supported when syncing

---

## 13. Future Extensions

- Weighted trust updates based on group reputation
- Multi-signature trust updates for large groups
- Zero-knowledge trust score proofs
- Decay models for long-term inactivity

---

## 14. Summary

Trust Score Update Messages allow Seed to maintain a decentralized reputation system without servers, internet, or centralized authorities. Through deterministic ordering, cryptographic verification, and offline-first propagation, trust scores remain consistent, fair, and resistant to abuse across the global Seed network.
