# Mesh Stack Overview

This document defines the mesh networking software stack used by Seed devices. The mesh stack enables fully offline, peer-to-peer communication between Seed devices without reliance on internet connectivity, centralized servers, or fixed infrastructure. It is the foundational layer that allows Seed to function as a decentralized financial system in low-connectivity or disconnected environments.

---

## 1. Purpose of the Mesh Stack

The mesh stack is responsible for:

- Enabling device-to-device communication over long distances
- Supporting multi-hop message propagation across a network of devices
- Operating efficiently on low-power hardware
- Functioning without internet, cellular service, or continuous power
- Providing reliable message delivery despite packet loss or intermittent connectivity
- Supporting offline-first synchronization of financial data

The mesh stack is intentionally lightweight, deterministic, and resilient to partial failures.

---

## 2. Design Principles

The mesh stack follows these core principles:

- Offline-first: All operations assume zero internet connectivity
- Decentralized: No central coordinator or gateway is required
- Opportunistic: Devices sync whenever they encounter one another
- Energy-aware: Communication minimizes power consumption
- Deterministic: Message handling produces consistent results across devices
- Secure-by-design: All messages are authenticated and integrity-checked

---

## 3. Hardware and Radio Abstraction

The mesh stack sits above the radio driver layer and abstracts away hardware-specific details.

- Supported radios:
  - LoRa (SX127x / SX126x family)
  - Sub-GHz ISM bands (region dependent)
- The stack does not assume continuous connectivity
- Radio interactions are handled via a Radio Abstraction Layer (RAL)

The mesh stack interacts with the radio layer through simple primitives:
- send_packet()
- receive_packet()
- sleep_radio()
- wake_radio()

This abstraction allows the mesh logic to remain portable across hardware platforms.

---

## 4. Network Topology Model

Seed uses an ad-hoc mesh topology with the following characteristics:

- No fixed roles (no master, no server)
- All devices are peers
- Devices dynamically discover neighbors
- Routes are temporary and opportunistic
- The network tolerates partitions and merges

Topologies supported include:
- Single-hop peer-to-peer
- Multi-hop mesh with store-and-forward routing
- Intermittent "sneakernet" style propagation

The mesh does not attempt to maintain a global network map.

---

## 5. Message-Oriented Architecture

The mesh stack operates entirely on message passing.

Message categories include:
- Transaction messages
- Ledger synchronization messages
- Trust score updates
- Group savings updates
- Heartbeat and presence announcements
- Error and diagnostic messages

Each message is:
- Self-describing
- Cryptographically signed
- Assigned a unique message ID
- Idempotent (safe to receive multiple times)

Messages are small, fixed-size where possible, and optimized for low bandwidth.

---

## 6. Packet Flow Lifecycle

The typical message lifecycle is:

1. Application layer generates a message
2. Message is serialized into a packet format
3. Packet is placed into the transmit queue
4. Radio layer broadcasts the packet
5. Nearby devices receive the packet
6. Receiving devices validate and process the message
7. Message may be forwarded further into the mesh

Forwarding decisions are based on simple, deterministic rules.

---

## 7. Routing and Forwarding Strategy

Seed uses a hybrid routing approach:

- Flooding for small, critical messages
- Gossip-style propagation for larger datasets
- Time-to-live (TTL) limits to prevent infinite loops
- Neighbor tables to reduce redundant forwarding

Devices do not compute shortest paths or maintain routing tables. Instead, the system favors simplicity and robustness.

---

## 8. Reliability and Fault Tolerance

The mesh stack accounts for unreliable links through:

- Message acknowledgments (when feasible)
- Retransmission with backoff
- Duplicate message detection
- Graceful handling of missing packets

If messages are lost:
- They may be retransmitted later
- Or recovered during future sync events

The system assumes eventual consistency rather than immediate delivery.

---

## 9. Power Management Integration

The mesh stack is tightly integrated with power management:

- Radios are duty-cycled aggressively
- Devices sleep between transmit windows
- Broadcast frequency adapts to battery level
- Low-power modes disable non-essential traffic

The stack exposes hooks so the power manager can:
- Pause mesh activity
- Reduce transmission power
- Delay non-urgent messages

---

## 10. Security Responsibilities

The mesh stack enforces:

- Message authentication using device keys
- Integrity checking via checksums and signatures
- Replay protection using message IDs and clocks
- Rejection of malformed or unauthorized messages

The mesh stack does NOT:
- Store private keys
- Perform cryptographic signing (delegated to security module)
- Make trust or ledger decisions

It strictly handles transport and propagation.

---

## 11. Interaction with Other Software Layers

The mesh stack interfaces with:

- Ledger Engine:
  - Receives transaction and sync messages
  - Delivers validated payloads for processing
- Security Module:
  - Requests signature verification
  - Validates sender identity
- Power Manager:
  - Receives energy constraints
  - Adjusts radio behavior
- Device Applications:
  - Sends user-generated messages
  - Receives network updates

The mesh stack itself remains application-agnostic.

---

## 12. Failure Modes and Recovery

The mesh stack is designed to tolerate:

- Device power loss
- Network partitions
- Packet collisions
- Temporary interference
- Partial data corruption

Recovery mechanisms include:
- Re-sync on reconnection
- Redundant message propagation
- Periodic state advertisements

No manual intervention is required to restore connectivity.

---

## 13. Scope and Non-Goals

The mesh stack intentionally does NOT:

- Provide real-time guarantees
- Support high-throughput data transfer
- Maintain global network state
- Enforce financial rules
- Depend on internet gateways

Its sole purpose is resilient offline communication.

---

## 14. Summary

The Seed mesh stack is the backbone of the system’s offline capability. By combining lightweight message passing, opportunistic routing, strong security boundaries, and power-aware design, it enables a global financial network that functions even in the absence of traditional infrastructure.

This mesh-first approach allows Seed to scale organically, adapt to local conditions, and remain usable in the most challenging environments.
