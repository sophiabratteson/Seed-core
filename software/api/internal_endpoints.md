# Internal API Endpoints

This document defines the internal API endpoints used within Seed devices to coordinate ledger operations, mesh communication, security functions, and device applications. These endpoints are **not public internet APIs**; they are **local, internal interfaces** used by firmware modules, device applications, and optional host interfaces (e.g., debug tools or kiosks).

The API is designed to function **offline-first**, **deterministically**, and **securely**, ensuring that all internal operations can proceed without network connectivity.

---

## 1. Design Principles

- Offline-first operation with no dependency on external servers
- Deterministic behavior across devices
- Minimal surface area to reduce attack vectors
- Clear separation between system-level APIs and app-level APIs
- Transport-agnostic (can be invoked via local calls, IPC, UART, or USB)

---

## 2. API Architecture Overview

Seed uses a **modular internal API model**, where each subsystem exposes a limited set of callable interfaces:

- Ledger Engine API
- Mesh Stack API
- Security API
- Device Services API
- Application API

Each API is accessed via **function calls or message dispatch**, not HTTP.

---

## 3. Ledger Engine Endpoints

### get_ledger_state
- Returns the current validated ledger snapshot
- Used by wallet app, group savings app, and sync engine

Inputs:
- none

Outputs:
- ledger_state_object

---

### submit_transaction
- Submits a new transaction for validation and inclusion

Inputs:
- transaction_object

Outputs:
- status (accepted | rejected | pending)
- reason (if rejected)

---

### validate_transaction
- Performs full validation checks

Inputs:
- transaction_object

Outputs:
- validation_result
- error_code (optional)

---

### reconcile_ledger
- Triggers deterministic merge with imported transactions

Inputs:
- imported_transaction_set

Outputs:
- reconciliation_report

---

## 4. Mesh Stack Endpoints

### mesh_send_message
- Queues a message for broadcast or targeted delivery

Inputs:
- message_type
- payload
- destination (optional)

Outputs:
- send_status

---

### mesh_receive_message
- Entry point for incoming messages

Inputs:
- raw_message

Outputs:
- parsed_message
- routing_decision

---

### mesh_get_neighbors
- Returns currently known neighboring devices

Inputs:
- none

Outputs:
- neighbor_list

---

### mesh_sync_trigger
- Initiates a sync cycle with nearby devices

Inputs:
- sync_mode (full | incremental)

Outputs:
- sync_status

---

## 5. Security Endpoints

### sign_message
- Cryptographically signs a payload

Inputs:
- payload

Outputs:
- signature

---

### verify_signature
- Verifies authenticity of a signed message

Inputs:
- payload
- signature
- sender_id

Outputs:
- verification_result

---

### encrypt_storage
- Encrypts sensitive data before storage

Inputs:
- plaintext_data

Outputs:
- encrypted_blob

---

### decrypt_storage
- Decrypts data when accessed by authorized modules

Inputs:
- encrypted_blob

Outputs:
- plaintext_data

---

## 6. Device Services Endpoints

### get_device_identity
- Returns device ID and public key

Inputs:
- none

Outputs:
- device_identity_object

---

### get_power_status
- Returns battery and charging state

Inputs:
- none

Outputs:
- power_status_object

---

### trigger_emergency_wipe
- Activates emergency data wipe protocol

Inputs:
- wipe_code

Outputs:
- wipe_confirmation

---

## 7. Application-Level Endpoints

### wallet_get_balance
- Returns current balance for user

Inputs:
- account_id

Outputs:
- balance_value

---

### wallet_send_payment
- Creates and submits a payment transaction

Inputs:
- recipient_id
- amount

Outputs:
- transaction_status

---

### group_savings_get_state
- Returns group savings pool state

Inputs:
- group_id

Outputs:
- group_state_object

---

### trust_score_get
- Returns current trust score

Inputs:
- account_id

Outputs:
- trust_score_value

---

## 8. Error Handling Model

All endpoints return standardized error codes:

- ERR_INVALID_INPUT
- ERR_INSUFFICIENT_FUNDS
- ERR_SIGNATURE_INVALID
- ERR_LEDGER_CONFLICT
- ERR_SECURITY_VIOLATION
- ERR_INTERNAL_FAILURE

Errors are logged locally and optionally propagated through the mesh for diagnostics.

---

## 9. Access Control

- Only authorized modules may call security-critical endpoints
- Application-level APIs are sandboxed
- Secure boot ensures API integrity
- Debug APIs are disabled in production builds

---

## 10. Future Extensions

- Read-only API exposure for audit kiosks
- Optional gateway API for internet bridge nodes
- Formal JSON-RPC mapping for host-based tooling
- Hardware-backed access tokens for sensitive calls

---

## 11. Summary

Seed’s internal API system provides a **secure, deterministic, offline-capable interface layer** that allows complex financial functionality to run reliably on constrained devices. By avoiding internet-style APIs and focusing on local, well-defined interfaces, Seed maintains resilience, privacy, and scalability in extreme environments.
