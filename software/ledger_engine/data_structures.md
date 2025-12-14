# Ledger Engine Data Structures

This document defines the core data structures used by the Seed ledger engine. These structures enable offline-first operation, deterministic conflict resolution, and secure synchronization across a distributed mesh network without reliance on centralized servers or real-time clocks.

All Seed devices must implement these structures consistently to ensure eventual global ledger convergence.

---

## 1. Design Principles

The ledger data structures are designed to satisfy the following requirements:

- Deterministic behavior across devices
- Offline-first operation with delayed synchronization
- Resistance to replay, duplication, and tampering
- Minimal memory and compute footprint
- Compatibility with constrained embedded hardware
- Forward extensibility for future protocol upgrades

---

## 2. Core Ledger Object Model

The Seed ledger is composed of three primary object types:

- Transaction
- Ledger Entry
- Ledger State Snapshot

Each object is described below.

---

## 3. Transaction Object

The Transaction is the atomic unit of value transfer within Seed.

Each transaction represents a single, immutable financial action created by a device.

### Transaction Structure

Transaction {
tx_id: string
sender_id: string
receiver_id: string
amount: float
lamport_clock: integer
device_id: string
prev_tx_ids: list
signature: string
metadata: map<string, string>
}

### Field Descriptions

- tx_id  
  Globally unique identifier for the transaction (UUID or equivalent).

- sender_id  
  Identifier of the account or wallet sending value.

- receiver_id  
  Identifier of the account or wallet receiving value.

- amount  
  Positive numeric value representing the amount transferred.

- lamport_clock  
  Logical timestamp generated locally by the originating device.

- device_id  
  Unique identifier of the device that created the transaction.

- prev_tx_ids  
  Optional list of parent transaction IDs establishing causal relationships.

- signature  
  Cryptographic signature verifying authenticity and integrity.

- metadata  
  Optional extensible key-value data (e.g. memo, group ID, trust update tag).

Transactions are immutable once created.

---

## 4. Ledger Entry Object

A Ledger Entry represents the validation and application state of a transaction within the local ledger.

### Ledger Entry Structure

LedgerEntry {
transaction: Transaction
status: enum { PENDING, VALID, INVALID, ORPHANED }
validation_reason: string
applied_balance_delta: float
}


### Field Descriptions

- transaction  
  The underlying Transaction object.

- status  
  Current validation state:
  - PENDING: awaiting missing dependencies
  - VALID: accepted and applied
  - INVALID: rejected due to rule violation
  - ORPHANED: unresolved causal references

- validation_reason  
  Human-readable explanation of validation outcome.

- applied_balance_delta  
  Net balance change applied by this transaction.

Ledger entries allow devices to store and reason about incomplete or conflicting histories.

---

## 5. Ledger State Snapshot

The Ledger State Snapshot represents the current resolved state of all balances and trust metrics.

### Ledger State Structure

LedgerState {
balances: map<account_id, float>
trust_scores: map<account_id, integer>
applied_tx_ids: set
last_checkpoint_lamport: integer
}

### Field Descriptions

- balances  
  Mapping of account IDs to current balances.

- trust_scores  
  Mapping of account IDs to trust scores.

- applied_tx_ids  
  Set of transaction IDs already applied to prevent duplication.

- last_checkpoint_lamport  
  Lamport timestamp of last committed checkpoint.

Snapshots enable fast recovery and validation without replaying full history.

---

## 6. Device Ledger Container

Each device maintains a local ledger container that aggregates all components.

### Ledger Container Structure

DeviceLedger {
entries: map<tx_id, LedgerEntry>
state: LedgerState
pending_queue: list<tx_id>
orphan_queue: list<tx_id>
}

### Responsibilities

- Store all known transactions
- Track validation state
- Apply deterministic ordering
- Support incremental reconciliation
- Enable safe power-loss recovery

---

## 7. Ordering and Sorting Rules

Transactions must be globally ordered using deterministic criteria:

1. Lamport clock (ascending)
2. Device ID (lexicographical)
3. Transaction ID (final tie-breaker)

This ordering guarantees identical ledger outcomes across all devices.

---

## 8. Memory and Storage Considerations

- Transactions stored in compact serialized form
- Ledger entries indexed by tx_id
- Periodic pruning of invalid/orphaned entries
- Snapshot-based recovery minimizes replay cost
- Structures optimized for flash storage and low RAM usage

---

## 9. Security Properties

The data structures enforce security by design:

- Immutability of transactions
- Explicit validation state tracking
- Duplicate prevention via tx_id sets
- Cryptographic verification hooks
- Isolation of pending and orphaned data

---

## 10. Extensibility

Future extensions may include:

- Merkle roots for ledger segments
- Vector clocks for multi-party causality
- Zero-knowledge metadata fields
- Compression-aware transaction formats

All extensions must preserve backward compatibility.

---

## 11. Summary

The Seed ledger data structures provide a robust foundation for decentralized, offline financial coordination. By separating immutable transactions from validation state and resolved balances, Seed ensures resilience, consistency, and security across unpredictable connectivity environments.

These structures are the backbone of Seed’s trustless, serverless financial network.
