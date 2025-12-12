# Routing Overview

This document defines how Seed devices route messages across a decentralized, offline-first mesh network. Because Seed operates without fixed infrastructure, internet connectivity, or centralized coordination, routing must be resilient, low-power, and fully autonomous.

Seed routing is designed for environments with:
- Intermittent connectivity
- Limited power availability
- Dynamic node participation
- Unreliable radio links
- No global network map

The routing layer ensures that transactions, ledger updates, group savings messages, trust score updates, and control signals reliably propagate through the mesh while minimizing energy consumption and avoiding network congestion.

---

## 1. Routing Goals

The routing system is designed to meet the following objectives:

- Enable peer-to-peer message delivery without central servers
- Support multi-hop message propagation across sparse networks
- Operate fully offline with no external coordination
- Minimize radio usage to preserve battery life
- Adapt automatically to changing network topology
- Ensure eventual delivery when paths become available
- Prevent routing loops and message storms
- Maintain deterministic behavior where possible

---

## 2. Network Model Assumptions

Seed routing assumes:

- Devices communicate using low-bandwidth LoRa radios
- Nodes may appear or disappear at any time
- There is no fixed gateway or backbone
- Network size may range from a few devices to thousands
- Latency is acceptable; immediacy is not required
- Message delivery is best-effort but eventually consistent

Routing is optimized for **eventual consistency**, not real-time guarantees.

---

## 3. Node Roles

All Seed devices operate as equal peers, but may temporarily assume different functional roles:

- Origin Node  
  The device that creates a message

- Relay Node  
  A device that forwards messages on behalf of others

- Sink Node  
  A device that consumes a message (final recipient)

There are no permanently assigned roles. Devices dynamically act as needed based on proximity, power state, and message relevance.

---

## 4. Routing Strategy Overview

Seed uses a **hybrid routing strategy** combining:

- Local neighbor awareness
- Controlled flooding for critical data
- Gossip-style propagation for non-urgent updates
- Opportunistic forwarding when nodes encounter each other

This hybrid approach avoids the overhead of maintaining full routing tables while still enabling messages to reach distant nodes.

---

## 5. Neighbor Awareness

Each device maintains a lightweight neighbor table that includes:

- Neighbor device ID
- Last-seen timestamp
- Signal strength (RSSI/SNR)
- Estimated link reliability
- Supported message types

This table is updated passively through:
- Periodic heartbeat messages
- Observed message traffic
- Successful acknowledgements

Neighbor tables expire entries automatically to prevent stale routes.

---

## 6. Message Forwarding Rules

When a device receives a message:

1. Validate message integrity and signature
2. Check if the message was previously seen
3. Determine whether the message is relevant locally
4. Decide whether to forward based on:
   - Message type
   - Hop count / TTL
   - Power state
   - Neighbor availability
5. Forward selectively to eligible neighbors
6. Cache message metadata to prevent duplication

This process ensures efficient propagation without redundant transmissions.

---

## 7. Loop Prevention and Deduplication

To prevent routing loops and message storms:

- Each message includes a unique message ID
- Devices maintain a recent-message cache
- Messages exceeding hop limits are discarded
- Duplicate messages are ignored silently
- Forwarding decisions are deterministic

This guarantees network stability even under high churn.

---

## 8. Priority Handling

Messages are categorized by priority:

- Critical  
  Ledger sync, conflict resolution, security alerts

- High  
  Transactions, group savings updates, trust score updates

- Medium  
  Heartbeats, neighbor discovery

- Low  
  Analytics, non-essential metadata

Higher-priority messages are forwarded first and may use broader propagation strategies.

---

## 9. Power-Aware Routing

Routing decisions adapt to device power state:

- Devices with low battery reduce forwarding frequency
- Power-critical nodes may refuse relay duties
- Solar-powered or externally powered nodes naturally act as hubs
- Routing load distributes dynamically across the mesh

This enables long-lived networks even in energy-constrained environments.

---

## 10. Failure Handling

The routing layer tolerates:

- Packet loss
- Temporary partitions
- Node failures
- Environmental interference

When delivery fails:
- Messages are retried opportunistically
- Nodes wait for future encounters
- No global recovery coordination is required

The system favors resilience over immediacy.

---

## 11. Security Considerations

Routing integrates with Seed security controls:

- All messages are authenticated
- Unauthorized forwarding is prevented
- Malformed messages are dropped early
- Replay attacks are blocked at the protocol layer
- Routing metadata reveals no sensitive user data

Routing does not require knowledge of transaction contents.

---

## 12. Extensibility

The routing layer is designed to support future enhancements such as:

- Adaptive routing metrics
- Trust-weighted forwarding
- Multi-radio support
- Regional super-nodes
- Integration with intermittent internet gateways

These extensions can be added without redesigning the core protocol.

---

## 13. Summary

Seed’s routing system enables reliable, low-power, offline communication across dynamic mesh networks. By combining neighbor awareness, opportunistic forwarding, controlled flooding, and power-aware decision-making, the network can function in environments where traditional infrastructure fails.

Routing is not optimized for speed — it is optimized for **survivability, fairness, and eventual convergence**, which are essential for Seed’s mission of global financial access.
