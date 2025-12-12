# Path Selection Logic

This document defines how Seed devices choose routes for sending messages across the mesh network. Because Seed operates without internet, servers, or fixed infrastructure, routing decisions must be decentralized, power-efficient, resilient to failure, and deterministic enough to support financial data integrity.

---

## 1. Goals of Path Selection

The path selection logic is designed to:

- Deliver messages reliably in low-connectivity environments
- Minimize power consumption on battery-constrained devices
- Avoid reliance on any central coordinator
- Adapt dynamically to changing network conditions
- Support eventual delivery even with intermittent links
- Prevent routing manipulation or malicious path control
- Scale from small village meshes to large regional networks

---

## 2. Routing Philosophy

Seed uses a **hybrid opportunistic routing model**, combining:

- Local neighbor awareness
- Probabilistic forwarding
- Store-and-forward delivery
- Redundant propagation for critical messages

The system does not attempt to maintain a full global routing table. Instead, each device makes local decisions based on partial knowledge, ensuring robustness under uncertainty.

---

## 3. Network Assumptions

The routing logic assumes:

- Nodes may join and leave unpredictably
- Links may be asymmetric or unreliable
- Devices may be offline for long periods
- Bandwidth is extremely limited
- Messages may take minutes, hours, or days to propagate
- Power availability varies widely across nodes

Routing must function correctly under all these conditions.

---

## 4. Neighbor Knowledge Model

Each device maintains a **Neighbor Table** containing:

- Neighbor device ID
- Last-seen timestamp (logical time)
- Signal strength estimate (RSSI / SNR)
- Recent message success rate
- Battery level hint (if shared)
- Trust score modifier (optional)

This table is updated passively through received messages and periodic heartbeats.

---

## 5. Message Priority Classes

Routing behavior depends on message type:

- **Critical**
  - Ledger sync messages
  - Conflict resolution updates
  - Group savings state changes
- **High**
  - Transaction broadcasts
  - Trust score updates
- **Medium**
  - Heartbeats
  - Network metadata
- **Low**
  - Analytics
  - Debug or diagnostics

Higher-priority messages receive more aggressive forwarding.

---

## 6. Path Selection Algorithm Overview

When a device needs to forward a message:

1. Identify all currently reachable neighbors
2. Filter neighbors based on:
   - Recent responsiveness
   - Minimum signal quality
3. Score remaining neighbors using:
   - Link reliability
   - Energy cost
   - Redundancy value
4. Select one or more forwarding candidates
5. Queue message for transmission
6. Apply retry and backoff logic if delivery fails

---

## 7. Neighbor Scoring Function

Each neighbor is assigned a dynamic score:

score = (reliability_weight * success_rate)
+ (signal_weight * signal_quality)
+ (trust_weight * trust_modifier)
- (power_weight * estimated_energy_cost)

Weights are configurable and may differ by message priority.

Neighbors with the highest scores are preferred, but lower-ranked neighbors may still be selected probabilistically to preserve diversity.

---

## 8. Multi-Path Forwarding

For critical messages:

- Messages may be sent to multiple neighbors
- Each copy includes a hop counter and message ID
- Devices discard duplicates upon receipt
- Redundant paths increase delivery probability

This ensures resilience against node failures and partitions.

---

## 9. Store-and-Forward Behavior

If no suitable neighbors are available:

- The message is stored locally
- The device periodically retries forwarding
- Retry intervals increase exponentially to save power
- Messages expire based on priority-specific TTL values

This allows Seed to function across time-separated encounters.

---

## 10. Loop Prevention and Deduplication

Each message includes:

- Unique message ID
- Origin device ID
- Hop count
- Seen-by hash (compressed)

Devices:

- Drop messages already seen
- Drop messages exceeding hop limit
- Drop expired messages

This prevents infinite loops and network flooding.

---

## 11. Energy-Aware Routing

Devices dynamically reduce routing participation when:

- Battery level is low
- Solar or hand-crank input is unavailable
- Device enters power-saving mode

In these states:

- Only critical messages are forwarded
- Heartbeat frequency is reduced
- Routing scores penalize high-cost links

---

## 12. Security Considerations

Path selection logic includes safeguards against:

- Routing manipulation by malicious nodes
- Eclipse attacks using fake neighbors
- Message suppression attacks

Mitigations include:

- Trust score weighting
- Redundant forwarding
- No single-node routing authority
- Deterministic merge rules at the ledger layer

---

## 13. Failure Scenarios

The routing system tolerates:

- Node disappearance mid-transfer
- Network partitions
- Temporary congestion
- Partial message loss
- Power outages

In all cases, messages eventually propagate when conditions permit.

---

## 14. Interaction with Ledger Consistency

Routing is deliberately separated from ledger validation:

- Routing delivers messages
- Ledger logic determines correctness
- Invalid or malicious data is rejected at higher layers

This separation simplifies routing and strengthens security.

---

## 15. Future Enhancements

Planned extensions include:

- Adaptive learning of optimal routes
- Geographic hints where available
- Trust-weighted gossip reduction
- Dynamic mesh density estimation
- Integration with Merkle-based sync summaries

---

## 16. Summary

Seed’s path selection logic enables reliable, power-aware, and attack-resilient message delivery across fully decentralized mesh networks. By relying on local decision-making, probabilistic forwarding, and redundancy, Seed ensures that financial data can traverse the network without servers, internet access, or centralized control.

This routing model is foundational to Seed’s ability to operate as a global, offline-first financial system.
