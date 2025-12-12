# Offline-First Sync Design

This document defines how the Seed mesh protocol is designed to operate in environments with **no internet**, **intermittent power**, **unreliable connectivity**, and **no central authority**. Offline-first behavior is a core, non-negotiable design principle of Seed.

---

## 1. Design Philosophy

Seed assumes the following conditions by default:

- Devices may be offline for hours, days, or weeks.
- There is no guaranteed global clock.
- There is no always-on central server.
- Connectivity occurs opportunistically and unpredictably.
- Power and bandwidth are scarce resources.

All protocol decisions prioritize **local usability first**, with synchronization occurring opportunistically when possible.

---

## 2. Core Offline-First Principles

The Seed mesh protocol follows these principles:

- **Local-first execution**
  - All actions (payments, savings, trust updates) execute locally.
  - No operation blocks waiting for network confirmation.

- **Eventual consistency**
  - Devices may temporarily diverge.
  - All honest devices converge when connectivity resumes.

- **Opportunistic synchronization**
  - Sync occurs when devices come into radio range.
  - No scheduled sync windows are required.

- **Deterministic convergence**
  - Given the same transaction set, all devices compute the same ledger state.

---

## 3. Local Operation While Offline

While offline, a Seed device can:

- Create and sign transactions.
- Update balances locally.
- Participate in group savings rotations.
- Update trust scores.
- Store all actions in a local outbox.

Offline operation **never disables core functionality**.

---

## 4. Data Model for Offline Sync

Each device maintains:

- **Local Ledger**
  - All known transactions (valid, pending, invalid).
- **Outbox**
  - Transactions created locally but not yet shared.
- **Inbox**
  - Transactions received from other devices.
- **Checkpoint**
  - A snapshot of the last fully validated ledger state.

This separation allows safe operation even during partial syncs.

---

## 5. Opportunistic Sync Triggers

Synchronization is triggered when:

- Another Seed device is detected via radio.
- A relay device (kiosk, gateway, phone) is encountered.
- A user manually initiates sync.
- A device regains power after shutdown.

No global coordination is required.

---

## 6. Sync Handshake Overview

When two devices meet:

1. Devices exchange metadata:
   - Device ID
   - Ledger version hash
   - Highest Lamport timestamp
2. Devices determine if sync is needed.
3. Devices exchange missing transactions only.
4. Each device independently reconciles its ledger.
5. Devices acknowledge completion.

The handshake is designed to be **short, resumable, and interrupt-safe**.

---

## 7. Partial Sync and Resume Behavior

Sync sessions may end unexpectedly due to:

- Power loss
- User movement
- Radio interference

Seed handles this by:

- Chunking transaction transfers.
- Tracking received transaction IDs.
- Allowing future syncs to resume from last known state.
- Never assuming a sync session completes.

---

## 8. Conflict Handling During Offline Periods

Conflicts are expected and handled deterministically:

- Transactions are never rejected solely due to being offline.
- Conflicts are resolved at merge time using:
  - Lamport clocks
  - Device ID tie-breakers
  - Validation rules
- Invalid transactions are preserved for audit but excluded from balances.

Offline creation never causes permanent failure.

---

## 9. Multi-Hop Offline Propagation

Transactions propagate through the mesh:

- Device A syncs with B.
- Device B later syncs with C.
- Device C receives A’s transactions indirectly.

No device needs direct contact with all others.

This allows information to spread gradually across communities.

---

## 10. Interaction with Gateways and Kiosks

Optional gateways may exist:

- Gateways follow the same protocol rules.
- They do not have special authority.
- They cannot override ledger rules.
- They only accelerate propagation.

Seed remains fully functional without them.

---

## 11. Security Implications of Offline-First Design

Offline-first design improves security by:

- Reducing attack surface (no permanent endpoints).
- Preventing real-time surveillance.
- Limiting large-scale coordinated attacks.
- Allowing users to operate privately without connectivity.

All security validation occurs locally.

---

## 12. Failure Scenarios and Recovery

Handled failure cases include:

- Device offline for months.
- Ledger state far behind network.
- Partial transaction history.
- Interrupted sync loops.

Recovery occurs automatically through repeated opportunistic syncs.

---

## 13. Design Constraints

Offline-first design imposes constraints:

- No reliance on real-time clocks.
- No central ordering authority.
- Limited message sizes.
- Strong emphasis on deterministic rules.

All protocol components respect these constraints.

---

## 14. Summary

The offline-first sync design ensures that Seed:

- Works where banks and internet do not.
- Respects real-world connectivity constraints.
- Allows users to transact with confidence.
- Converges safely without coordination.
- Remains resilient under extreme conditions.

Offline is not an edge case — it is the default operating mode of Seed.
