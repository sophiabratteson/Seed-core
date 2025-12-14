# Transaction Validation Engine

This document defines how Seed validates transactions before they are accepted into the ledger. Because Seed operates without centralized servers or continuous connectivity, transaction validation must be deterministic, secure, offline-capable, and resistant to abuse. The validation engine ensures that only legitimate, well-formed, and economically sound transactions affect the ledger state.

---

## Purpose of Transaction Validation

The transaction validation engine exists to:

- Prevent double-spending in offline environments
- Reject malformed or tampered transactions
- Enforce economic rules (balances, limits, group rules)
- Ensure deterministic behavior across all devices
- Maintain trust without centralized oversight

Every Seed device independently validates transactions using the same rules. This guarantees that all devices converge on the same ledger state.

---

## Validation Philosophy

Seed validation follows these core principles:

- **Offline-first:** No reliance on internet, servers, or real-time clocks
- **Deterministic:** Same inputs always produce the same result
- **Fail-safe:** Invalid transactions never modify balances
- **Idempotent:** Re-processing a transaction does not change outcomes
- **Auditable:** Validation decisions can be reconstructed later

---

## Transaction Lifecycle States

Each transaction exists in exactly one of the following states:

- **Received:** Transaction has been received but not validated
- **Pending:** Waiting on missing dependencies (causal references)
- **Valid:** Fully validated and applied to the ledger
- **Invalid:** Permanently rejected due to rule violations
- **Orphaned:** Dependencies missing after retry window expires

State transitions are deterministic and irreversible once marked invalid.

---

## Required Transaction Fields

Before validation begins, the transaction must include:

- `tx_id`: Globally unique transaction identifier
- `sender_id`: Originating account or device
- `receiver_id`: Recipient account or group
- `amount`: Positive numeric value
- `lamport_clock`: Logical timestamp
- `device_id`: Originating device identifier
- `signature`: Cryptographic signature
- `prev_tx_ids`: Optional causal dependencies

Transactions missing required fields are immediately rejected.

---

## Validation Pipeline Overview

Transactions pass through validation in the following strict order:

1. Structural Validation
2. Cryptographic Validation
3. Causal Validation
4. Economic Validation
5. Policy Validation
6. Final Acceptance or Rejection

Failure at any stage stops processing.

---

## 1. Structural Validation

The engine checks that:

- All required fields are present
- Field types match specification
- Amount is finite and non-negative
- IDs conform to expected formats
- Payload size is within limits

Malformed transactions are rejected immediately.

---

## 2. Cryptographic Validation

The engine verifies:

- Transaction signature authenticity
- Signature matches sender identity
- Signature covers immutable fields
- Device public key is trusted or recognized

Transactions with invalid or missing signatures are rejected.

---

## 3. Causal Validation

The engine ensures:

- All referenced `prev_tx_ids` exist locally
- No circular dependencies are introduced
- Lamport clock value is greater than causal parents

If dependencies are missing, the transaction enters the **Pending** state until resolved.

---

## 4. Economic Validation

The engine enforces economic rules:

- Sender balance is sufficient
- No double-spending within ledger order
- Group savings rules are respected
- Trust-score-based limits are enforced (if applicable)

If economic rules fail, the transaction is marked **Invalid**.

---

## 5. Policy Validation

Optional policy checks may include:

- Transaction rate limits
- Daily or per-user caps
- Group governance rules
- Emergency freeze conditions

Policies are configurable but deterministic.

---

## 6. Deterministic Ordering Context

Validation always occurs within a deterministic ordering context:

- Transactions are evaluated in global order:
  - Lamport clock (ascending)
  - Device ID (alphabetical tie-breaker)

This ensures consistent validation results across devices.

---

## Duplicate and Replay Handling

The engine prevents replay attacks by:

- Rejecting duplicate `tx_id` values
- Tracking applied transactions permanently
- Ignoring already-validated transactions

Duplicate imports do not change ledger state.

---

## Failure Handling Strategy

When validation fails:

- The transaction is marked invalid
- Reason codes are stored for audit
- Ledger state remains unchanged
- The device continues processing other transactions

Invalid transactions are never retried.

---

## Audit and Transparency

For every validated transaction, the device stores:

- Validation outcome
- Timestamp of validation (logical)
- Failure reason (if invalid)
- Dependencies used

This enables later forensic analysis and dispute resolution.

---

## Security Considerations

The validation engine defends against:

- Double-spend attacks
- Signature forgery
- Replay attacks
- Malformed payload attacks
- Resource exhaustion attempts

All rules are enforced locally and independently.

---

## Extensibility

Future enhancements may include:

- Zero-knowledge balance proofs
- Multi-signature group approvals
- Smart rule modules for NGOs or cooperatives
- Pluggable economic policies

Extensions must preserve determinism.

---

## Summary

The transaction validation engine is the backbone of Seed’s trustless financial system. By enforcing strict, deterministic rules at every device, Seed enables secure economic activity without banks, servers, or constant connectivity. Validation ensures that trust emerges from protocol design rather than institutional authority.
