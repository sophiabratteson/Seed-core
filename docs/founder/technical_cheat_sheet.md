# Technical Cheat Sheet
A fast, founder-friendly reference explaining how Seed works, what each subsystem does, and the minimum vocabulary needed for investor, professor, and engineer conversations.

---

# 1. What Seed Is
Seed is an offline-first financial device that works without internet, without electricity, and without a traditional bank. It uses:
- LoRa mesh radios for communication
- A local encrypted ledger for storing transactions
- Deterministic conflict resolution for syncing histories
- A small CPU, e-ink screen, and fingerprint sensor for authentication
- Solar and hand-crank power for energy resilience

Seed behaves like a bank account, payment terminal, and microfinance tool that works entirely beyond traditional infrastructure.

---

# 2. Core Technical Pillars

## 2.1 Offline-First Ledger
- Every device stores its own encrypted transaction ledger.
- Transactions sync when two devices come near each other using LoRa radio.
- Ledger merges follow deterministic rules so all devices eventually agree.

## 2.2 Mesh Networking
- Devices do not require towers or WiFi.
- Each device relays messages for others, forming a peer-to-peer mesh.
- Only small packets of data are transmitted (transaction updates, trust scores, group savings updates).

## 2.3 Conflict Resolution
- Seed uses Lamport clocks: a simple increasing counter that tracks ordering of events.
- If two transactions conflict, deterministic tie-breaking rules (clock → device ID) select a winner.
- This ensures global consistency without central authority.

## 2.4 Security
- Each Seed device has a secure chip that stores private keys.
- Transactions are signed to prevent tampering.
- Ledger is encrypted and unreadable if a device is stolen.
- A fingerprint pad controls access.
- An emergency wipe mode protects the user during theft or political danger.

## 2.5 Power System
- Battery: LiFePO4 (safe, long-lasting, heat tolerant)
- Charging inputs: solar panel + hand-crank generator
- Display: e-ink (ultra low power)
- Duty cycle: radio wakes only when transmitting, preserving battery for weeks.

---

# 3. Hardware Components (High-Level)
- Microcontroller (ESP32 or similar)
- LoRa radio module (SX1262 or SX1276 family)
- Secure hardware module (ATECC608 or equivalent)
- E-ink display
- Capacitive fingerprint reader
- Solar charging circuit + battery management system
- Protective enclosure built for harsh and rural environments

---

# 4. Software Architecture Summary

## 4.1 Ledger Engine
- Stores, validates, and merges transactions
- Prevents double spending
- Maintains trust scores and group savings states

## 4.2 Mesh Network Stack
- Radio abstraction layer (LoRa)
- Packet formatting and validation
- Retry logic and acknowledgements
- Offline-first sync mechanism

## 4.3 Apps on Device
- Wallet app
- Group savings app
- Trust score dashboard
- Financial assistant (offline AI)
- Settings and security tools

## 4.4 Storage
- Transactions stored in flash memory
- Periodic checkpoints reduce computation load during sync

---

# 5. Key Data Structures (Founder-Level Explanation)

## Transaction
Represents a transfer of funds.

Fields:
- tx_id: unique ID
- sender
- receiver
- amount
- lamport clock
- device ID (origin)
- signature
- optional causal references (for multi-step dependencies)

## Ledger
- A map (database) of all transactions
- Sorted using deterministic rules
- Can rebuild state from scratch when needed

## Trust Score
A numerical representation of user reliability based on:
- Repayment behavior
- Group contributions
- Transaction consistency
- Network participation (helping relay messages)

---

# 6. Syncing Workflow Explained Simply
1. Two devices come within range.
2. They exchange only the transactions the other device is missing.
3. Each device merges incoming transactions locally.
4. Conflicts are resolved deterministically.
5. Both devices now have matching ledger states.
6. This repeats throughout the community until everyone converges.

This happens without:
- Internet
- Cell towers
- Banks
- External servers

---

# 7. Threat Model (Founder Summary)
Seed is designed for low-trust, high-risk contexts.

Protects against:
- Device theft
- Physical tampering
- Replay attacks
- Radio interception
- Malicious users submitting fraudulent transactions
- Ledger corruption
- Government shutdown of communications infrastructure

Seed does not require:
- Identity documents
- Phone numbers
- SIM cards
- National infrastructure

---

# 8. Founder Talking Points for Investors and Experts
- Seed is a self-contained decentralized financial device.
- Works offline and powers itself.
- Designed for 1 billion unbanked people lacking internet or stable governments.
- Uses deterministic, mathematically provable consistency algorithms (Lamport clocks).
- Builds trust scores and supports group savings, which are culturally validated mechanisms for microfinance.
- The tech stack is intentionally simple: low-power radio, e-ink, and local cryptography.
- No dependency on volatile crypto markets; this is not a blockchain, but a practical ledger.

---

# 9. Founder Vocabulary Cheat Sheet

Mesh Network  
Devices talk to each other directly using radio waves.

Lamport Clock  
A simple numerical counter to order events without internet.

Deterministic  
Every device arrives at the same answer, even offline.

Sync / Reconciliation  
The process of merging transaction histories.

Secure Element  
A small hardware chip that stores private keys safely.

Ledger  
Record of all transactions.

Duty Cycle  
How often the radio is awake vs asleep.

Checkpoint  
A saved summary of the ledger to speed up future syncing.

Group Savings  
A pooled community fund based on rotating contributions.

---

# 10. What You Should Be Able to Explain in One Sentence Each
- How Seed syncs: It exchanges transaction packets over LoRa and merges them deterministically.
- Why offline-first matters: Most unbanked regions have unreliable or no internet.
- How security works: Every transaction is signed using hardware-protected keys.
- Why e-ink: Uses almost zero power.
- Why mesh networking: It scales without towers, SIM cards, or infrastructure.
- Why trust scores: They enable microfinance and lending in communities without banks.

---

# 11. Investor-Level Summary
Seed is a resilient, infrastructure-free financial platform built for the bottom billion. It uses local mesh radios, an offline ledger, deterministic conflict resolution, and ultra-low-power hardware to give financially excluded populations the ability to store value, make payments, participate in group savings, and build trust — all without internet, smartphones, or banks.
