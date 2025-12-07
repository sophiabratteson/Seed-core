# Backup, Sync, and Knowledge Persistence Logic

## Purpose
This document explains how Seed devices preserve data, recover from failures, and synchronize knowledge across a distributed, intermittently connected mesh network. This ensures that no user loses money, transaction history, trust score, or group savings contributions even in harsh environments with unreliable power, limited connectivity, or device loss.

## Core Principles
- Local-first data storage
- Deterministic conflict resolution
- Multi-path redundancy across nearby devices
- Sync independence from internet or centralized servers
- Graceful recovery after partial or total device failure
- Privacy-preserving design with encrypted local data

## Local Storage Strategy
Each device maintains:
- A full local ledger of the user's transactions
- Group savings contributions and rotation history
- Trust score state transitions
- Outgoing message queue for unsynchronized updates
- Known-neighbor table for future sync opportunities

Data is stored in:
- Encrypted flash memory for persistence during power loss
- A checkpoint file for stable recovery
- A write-ahead log for recent actions

## Checkpointing
Devices periodically create a checkpoint to reduce memory usage and support faster recovery.

Checkpoint includes:
- Consolidated ledger snapshot
- Trust score value
- Latest known Lamport timestamp
- A hash of current state to detect corruption

Checkpoints are created:
- On power-down events
- After major ledger updates
- During idle periods with sufficient battery

## Write-Ahead Log
Before any update is applied:
- Entry is written to WAL
- Device ensures write success
- Device applies update to in-memory ledger

WAL enables:
- Recovery after sudden power loss
- Validation of last known state
- Replay of incomplete updates

## Sync Process Overview
When two Seed devices come into range:
1. Devices exchange handshake messages.
2. Each sends its highest Lamport timestamp and list of transaction IDs.
3. Devices determine which records the other is missing.
4. Missing records are exchanged in compact batches.
5. Both devices apply reconciliation rules.
6. Both devices produce identical ledger states.

No internet is needed. Sync happens through:
- LoRa radio messages
- Mesh gossip between any available nodes

## Reconciliation Rules
Seed uses deterministic rules to guarantee consistency:
- Higher Lamport timestamp wins
- If timestamps tie, higher origin device ID wins
- If still tied, lower hash of transaction ID wins
- Invalid or tampered entries are rejected

This ensures:
- Guaranteed convergence across all devices
- Protection from accidental forks
- Predictable behavior even with conflicting updates

## Redundant Knowledge Distribution
To avoid single-device loss:
- Each device stores a partial copy of neighbors' state summaries
- Group savings states are mirrored across all members
- High-value or high-risk transactions are gossiped more widely
- Critical messages may be broadcast multiple times automatically

This increases resilience in:
- Disaster zones
- Power outages
- Device theft or breakage

## Device Loss Recovery
If a user's device is lost:
1. User authenticates with fingerprint on any trusted replacement Seed unit.
2. The replacement syncs with the network.
3. Neighboring devices provide the user's recovered ledger and trust score.
4. Device reconstructs user state from distributed backups.

No cloud server is required.

## Outgoing Message Queue
Pending updates are stored locally until delivered.

Queue contains:
- New transactions
- Trust score updates
- Group savings contributions
- Mesh routing metadata

Queue processing happens:
- Whenever a neighbor is detected
- When the radio schedules a retry window
- When power level is safe for transmission

## Handling Partial Sync
If sync is interrupted:
- Devices keep partial state records
- Resume from last confirmed message
- Duplicate messages are safely ignored
- No data is lost, even if transmission fails

## Knowledge Persistence in Mesh Network
The mesh operates as a community memory system:
- Devices share encrypted fragments of global economic state
- Redundancy allows the economy to survive local failures
- Trust updates propagate gradually but reliably
- Group savings cycles remain intact even through outages

## Fail-Safe Triggers
Devices activate special logic if:
- Ledger corruption is detected
- Replay attacks are suspected
- Neighbor tables disappear unexpectedly
- Battery falls to critical levels

Responses include:
- Switching to read-only mode
- Creating an emergency checkpoint
- Broadcasting warnings to nearby devices

## Summary
This system provides:
- Reliable offline financial operation
- Distributed redundancy without servers
- Predictable consistency rules
- Strong recoverability even in extreme conditions
- A foundation for a resilient economic network for underserved regions
