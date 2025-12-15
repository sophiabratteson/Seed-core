# JSON-RPC API Specification (Seed)

This document defines the JSON-RPC–style interface used internally by Seed devices to expose, query, and synchronize state across devices, kiosks, maintenance tools, and future external integrations. This API is **offline-first**, **device-local**, and **transport-agnostic**, meaning it can operate over mesh radio, USB, local WiFi, or file-based transfer without requiring the internet.

---

## 1. Purpose and Scope

The Seed JSON-RPC API exists to:

- Standardize how Seed devices expose internal state and actions
- Enable deterministic, auditable state exchange between devices
- Support debugging, diagnostics, and maintenance tools
- Allow future interoperability with kiosks, gateways, or regulated systems
- Maintain strict security boundaries while remaining extensible

This API **does not imply internet connectivity** and is not a public web API.

---

## 2. Design Principles

- Offline-first: All calls must work without network connectivity
- Deterministic: Identical inputs produce identical outputs
- Minimal surface area: Only essential methods are exposed
- Explicit authorization: Every call is permission-checked
- Transport-neutral: JSON-RPC payloads can be carried over any medium

---

## 3. JSON-RPC Envelope Format

All API calls use a standard JSON-RPC 2.0–style envelope.

### Request Format

```
{
  "jsonrpc": "2.0",
  "method": "method.name",
  "params": { },
  "id": "request_id"
}
```

### Response Format (Success)

```
{
  "jsonrpc": "2.0",
  "result": { },
  "id": "request_id"
}
```

### Response Format (Error)

```
{
  "jsonrpc": "2.0",
  "error": {
    "code": -32001,
    "message": "Error description",
    "data": { }
  },
  "id": "request_id"
}
```

---

## 4. Core Method Categories

Methods are grouped into logical domains.

- Device management
- Ledger operations
- Sync and export
- Security and identity
- Diagnostics and status

---

## 5. Device Management Methods

### device.getInfo

Returns basic device metadata.

```
method: "device.getInfo"
```

Result:
```
{
  "device_id": "SEED-ABC123",
  "firmware_version": "0.1.0",
  "hardware_revision": "revA",
  "region": "US-915"
}
```

---

### device.getStatus

Returns current operational status.

```
method: "device.getStatus"
```

Result:
```
{
  "battery_level": 82,
  "power_mode": "low_power",
  "radio_state": "idle",
  "secure_element": "locked"
}
```

---

## 6. Ledger Methods

### ledger.getSummary

Returns high-level ledger statistics.

```
method: "ledger.getSummary"
```

Result:
```
{
  "transaction_count": 124,
  "last_lamport": 893,
  "checkpoint_id": "chk_2024_09_18"
}
```

---

### ledger.exportState

Exports a deterministic snapshot of the ledger.

```
method: "ledger.exportState"
```

Result:
```
{
  "ledger_hash": "abc123...",
  "transactions": [ ... ]
}
```

---

### ledger.importState

Imports and merges an external ledger snapshot.

```
method: "ledger.importState"
```

Params:
```
{
  "transactions": [ ... ]
}
```

Result:
```
{
  "imported": 34,
  "conflicts_resolved": 2
}
```

---

## 7. Sync and Communication Methods

### sync.prepareOutbox

Prepares outbound data for transmission.

```
method: "sync.prepareOutbox"
```

Result:
```
{
  "outbox_id": "out_9981",
  "size_bytes": 2048
}
```

---

### sync.applyInbox

Applies received data from another device.

```
method: "sync.applyInbox"
```

Params:
```
{
  "payload": { ... }
}
```

Result:
```
{
  "applied": true,
  "new_transactions": 12
}
```

---

## 8. Security and Identity Methods

### security.getPublicKey

Returns the device’s public identity key.

```
method: "security.getPublicKey"
```

Result:
```
{
  "public_key": "BASE64ENCODEDKEY"
}
```

---

### security.verifyPayload

Verifies a signed payload.

```
method: "security.verifyPayload"
```

Params:
```
{
  "payload": { ... },
  "signature": "..."
}
```

Result:
```
{
  "valid": true
}
```

---

## 9. Diagnostics and Maintenance Methods

### diagnostics.healthCheck

Returns internal health metrics.

```
method: "diagnostics.healthCheck"
```

Result:
```
{
  "storage_ok": true,
  "radio_ok": true,
  "ledger_ok": true
}
```

---

### diagnostics.exportLogs

Exports recent diagnostic logs.

```
method: "diagnostics.exportLogs"
```

Result:
```
{
  "log_bundle_id": "logs_2024_09_18"
}
```

---

## 10. Error Codes

Standardized error codes ensure consistent handling.

- -32000: General failure
- -32001: Invalid parameters
- -32002: Unauthorized
- -32003: Ledger conflict
- -32004: Storage error
- -32005: Cryptographic failure

---

## 11. Authorization Model

- Every method checks caller permissions
- Sensitive methods require secure-element authorization
- Emergency or recovery modes restrict method access
- No method allows raw key extraction or balance overrides

---

## 12. Offline and Transport Considerations

- API payloads may be chunked for radio transmission
- Responses are deterministic and idempotent
- Calls may be replayed safely without side effects
- File-based and USB-based transports use identical payloads

---

## 13. Extensibility and Versioning

- New methods must follow namespaced conventions
- Backward compatibility is preserved where possible
- Version negotiation occurs at transport initialization

---

## 14. Investor Summary

This JSON-RPC API provides Seed with:

- A clean abstraction between hardware, firmware, and higher-level systems
- A future-proof interface for scaling beyond early prototypes
- A secure, auditable foundation for offline financial operations
- Clear separation between internal logic and external integrations

The API is intentionally minimal today while enabling long-term interoperability with regulated financial infrastructure, kiosks, and global gateways as Seed evolves.
