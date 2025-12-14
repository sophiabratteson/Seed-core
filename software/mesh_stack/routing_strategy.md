# Mesh Routing Strategy

This document defines how Seed devices route messages across a decentralized, offline-first mesh network. The routing strategy is designed to function without internet connectivity, centralized servers, or fixed infrastructure, while prioritizing reliability, low power usage, and eventual message delivery.

---

## 1. Routing Goals

The routing strategy must:

- Enable peer-to-peer communication without internet or cellular service
- Support intermittent connectivity and device mobility
- Minimize power consumption on battery-constrained devices
- Avoid centralized coordinators or fixed routing authorities
- Ensure messages eventually reach intended recipients
- Scale from small village clusters to large regional meshes

---

## 2. Network Model Assumptions

Seed operates under the following assumptions:

- Devices communicate using low-bandwidth radio (e.g., LoRa)
- Links are unreliable and asymmetric
- Devices may frequently join or leave the network
- Network topology changes dynamically
- Message delivery is opportunistic, not guaranteed in real time
- Devices may be offline for long periods

The routing strategy is therefore **delay-tolerant** and **offline-first**.

---

## 3. Routing Architecture Overview

Seed uses a **hybrid gossip + store-and-forward routing model**:

- Messages are not routed along fixed paths
- Devices forward messages opportunistically when peers are encountered
- Each device maintains a lightweight neighbor table
- Messages are cached locally until delivery is confirmed or expired

There is no global routing table and no assumption of continuous connectivity.

---

## 4. Message Forwarding Model

Each message includes:

- Message ID
- Origin device ID
- Destination device ID (or group ID)
- Hop count
- Time-to-live (TTL)
- Payload hash

Forwarding rules:

- Devices forward messages they have not seen before
- Messages are forwarded only to neighbors likely to advance delivery
- Duplicate messages are discarded using message IDs
- Messages exceeding TTL are dropped

---

## 5. Neighbor Awareness

Each device maintains a **Neighbor Table** containing:

- Neighbor device ID
- Last seen timestamp
- Estimated link quality (RSSI / SNR)
- Recent message success rate

Neighbors are discovered via:

- Periodic heartbeat broadcasts
- Passive observation of message traffic

Neighbor entries expire automatically if not refreshed.

---

## 6. Routing Decision Logic

When a device receives or generates a message:

1. Check if destination is self → deliver locally
2. Check if destination is a known neighbor → forward directly
3. Otherwise:
   - Forward to a subset of neighbors based on:
     - Link quality
     - Historical reliability
     - Power availability
4. Cache the message locally for future forwarding

Routing decisions are deterministic and do not rely on randomness.

---

## 7. Gossip vs Controlled Flooding

Seed avoids full flooding to conserve power.

Instead:

- Gossip is used for low-priority or informational messages
- Controlled flooding is used for:
  - Ledger synchronization
  - Group savings updates
  - Trust score changes

Flooding limits include:

- Max hop count
- Per-message forward limits
- Backoff timers to prevent storms

---

## 8. Power-Aware Routing

Routing behavior adapts based on device power state:

- High battery:
  - Acts as active forwarder
  - Relays messages aggressively
- Medium battery:
  - Selective forwarding
- Low battery:
  - Minimal forwarding
  - Prioritizes own critical messages only

Power state is evaluated before forwarding any message.

---

## 9. Group and Broadcast Routing

Group messages (e.g., group savings updates):

- Include group ID instead of device ID
- Are forwarded to all neighbors participating in the group
- Use controlled flooding with strict TTL limits

Broadcast messages (e.g., alerts):

- Are flagged as broadcast
- Use very small TTL
- Are never re-forwarded once seen

---

## 10. Loop Prevention

Seed prevents routing loops using:

- Message ID de-duplication
- Hop count limits
- TTL expiration
- Forwarding history cache

Devices never forward the same message twice.

---

## 11. Failure Handling

If delivery fails:

- Message remains cached
- Retries occur when new neighbors appear
- Message expires after TTL or expiration time
- Failure is logged for diagnostics

Routing failure does not block other operations.

---

## 12. Security Considerations

Routing strategy enforces:

- Message authentication before forwarding
- Encrypted payloads
- No metadata leakage beyond device IDs
- Resistance to routing manipulation via deterministic rules

Malicious devices cannot redirect traffic arbitrarily.

---

## 13. Future Enhancements

Planned improvements include:

- Probabilistic routing based on encounter history
- Trust-weighted forwarding preferences
- Adaptive TTL based on network density
- Optional gateway-assisted routing when internet is available

---

## 14. Summary

Seed’s routing strategy enables resilient, offline communication across a dynamic mesh network by combining store-and-forward delivery, power-aware decisions, and deterministic forwarding rules. This approach ensures that financial data, ledger updates, and coordination messages propagate reliably even in environments with extreme connectivity constraints.
