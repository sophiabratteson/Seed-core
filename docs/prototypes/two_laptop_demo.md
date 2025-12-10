# Two-Laptop Prototype Demo

This document describes the first functional demonstration of Seed’s offline-first financial system using two laptops as stand-in “Seed devices.” The goal of this prototype is to validate the core principles of the Seed network: device identity, local ledger storage, offline transaction creation, and offline synchronization via physical transfer (“sneakernet”).

This prototype contains **no networking, no WiFi, and no internet usage**. All communication occurs through manually exchanged files, proving that Seed’s ledger logic can operate completely offline.

---

# 1. Objectives of the Two-Laptop Demo

The prototype is designed to demonstrate the following:

1. Two independent devices can each:
   - Maintain their own ledger
   - Create transactions locally
   - Store their own device identity
2. Devices can exchange transaction files without WiFi, using:
   - AirDrop
   - USB flash drive
   - Email (optional)
   - Any offline file transfer method
3. After exchanging files, both devices:
   - Merge incoming transactions
   - Apply deterministic conflict-resolution rules
   - Produce identical ledger states
4. The system remains operational in environments with:
   - No internet
   - No power grid
   - No cell service
   - Limited technical infrastructure

This demo is the **minimum viable proof** of Seed’s offline-first financial foundation.

---

# 2. Architecture Overview

Each laptop represents a Seed device.

## Device Components in This Demo
- A unique device identity (ex: `DEVICE_A`, `DEVICE_B`)
- A local ledger stored in memory
- A transaction creation module
- A deterministic merge algorithm for conflict resolution
- An outbox file exporter (JSON)
- An inbox file importer (JSON)

## Communication Method
Instead of LoRa radios, the demo uses a **manually transferred JSON file** to simulate real-world offline sync events.

This validates the merging logic without requiring hardware.

---

# 3. File Structure for the Demo

Each laptop contains three files:

```
node.py             # Ledger + identity + merge logic
laptop_A.py         # Actions for Device A
laptop_B.py         # Actions for Device B
```

This mirrors the future firmware structure where each Seed device has:
- Device identity module
- Ledger engine
- Sync handler
- IO abstraction layer

---

# 4. Workflow of the Demo

The synchronization workflow mirrors real hardware behavior.

## Step 1 — Laptop A Runs First
Laptop A performs:
1. Load ledger (if any)
2. Create new transactions
3. Import B’s transactions (if outbox_B.json exists)
4. Export `outbox_A.json`

After this step:
- `outbox_A.json` appears in Laptop A’s folder.

You then manually copy this file to Laptop B.

---

## Step 2 — Laptop B Runs
Laptop B:
1. Loads A’s file (`outbox_A.json`)
2. Merges A’s transactions with its own
3. Creates its own new transactions
4. Exports `outbox_B.json`

After this step:
- `outbox_B.json` is generated

You then manually copy it back to Laptop A.

---

## Step 3 — Repeat the Cycle
Every cycle models:
- A sync event
- A mesh encounter
- A peer-to-peer ledger merge

This loop can continue indefinitely.

---

# 5. Conflict Resolution Logic Used in the Demo

The prototype implements a simplified version of Seed’s production system:

## Rules
1. If transaction IDs are unique → both are accepted.
2. If two transactions share the same ID:
   - The one with the higher lamport clock wins.
   - If tied, the device ID alphabetical order acts as the tie-breaker.
3. Duplicate transactions are ignored.
4. Ledger rebuilding is deterministic on all devices.

This guarantees that:
- The ledger cannot fork
- All nodes eventually converge
- Parallel histories merge cleanly

This is the foundation of Seed’s global consistency model.

---

# 6. Example Run

## Laptop A creates:
- Alice → Bob : 5
- Carol → Dave : 3

Produces `outbox_A.json`.

## Laptop B imports A’s transactions, then creates its own:
- Eve → Frank : 7

Produces `outbox_B.json`.

## Laptop A imports B’s transactions:
A’s and B’s ledgers match exactly after merge.

This mirrors the expected behavior of two hardware Seed devices exchanging data offline.

---

# 7. Why This Demo Matters

This small prototype validates several critical components of Seed’s vision:

## Offline-first feasibility
Demonstrates that a financial system **does not require internet or servers** to function.

## Deterministic global convergence
All devices independently compute the same final ledger state, even when offline.

## Secure value transfer in low-resource environments
Users can:
- Send value
- Receive value
- Sync with others
- Operate fully offline

## Modular path to hardware implementation
The same logic maps directly onto:
- ESP32 + LoRa hardware
- Secure element chips
- Storage modules
- Mesh radios

This demo establishes the foundation for the upcoming hardware prototype.

---

# 8. Future Extensions of This Prototype

The next steps after the two-laptop version include:

## Phase 1 — Add persistent storage
- Each laptop stores ledger state in a local JSON file
- Ledger survives restarts

## Phase 2 — Add validation logic
- Signature checking
- Balance verification
- Sender authorization

## Phase 3 — Add multi-device syncing
- Three or more laptops
- Multi-directional merges

## Phase 4 — Replace file transfer with LoRa radios
Once hardware arrives, replace manual file exchange with actual packet sync.

## Phase 5 — Full Seed device emulation
- Trust scores
- Group savings
- Training assistant prompts
- Secure messaging
- Emergency wipe protocols

---

# 9. Summary

This two-laptop demo is the **first working version of Seed**.

It proves:
- Offline transactions are possible
- Sync does not depend on internet
- Ledger merging works deterministically
- A minimum version of Seed can exist anywhere in the world today

This prototype is a critical step toward:
- Hardware device firmware
- Field pilots
- Investor demonstrations
- A fully functional global offline-friendly financial network
