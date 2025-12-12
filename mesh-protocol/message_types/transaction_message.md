# Transaction Message Specification

This document defines the **Transaction Message** used by Seed devices to exchange financial transactions across a fully offline, peer-to-peer mesh network. Transaction messages are the core unit of value transfer in the Seed protocol and are designed to function reliably without internet connectivity, centralized servers, or synchronized clocks.

---

## 1. Purpose

Transaction messages allow Seed devices to:

- Transfer value between users
- Propagate new transactions across the mesh
- Maintain a consistent distributed ledger
- Support offline-first financial interactions
- Enable eventual global convergence of ledger state

These messages must be **compact, secure, verifiable, and deterministic**.

---

## 2. Design Principles

Transaction messages are designed according to the following principles:

- **Offline-first**: No reliance on internet or external time sources
- **Deterministic**: All devices reach identical results
- **Idempotent**: Duplicate messages do not alter state
- **Secure-by-default**: Cryptographically signed and validated
- **Bandwidth-efficient**: Optimized for low-power LoRa transmission
- **Composable**: Can be batched, forwarded, or cached

---

## 3. When Transaction Messages Are Used

Transaction messages are generated and transmitted when:

- A user sends money to another user
- A group savings contribution is made
- A loan repayment is recorded
- A trust-score-affecting action occurs
- A previously offline device reconnects and syncs

---

## 4. Message Structure Overview

Each transaction message encapsulates a **single logical financial transaction**.

High-level structure:

- Message metadata
- Transaction payload
- Cryptographic signature
- Optional causal references

---

## 5. Transaction Message Schema

### 5.1 JSON Representation

```json
{
  "message_type": "TRANSACTION",
  "tx_id": "uuid-v4-string",
  "sender_id": "DEVICE_OR_USER_ID",
  "receiver_id": "DEVICE_OR_USER_ID",
  "amount": 5.00,
  "currency": "SEED",
  "lamport": 42,
  "device_id": "NODE_A",
  "prev_tx_ids": ["uuid-1", "uuid-2"],
  "timestamp_hint": 1710000000,
  "signature": "BASE64_SIGNATURE"
}
