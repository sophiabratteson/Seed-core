# Replay Attack Protection

This document defines how the Seed mesh protocol prevents replay attacks in a fully offline, decentralized environment. Replay attacks occur when a malicious or compromised device captures valid network messages and resends them later to trick other devices into duplicating actions such as transferring funds, modifying trust scores, or altering group savings states.

Because Seed operates without continuous internet connectivity or centralized servers, replay protection must be enforced locally and deterministically by every device.

---

## 1. Goals of Replay Attack Protection

- Prevent duplicated execution of previously valid messages
- Ensure idempotent processing of all network messages
- Maintain ledger integrity across long offline periods
- Detect and reject stale, reordered, or malicious retransmissions
- Enable safe synchronization in hostile or adversarial environments

---

## 2. Threat Model

Replay attacks may occur when:

- A device is stolen or temporarily compromised
- Radio traffic is intercepted and rebroadcast
- A malicious node replays old transactions to inflate balances
- Trust score or group savings updates are resent intentionally
- Devices rejoin the network after long offline periods

Seed assumes attackers may:
- Capture valid signed messages
- Delay messages arbitrarily
- Reinject messages multiple times
- Attempt selective replay against specific targets

Seed does not assume attackers can:
- Break cryptographic signatures
- Forge device identities without key compromise
- Modify message contents without detection

---

## 3. Core Replay Protection Mechanisms

Replay protection in Seed is enforced through a layered approach:

1. Unique message identifiers
2. Lamport logical clocks
3. Per-device monotonic counters
4. Message history caching
5. Deterministic rejection rules

Each layer independently blocks replay attempts, ensuring redundancy and resilience.

---

## 4. Unique Message Identifiers

Every mesh message includes a globally unique message ID.

### Message ID Properties:
- Generated using cryptographically strong randomness
- Unique per message across the entire network
- Never reused, even across reboots

### Enforcement:
- Devices maintain a local cache of seen message IDs
- Any message with a previously seen ID is immediately rejected
- Message ID cache persists across reboots

This ensures strict idempotence: no message can be applied more than once.

---

## 5. Lamport Logical Clock Validation

Each message includes the sender’s Lamport clock value.

### Rules:
- Each device maintains a local Lamport clock
- Outgoing messages increment the sender’s clock
- Incoming messages must have a Lamport value >= last known value for that sender

### Rejection Conditions:
- Message Lamport value is lower than previously recorded value
- Message violates expected monotonic progression

Lamport clocks prevent replays that attempt to rewind device history.

---

## 6. Per-Device Sequence Numbers

In addition to Lamport clocks, Seed enforces per-device sequence numbers.

### Properties:
- Strictly increasing counter per device
- Reset only on full device reinitialization with key regeneration
- Included in all signed messages

### Enforcement:
- Devices track the highest sequence number per peer
- Messages with sequence numbers <= previously accepted values are rejected

This protects against delayed replays even if Lamport clocks appear valid.

---

## 7. Message Type–Specific Replay Rules

Different message types apply additional replay protections:

### Transaction Messages:
- tx_id must be globally unique
- Duplicate tx_id results in rejection
- Conflicting tx_id with different content is flagged as malicious

### Ledger Sync Messages:
- Checkpoint hash must differ from last accepted checkpoint
- Replayed checkpoints are ignored

### Trust Score Updates:
- Must include monotonic update index
- Duplicate index values are rejected

### Group Savings Messages:
- Must include group_id and contribution index
- Duplicate contributions are rejected
- Conflicting updates are archived but not applied

---

## 8. Signed Message Binding

All replay-relevant fields are included inside the signed payload:

- message_id
- lamport_clock
- sequence_number
- message_type
- payload_hash

This prevents attackers from modifying metadata to bypass replay detection.

Unsigned metadata is never trusted.

---

## 9. Message History Cache Management

Each device maintains a bounded cache of recently seen message IDs.

### Cache Properties:
- Stored in encrypted persistent storage
- Size-limited to prevent memory exhaustion
- Uses rolling eviction based on age and relevance

### Eviction Rules:
- Old messages beyond ledger finality checkpoints may be evicted
- Critical transaction IDs remain indefinitely

Replay protection remains effective even with limited memory.

---

## 10. Handling Replayed Messages

When a replayed message is detected:

1. Message is rejected
2. Event is logged locally
3. Optional reputation penalty applied to sender
4. No error response is sent (to avoid amplification)

Repeated replay attempts may trigger trust degradation or isolation.

---

## 11. Interaction with Offline Sync

Replay protection remains effective during offline synchronization:

- Devices import large batches of messages
- Replay detection applies identically to live and batch imports
- Arrival order does not affect replay validation
- Devices can safely sync months of offline data

This ensures robust convergence regardless of connectivity patterns.

---

## 12. Edge Cases and Recovery

### Device Reset:
- If keys are regenerated, device identity changes
- Old messages from previous identity are invalid
- Sequence numbers restart safely

### Clock Desynchronization:
- Lamport clocks self-correct on merge
- Replay checks remain valid due to sequence enforcement

### Partial State Loss:
- Devices fall back to tx_id and signature checks
- Ledger consistency is preserved

---

## 13. Security Guarantees

Replay protection ensures:

- No transaction executes more than once
- No trust score can be artificially inflated
- No group savings contribution is duplicated
- No historical ledger state can be resurrected

These guarantees hold even under adversarial radio conditions.

---

## 14. Future Enhancements

Planned improvements include:

- Bloom filter–based replay detection
- Merkle proof–based message presence checks
- Trust-weighted replay penalties
- Adaptive cache sizing based on memory availability

---

## 15. Summary

Seed’s replay attack protection enables a secure, offline-first financial mesh by combining unique message IDs, Lamport clocks, per-device counters, signed metadata, and deterministic rejection rules.

Replay attacks are neutralized without servers, without clocks, and without internet access—allowing Seed to operate safely in the most constrained and adversarial environments.
