# JSON Schema for Seed Transactions

This document defines the canonical JSON schema for Seed transactions.  
All devices—hardware prototypes, emulators, and software simulations—must follow this schema exactly to ensure interoperability, deterministic merging, and secure validation across the mesh network.

Seed is an offline-first financial system. Because devices often sync asynchronously and without servers, the transaction format must be strict, compact, and easy to validate on low-power hardware.

---

# 1. Purpose of the Schema

The JSON schema:

- Ensures every device structures transaction data the same way.
- Allows deterministic validation across CPU architectures.
- Prevents malformed or tampered transactions from entering the ledger.
- Enables future expansion while preserving backward compatibility.
- Allows simple verification on embedded hardware using lightweight parsers.

---

# 2. High-Level Requirements

A Seed transaction must:

- Be uniquely identifiable.
- Be cryptographically signed.
- Include causal context for conflict resolution.
- Carry a monotonic Lamport clock.
- Reference sender and receiver identities.
- Support optional metadata without breaking compatibility.

---

# 3. Full JSON Schema (Draft-07)

```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "title": "Seed Transaction",
  "type": "object",

  "required": [
    "tx_id",
    "sender",
    "receiver",
    "amount",
    "lamport",
    "device_id",
    "prev_tx_ids",
    "signature"
  ],

  "properties": {
    "tx_id": {
      "type": "string",
      "description": "Globally unique transaction identifier (UUIDv4 recommended)."
    },

    "sender": {
      "type": "string",
      "description": "Device or account ID of the sender."
    },

    "receiver": {
      "type": "string",
      "description": "Device or account ID of the receiver."
    },

    "amount": {
      "type": "number",
      "minimum": 0,
      "description": "Amount transferred. Always a positive decimal value."
    },

    "lamport": {
      "type": "integer",
      "minimum": 0,
      "description": "Lamport logical timestamp for deterministic ordering."
    },

    "device_id": {
      "type": "string",
      "description": "ID of the originating device."
    },

    "prev_tx_ids": {
      "type": "array",
      "items": { "type": "string" },
      "description": "List of referenced transaction IDs for causal linking."
    },

    "signature": {
      "type": "string",
      "description": "Cryptographic signature of the transaction payload (Base64 or hex)."
    },

    "metadata": {
      "type": "object",
      "description": "Optional key-value dictionary for future extensions.",
      "additionalProperties": true
    }
  },

  "additionalProperties": false
}
```

---

# 4. Field-by-Field Explanation

## tx_id
- Must be unique.
- Prevents duplicate/replay transactions.
- Usually UUIDv4, but any sufficiently random 128-bit ID works on embedded devices.

## sender / receiver
- Represent device IDs or account addresses.
- Must match identities known to the system.
- Can later be replaced by public keys for a cryptographic identity layer.

## amount
- Positive number.
- Embedded builds may convert this to an integer (e.g., cents) for precision.

## lamport
- Provides deterministic ordering without real-time clocks.
- Incremented locally every time a new transaction is created.

## device_id
- Identifies the device where the transaction originated.
- Used as secondary tie-breaker in conflict resolution.

## prev_tx_ids
- Used to model dependency, e.g., “B2 depends on B1”.
- Helps reconstruct causal graphs during offline merging.

## signature
- Proof that the sender authorized the transaction.
- Verified using per-device public keys.
- Prevents tampering.

## metadata (optional)
Common examples include:
- group_id for group savings
- trust_score_update flags
- comments/labels
- version numbers

---

# 5. Validation Rules

A transaction is considered **valid** if:

- All required fields exist.
- Data types match the schema.
- Signature matches payload signed by sender.
- Amount is non-negative.
- Lamport value is ≥ the device’s previous lamport.
- prev_tx_ids either exist locally or will be fetched during sync.
- No double-spending occurs when applying ledger rules.

Invalid transactions must be stored but flagged as `invalid` or `orphaned`.

---

# 6. Example Transaction

```json
{
  "tx_id": "7f1c28af-8b52-4b06-b551-01cc3bce98b4",
  "sender": "NODE_A",
  "receiver": "NODE_B",
  "amount": 5.0,
  "lamport": 12,
  "device_id": "NODE_A",
  "prev_tx_ids": [
    "1c83e971-5ed2-4f25-8ac2-e8739e88d8e0"
  ],
  "signature": "ab431ff29bc1eaa9d1f4...",
  "metadata": {
    "note": "Group savings contribution",
    "group_id": "GS_12",
    "version": 1
  }
}
```

---

# 7. Example for Minimal Devices (No Metadata)

```json
{
  "tx_id": "b181b0c7-91d7-4b0c-9305-f4cc964a884a",
  "sender": "NODE_C",
  "receiver": "STORE_17",
  "amount": 1.25,
  "lamport": 3,
  "device_id": "NODE_C",
  "prev_tx_ids": [],
  "signature": "ce8812aa3..."
}
```

---

# 8. Future Extensions

Seed is designed to grow without breaking compatibility. Future schema additions may include:

- ZK-proof fields for private balance verification.
- Merkle roots for checkpointed history.
- Smart-contract–style conditional transactions.
- Multi-signature workflows.
- Local fee accounting.
- Governance flags or trust-score weight hints.

All extensions must go under `metadata` to avoid breaking legacy devices.

---

# 9. Summary

This JSON schema allows Seed devices to:

- Operate fully offline.
- Merge ledgers safely through deterministic, conflict-free rules.
- Verify every transaction securely.
- Maintain compatibility across hardware generations.
- Support low-power embedded systems and full software nodes.

This schema is foundational to the entire Seed architecture and must remain stable, strict, and forward-compatible.
