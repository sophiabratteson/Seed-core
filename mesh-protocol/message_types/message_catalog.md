# Message Catalog

This document defines the complete set of message types used in the Seed mesh protocol. Messages are the fundamental units of communication between Seed devices. Because Seed operates in a fully offline, peer-to-peer environment with limited bandwidth, every message type is purpose-built, minimal, and deterministic.

This catalog serves as the authoritative reference for all device-to-device communication.

---

## 1. Design Principles

Seed messages are designed according to the following principles:

- Offline-first: Messages must function without internet access.
- Low bandwidth: Messages must be compact and efficient.
- Deterministic: Messages must produce identical results across all devices.
- Secure: Messages must be verifiable and tamper-resistant.
- Resilient: Messages must tolerate loss, delay, and duplication.

All messages share a common envelope structure with type-specific payloads.

---

## 2. Common Message Envelope

Every Seed message includes a shared header format.

```
{
  "message_id": "uuid",
  "message_type": "string",
  "sender_device_id": "string",
  "lamport": integer,
  "timestamp_hint": integer,
  "signature": "string",
  "payload": { }
}
```

### Field Definitions

- message_id  
  Globally unique identifier for the message.

- message_type  
  Identifies how the payload should be interpreted.

- sender_device_id  
  Unique identifier of the originating Seed device.

- lamport  
  Logical clock value used for deterministic ordering.

- timestamp_hint  
  Optional local timestamp used for UI display only.

- signature  
  Cryptographic signature covering header and payload.

- payload  
  Message-type-specific data.

---

## 3. Message Type Overview

The Seed protocol defines the following primary message categories:

- Transaction messages
- Ledger synchronization messages
- Group savings messages
- Trust score update messages
- Heartbeat and presence messages
- Error and diagnostic messages

Each message type is documented below.

---

## 4. Transaction Message

### Purpose
Carries a single financial transaction between devices.

### Message Type
```
"transaction"
```

### Payload Structure
```
{
  "tx_id": "uuid",
  "sender_account": "string",
  "receiver_account": "string",
  "amount": number,
  "currency_unit": "string",
  "prev_tx_ids": ["uuid"],
  "metadata": { }
}
```

### Notes
- Transactions are immutable once broadcast.
- Devices validate transactions before acceptance.
- Duplicate transactions are ignored.

---

## 5. Ledger Sync Message

### Purpose
Shares batches of transactions and ledger state information.

### Message Type
```
"ledger_sync"
```

### Payload Structure
```
{
  "known_tx_ids": ["uuid"],
  "new_transactions": [ { transaction } ],
  "ledger_checkpoint": "hash"
}
```

### Notes
- Used during device encounters or periodic sync windows.
- Supports partial syncing when bandwidth is limited.

---

## 6. Group Savings Message

### Purpose
Coordinates rotating savings pools and group contributions.

### Message Type
```
"group_savings"
```

### Payload Structure
```
{
  "group_id": "uuid",
  "action": "contribute | payout | join | leave",
  "member_id": "string",
  "amount": number,
  "round_index": integer
}
```

### Notes
- Enforces deterministic ordering using lamport clocks.
- Group rules are validated locally by each device.

---

## 7. Trust Score Update Message

### Purpose
Propagates trust score changes across the mesh.

### Message Type
```
"trust_score_update"
```

### Payload Structure
```
{
  "subject_id": "string",
  "delta": integer,
  "reason_code": "string",
  "related_tx_id": "uuid"
}
```

### Notes
- Trust scores are advisory, not authoritative.
- Devices recompute trust locally after merges.

---

## 8. Heartbeat Message

### Purpose
Signals device presence and basic health status.

### Message Type
```
"heartbeat"
```

### Payload Structure
```
{
  "battery_level": integer,
  "storage_available": integer,
  "capabilities": ["string"]
}
```

### Notes
- Helps devices discover neighbors.
- Used for routing optimization and mesh stability.

---

## 9. Error Report Message

### Purpose
Reports malformed messages or protocol violations.

### Message Type
```
"error_report"
```

### Payload Structure
```
{
  "error_code": "string",
  "description": "string",
  "related_message_id": "uuid"
}
```

### Notes
- Errors are informational and non-blocking.
- Used to improve resilience and debugging.

---

## 10. Message Validation Rules

All devices must enforce the following validation steps:

1. Verify message signature.
2. Check message schema correctness.
3. Confirm lamport clock monotonicity.
4. Reject replayed or duplicate message IDs.
5. Validate payload according to message type rules.

Messages failing validation are discarded and optionally logged.

---

## 11. Security Considerations

- All messages are signed using per-device private keys.
- Payload encryption may be applied for sensitive message types.
- Replay attacks are prevented using message IDs and lamport clocks.
- Tampered messages are ignored without propagating errors.

---

## 12. Extensibility

The message catalog is designed to support future extensions:

- New message types can be added without breaking compatibility.
- Unknown message types are safely ignored by older devices.
- Version fields may be added if protocol evolution requires it.

---

## 13. Summary

The Seed message catalog defines a compact, secure, and deterministic communication language for offline financial coordination. By strictly separating message types and enforcing strong validation rules, Seed enables reliable global value exchange without centralized infrastructure.

This catalog forms the backbone of Seed’s mesh protocol.
