# JSON Serialization Format

This document defines the JSON serialization format used by the Seed mesh protocol. JSON is used as the primary human-readable message format for early prototypes, debugging, interoperability testing, and low-bandwidth ledger synchronization. While binary formats may be introduced later, JSON remains the canonical reference representation.

---

## 1. Purpose of JSON Serialization

The JSON format in Seed serves several purposes:

- Enable deterministic data exchange between offline devices
- Allow easy inspection, debugging, and auditing
- Provide a bridge format for gateways, kiosks, and future APIs
- Support forward compatibility with binary compression layers
- Maintain readability for researchers, regulators, and partners

JSON is chosen because it is widely supported, self-describing, and resilient to partial transmission failures.

---

## 2. General Serialization Principles

All JSON messages in Seed follow these rules:

- UTF-8 encoding only
- Canonical key ordering (alphabetical)
- No trailing commas
- No floating-point ambiguity (fixed decimal precision where required)
- Explicit versioning in every message
- Deterministic field inclusion (no optional omission once defined)

This ensures that identical data always serializes to identical byte sequences.

---

## 3. Top-Level Message Envelope

Every JSON message transmitted over the mesh uses a standard envelope:

```
{
  "protocol_version": "1.0",
  "message_type": "transaction",
  "message_id": "uuid",
  "sender_device_id": "DEVICE_ABC",
  "lamport_clock": 42,
  "payload": { ... },
  "signature": "base64_signature"
}
```

### Field Definitions

- protocol_version  
  Semantic version of the mesh protocol

- message_type  
  Identifies the payload schema (transaction, ledger_sync, heartbeat, etc.)

- message_id  
  Globally unique UUID for deduplication

- sender_device_id  
  Deterministic device identifier

- lamport_clock  
  Logical timestamp for ordering and conflict resolution

- payload  
  Message-specific data structure

- signature  
  Cryptographic signature of the canonicalized message

---

## 4. Transaction Payload Format

Transaction messages serialize as follows:

```
{
  "tx_id": "uuid",
  "sender": "USER_A",
  "receiver": "USER_B",
  "amount": 5.00,
  "currency": "LOCAL_UNIT",
  "balance_before": 20.00,
  "balance_after": 15.00,
  "prev_tx_ids": ["uuid1", "uuid2"],
  "created_lamport": 41,
  "origin_device": "DEVICE_ABC"
}
```

### Serialization Rules

- Amounts use fixed decimal precision
- Currency codes are explicit
- All balances are calculated locally and validated during merge
- prev_tx_ids preserve causal ordering

---

## 5. Ledger Sync Payload Format

Ledger synchronization messages serialize as:

```
{
  "ledger_id": "LEDGER_MAIN",
  "known_tx_ids": ["uuid1", "uuid2"],
  "missing_ranges": [
    { "from": 10, "to": 25 }
  ],
  "checkpoint_hash": "sha256_hash"
}
```

This allows partial ledger reconciliation without full state transfer.

---

## 6. Group Savings Payload Format

Group savings messages include structured metadata:

```
{
  "group_id": "GROUP_X",
  "member_id": "USER_A",
  "contribution_amount": 1.00,
  "cycle_index": 12,
  "group_balance": 48.00,
  "rotation_order": ["USER_A","USER_B","USER_C"]
}
```

Group state is reconstructed deterministically across devices.

---

## 7. Trust Score Update Payload Format

Trust score updates serialize as:

```
{
  "user_id": "USER_A",
  "previous_score": 62,
  "delta": +3,
  "new_score": 65,
  "reason_code": "ON_TIME_REPAYMENT",
  "related_tx_id": "uuid"
}
```

Reason codes are standardized across the protocol.

---

## 8. Canonicalization Process

Before signing or transmitting, JSON messages are canonicalized:

1. Keys sorted alphabetically
2. Whitespace removed
3. Numeric values normalized
4. Arrays preserved in declared order
5. Payload serialized before signature applied

Canonicalization guarantees cryptographic integrity across devices.

---

## 9. Compression Compatibility

JSON is designed to be:

- Directly compressible (gzip, CBOR, zstd)
- Convertible to binary formats without semantic loss
- Backward-compatible with older parsers

Future versions may transmit compressed JSON frames.

---

## 10. Error Handling and Validation

Devices validate incoming JSON by:

- Schema validation
- Signature verification
- Field completeness checks
- Lamport monotonicity enforcement
- Duplicate message detection

Invalid messages are rejected and optionally logged.

---

## 11. Security Considerations

- Sensitive data is minimized at the JSON layer
- Private keys never appear in serialized messages
- Replay attacks prevented via message_id + lamport tracking
- Tampering detected via signature mismatch

---

## 12. Future Extensions

Planned extensions include:

- Encrypted JSON payloads
- Selective field disclosure
- Zero-knowledge metadata proofs
- Automatic downgrade to minimal payloads

---

## 13. Summary

The JSON serialization format provides Seed with a transparent, deterministic, and secure data exchange layer suitable for offline-first mesh networking. It balances human readability with strict ordering guarantees, making it ideal for early deployment, auditing, and gradual system evolution.
