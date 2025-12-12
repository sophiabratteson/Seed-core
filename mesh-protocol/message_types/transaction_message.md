# Transaction Message Specification

This document defines the **Transaction Message** used in the Seed mesh protocol. Transaction messages are the primary mechanism by which value transfers, group contributions, and trust-related updates are propagated across the offline-first mesh network.

Transaction messages are designed to be:
- Compact and energy-efficient
- Secure and tamper-resistant
- Fully offline-compatible
- Deterministically mergeable across devices

---

## 1. Purpose of the Transaction Message

The transaction message exists to:
- Represent a single financial action performed on a Seed device
- Allow that action to be shared with other devices over the mesh
- Enable consistent ledger reconstruction across disconnected nodes
- Prevent double-spending and replay attacks

Transaction messages are **append-only** and never modify past history.

---

## 2. When Transaction Messages Are Generated

A transaction message is generated when:
- A user sends value to another user
- A user contributes to a group savings pool
- A group payout is executed
- A trust score–relevant action occurs
- An administrative or system-level transaction is recorded

Each transaction message corresponds to **exactly one ledger entry**.

---

## 3. Message Transport Context

Transaction messages may be transmitted via:
- Direct peer-to-peer LoRa communication
- Multi-hop mesh routing
- Opportunistic device encounters
- Physical transfer (store-and-forward via storage)

The protocol does not assume:
- Reliable delivery
- Ordered delivery
- Immediate acknowledgment

All transaction messages must be idempotent and safely re-importable.

---

## 4. Transaction Message Structure

Each transaction message uses a structured JSON-compatible payload.

### Required Fields

- tx_id  
  Globally unique transaction identifier.

- sender_id  
  The originating device or user identity.

- receiver_id  
  The intended recipient identity.

- amount  
  Numeric value transferred (may be zero for non-monetary actions).

- lamport  
  Logical timestamp assigned by the originating device.

- device_id  
  Unique ID of the device that created the transaction.

- signature  
  Cryptographic signature covering the message payload.

- prev_tx_ids  
  Optional list of causal predecessor transaction IDs.

---

## 5. Canonical Message Format

{
“type”: “transaction”,
“tx_id”: “uuid-string”,
“sender_id”: “USER_A”,
“receiver_id”: “USER_B”,
“amount”: 5.00,
“lamport”: 42,
“device_id”: “DEVICE_X”,
“prev_tx_ids”: [“uuid-previous”],
“signature”: “base64-signature”
}

All fields must be serialized in a consistent order before signing.

---

## 6. Validation Rules

Upon receiving a transaction message, a device MUST:

- Verify the message type is `transaction`
- Verify the transaction ID has not already been applied
- Validate the cryptographic signature
- Confirm the lamport value is valid relative to local state
- Ensure required fields are present and well-formed
- Check that causal predecessors (if any) are known or queued

If validation fails, the transaction is rejected and logged.

---

## 7. Ledger Integration Rules

If validation succeeds:
- The transaction is added to the local ledger store
- It is marked as pending or valid depending on dependencies
- The lamport clock is updated if necessary
- The transaction becomes eligible for rebroadcast

Ledger state must never be mutated retroactively.

---

## 8. Conflict Handling

Transaction messages may arrive:
- Out of order
- Multiple times
- From different paths

Conflict resolution relies on:
- Lamport ordering
- Deterministic device ID tie-breaking
- Ledger-level balance checks

Transaction messages themselves do not resolve conflicts; they are inputs to the ledger merge process.

---

## 9. Security Properties

Transaction messages provide:
- Integrity via cryptographic signatures
- Replay protection via tx_id uniqueness
- Ordering safety via lamport clocks
- Offline authenticity via device identity keys

Transaction messages never expose:
- Private keys
- User biometrics
- Plaintext sensitive metadata

---

## 10. Message Size Considerations

Transaction messages are designed to:
- Fit within LoRa payload limits
- Be compressible for binary serialization
- Avoid unnecessary verbosity

Future versions may include:
- Binary-encoded variants
- Merkle references for batch sync

---

## 11. Failure and Retry Behavior

If a transaction message fails to transmit:
- It remains in the local outbox
- It may be retried opportunistically
- It may be forwarded by other nodes later

Transaction messages are never deleted once created.

---

## 12. Audit and Transparency

Every transaction message:
- Can be independently verified
- Is traceable through its tx_id
- Can be audited without central authority

This enables transparency without requiring internet connectivity.

---

## 13. Future Extensions

Planned extensions include:
- Encrypted transaction fields
- Zero-knowledge validation hooks
- Group transaction batching
- Trust-score–weighted propagation rules

Backward compatibility must be maintained.

---

## 14. Summary

Transaction messages are the atomic unit of value transfer in Seed. By combining deterministic ordering, offline safety, and cryptographic integrity, they enable a resilient financial system that functions without servers, internet access, or centralized control.

Every Seed device can independently verify, store, and propagate transaction messages while maintaining global consistency.
