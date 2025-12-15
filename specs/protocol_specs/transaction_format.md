# Transaction Format Specification

This document defines the canonical transaction format used by Seed devices.  
The transaction format is the foundational data structure that enables secure, offline-first financial interactions across a distributed mesh network without reliance on internet connectivity or centralized infrastructure.

This specification is designed to be:
- Deterministic
- Compact
- Auditable
- Offline-compatible
- Secure against tampering and replay attacks

---

## 1. Design Goals

The Seed transaction format is designed to:

- Enable peer-to-peer value transfer without centralized validation
- Support delayed synchronization and eventual consistency
- Prevent double-spending and replay attacks
- Operate efficiently on low-power, low-memory devices
- Be extensible for future features such as group savings and trust scoring
- Allow deterministic conflict resolution across devices

---

## 2. Core Transaction Structure

Each transaction is a self-contained record representing a single financial action.

### Canonical JSON Representation

{
“tx_id”: “uuid-v4-string”,
“sender_id”: “DEVICE_OR_USER_ID”,
“receiver_id”: “DEVICE_OR_USER_ID”,
“amount”: 5.00,
“currency”: “LOCAL_UNIT”,
“lamport_clock”: 42,
“device_id”: “SEED_NODE_ID”,
“prev_tx_ids”: [“uuid-v4-string”],
“timestamp_hint”: 1710000000,
“tx_type”: “TRANSFER”,
“metadata”: {},
“signature”: “BASE64_SIGNATURE”
}

---

## 3. Field Definitions

### tx_id
- Type: String (UUID v4)
- Purpose: Globally unique transaction identifier
- Generated locally by the originating device
- Prevents duplication and replay

---

### sender_id
- Type: String
- Identifies the account or identity sending value
- May represent:
  - Individual user
  - Group wallet
  - Merchant account
- Not required to map to a government identity

---

### receiver_id
- Type: String
- Identifies the recipient of value
- Same identity rules as sender_id

---

### amount
- Type: Decimal
- Must be greater than zero
- Precision determined by device configuration
- Validated against sender balance during ledger application

---

### currency
- Type: String
- Represents local unit of value
- Examples:
  - USD-equivalent token
  - Local community credit
  - Stable-value ledger unit
- Enables regional flexibility without protocol changes

---

### lamport_clock
- Type: Integer
- Logical timestamp used for deterministic ordering
- Incremented locally for every new transaction
- Enables offline ordering without real-time clocks

---

### device_id
- Type: String
- Identifies the Seed device that created the transaction
- Used as a deterministic tie-breaker during conflict resolution

---

### prev_tx_ids
- Type: Array of Strings
- Optional causal references to prior transactions
- Enables dependency tracking and orphan resolution
- Particularly important for:
  - Group savings
  - Trust score updates
  - Sequential withdrawals

---

### timestamp_hint
- Type: Integer (Unix epoch)
- Optional and non-authoritative
- Used only for user display
- Never used for validation or ordering

---

### tx_type
- Type: String (Enum)
- Supported values include:
  - TRANSFER
  - GROUP_CONTRIBUTION
  - GROUP_PAYOUT
  - TRUST_UPDATE
  - SYSTEM_ADJUSTMENT
- Enables extensibility without breaking compatibility

---

### metadata
- Type: Object
- Optional, size-limited
- Used for contextual information such as:
  - Group ID
  - Notes
  - UI hints
- Never used in consensus logic

---

### signature
- Type: String (Base64)
- Cryptographic signature over transaction contents
- Generated using device-held private key
- Verified before ledger acceptance

---

## 4. Serialization Rules

- Transactions are serialized in canonical field order
- No whitespace or formatting variance allowed
- Binary serialization may be used for radio transmission
- JSON is used for storage, debugging, and interoperability

---

## 5. Validation Rules

A transaction is considered valid if:

- tx_id is unique
- Signature is valid
- Sender has sufficient balance
- lamport_clock is >= last known value for sender
- tx_type is recognized
- Required fields are present and correctly typed

Invalid transactions are retained but marked as invalid for auditability.

---

## 6. Conflict Handling

When conflicting transactions are detected:

1. Sort by lamport_clock (ascending)
2. If equal, sort by device_id (lexicographically)
3. Apply transactions in sorted order
4. Reject any transaction that violates balance or rules

This ensures all devices converge on the same ledger state.

---

## 7. Storage Considerations

- Transactions are append-only
- Immutable once accepted
- Periodic checkpoints summarize balances to reduce storage
- Historical transactions may be archived but never altered

---

## 8. Security Properties

The transaction format guarantees:

- Tamper resistance via signatures
- Replay prevention via tx_id uniqueness
- Offline safety via logical clocks
- Deterministic convergence without central authority

---

## 9. Future Extensions

Planned extensions include:

- Merkle proof inclusion
- Zero-knowledge balance validation
- Multi-signature transactions
- Privacy-preserving transaction fields

These extensions will be backward compatible with the current format.

---

## 10. Summary

The Seed transaction format is the core primitive that enables a fully offline, decentralized financial system. By combining cryptographic signatures, logical clocks, and deterministic ordering, Seed allows independent devices to securely exchange value and converge on a shared ledger without internet access, centralized servers, or synchronized time.

This format is intentionally simple, extensible, and resilient, making it suitable for deployment in low-resource environments and high-risk conditions.
