# Ledger Checkpointing and Recovery

This document defines how Seed devices safely persist ledger state, recover from crashes, power loss, or device failure, and rejoin the mesh network without corruption or inconsistency. Because Seed operates in offline, low-power, and unstable environments, robust checkpointing and recovery are core to system reliability.

---

## 1. Objectives

The checkpointing and recovery system is designed to:

- Prevent loss of financial data during power failure or reboot
- Ensure ledger consistency across restarts
- Enable devices to rejoin the mesh after long offline periods
- Protect against partial writes and corrupted storage
- Minimize flash wear and power consumption
- Support forensic audit and dispute resolution

---

## 2. Core Concepts

### Ledger State
The ledger state includes:
- All validated transactions
- Current account balances
- Group savings pool states
- Trust score values
- Lamport clock position
- Device identity metadata

### Checkpoint
A checkpoint is a snapshot of the ledger state at a specific moment that can be safely reloaded later.

### Recovery
Recovery is the process of restoring the ledger from the most recent valid checkpoint and replaying newer transactions if needed.

---

## 3. Checkpoint Strategy

### 3.1 Incremental Checkpointing

Seed uses incremental checkpointing to balance safety and performance.

- Full checkpoint created periodically
- Incremental deltas written between full checkpoints
- Transactions logged append-only until checkpoint commit

This minimizes write amplification and flash wear.

---

### 3.2 Trigger Conditions

A checkpoint may be triggered by:

- Fixed transaction count threshold
- Time-based interval
- Battery level reaching critical threshold
- Manual user request
- Before firmware update
- Before entering deep sleep

---

### 3.3 Atomic Write Guarantee

To ensure safety:

- Checkpoints are written to a temporary location
- Data is verified using checksums
- Only after verification is the checkpoint marked “active”
- Old checkpoint is retained until new one is confirmed

This prevents corruption from power loss mid-write.

---

## 4. Storage Layout

### 4.1 Storage Components

Ledger storage consists of:

- Active checkpoint
- Previous checkpoint (fallback)
- Transaction journal
- Integrity metadata
- Recovery markers

Each component is stored separately to reduce corruption risk.

---

### 4.2 Flash Wear Management

To extend device lifespan:

- Checkpoint locations are rotated
- Writes are aligned to erase boundaries
- Redundant metadata is minimized
- Large objects stored once and referenced

---

## 5. Recovery Process

### 5.1 Boot-Time Recovery Flow

On device startup:

1. Validate active checkpoint checksum
2. If invalid, load fallback checkpoint
3. Replay transaction journal since checkpoint
4. Recompute balances and trust scores
5. Restore Lamport clock to highest value
6. Mark recovery success

---

### 5.2 Partial Recovery Scenarios

If transaction journal is corrupted:

- Truncate journal at last valid entry
- Preserve earlier ledger state
- Flag device for mesh reconciliation

This ensures safety over completeness.

---

## 6. Mesh Reconciliation After Recovery

Once recovered:

- Device advertises its checkpoint hash
- Mesh peers compare ledger state
- Missing transactions are requested
- Deterministic merge rules are applied
- Ledger converges without central authority

---

## 7. Failure Modes and Handling

### Power Loss During Write
- Temporary checkpoint discarded
- Old checkpoint remains intact

### Flash Corruption
- Fallback checkpoint used
- Device requests ledger sync from peers

### Firmware Crash
- Recovery markers detect incomplete state
- Safe rollback performed

### Clock Regression
- Lamport clock restored from checkpoint
- Prevents replay and ordering attacks

---

## 8. Security Considerations

- All checkpoints encrypted at rest
- Integrity protected via checksum and signature
- Device identity bound to checkpoint
- Tampered checkpoints rejected
- Recovery attempts logged for audit

---

## 9. Performance Considerations

- Checkpointing optimized for low power
- Writes scheduled during high battery availability
- Journal replay optimized using indexing
- Minimal RAM usage during recovery

---

## 10. Audit and Transparency

For governance and disputes:

- Checkpoint metadata includes timestamp and hash
- Devices retain limited historical checkpoints
- Group savings and trust score transitions traceable
- Supports post-incident investigation

---

## 11. Future Enhancements

Planned improvements include:

- Merkle-tree based checkpoints
- Peer-assisted recovery optimization
- Adaptive checkpoint frequency
- Secure cloud escrow (optional, opt-in)

---

## 12. Summary

Checkpointing and recovery allow Seed devices to function reliably in extreme environments without servers, stable power, or internet access. By combining atomic writes, deterministic replay, and mesh-based reconciliation, Seed guarantees that financial data remains safe, consistent, and recoverable under all conditions.

This system is foundational to Seed’s promise of resilient, offline-first financial infrastructure.
