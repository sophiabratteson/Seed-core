# Mesh Sync Overview

This document defines how Seed devices synchronize financial data across a fully offline, peer-to-peer mesh network. The sync system is designed to operate without internet access, centralized servers, or continuous connectivity. It ensures that all Seed devices eventually converge on the same ledger state while preserving security, efficiency, and resilience in low-resource environments.

---

## Purpose of the Sync System

The mesh sync system enables Seed devices to:
- Exchange financial data without internet connectivity
- Operate asynchronously with long offline periods
- Merge transaction histories deterministically
- Prevent data loss, duplication, or corruption
- Scale from two devices to large, distributed communities

The sync layer is the backbone that allows Seed to function as a decentralized financial infrastructure.

---

## Core Design Principles

### Offline-First Operation
- Devices assume no continuous connectivity
- All operations must succeed without real-time communication
- Sync occurs opportunistically when devices come into proximity

### Peer-to-Peer Architecture
- No central authority or master node
- All devices are equal participants
- Any device can initiate sync with any other device

### Eventual Consistency
- Devices may temporarily diverge
- Deterministic merge rules guarantee convergence over time
- Final ledger state is identical across devices

### Deterministic Behavior
- Sync outcomes do not depend on message order or arrival time
- All devices follow identical merge logic
- Eliminates ambiguity and forks

---

## Sync Trigger Conditions

A Seed device initiates sync under the following conditions:

- Physical proximity to another Seed device
- Periodic background sync intervals
- User-initiated sync action
- Detection of stale or incomplete ledger state
- Power availability threshold met

Sync attempts are lightweight and adaptive to conserve power.

---

## Sync Participants

Each sync session involves:

### Initiating Device
- Detects nearby peers
- Requests ledger metadata
- Proposes data exchange

### Responding Device
- Shares ledger summary
- Provides missing transactions
- Accepts or rejects incoming data

Roles are symmetric and can switch dynamically.

---

## Data Types Exchanged During Sync

During a sync session, devices may exchange:

- Ledger metadata (ledger hash, transaction count)
- Transaction records
- Group savings updates
- Trust score updates
- Device health and version metadata
- Error or recovery messages

Sensitive data is encrypted at all times.

---

## Sync Phases

### Phase 1: Discovery
- Devices broadcast presence beacons
- Nearby devices respond with basic identity metadata
- Devices assess compatibility and protocol version

### Phase 2: Ledger Summary Exchange
- Devices exchange:
  - Latest ledger checkpoint hash
  - Transaction count
  - Last known lamport clock
- Differences are identified without transferring full data

### Phase 3: Delta Identification
- Devices determine which transactions are missing
- Only unknown or newer transactions are requested
- Prevents unnecessary data transfer

### Phase 4: Transaction Transfer
- Missing transactions are exchanged in batches
- Batches are size-limited to preserve bandwidth
- Each batch is verified upon receipt

### Phase 5: Merge and Validation
- Transactions are merged using deterministic rules
- Conflicts are resolved via lamport clocks and device IDs
- Invalid transactions are discarded

### Phase 6: Checkpointing
- Updated ledger state is saved to secure storage
- New checkpoint hash is generated
- Device becomes eligible to propagate updated state

---

## Partial Sync and Interruption Handling

The sync protocol supports:
- Interrupted sync sessions
- Power loss mid-transfer
- Partial data receipt
- Resume-from-last-known-state logic

Devices store progress markers to avoid restarting from scratch.

---

## Bandwidth and Power Optimization

The sync system minimizes resource usage by:
- Transmitting only deltas, not full ledgers
- Compressing payloads
- Prioritizing critical transactions
- Throttling sync frequency under low battery
- Suspending sync during unsafe power conditions

---

## Security Considerations

- All sync messages are encrypted
- Transactions are cryptographically signed
- Replay attacks are prevented using lamport clocks
- Devices verify origin authenticity before accepting data
- Tampered data is rejected automatically

No device can force invalid data onto another device.

---

## Failure Modes and Recovery

The sync system gracefully handles:
- Malicious or faulty peers
- Corrupted messages
- Version mismatches
- Incomplete transaction chains

Devices isolate problematic peers and continue syncing with others.

---

## Scalability Model

The sync protocol supports:
- Small local groups
- Large community networks
- Multi-hop propagation
- Gradual dissemination across regions

Ledger state spreads organically through repeated local interactions.

---

## Relationship to Other Systems

The sync system integrates with:
- Ledger engine (transaction validation and ordering)
- Conflict resolution logic
- Trust score computation
- Group savings mechanisms
- Security and encryption layers

It does not directly depend on user interfaces or AI systems.

---

## Future Extensions

Planned enhancements include:
- Merkle tree summaries for faster diffing
- Priority-based transaction classes
- Trust-weighted propagation
- Snapshot compression
- Cross-region sync gateways

These features can be added without breaking compatibility.

---

## Summary

The Seed mesh sync protocol enables a resilient, offline-first financial network by allowing devices to discover each other, exchange only necessary data, resolve conflicts deterministically, and converge on a shared ledger state. This system removes the need for centralized infrastructure while preserving security, scalability, and reliability in the most constrained environments.
