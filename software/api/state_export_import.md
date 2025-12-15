# State Export and Import API

This document defines how Seed devices export, transfer, and import state data across a fully offline, distributed mesh network. The state export/import mechanism enables devices to synchronize ledger data, trust scores, and system metadata without relying on continuous connectivity, centralized servers, or real-time communication.

This API is foundational to Seed’s offline-first design and supports file-based transfer, mesh radio exchange, and delayed reconciliation.

---

## 1. Purpose and Design Goals

The State Export and Import API exists to:

- Enable full device-to-device synchronization without internet access
- Support intermittent connectivity and long offline periods
- Allow deterministic recovery and reconciliation of device state
- Prevent data corruption, replay attacks, or partial imports
- Enable multiple transport methods (mesh radio, file transfer, kiosk sync)
- Maintain privacy and security during offline transfers

The API treats exported state as portable, verifiable, and mergeable units.

---

## 2. What “State” Includes

Exported state is a structured snapshot containing the following components:

### Ledger State
- All known transactions
- Transaction validity flags
- Lamport clock values
- Causal references between transactions

### Trust and Reputation State
- Trust score values
- Trust score history
- Group participation records

### Device Metadata
- Device ID (public identifier)
- Firmware version
- Protocol version
- Last checkpoint ID
- Export timestamp (logical, not wall-clock)

### Sync Metadata
- Export sequence number
- Hash of previous export (for chaining)
- Flags indicating partial or full export

No private keys are ever included in exports.

---

## 3. Export Triggers

A device may initiate a state export under the following conditions:

- Scheduled periodic export
- User-initiated sync action
- Detection of nearby mesh peers
- Before shutdown or low-power state
- Prior to firmware update
- When entering or exiting offline mode

Exports are idempotent and safe to repeat.

---

## 4. Export Format

State exports use a structured, versioned format.

### Logical Structure

- Header
- Payload sections
- Integrity metadata
- Optional compression wrapper

### Example High-Level Structure

{
“export_id”: “…”,
“device_id”: “…”,
“protocol_version”: “X.Y”,
“export_sequence”: 42,
“previous_export_hash”: “…”,
“payload”: {
“ledger”: […],
“trust_scores”: […],
“groups”: […],
“metadata”: {…}
},
“integrity”: {
“checksum”: “…”,
“signature”: “…”
}
}

---

## 5. Export Integrity and Security

Each exported state includes:

- Cryptographic checksum of payload
- Digital signature using device private key
- Protocol version enforcement
- Size and structure validation

These guarantees ensure:

- No silent corruption
- No unauthorized modification
- No replay of stale exports
- Deterministic verification on import

---

## 6. Transport Mechanisms

The API is transport-agnostic and supports:

- Mesh radio packet streaming
- Opportunistic peer exchange
- Physical file transfer (USB, SD, kiosk)
- Intermediary relay devices

Transport layers must preserve payload integrity but do not interpret content.

---

## 7. Import Workflow

When a device receives an exported state:

1. Verify checksum and signature
2. Validate protocol compatibility
3. Check export sequence and chaining
4. Parse payload sections independently
5. Deduplicate transactions and records
6. Merge using deterministic conflict resolution
7. Recompute ledger validity
8. Update local checkpoints
9. Store audit record of import

Partial imports are allowed and resumable.

---

## 8. Deterministic Merge Rules

Imported state is merged using strict deterministic rules:

- Duplicate transaction IDs are ignored
- Conflicts resolved via Lamport clock ordering
- Device ID tie-breakers applied consistently
- Invalid transactions are quarantined
- Trust score updates follow monotonic rules

All devices importing the same data converge to identical results.

---

## 9. Failure Handling

If an import fails:

- No partial state is committed
- Device rolls back to last checkpoint
- Failure reason is logged
- Export may be retried safely

Failure modes include:

- Signature mismatch
- Schema mismatch
- Incompatible protocol version
- Corrupted payload

---

## 10. Privacy Guarantees

The State Export and Import API enforces:

- No personally identifying information
- No private key material
- No plaintext sensitive data
- Minimal metadata exposure

Optional redaction flags allow devices to export reduced views when required.

---

## 11. Versioning and Backward Compatibility

Each export includes:

- Protocol version
- Schema version
- Feature flags

Devices may:

- Reject unsupported versions
- Import compatible subsets
- Flag unknown fields for future reconciliation

Backward compatibility is prioritized.

---

## 12. Audit and Transparency

Every import and export event is logged locally:

- Export ID
- Source device ID
- Import outcome
- Timestamp (logical)
- Hash references

This supports transparency, dispute resolution, and debugging.

---

## 13. Future Extensions

Planned extensions include:

- Incremental delta exports
- Merkle-based state proofs
- Encrypted selective exports
- Trust-weighted import prioritization
- Anonymous aggregation modes

---

## 14. Summary

The State Export and Import API is the backbone of Seed’s offline-first architecture. By treating device state as a portable, verifiable, and deterministically mergeable artifact, Seed enables resilient financial coordination in environments with no internet, no servers, and no continuous connectivity.

This mechanism allows Seed to scale globally while remaining robust at the extreme edge.
