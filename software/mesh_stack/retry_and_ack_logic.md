# Retry and Acknowledgment Logic

This document defines how Seed devices ensure reliable message delivery across an unreliable, low-bandwidth, offline-first mesh network. Because Seed operates without continuous connectivity, acknowledgments (ACKs) and retries are essential to guarantee that critical messages—such as transactions, ledger sync updates, and trust score changes—are eventually delivered without overwhelming the network or draining power.

---

## 1. Design Goals

The retry and acknowledgment system is designed to:

- Ensure eventual delivery of critical messages
- Minimize radio airtime and power usage
- Operate without centralized coordination
- Tolerate packet loss, node mobility, and intermittent availability
- Prevent message duplication or replay
- Scale across dense and sparse mesh topologies

---

## 2. Message Classification

Not all messages require the same reliability guarantees. Seed classifies messages into reliability tiers.

### 2.1 Critical Messages (ACK Required)
- Financial transactions
- Ledger sync messages
- Group savings updates
- Trust score updates
- Device provisioning updates

These messages **must** be acknowledged by the receiving node.

### 2.2 Non-Critical Messages (Best Effort)
- Heartbeat messages
- Network discovery beacons
- Status broadcasts
- Diagnostic telemetry

These messages do **not** require acknowledgments.

---

## 3. Acknowledgment Model

### 3.1 ACK Message Structure

Each acknowledged message includes:
- `message_id`
- `sender_device_id`
- `receiver_device_id`
- `message_type`
- `lamport_timestamp`
- `checksum`

ACK messages are lightweight and signed to prevent spoofing.

---

## 4. Retry Logic Overview

Seed uses a **bounded exponential backoff** retry strategy.

### 4.1 Retry Parameters

- Initial retry delay: 2–5 seconds (randomized)
- Maximum retries per message: configurable (default: 5)
- Backoff multiplier: 2×
- Maximum retry window: capped to preserve power

Retry timers are paused during deep sleep or power-saving states.

---

## 5. Message Lifecycle

Each outbound message follows a deterministic lifecycle:

1. Message created and signed
2. Message placed in transmit queue
3. Message transmitted
4. Await ACK
5. If ACK received → mark delivered
6. If timeout expires → schedule retry
7. If retry limit exceeded → mark failed and escalate

---

## 6. Duplicate Detection

To prevent duplicate application of messages:

- Every message has a globally unique `message_id`
- Receiving nodes maintain a rolling cache of recently seen message IDs
- Duplicate messages are acknowledged but not re-applied

This ensures idempotent behavior across retries.

---

## 7. Partial Connectivity Handling

In multi-hop mesh scenarios:

- ACKs may traverse different paths than the original message
- Intermediate nodes forward ACKs opportunistically
- If an ACK cannot reach the originator immediately, it is cached and forwarded later

This supports asynchronous convergence.

---

## 8. Power-Aware Behavior

Retry behavior adapts to device power state:

- High battery: normal retry schedule
- Low battery: extended backoff intervals
- Critical battery: retries suspended except for emergency messages

This prevents battery exhaustion in harsh environments.

---

## 9. Failure Escalation

If retries fail:

- Message is flagged as undelivered
- Transaction remains pending in ledger
- Device attempts delivery again during future sync windows
- User may be notified if human intervention is required

No message failure causes ledger corruption.

---

## 10. Security Considerations

- ACKs are signed to prevent spoofed delivery confirmations
- Replay attacks are mitigated using message IDs and lamport timestamps
- Retry floods are prevented via rate limiting and backoff caps
- Malicious nodes cannot force infinite retries

---

## 11. Interaction with Offline Sync

Retry logic integrates with offline-first sync:

- Messages queued during offline periods
- Retries resume when peers are rediscovered
- Ledger convergence does not depend on immediate ACK success

This ensures long-term reliability even with weeks of disconnection.

---

## 12. Future Enhancements

Planned improvements include:

- Priority-based retry scheduling
- Trust-weighted ACK acceptance
- Adaptive retry limits based on network density
- Batch acknowledgments for large ledger syncs

---

## 13. Summary

Seed’s retry and acknowledgment logic enables reliable communication over unreliable, power-constrained mesh networks. By combining deterministic retries, secure acknowledgments, and power-aware behavior, Seed ensures that financial and governance data is delivered safely without sacrificing resilience or efficiency.

This mechanism is foundational to Seed’s ability to operate as a global, offline-first financial system.
