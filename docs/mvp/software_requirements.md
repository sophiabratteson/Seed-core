# MVP Software Requirements

This document defines the complete software requirements for the Seed Minimum Viable Product (MVP). These requirements reflect the smallest functional system capable of demonstrating Seed’s core value: secure offline-first financial transactions using low-power hardware and a peer-to-peer mesh network. The goal is to build the simplest version of Seed that is still technically credible, testable, and deployable in constrained environments.

---

# 1. Objectives of the MVP Software

- Enable two or more Seed devices to send, receive, and reconcile transactions without internet.
- Maintain a secure local ledger with deterministic conflict resolution.
- Support simple user authentication and device identity.
- Communicate via long-range radio using a lightweight mesh protocol.
- Provide minimal user interface flows for sending, receiving, and viewing balances.
- Store all critical data in persistent memory so devices can operate for long periods offline.

---

# 2. Core Software Components

## 2.1 Ledger Engine (Required)
The ledger engine is responsible for storing, validating, and merging financial transactions.

- Local ledger storage
- Transaction creation and validation
- Duplicate detection
- Ledger checkpointing
- Lamport-clock ordering
- Conflict resolution rules
- Balance calculation per account
- Safe write operations to flash memory

## 2.2 Mesh Communication Stack (Required)
This component handles radio communication between devices.

- Radio driver abstraction for SX1262 or SX1276
- Message serialization and deserialization
- Broadcast and rebroadcast mechanisms
- Basic anti-flooding controls
- Message acknowledgment logic
- Lightweight neighbor awareness (not full routing yet)
- Offline-first sync protocol for exchanging outboxes

## 2.3 User Interface Layer (Required for MVP)
A simple interface that allows minimal user actions.

- Basic e-ink screen rendering
- Navigation between 3 to 5 screens
  - Home / Balance
  - Send funds
  - Receive funds
  - Transaction history
  - Settings (optional)
- Button input handling (up, down, select)
- Error and confirmation messages

## 2.4 Device Identity and Security (Required)
Devices must be uniquely identifiable and able to sign transactions.

- Generate device identity keys on first boot
- Serialize and store device_id in secure memory
- Sign outgoing transactions
- Verify incoming signatures (optional but preferred)
- Secure boot not required for MVP but recommended later

## 2.5 Storage and Persistence (Required)
The system must persist data across reboots or power loss.

- Flash storage or FRAM support
- Ledger persistence
- Config file storage
- Device identity storage
- Safe writes to prevent corruption

## 2.6 Minimal System Utilities (Required)
Small internal helper modules.

- Tiny JSON serializer
- CRC16 or similar checksum for data integrity
- Monotonic clock for lamport increments
- Power-state notifications

---

# 3. Functional Requirements

## 3.1 Device Setup
- Device generates a unique ID on first launch.
- User initializes wallet with a starting balance (test-mode only).
- Device stores identity locally.

## 3.2 Create a Transaction
- User selects "Send".
- Device prompts for recipient ID and amount.
- Device signs and stores the transaction in the outbox.
- Ledger updates local pending state.

## 3.3 Receive and Validate Incoming Transactions
- Device receives a message from the mesh.
- Transaction is parsed and validated.
- Ledger merges incoming history with local history.
- Conflicts resolved deterministically.

## 3.4 Offline Synchronization
- Devices periodically broadcast outboxes.
- Peers import transactions and merge.
- A sync completes when both devices have identical ledger states.

## 3.5 Display Data to User
- Home screen shows current balance.
- Transaction history shows most recent entries.
- Errors and warnings displayed clearly.

---

# 4. Non-Functional Requirements

## 4.1 Performance
- Must handle at least 200 stored transactions.
- Reconciliation must complete within 500 ms on microcontroller hardware.
- Radio message size < 200 bytes per transaction bundle.

## 4.2 Power Efficiency
- Radio transmissions duty-cycled to minimize battery usage.
- Screen updates minimized due to e-ink refresh costs.

## 4.3 Reliability
- System must recover cleanly after a reboot.
- Ledger must never lose committed transactions.
- Duplicate messages must not break the system.

## 4.4 Security
- Simple digital signature scheme required.
- Replay protection using lamport clocks and tx_id uniqueness.
- Device identity keys must never leave secure storage.

---

# 5. Out of Scope for MVP

The following features are important but are excluded to keep the MVP realistic:

- Full routing across multi-hop mesh networks
- Group savings
- Trust score calculations
- Language localization
- AI assistant
- Solar and hand-crank power monitoring
- Advanced encryption hardware
- Large-scale sync optimization
- Phone integration or dashboards

These will be included in future phases once the core MVP is stable.

---

# 6. MVP Acceptance Criteria

- Two devices can exchange transactions fully offline.
- Both devices converge to identical ledger state after sync.
- Users can send and receive money successfully.
- Basic UI works on e-ink screens.
- System survives reboot without losing data.
- All MVP modules pass basic unit tests on microcontroller hardware.

---

# 7. Summary

The MVP software requirements define the smallest end-to-end version of Seed capable of demonstrating its core purpose: providing secure, resilient, offline-capable digital finance to communities without internet access. This MVP provides a stable foundation for scaling into advanced group features, mesh optimization, trust scoring, and full production hardware.
