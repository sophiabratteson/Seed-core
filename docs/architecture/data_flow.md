# Seed Architecture: End-to-End Data Flow

This document describes how data moves through the Seed ecosystem across hardware, firmware, mesh networking, ledger logic, user interaction, and optional cloud sync. It traces the full life cycle of actions such as creating a transaction, recording it locally, sharing it via mesh, resolving conflicts, updating trust scores, and maintaining long-term system coherence in extremely low-connectivity environments.

---

# 1. Overview of the Seed Data Model

Seed handles several core data types:

- Transactions (money transfers, group savings deposits, loan withdrawals)
- Ledger states (local record of all accepted transactions)
- Device identity (public key, fingerprint hash)
- Trust score data (behavior-based rating)
- Group membership metadata
- User profile settings
- System status metrics (battery, storage, sync history)

These pieces of data must flow reliably across devices without internet, while remaining secure, tamper-resistant, and recoverable.

---

# 2. End-to-End Transaction Flow (Single Device)

This section outlines what happens inside *one Seed device* when a user performs an action.

## 2.1 User Input Stage
- User interacts with the e-ink interface.
- UI code sends input events to the application layer.
- Application layer validates the request (e.g., sufficient balance).

## 2.2 Transaction Construction
- Firmware assembles a transaction object containing:
  - Sender ID
  - Receiver ID
  - Amount
  - Local timestamp
  - Lamport clock value
  - Previous known ledger reference
  - Digital signature from secure element
- This object is serialized into Seed's JSON or compact binary format.

## 2.3 Local Storage
- The transaction is appended to:
  - The local ledger file
  - A pending-sync queue
- A checkpoint is saved so recovery is possible even after device loss or battery drain.

---

# 3. Mesh Sync Flow (Device-to-Device Data Movement)

This section covers how data travels between two Seed devices using LoRa mesh.

## 3.1 Neighbor Discovery
- Device broadcasts a low-power beacon.
- Other devices reply with short identity frames.
- A neighbor table is updated.

## 3.2 Transaction Advertisement
- Device announces:
  - Latest ledger hash (rolling checksum)
  - Count of pending transactions
  - Optional trust-score changes

## 3.3 Selective Sync
When Device A meets Device B:

1. They compare ledger hashes.
2. Each device requests only missing transactions.
3. Requested transactions are sent in compact batches.
4. Devices confirm receipt and update local state.

## 3.4 Conflict Resolution
- If two different versions of a transaction exist:
  - Lamport timestamp is compared.
  - If equal, deterministic tie-break rules are applied.
- Final accepted version is stored on both devices.

## 3.5 Trust Score Update Flow
Trust-score updates follow the same sync flow:
- Local calculation → signed update packet → mesh advertisement → sync → merge.

---

# 4. Group Savings Data Flow

Group savings involves multiple devices contributing to the same shared pot.

## 4.1 Contribution Event
- User selects contribution amount.
- Transaction is created with a group identifier.

## 4.2 Rotation / Payout Request
- A designated user requests funds through the UI.
- Device creates a signed payout transaction.
- Group rules are validated locally before allowing the request.

## 4.3 Multi-Party Acknowledgement
- Devices exchange acknowledgment signatures.
- Only once minimum threshold is reached, the payout becomes valid.

## 4.4 Sync Across the Group Mesh
- All group devices share the update when they next come in contact.
- Missing signatures or contradictory states are resolved via quorum logic.

---

# 5. Backup and Recovery Data Flow (Offline-First)

Seed devices may encounter power loss, theft, environmental damage, or extended isolation.

## 5.1 Local Backup
- Device periodically writes:
  - Ledger snapshot
  - Transaction log
  - Device identity
  - Trust score history
- Data is encrypted at rest.

## 5.2 Device Replacement Flow
- New Seed device imports:
  - Identity keys (if backup exists)
  - Last ledger snapshot
- Mesh sync fills gaps by comparing hashes and requesting missing transactions.

## 5.3 Emergency Wipe Path
- Forced fingerprint triggers:
  - Display of fake/decoy data
  - Optional destruction of sensitive keys
  - Redirection to a locked state until reset protocol

---

# 6. Optional Internet Gateway Sync Flow

When any Seed device briefly encounters internet, it can:

## 6.1 Uplink Flow
- Upload a compressed ledger delta to a Seed gateway node.
- Gateway:
  - Validates signatures
  - Stores global state
  - Makes anonymized statistics available

## 6.2 Downlink Flow
- Gateway provides:
  - Missing ledger updates
  - Firmware update metadata
  - Global trust-score rules
  - Educational content for the AI assistant

## 6.3 Privacy Model
- No personal data is uploaded.
- Transactions are encrypted end-to-end.
- Only anonymous aggregates go to the gateway.

---

# 7. Full System Data Life Cycle Summary

1. User performs an action on device.
2. Device builds a signed transaction.
3. Transaction is stored locally.
4. Pending transactions propagate through the mesh.
5. Conflicts are resolved deterministically.
6. Ledger converges across devices.
7. Trust scores update based on actions.
8. Group savings events propagate through multi-party sync.
9. Periodic backup ensures durability.
10. Optional gateway connections improve global coherence.

---

# 8. High-Level Sequence Diagram (Conceptual)

User → Device UI
Device UI → App Layer
App Layer → Ledger Engine
Ledger Engine → Secure Element (sign)
Secure Element → Ledger Engine (signature)
Ledger Engine → Local Storage (append tx)
Local Storage → Mesh Layer (pending queue)
Mesh Layer → Neighbor Discovery
Mesh Layer ↔ Other Devices (tx exchange)
Ledger Engine ↔ Mesh Layer (merge + resolve)
Ledger Engine → Local Storage (commit)
Local Storage → Backup Module (snapshot)
Optional: Mesh Layer → Internet Gateway

---

# 9. Why This Data Flow Matters

This architecture ensures that Seed can function under extreme constraints:

- No internet required
- No phone required
- No electricity grid required
- Works in refugee camps, rural villages, disaster zones, informal settlements, and areas with collapsed institutions
- Ledger remains consistent even when devices are offline for months
- Trust score and group savings mechanisms operate reliably
- Security is maintained with local verification, signatures, and tamper resistance

---

# 10. Future Extensions

- Multi-hop routing optimization
- Incentive mechanisms for relaying messages
- Regional frequency adaptation
- Formal verification of ledger merge logic
- Secure multi-party computation for shared pots
- Optional interoperability with digital cash systems

---
