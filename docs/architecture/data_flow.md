# Seed Architecture: End-to-End Data Flow

## Overview
This document describes how data moves through the Seed ecosystem, from user actions on the device to ledger updates, mesh network propagation, conflict resolution, and secure long-term storage. It is designed to show how every subsystem interacts, including hardware, firmware, networking, ledger logic, synchronization, and external interfaces such as optional cloud gateways.

## High-Level Pipeline
- User input
- Application layer processing
- Ledger engine validation and state update
- Transaction serialization
- Mesh network broadcast (LoRa + mesh protocol)
- Neighbor reception and local merge
- Conflict resolution
- Secure storage and checkpointing
- Optional cloud sync (when internet is available)
- Local AI assistant updates (trust score, savings coach, recommendations)

## Step 1: User Creates an Action
### Examples
- Send money
- Request money
- Contribute to group savings
- Withdraw weekly group savings pot
- Check balance
- Display transaction history
- Ask AI assistant a question

### Data produced at this step
- sender_id
- recipient_id (optional for read-only operations)
- amount
- transaction_type
- user authentication (fingerprint)
- timestamp (device-local)
- any relevant metadata

## Step 2: Application Layer Interprets the Action
- Verifies fingerprint authentication
- Checks local device configuration
- Loads user profile and trust score
- Collects required transaction fields
- Prepares a request object for the ledger engine

### Data transformations
- Convert user intent into a structured transaction request
- Validate basic fields (amount > 0, known recipient, etc.)

## Step 3: Ledger Engine Builds the Transaction
- Assigns a unique transaction ID
- Increments Lamport clock
- Captures dependencies (previous transaction IDs)
- Runs validation rules
- Signs transaction using secure element

### Output structure
- tx_id
- from_id
- to_id
- amount
- lamport_clock
- dependencies
- signature
- device_id

## Step 4: Serialize and Prepare for Transport
- Converts structured transaction into JSON or compact binary format
- Attaches small header block with message type indicators
- Compresses if needed

### Message fields
- message_type (transaction, sync_request, sync_response, heartbeat, error)
- payload (transaction JSON)
- checksum (CRC16 or similar)

## Step 5: Mesh Protocol Sends Transaction Over Radio
- Chooses frequency band based on region (e.g., 915 MHz US)
- Uses LoRa modulation for long-range low-power messaging
- Selects routing strategy (gossip flood, neighborhood table, power-aware routing)
- Transmits packet with retry logic

### Radio-layer behavior
- Radio interface encodes and transmits packet
- Performs backoff to reduce collisions
- Logs packet for debugging

## Step 6: Neighbor Devices Receive Message
### Upon reception:
- Validate checksum
- Validate signature
- Validate not seen before (deduplication)
- Add to local ledger merge queue
- Update neighbor table (for routing optimization)
- Pass payload into ledger engine

### If invalid:
- Drop packet
- Optionally send error message

## Step 7: Ledger Merge and Conflict Resolution
- Compares received transaction’s Lamport timestamp with local version
- If newer: overwrite
- If same timestamp: break ties using deterministic rule based on device_id
- If conflicts detected (e.g., double spend): queue for dispute resolution
- Update local state: balances, trust score inputs, group savings state

### Merge logic ensures:
- Consistency across devices
- Deterministic ordering
- No central authority required
- Offline-first behavior

## Step 8: Local Storage and Checkpointing
- Append new transaction to encrypted storage
- Update state database on flash memory
- Trigger periodic checkpoint:
  - Summaries of balances
  - Group savings pot state
  - Trust score snapshot
  - Last merged lamport timestamp

### Backup goals
- Allow recovery after device loss or tampering
- Reduce storage size over long periods
- Improve sync speed between devices

## Step 9: Optional Internet Sync (when available)
If the device is near WiFi:
- Upload ledger diffs through mesh gateway
- Receive global ledger state
- Merge again using same deterministic rules
- Distribute global updates back through mesh when offline

This creates:
- A global economic view
- Cross-region stability
- Support for diaspora remittances

## Step 10: AI Assistant Updates Insights
- Reads new financial behavior
- Updates personalization model
- Recalculates trust-score components
- Generates educational prompts, warnings, or suggestions

Examples:
- "Your savings streak is 4 weeks long."
- "This sender has a low trust score. Confirm transaction?"
- "Your group savings pot will reach 200 units next cycle."

## Step 11: Device UI Refresh
- E-ink display updates with extremely low power usage
- Shows new balance, confirmation, or errors
- Logs action to activity view
- Stays static without draining battery

## Complete End-to-End Example Scenario
### User action
Alice sends 5 units to Bob.

### Data flow
- Fingerprint verifies user
- Application builds request object
- Ledger engine validates and constructs transaction
- Transaction serialized into JSON message
- Mesh protocol wraps message and transmits via LoRa
- Nearby devices receive and validate
- Ledger merge resolves any conflicts
- State updates and is stored securely
- If online, global sync occurs
- AI updates Alice’s trust score and spending pattern analysis
- E-ink screen displays confirmation

## Summary of Data Flow Principles
- Offline-first by design
- Deterministic consensus without a blockchain
- Local-first economic computation
- Minimal-power data movement
- Self-healing network through mesh propagation
- Privacy-preserving identity and encryption
- Scalable across millions of devices
