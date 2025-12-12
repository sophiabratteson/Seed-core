# Lamport Clock Usage in Seed Mesh Sync

This document defines how Lamport logical clocks are used throughout the Seed mesh protocol to ensure deterministic ordering, conflict resolution, and eventual ledger consistency in a fully offline, decentralized environment.

Lamport clocks are a foundational mechanism that allow Seed devices to coordinate state without relying on real time, synchronized clocks, internet access, or centralized authorities.

---

## Purpose of Lamport Clocks in Seed

Lamport clocks serve five core purposes:

- Establish a consistent global ordering of events across devices
- Enable deterministic conflict resolution
- Prevent replay and reordering attacks
- Support offline-first operation over long disconnection periods
- Guarantee eventual ledger convergence across all nodes

They are used anywhere Seed must answer the question:
**“Which event happened later?”** — without knowing the real time.

---

## What a Lamport Clock Is (Conceptually)

A Lamport clock is a simple integer counter maintained locally by each device.

Rules:
- Each device maintains its own counter
- The counter only ever increases
- No two devices need to agree on absolute values
- Ordering is derived from comparisons, not timestamps

Lamport clocks do NOT represent time.
They represent **causal ordering**.

---

## Device-Level Lamport Clock State

Each Seed device maintains:

- `lamport_counter` (integer)
- `device_id` (unique, immutable identifier)

These two values together define a globally comparable event identity.

---

## Lamport Clock Update Rules

### Rule 1: Local Event
Whenever a device creates a new event (transaction, trust update, group savings action):

- Increment `lamport_counter` by 1
- Assign the new value to the event

### Rule 2: Receiving an Event
When a device receives an event from another node:

- Compare local `lamport_counter` with received `lamport`
- Set local counter to:

max(local_counter, lamport_recieved) + 1

This guarantees forward progress and preserves causal ordering.

---

## Lamport Clock in Transactions

Every transaction includes:

- `lamport` — logical timestamp
- `device_id` — origin identifier

Example:

{
“tx_id”: “abc123”,
“sender”: “user_A”,
“receiver”: “user_B”,
“amount”: 5.0,
“lamport”: 42,
“device_id”: “NODE_A”
}

This pair uniquely defines the transaction’s position in global order.

---

## Deterministic Global Ordering

Seed orders all events using the following rule:

1. Sort by `lamport` (ascending)
2. If equal, sort by `device_id` (lexicographically)

This ensures:
- Every device computes the same ordering
- Arrival order does not matter
- No ambiguity remains

---

## Why Device ID Tie-Breaking Matters

Lamport clocks alone do not prevent ties.
Two devices may independently generate events with the same lamport value.

The device ID tie-breaker guarantees:
- Deterministic resolution
- No randomness
- No reliance on trust or reputation

All nodes will resolve ties identically.

---

## Use Cases Across Seed

Lamport clocks are used in:

- Financial transactions
- Group savings contributions and withdrawals
- Trust score updates
- Ledger synchronization
- Conflict resolution
- Replay protection
- Audit ordering

They are a system-wide primitive.

---

## Offline-First Benefits

Lamport clocks enable:

- Unlimited offline operation
- Safe batch sync after long disconnections
- No dependence on real-time clocks
- No clock drift issues
- No NTP, GPS, or internet dependencies

Devices may be offline for days, weeks, or months without risk of corruption.

---

## Replay Attack Prevention

A replayed event will have:
- A lamport value lower than or equal to already-applied events
- A duplicate `tx_id`

Such events are rejected automatically during validation.

---

## Ledger Merge Behavior

When merging ledgers:

1. Collect all known events
2. Remove duplicates by `tx_id`
3. Sort using lamport + device ID
4. Apply sequentially
5. Reject invalid or conflicting operations

Lamport clocks ensure this merge is deterministic and idempotent.

---

## Interaction With Conflict Resolution

Lamport clocks do not decide *validity*.
They decide *order*.

Validity is determined by:
- Balance checks
- Signature verification
- Business rules
- Trust constraints

Ordering ensures all devices evaluate validity in the same sequence.

---

## Storage and Persistence

Each device must persist:

- Current lamport counter
- Highest lamport seen per peer (optional optimization)

On reboot or power loss:
- Counter resumes from last stored value
- Never resets or decreases

---

## Failure and Edge Cases

### Device Reset
If a device resets improperly:
- It must restore lamport from secure storage
- If reset to zero, it risks rejection by peers

### Malicious Lamport Inflation
If a device artificially inflates lamport:
- Ordering still works
- Economic and trust rules limit damage
- No system-wide failure occurs

---

## Why Not Real Time?

Seed explicitly avoids real timestamps because:

- No reliable clocks in many regions
- High drift in low-cost hardware
- Vulnerability to manipulation
- Dependency on external infrastructure

Lamport clocks are sufficient and safer.

---

## Future Extensions

Possible enhancements:

- Vector clocks for multi-party causal graphs
- Merkle proofs referencing lamport ranges
- Compression of lamport deltas
- Trust-weighted ordering layers (without breaking determinism)

All extensions must preserve deterministic ordering.

---

## Summary

Lamport clocks are the backbone of Seed’s offline synchronization model.

They allow:
- Global consistency without connectivity
- Deterministic conflict resolution
- Secure, auditable event ordering
- Scalable, infrastructure-free finance

Without Lamport clocks, Seed cannot exist.

With them, Seed works anywhere.
