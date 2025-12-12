# Ledger Sync Message Specification

This document defines the **Ledger Sync Message**, a core message type used by Seed devices to synchronize financial ledgers across an offline-first, peer-to-peer mesh network.

Ledger Sync Messages allow Seed devices to exchange transaction histories, reconcile differences, and converge on a consistent ledger state **without relying on internet connectivity, servers, or centralized infrastructure**.

---

## 1. Purpose of Ledger Sync Messages

Ledger Sync Messages enable devices to:

- Share newly created transactions with nearby Seed devices
- Recover missing ledger entries after periods of disconnection
- Reconcile parallel transaction histories created offline
- Support gradual convergence across low-bandwidth mesh networks
- Maintain financial consistency without real-time connectivity

These messages are fundamental to Seed’s offline financial system.

---

## 2. When Ledger Sync Messages Are Used

Ledger Sync Messages are exchanged in the following scenarios:

- Two Seed devices come within mesh range after being offline
- A device reboots and requests missing ledger data
- A device joins a group savings pool
- Periodic background synchronization occurs
- A kiosk or bridge node reconnects to a larger network

Syncs may be **opportunistic**, **scheduled**, or **user-initiated**.

---

## 3. Sync Model Overview

Seed uses a **transaction-based, append-only ledger model**.

Devices do **not** exchange balances or account states directly.

Instead, they exchange:

- Transaction metadata
- Transaction identifiers
- Transaction payloads (when requested)

Ledger state is reconstructed deterministically from transactions.

---

## 4. Types of Ledger Sync Messages

Ledger synchronization occurs in stages using multiple message subtypes.

### 4.1 Ledger Summary Message

A lightweight message that advertises what a device knows.

Used to minimize bandwidth usage.

Contains:
- Device ID
- Latest Lamport clock value
- Ledger checkpoint hash
- Count of known transactions

---

### 4.2 Transaction Inventory Message

Lists transaction IDs held by a device.

Used to detect missing transactions.

Contains:
- List of tx_id values
- Corresponding Lamport timestamps
- Origin device IDs

---

### 4.3 Transaction Request Message

Sent when a device detects missing transactions.

Contains:
- Requested tx_id values
- Priority flags (e.g., group savings, trust score updates)

---

### 4.4 Transaction Transfer Message

Carries full transaction payloads.

Contains:
- Complete transaction objects
- Cryptographic signatures
- Causal references

---

### 4.5 Sync Completion Message

Indicates sync cycle completion.

Contains:
- Final ledger hash
- Sync success/failure status
- Optional diagnostics

---

## 5. Ledger Sync Message Format

All Ledger Sync Messages follow a common envelope structure.

### 5.1 Message Envelope

```
{
  "message_type": "LEDGER_SYNC",
  "subtype": "SUMMARY | INVENTORY | REQUEST | TRANSFER | COMPLETE",
  "sender_device_id": "NODE_A",
  "receiver_device_id": "NODE_B",
  "session_id": "UUID",
  "lamport": 42,
  "payload": { ... },
  "signature": "BASE64_SIGNATURE"
}
```

---

## 6. Payload Definitions

### 6.1 Ledger Summary Payload

```
{
  "latest_lamport": 128,
  "ledger_hash": "abc123...",
  "transaction_count": 542
}
```

---

### 6.2 Transaction Inventory Payload

```
{
  "transactions": [
    {
      "tx_id": "uuid",
      "lamport": 34,
      "origin_device": "NODE_C"
    }
  ]
}
```

---

### 6.3 Transaction Request Payload

```
{
  "requested_tx_ids": ["uuid1", "uuid2"],
  "priority": "HIGH | NORMAL"
}
```

---

### 6.4 Transaction Transfer Payload

```
{
  "transactions": [
    {
      "tx_id": "uuid",
      "sender": "alice",
      "receiver": "bob",
      "amount": 5.0,
      "lamport": 12,
      "device_id": "NODE_A",
      "prev_tx_ids": [],
      "signature": "..."
    }
  ]
}
```

---

### 6.5 Sync Completion Payload

```
{
  "final_ledger_hash": "def456...",
  "status": "SUCCESS | PARTIAL | FAILED",
  "notes": "optional diagnostics"
}
```

---

## 7. Sync Flow Sequence

Typical sync sequence:

1. Devices exchange Ledger Summary messages
2. Devices compare ledger hashes and Lamport clocks
3. Inventory messages are exchanged
4. Missing transactions are requested
5. Transactions are transferred
6. Conflict resolution is applied locally
7. Sync Completion message is sent

Each step may repeat until convergence.

---

## 8. Bandwidth and Power Optimization

Ledger Sync Messages are optimized for:

- Low packet sizes
- Incremental sync
- Partial transmission
- Opportunistic retries
- Energy-aware duty cycling

Inventory and summary messages are preferred over full transfers whenever possible.

---

## 9. Conflict Handling During Sync

Ledger Sync Messages do not resolve conflicts directly.

They provide inputs to the **Conflict Resolution Engine**, which:

- Sorts transactions deterministically
- Applies Lamport clock ordering
- Enforces balance and validity rules
- Produces a consistent ledger state

---

## 10. Security Considerations

- All messages are cryptographically signed
- Replay attacks prevented via Lamport clocks
- Tampered payloads fail signature validation
- Device identity verified before acceptance
- Invalid transactions are quarantined

---

## 11. Failure and Recovery

If sync fails:

- Partial progress is retained
- Requests are retried opportunistically
- No data loss occurs
- Devices resume syncing when connectivity returns

Ledger Sync is **eventually consistent**, not real-time dependent.

---

## 12. Investor Summary

Ledger Sync Messages enable Seed to operate as a **fully decentralized financial network** without servers, internet, or banks.

This protocol allows:

- Offline-first money
- Community-based trust
- Global convergence through local interactions

Ledger Sync is the backbone that makes Seed scalable, resilient, and inclusive.

---
