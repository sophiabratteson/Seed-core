# Flooding vs Gossip Routing Strategy

This document defines the routing dissemination strategies used within the Seed mesh network, specifically comparing **Flooding** and **Gossip-based propagation**. Seed is designed for low-power, offline-first environments where devices must exchange critical financial data reliably while conserving energy and bandwidth.

---

## 1. Purpose of Routing Strategy Selection

Seed devices must propagate transactions, ledger updates, and control messages across a decentralized mesh network without centralized coordination. The routing strategy must:

- Ensure eventual delivery of critical messages
- Operate under intermittent connectivity
- Minimize power consumption
- Avoid network congestion
- Remain simple enough for constrained hardware
- Be resilient to node loss or malicious behavior

Flooding and Gossip represent two core propagation models that Seed can dynamically switch between depending on context.

---

## 2. Flooding Strategy Overview

### Definition
Flooding is a routing strategy where each node forwards every new message to all known neighbors (except the one it received it from).

### Behavior
- A message is broadcast outward until all reachable nodes have seen it
- Nodes suppress re-forwarding duplicates using message IDs
- No routing tables or path discovery required

### Advantages
- Extremely simple to implement
- High delivery reliability
- Fast network-wide propagation
- Works well in sparse or unstable networks

### Disadvantages
- High message redundancy
- Increased power consumption
- Risk of congestion in dense networks
- Poor scalability at large node counts

### Use Cases in Seed
- Initial network bootstrapping
- Emergency updates
- Disaster recovery scenarios
- Small or sparse mesh deployments
- Critical ledger checkpoints

---

## 3. Gossip Strategy Overview

### Definition
Gossip routing is a probabilistic dissemination method where nodes forward messages to a randomly selected subset of neighbors.

### Behavior
- Each node forwards a message with probability *p*
- Messages propagate gradually through the network
- Redundancy exists but is bounded
- Nodes track seen message IDs to avoid loops

### Advantages
- Lower power usage
- Reduced congestion
- Better scalability
- More efficient in dense networks

### Disadvantages
- Slower convergence
- Non-zero probability of message loss
- Requires parameter tuning
- Less deterministic than flooding

### Use Cases in Seed
- Routine transaction propagation
- Background ledger syncing
- Dense village or market networks
- Power-constrained environments

---

## 4. Deterministic Safety Guarantees

Seed ensures correctness even with probabilistic gossip by:

- Treating ledger sync as **eventual consistency**
- Using deterministic merge rules (Lamport clocks, device IDs)
- Re-broadcasting unresolved transactions periodically
- Escalating to flooding when conflicts or gaps are detected

No single missed packet can permanently break ledger integrity.

---

## 5. Hybrid Adaptive Routing Model

Seed does not commit to a single routing strategy. Instead, it uses a **hybrid adaptive model**.

### Routing Mode Selection Logic
- Default mode: Gossip
- Escalate to Flooding when:
  - Ledger divergence detected
  - New device joins network
  - Group savings pot closes
  - Trust score dispute occurs
  - Emergency or system alert triggered

### De-escalation
- After confirmation of network convergence
- After a defined cooldown window
- Based on power budget thresholds

---

## 6. Message Type Sensitivity

Different message types use different routing strategies:

| Message Type                | Routing Mode |
|----------------------------|--------------|
| Transaction messages        | Gossip       |
| Ledger sync messages        | Gossip → Flood fallback |
| Group savings messages      | Flooding     |
| Trust score updates         | Gossip       |
| Heartbeats                  | Gossip       |
| Emergency / alerts          | Flooding     |

This prioritization balances reliability and efficiency.

---

## 7. Duplicate Suppression and Loop Prevention

All messages include:
- Message ID
- Origin device ID
- Hop count or TTL
- Optional bloom filter reference

Nodes maintain a short-term cache of recently seen message IDs to:
- Prevent infinite loops
- Avoid redundant forwarding
- Reduce power waste

---

## 8. Power and Bandwidth Considerations

Flooding is capped by:
- Maximum hop count
- Time-based flood suppression
- Battery state thresholds

Gossip parameters are tuned dynamically based on:
- Neighbor count
- Battery level
- Recent message success rates
- Network density estimates

This allows Seed devices to operate for months on limited power.

---

## 9. Security Implications

- Flooding increases exposure to denial-of-service risks
- Gossip limits amplification attacks
- Message authentication prevents spoofing
- Rate limits prevent malicious rebroadcast storms
- Abuse patterns trigger routing mode restrictions

Routing decisions are made locally and cannot be remotely forced.

---

## 10. Failure and Recovery Behavior

If messages fail to propagate:
- Devices reattempt gossip periodically
- Missing transactions are requested explicitly during sync
- Flooding is triggered only as a last resort
- Ledger state always converges once connectivity resumes

Routing failures do not result in permanent data loss.

---

## 11. Future Enhancements

Planned improvements include:
- Adaptive gossip probability based on trust score
- Directional flooding using neighbor reliability metrics
- Energy-aware routing heuristics
- Mesh partition detection and healing
- Opportunistic relay prioritization

---

## 12. Summary

Seed’s routing layer balances simplicity, resilience, and efficiency by combining Flooding and Gossip strategies in an adaptive, context-aware system. This design ensures reliable financial data propagation across unreliable, low-power mesh networks without requiring centralized coordination or continuous connectivity.

The routing system is foundational to Seed’s ability to function as a global, offline-first financial infrastructure.
