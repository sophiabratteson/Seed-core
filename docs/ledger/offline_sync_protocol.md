# Offline Sync Protocol

This document describes how Seed devices synchronize financial transactions, trust-score updates, and group-savings records across a fully offline mesh network. Because devices cannot rely on the internet or a central server, the offline sync protocol ensures that all nodes eventually converge on identical ledger states while handling unpredictable connectivity, delays, packet loss, and partial communication paths.

The protocol is intentionally simple, bandwidth-efficient, and fully deterministic.

---

# 1. Goals of the Offline Sync Protocol

- Allow any two devices to synchronize ledgers without internet.
- Support mesh-based multi-hop propagation.
- Ensure deterministic ledger convergence.
- Protect data with signatures and integrity checks.
- Avoid double-spending and replay attacks.
- Enable sync even after long periods of disconnection.
- Minimize energy usage on e-ink, low-power, solar-charged hardware.
- Work reliably in environments with:
  - No infrastructure
  - Intermittent connectivity
  - Limited bandwidth
  - Offline-first priorities

---

# 2. High-Level Sync Architecture

Seed devices maintain two local data structures:

- Outbox (pending outbound transactions)
- Ledger (full history of validated transactions)

Sync occurs through the exchange of compact messages via LoRa mesh. Devices merge incoming data using deterministic conflict resolution logic.

---

# 3. Data Structures Used in Sync

## Transaction Object

{
"tx_id": "UUID",
"sender": "user123",
"receiver": "user789",
"amount": 4.0,
"lamport": 17,
"device_id": "NODE_A",
"prev_tx_ids": ["..."],
"signature": "BASE64",
"type": "payment"
}

## Sync Packet (compact form)

