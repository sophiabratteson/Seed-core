# Software API Overview

## Purpose

This document defines the internal and external API surface of the Seed system.  
Seed is an offline-first, device-centric platform, so APIs are **not web-based REST endpoints** in the traditional sense. Instead, Seed APIs define **how internal modules communicate**, **how devices exchange data**, and **how state is exported/imported** during synchronization events.

The API layer acts as a contract between:
- Ledger engine
- Mesh networking stack
- Device applications
- Secure storage
- External interfaces (future gateways, kiosks, audits)

---

## Design Principles

- Offline-first: APIs must function without internet access
- Deterministic behavior: identical inputs always produce identical outputs
- Minimal bandwidth usage: optimized for low-power mesh transport
- Secure-by-default: every API call assumes adversarial conditions
- Explicit versioning: forward-compatible evolution without breaking old devices

---

## API Categories

Seed APIs are divided into five categories:

1. Internal Module APIs
2. Ledger APIs
3. Mesh Communication APIs
4. State Export / Import APIs
5. Future External Integration APIs

---

## 1. Internal Module APIs

These APIs define how firmware and software components interact inside a single Seed device.

### Examples
- Ledger engine calling storage manager
- Device app requesting balance update
- Trust score engine querying transaction history

### Characteristics
- Function-call based
- No serialization overhead
- Strong typing (C structs / internal objects)
- Trusted execution environment

### Example (conceptual)
```
ledger_apply_transaction(transaction_t *tx)
ledger_get_balance(account_id)
trust_score_update(account_id, event)
```

---

## 2. Ledger APIs

Ledger APIs expose controlled access to the financial state of the device.

### Core Responsibilities
- Transaction submission
- Transaction validation
- Ledger queries
- Checkpoint generation
- Conflict resolution triggers

### Supported Operations
- Submit transaction
- Validate transaction
- Query account balance
- Query transaction history
- Generate ledger snapshot

### Example Ledger API Calls
```
ledger_submit(tx)
ledger_validate(tx)
ledger_get_balance(user_id)
ledger_export_checkpoint()
```

Ledger APIs never expose raw storage or allow mutation without validation.

---

## 3. Mesh Communication APIs

These APIs define how Seed devices exchange information over the mesh network.

### Message Types Supported
- Transaction broadcast
- Ledger sync request
- Ledger sync response
- Trust score update
- Group savings update
- Heartbeat / presence signal
- Error and diagnostics reports

### API Responsibilities
- Packet construction
- Serialization
- Encryption
- Routing metadata attachment
- Retry and acknowledgment handling

### Conceptual Interface
```
mesh_send(message)
mesh_receive(message)
mesh_ack(message_id)
```

Mesh APIs are transport-agnostic and do not assume LoRa, Wi-Fi, or Bluetooth.

---

## 4. State Export / Import APIs

These APIs enable devices to synchronize state across long offline periods.

### Export Functions
- Ledger snapshot export
- Transaction outbox export
- Trust score state export
- Group savings state export

### Import Functions
- Merge incoming state
- Validate integrity
- Resolve conflicts deterministically
- Update checkpoints

### Use Cases
- Two devices meet briefly and sync
- Device connects to a kiosk or gateway
- Device recovered after long offline period

### Example
```
state_export()
state_import(payload)
state_merge(payload)
```

These APIs form the backbone of Seed’s offline resilience.

---

## 5. Future External Integration APIs

These APIs are **not required for MVP**, but are designed to allow future expansion without re-architecture.

### Potential Integrations
- Cash-in / cash-out kiosks
- NGO or aid distribution systems
- Government disbursement programs
- Auditing and compliance tools
- Optional internet gateways

### Design Constraints
- Read-only or limited-write access
- Strict permission scopes
- No direct ledger mutation
- Fully logged and auditable

### Example
```
external_query_balance(device_id)
external_submit_signed_tx(tx)
```

External APIs never bypass on-device validation or conflict resolution.

---

## API Versioning Strategy

- Every API message includes:
  - Protocol version
  - Message type
  - Capability flags
- Devices ignore unsupported versions gracefully
- Backward compatibility is prioritized
- Breaking changes require explicit migration steps

---

## Security Model

- All API messages are authenticated
- Sensitive payloads are encrypted
- Replay protection enforced at API layer
- Invalid or malformed API calls are rejected silently
- Rate limiting applied to mesh-facing APIs

APIs are treated as attack surfaces and hardened accordingly.

---

## Error Handling

API errors are categorized as:
- Validation errors
- Authorization errors
- Synchronization conflicts
- Resource exhaustion
- Protocol mismatch

Errors are:
- Logged locally
- Optionally shared over mesh
- Never fatal to device operation

---

## Summary

The Seed API layer defines **how a fully decentralized financial system functions without servers, internet, or centralized control**.  
By separating internal logic, mesh communication, ledger access, and future integrations, Seed achieves:

- Modularity
- Security
- Scalability
- Long-term extensibility

This API design allows Seed to grow from a two-device prototype into a global offline financial network without rewriting its core architecture.
