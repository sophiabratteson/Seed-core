# Mesh Topology Options

This document describes the network topology models supported by the Seed mesh protocol. Because Seed operates without centralized infrastructure, internet connectivity, or permanent gateways, network topology must be flexible, fault-tolerant, and energy-efficient. Different environments require different topology behaviors, and Seed supports multiple models that can adapt dynamically.

---

## Purpose of Topology Design

The topology defines how Seed devices discover each other, exchange messages, and propagate ledger updates across the network. The goals of Seed’s topology design are:

- Enable communication without fixed infrastructure
- Tolerate intermittent connectivity and node failure
- Minimize power consumption
- Avoid single points of failure
- Scale from small local groups to large regional networks
- Maintain deterministic behavior for financial data

---

## Supported Topology Models

Seed supports multiple topology strategies that can be selected dynamically based on environment, density, and power conditions.

---

## Fully Decentralized Peer-to-Peer Mesh

### Description

Every Seed device acts as an equal peer. Devices communicate directly with nearby nodes and relay messages onward when appropriate.

There is no hierarchy, no leader node, and no permanent routing authority.

### Characteristics

- All nodes have identical roles
- Messages propagate through neighbor-to-neighbor forwarding
- Nodes maintain a local neighbor table
- No dependency on internet or gateways

### Advantages

- Maximum resilience
- No central failure points
- Ideal for rural, disaster, or low-trust environments
- Works well for financial autonomy

### Tradeoffs

- Higher message redundancy
- Requires careful power and bandwidth management
- Routing efficiency depends on node density

---

## Clustered Local Mesh (Community Mesh)

### Description

Devices form small local clusters (e.g. village, market, refugee camp). Within a cluster, communication is dense and frequent. Inter-cluster communication happens opportunistically.

### Characteristics

- Strong connectivity inside clusters
- Weaker but functional links between clusters
- Clusters are not formally defined; they emerge naturally

### Advantages

- Efficient local syncing
- Reduced long-range transmission cost
- Mirrors real-world social and economic groups

### Tradeoffs

- Cross-cluster propagation may be delayed
- Requires gossip-based forwarding between clusters

---

## Opportunistic Bridge Nodes

### Description

Some nodes temporarily act as bridges between otherwise disconnected mesh segments. This can happen when a user travels, visits a market, or enters a WiFi-enabled area.

### Characteristics

- Bridge nodes are not fixed or permanent
- Any node can act as a bridge
- Bridges synchronize ledgers between groups

### Advantages

- Enables long-distance data propagation
- No dedicated infrastructure required
- Works naturally with human movement patterns

### Tradeoffs

- Propagation latency depends on movement
- No guaranteed delivery timing

---

## Gateway-Assisted Hybrid Topology (Optional)

### Description

In environments where internet access exists, some Seed devices may temporarily act as gateways to external networks. This does not replace the mesh but supplements it.

### Characteristics

- Gateways are optional and ephemeral
- Devices continue to function without them
- Gateway access is opportunistic, not required

### Advantages

- Faster global synchronization
- Allows limited integration with external systems
- Improves analytics and monitoring

### Tradeoffs

- Must not create dependency
- Must preserve offline-first guarantees

---

## Topology Selection Logic

Seed devices do not permanently select a single topology. Instead, they adapt dynamically based on:

- Number of nearby peers
- Battery level
- Message backlog
- User activity
- Environmental conditions

Topology behavior is emergent, not centrally configured.

---

## Topology and Ledger Consistency

Regardless of topology:

- Ledger consistency rules remain identical
- Conflict resolution logic is unchanged
- Ordering is deterministic
- No topology can override validation rules

Topology only affects *how fast* data moves, not *what* data is valid.

---

## Failure Handling

Seed topologies are designed to degrade gracefully.

- If nodes disappear, routing tables shrink naturally
- If density drops, devices switch to store-and-forward
- If power is low, nodes reduce participation frequency

No explicit reconfiguration is required.

---

## Security Considerations

- Topology does not imply trust
- All messages are authenticated
- Relayed messages are verified independently
- Malicious nodes cannot control routing outcomes

Routing decisions never override cryptographic validation.

---

## Future Topology Extensions

Potential future enhancements include:

- Trust-weighted routing decisions
- Energy-aware adaptive transmission power
- Geographic-aware routing hints
- Multi-radio hybrid meshes (LoRa + BLE)

These extensions must preserve offline-first and decentralization guarantees.

---

## Summary

Seed’s mesh topology design prioritizes resilience, flexibility, and independence from infrastructure. By supporting multiple emergent topology behaviors rather than a single rigid model, Seed can function across diverse environments while maintaining financial integrity and user autonomy.
