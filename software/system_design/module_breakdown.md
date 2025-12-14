# Module Breakdown

This document defines the full software module architecture of Seed. It explains each major software component, its responsibilities, inputs and outputs, and how modules interact to form a secure, offline-first financial system.

---

## 1. Design Principles

The Seed software architecture follows these principles:

- Offline-first operation
- Deterministic behavior across devices
- Minimal memory and power usage
- Clear separation of concerns
- Hardware abstraction
- Security-by-design

Each module has a single, well-defined responsibility and communicates through explicit interfaces.

---

## 2. High-Level Module Map

The Seed software stack is divided into the following major layers:

- Core runtime
- Ledger engine
- Mesh networking stack
- Device applications
- Security services
- Hardware abstraction layer
- System utilities

Each layer can be independently tested and evolved.

---

## 3. Core Runtime Modules

### main_loop

Responsibilities:
- System initialization
- Scheduling periodic tasks
- Power-aware execution
- Event dispatch

Inputs:
- Hardware interrupts
- Timers
- User input events

Outputs:
- Task execution signals
- Sleep/wake transitions

---

### power_manager

Responsibilities:
- Battery level monitoring
- Power mode transitions
- Solar and hand-crank charging awareness
- Load shedding under low power

Inputs:
- Battery sensor readings
- Charging status
- System usage metrics

Outputs:
- Power state decisions
- Throttling signals to other modules

---

## 4. Ledger Engine Modules

### ledger_manager

Responsibilities:
- Maintains authoritative local ledger state
- Applies validated transactions
- Coordinates ledger rebuilds during sync

Inputs:
- Validated transactions
- Sync merge results

Outputs:
- Updated ledger state
- Balance snapshots

---

### ledger_validation

Responsibilities:
- Verifies transaction correctness
- Enforces balance constraints
- Checks causal dependencies

Inputs:
- Incoming transaction objects
- Current ledger state

Outputs:
- Valid / invalid decision
- Rejection reasons

---

### conflict_resolution

Responsibilities:
- Resolves transaction conflicts deterministically
- Orders transactions using lamport clocks and device IDs
- Ensures convergence across devices

Inputs:
- Sets of transactions from multiple devices

Outputs:
- Canonical transaction order
- Conflict resolution outcomes

---

### ledger_storage

Responsibilities:
- Persists ledger data to flash storage
- Handles checkpoints and recovery
- Protects against corruption

Inputs:
- Ledger state updates

Outputs:
- Serialized ledger snapshots

---

## 5. Mesh Networking Modules

### mesh_protocol

Responsibilities:
- Defines message formats and message handling rules
- Coordinates send/receive lifecycle

Inputs:
- Outgoing messages from ledger or apps
- Incoming packets from radio layer

Outputs:
- Routed messages
- Protocol-level acknowledgments

---

### mesh_tx_queue

Responsibilities:
- Queues outbound messages
- Handles retransmissions
- Prioritizes critical messages

Inputs:
- Message send requests
- Power constraints

Outputs:
- Packets sent to radio interface

---

### mesh_rx_handler

Responsibilities:
- Parses incoming packets
- Verifies integrity and authenticity
- Dispatches messages to appropriate modules

Inputs:
- Raw radio packets

Outputs:
- Validated protocol messages

---

### mesh_neighbor_table

Responsibilities:
- Tracks nearby devices
- Maintains last-seen timestamps
- Estimates network topology

Inputs:
- Heartbeat messages
- Routing updates

Outputs:
- Neighbor metadata
- Routing hints

---

## 6. Device Application Modules

### wallet_app

Responsibilities:
- User balance display
- Payment initiation
- Transaction history viewing

Inputs:
- User actions
- Ledger snapshots

Outputs:
- Transaction creation requests

---

### group_savings_app

Responsibilities:
- Group contribution tracking
- Rotation scheduling
- Accountability enforcement

Inputs:
- Group transactions
- Trust score data

Outputs:
- Group update messages

---

### trust_score_app

Responsibilities:
- Displays trust score
- Explains score changes to users
- Flags risky behavior

Inputs:
- Trust score updates
- Behavioral metrics

Outputs:
- User feedback prompts

---

### training_assistant_app

Responsibilities:
- Financial education prompts
- Scam warnings
- Contextual advice

Inputs:
- User behavior patterns
- Ledger events

Outputs:
- Spoken or displayed guidance

---

## 7. Security Modules

### security_module

Responsibilities:
- Key management
- Signature verification
- Secure boot enforcement

Inputs:
- Transactions
- System state

Outputs:
- Authentication decisions
- Security alerts

---

### secure_storage

Responsibilities:
- Encrypts sensitive data at rest
- Protects keys and identities

Inputs:
- Data write requests

Outputs:
- Encrypted storage blobs

---

## 8. Hardware Abstraction Modules

### radio_interface

Responsibilities:
- Abstracts LoRa hardware
- Sends and receives packets
- Manages radio sleep states

Inputs:
- Packets from mesh stack

Outputs:
- Radio transmissions
- Received packets

---

### display_driver

Responsibilities:
- E-ink screen updates
- Low-power rendering
- Partial refresh handling

Inputs:
- UI render commands

Outputs:
- Display state changes

---

### input_buttons

Responsibilities:
- Reads physical button input
- Debounces signals
- Triggers UI events

Inputs:
- Button presses

Outputs:
- User action events

---

## 9. Utility Modules

### timekeeping

Responsibilities:
- Maintains logical clocks
- Tracks uptime
- Supports lamport clock updates

---

### crc16

Responsibilities:
- Packet integrity checks
- Data corruption detection

---

### safe_memory

Responsibilities:
- Bounds-checked memory access
- Secure erase operations

---

## 10. Module Interaction Summary

- Device apps create transactions
- Ledger engine validates and applies transactions
- Mesh stack syncs data between devices
- Security layer authenticates all operations
- Power manager governs execution frequency
- Hardware abstraction isolates physical dependencies

This modular architecture allows Seed to scale, remain secure, and operate reliably in the absence of internet, centralized servers, or continuous power.
