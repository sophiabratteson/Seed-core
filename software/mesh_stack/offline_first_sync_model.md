# Offline-First Sync Model

This document defines how Seed devices synchronize data in a fully offline-first environment. The system is designed so that **no internet, no servers, and no continuous connectivity** are required for correct operation. Devices may be offline for minutes, days, or months and still safely rejoin the network.

---

## 1. Design Principles

- Offline-first: All functionality must work without internet access.
- Eventual consistency: All devices converge on the same ledger state over time.
- No central authority: No single device controls synchronization.
- Low power: Sync operations must be lightweight and energy-efficient.
- Intermittent connectivity tolerance: Devices sync opportunistically.

---

## 2. Device Roles in Sync

Every Seed device acts as:

- A ledger creator (can generate transactions)
- A ledger holder (stores a local copy)
- A sync participant (shares and merges data)
- A relay node (optionally forwards data for others)

There are **no special master nodes**.

---

## 3. Local-First Data Model

Each device maintains:

- A local ledger (append-only transaction history)
- A local Lamport clock
- A local outbox (new transactions to share)
- A local inbox (received transactions)
- A checkpointed state snapshot

All actions write locally first before any communication occurs.

---

## 4. Sync Triggers

Synchronization can occur when:

- Two devices come within radio range
- A scheduled sync window opens
- A user manually initiates sync
- A relay node rebroadcasts updates
- A device wakes from low-power mode

Sync is opportunistic, not continuous.

---

## 5. Sync Handshake Overview

When two devices detect each other:

1. Exchange device IDs and protocol versions
2. Exchange ledger summary metadata:
   - Latest Lamport clock
   - Last checkpoint hash
   - Known transaction count
3. Determine which transactions are missing
4. Request only missing data
5. Exchange transactions in batches
6. Apply conflict resolution
7. Update local checkpoints

No full ledger dumps are required after initial bootstrap.

---

## 6. Transaction Exchange Strategy

- Transactions are sent in small packets
- Each packet includes:
  - Transaction ID
  - Lamport timestamp
  - Origin device ID
- Devices acknowledge receipt
- Unacknowledged packets are retried later
- Duplicate transactions are ignored safely

This minimizes bandwidth and power use.

---

## 7. Deterministic Merge Process

Upon receiving transactions:

1. Validate transaction format
2. Verify signatures
3. Check for duplicates
4. Insert into pending pool
5. Sort all known transactions by:
   - Lamport clock
   - Device ID
6. Apply transactions in order
7. Mark invalid transactions
8. Commit updated ledger state

All devices perform the same steps and reach the same result.

---

## 8. Handling Long Offline Periods

If a device has been offline for an extended time:

- It may hold many unseen transactions
- Upon reconnection:
  - It advertises its latest Lamport clock
  - Peers respond with newer transactions
  - Missing causal dependencies are requested
- Sync proceeds incrementally until caught up

There is no penalty for long offline gaps.

---

## 9. Partial Sync and Resume

If a sync is interrupted:

- Progress is remembered locally
- Already-received transactions are not re-requested
- Sync resumes at next opportunity
- No data corruption occurs

This supports unstable environments.

---

## 10. Power-Aware Sync Behavior

To conserve power:

- Sync pauses when battery is low
- Large syncs are split into sessions
- Background sync uses reduced radio power
- User-facing operations always take priority

Power state directly influences sync behavior.

---

## 11. Security During Offline Sync

- All messages are signed
- Replay attacks are rejected
- Tampered packets are discarded
- Device identity is verified cryptographically
- No plaintext sensitive data is transmitted

Security does not rely on connectivity.

---

## 12. Failure Scenarios

The system tolerates:

- Packet loss
- Device crashes mid-sync
- Power loss during write
- Duplicate message delivery
- Network partitions

Recovery is automatic via deterministic re-sync.

---

## 13. Example Offline Sync Scenario

1. Device A and B are offline for weeks
2. Both create transactions locally
3. They later come into range
4. They exchange summaries
5. Missing transactions are exchanged
6. Ledgers merge deterministically
7. Both devices reach identical state

No external infrastructure is required.

---

## 14. Relationship to Other Components

This sync model depends on:

- Ledger engine conflict resolution
- Mesh routing layer
- Serialization format
- Security and authentication modules

It does not depend on internet access or centralized services.

---

## 15. Summary

Seed’s offline-first sync model enables resilient financial coordination in environments where connectivity is unreliable or nonexistent. By prioritizing local state, deterministic merging, and opportunistic exchange, Seed achieves global consistency without centralized infrastructure.

This model is foundational to Seed’s mission.