{
"device_id": "NODE_A",
"lamport": 17,
"known_tx_ids": ["id1","id2","id3"],
"requested_tx_ids": ["id9,"id10"],
"payload": [...transactions...]
}

## Ledger Metadata

checkpoint_hash: "SHA256"
last_sync_time:
known_neighbors: ["NODE_B", "NODE_C"]

---

# 4. Device Roles During Sync

Every Seed device acts simultaneously as:

- A broadcaster (announcing new transactions)
- A listener (importing remote transactions)
- A validator (sorting, resolving conflicts, checking signatures)
- A forwarder (repeating messages for multi-hop propagation)

Because there is no central server, all devices perform identical logic.

---

# 5. Sync Cycle Overview

The typical offline sync cycle follows these steps:

1. Device broadcasts a lightweight heartbeat message.
2. Nearby devices compare ledger summaries.
3. Devices exchange missing transaction IDs.
4. Devices request missing items.
5. Devices send back the requested data.
6. Devices merge new transactions into their ledger.
7. Devices compute new checkpoints.
8. Devices rebroadcast updated summaries to propagate changes.

This cycle repeats automatically whenever devices detect neighbors.

---

# 6. Stage-by-Stage Protocol Details

## Stage A: Discovery and Heartbeats

Each device periodically sends:

{
"msg_type": "heartbeat",
"device_id": "NODE_A",
"lamport": 17,
"tx_count": 492,
"checkpoint_hash": "XYZ123"
}

Neighbors compare:

- tx_count
- checkpoint_hash
- lamport values

If differences are detected, sync is activated.

---

## Stage B: Exchange of Known Transaction IDs

To avoid sending the entire ledger, devices exchange compact sets:

{
"msg_type": "summary",
"device_id": "NODE_A",
"known_tx_ids": ["id1", "id2", "id3"]
}

Neighbor compares with its own known IDs.

Missing IDs become "requested_tx_ids".

---

## Stage C: Request-Missing-Transactions Phase

Device sends:

{
"msg_type": "request",
"requested_tx_ids": ["id8", "id12"]
}

Other device responds with: 

{ 
"msg_type": "payload",
"transactions": [...]
}

This keeps bandwidth usage very low compared to broadcasting entire ledgers.

---

## Stage D: Deterministic Ledger Merge

Incoming transactions are merged using:

1. Lamport ordering
2. Device ID tie-breaking
3. Signature verification
4. Causal ancestry checking
5. Balance validation
6. Idempotency checks

This guarantees all devices eventually converge to the same ledger state.

---

## Stage E: Reconciliation and Checkpointing

After applying all transactions:

- Ledger is revalidated.
- A new `checkpoint_hash` is computed.
- Outbox is cleared for transactions already acknowledged.
- Device prepares next sync iteration.

---

# 7. Sync Timing and Power Optimization

Seed devices operate with extremely limited energy, so sync frequency is adaptive:

- High battery: frequent syncs.
- Low battery: rare syncs.
- Solar charging: syncs increase when panel is producing energy.
- Hand-crank charging: one-time burst sync.

Sync is triggered by:

- Neighbor detection
- New transaction creation
- Scheduled intervals
- Manual user prompt (optional)

---

# 8. Multi-Hop Mesh Behavior

Devices forward certain packet types to extend network reach.

For routing, the protocol uses:

- Gossip spreading for robustness
- Deduplication of repeated messages
- Hop counters to prevent infinite loops
- Opportunistic forwarding based on signal strength

Effectively, a transaction generated in one village can eventually reach others even days later.

---

# 9. Handling Long Offline Periods

When a device is offline for weeks or months:

- It continues generating transactions locally.
- Lamport clocks keep increasing.
- Prev_tx_ids preserve causal order.
- Outbox may accumulate many entries.
- First sync upon reconnection triggers a deep merge.

This is the core of offline-first design.

---

# 10. Failure Modes and Recovery Rules

## Case 1: Device dies during sync
- Outbox remains intact.
- Next boot completes sync.

## Case 2: Conflicting transactions detected
- Merge logic resolves via lamport and device ID.

## Case 3: Missing transaction ancestors
- Device stores child tx as pending.
- Requests missing ancestors during next sync.

## Case 4: Malicious or corrupted packet
- Signature check fails.
- Packet is ignored and logged.

## Case 5: Partial sync due to packet loss
- Only missing items are requested next round.

---

# 11. Example End-to-End Sync Walkthrough

Device A ledger:
- A1 lamport 1
- A2 lamport 2

Device B ledger:
- B1 lamport 1
- B2 lamport 3

Sync steps:

1. A sends summary
2. B detects missing A1, A2
3. B requests missing IDs
4. A sends A1, A2
5. B merges and sorts all:
   - A1
   - B1
   - A2
   - B2
6. B updates checkpoint
7. B sends updated summary
8. A pulls any missing B transactions

Both converge to the same ledger sequence.

---

# 12. Security Protections

- Signatures prevent tampering.
- Checkpoint hashes detect inconsistencies.
- Replay prevention via tx_id uniqueness and lamport counters.
- No device can "fake" ordering due to deterministic global sort rules.
- All sync channels encrypted at the mesh layer.

---

# 13. Storage and Bandwidth Management

To reduce memory usage:

- Devices prune expired or invalid transactions.
- Devices compress historical segments.
- Devices apply thinning of old group-savings updates.
- Only missing pieces are transferred, not entire ledgers.

---

# 14. Future Extensions

- Merkle tree summaries for extremely large ledgers.
- Bloom filters instead of full ID lists.
- Zero-knowledge proof sync for privacy-sensitive environments.
- Opportunistic WiFi sync when available.
- Cross-border interoperability.

---

# 15. Summary

The offline sync protocol allows Seed devices to function independently of any central infrastructure while still maintaining global ledger consistency. By combining compact summaries, deterministic merge logic, Lamport clocks, causal references, and mesh-based propagation, Seed devices can operate confidently in environments with zero internet, low energy, and unpredictable communication.

This system ensures that financial empowerment and economic participation remain possible anywhere in the world, regardless of connectivity barriers.
