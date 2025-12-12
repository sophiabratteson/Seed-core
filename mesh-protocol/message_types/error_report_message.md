# Error Report Message Specification

This document defines the **Error Report Message** used in the Seed mesh protocol.  
Error Report Messages allow devices to communicate faults, failures, or abnormal conditions across the offline mesh network in a controlled, privacy-preserving, and bandwidth-efficient way.

---

## 1. Purpose and Goals

The Error Report Message exists to:

- Detect and diagnose failures in a fully offline mesh network
- Improve network resilience without centralized monitoring
- Allow devices to self-heal or trigger safe fallbacks
- Provide auditability without exposing sensitive user data
- Support field diagnostics during pilots and deployments

The protocol is designed to **never leak private financial data**, even during error reporting.

---

## 2. When Error Reports Are Generated

A Seed device generates an Error Report Message when it encounters:

- Transaction validation failures
- Ledger merge inconsistencies
- Radio transmission failures beyond retry thresholds
- Storage corruption or checksum mismatches
- Power instability or unsafe battery conditions
- Security violations or suspected tampering
- Firmware or protocol version incompatibility
- Unexpected crashes or watchdog resets

Error reporting is **rate-limited** to prevent abuse or flooding.

---

## 3. Error Severity Levels

Each error includes a severity classification:

- INFO  
  - Non-critical informational events
  - Example: temporary packet loss

- WARNING  
  - Recoverable issues
  - Example: delayed ledger sync

- ERROR  
  - Functional failure requiring intervention
  - Example: invalid ledger state

- CRITICAL  
  - Security or safety risk
  - Example: tamper detection triggered

Severity affects propagation scope and retention time.

---

## 4. Error Report Message Format

```
{
  "message_type": "ERROR_REPORT",
  "device_id": "NODE_A",
  "error_id": "ERR-LEDGER-004",
  "severity": "ERROR",
  "subsystem": "ledger_engine",
  "error_code": "CONFLICT_RESOLUTION_FAILURE",
  "description": "Ledger merge failed due to missing causal ancestors",
  "timestamp_lamport": 187,
  "related_tx_ids": ["tx_92af", "tx_13bd"],
  "firmware_version": "0.3.1",
  "protocol_version": "1.0",
  "retryable": true,
  "signature": "BASE64_SIGNATURE"
}
```

---

## 5. Field Definitions

- message_type  
  Always set to `"ERROR_REPORT"`

- device_id  
  Anonymous device identifier (not user identity)

- error_id  
  Unique error identifier for classification and analytics

- severity  
  INFO | WARNING | ERROR | CRITICAL

- subsystem  
  Originating subsystem  
  Examples: radio, ledger_engine, power_system, security

- error_code  
  Machine-readable error category

- description  
  Human-readable summary (no sensitive data)

- timestamp_lamport  
  Logical clock for ordering across offline devices

- related_tx_ids  
  Optional references to affected transactions

- firmware_version  
  Helps identify version-specific issues

- protocol_version  
  Ensures compatibility during debugging

- retryable  
  Indicates whether automatic retry is safe

- signature  
  Cryptographic signature for authenticity

---

## 6. Propagation Rules

Error messages propagate differently based on severity:

- INFO  
  - Local only
  - Not forwarded across mesh

- WARNING  
  - Shared with immediate neighbors

- ERROR  
  - Propagated to mesh within limited radius

- CRITICAL  
  - Flooded across mesh with priority
  - Stored until acknowledged

Propagation respects power constraints and network congestion.

---

## 7. Privacy and Security Guarantees

Error reports **must never include**:

- User names or personal identifiers
- Account balances
- Raw transaction payloads
- Biometric data
- Location data

Security safeguards:

- Signed by device identity key
- Encrypted during transport
- Replay-protected using lamport clocks
- Deduplicated via error_id + device_id

---

## 8. Storage and Retention

Devices store error reports:

- INFO: Not persisted
- WARNING: Temporary cache
- ERROR: Stored until resolved
- CRITICAL: Stored permanently until cleared

Retention policies can be tuned per deployment.

---

## 9. Interaction with Other Message Types

Error Report Messages may trigger:

- Retry logic in transaction sync
- Safe-mode activation
- Reduced radio duty cycle
- Emergency wipe protocol (security subsystem)
- Maintenance alerts during field tests

They do **not** block normal ledger operation unless marked CRITICAL.

---

## 10. Example Scenarios

### Ledger Conflict Failure
- Device reports missing causal references
- Neighbor devices respond with missing transactions

### Radio Failure
- Device reports repeated send failures
- Mesh reroutes traffic around node

### Tamper Detection
- CRITICAL error broadcast
- Device locks ledger and disables inputs

---

## 11. Future Extensions

Planned enhancements include:

- Aggregated error summaries
- Trust-score weighted error credibility
- Optional anonymized telemetry export during audits
- Field-debug modes for NGOs and researchers

---

## 12. Summary

The Error Report Message enables Seed to operate safely and transparently in extreme environments.  
By combining structured error classification, offline-safe ordering, and strict privacy boundaries, Seed ensures reliability without sacrificing user trust or security.

This mechanism is essential for scaling Seed from pilot deployments to global networks.
