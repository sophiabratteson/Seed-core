# Mesh Protocol Overview

This document defines the Seed Mesh Protocol: the communication layer that allows Seed devices to exchange financial data securely, reliably, and entirely offline. The protocol is designed for extreme environments with no internet, intermittent power, and unreliable connectivity.

The mesh protocol enables Seed to function as a decentralized financial network without servers, cellular infrastructure, or centralized coordination.

---

## 1. Design Goals

The Seed mesh protocol is designed to:

- Operate fully offline with no internet dependency
- Support intermittent connectivity and long offline periods
- Enable peer-to-peer financial transactions
- Ensure eventual consistency of ledgers across devices
- Minimize power consumption
- Preserve user privacy and anonymity
- Remain resilient against malicious or faulty nodes

---

## 2. Network Model

Seed devices form a decentralized, peer-to-peer mesh network.

Key characteristics:

- No central coordinator or master node
- Any device can join or leave at any time
- Devices discover neighbors automatically
- Messages may hop across multiple devices
- The network tolerates partial connectivity and partitions

The mesh behaves as a store-and-forward network rather than a real-time system.

---

## 3. Communication Medium

Seed uses low-power radio (LoRa or equivalent) as the primary transport.

Characteristics:

- Long-range, low-bandwidth communication
- Optimized for small packets
- High resistance to interference
- Suitable for rural and disaster-prone regions

The protocol assumes limited bandwidth and high latency.

---

## 4. Message-Based Architecture

All communication occurs via discrete messages.

Each message includes:

- Message type
- Sender device ID
- Sequence number
- Payload
- Integrity check
- Optional cryptographic signature

Messages are self-contained and can be relayed without understanding their contents.

---

## 5. Message Categories

The mesh protocol supports multiple message categories:

- Transaction messages
- Ledger synchronization messages
- Group savings messages
- Trust score updates
- Heartbeat messages
- Error and diagnostic messages

Each category has a defined schema and validation rules.

---

## 6. Store-and-Forward Model

Seed devices do not require live connections.

Workflow:

1. Device creates a message
2. Message is stored locally
3. Message is broadcast when radio is available
4. Neighboring devices store the message
5. Messages propagate opportunistically through the mesh

Messages may take minutes, hours, or days to reach all devices.

---

## 7. Offline-First Synchronization

The protocol assumes devices are offline by default.

Design principles:

- Messages are never assumed delivered
- Duplicate messages are expected
- Order of arrival is irrelevant
- Devices reconcile state deterministically

Synchronization correctness does not depend on timing or delivery order.

---

## 8. Deterministic Convergence

All devices eventually converge to the same ledger state.

This is achieved through:

- Lamport logical clocks
- Deterministic sorting rules
- Idempotent message processing
- Strict validation logic

Even if devices sync in different orders, final state is identical.

---

## 9. Neighbor Discovery

Devices periodically broadcast lightweight discovery messages.

Discovery includes:

- Device ID
- Protocol version
- Supported features
- Optional signal strength metrics

Neighbor tables are maintained locally and expire automatically.

---

## 10. Routing Strategy

Seed uses a hybrid routing approach:

- Local broadcast for nearby devices
- Opportunistic multi-hop forwarding
- Gossip-based propagation for scalability

The protocol avoids complex routing tables to conserve memory and power.

---

## 11. Power-Aware Behavior

The mesh protocol is power-conscious by design.

Strategies include:

- Duty-cycled radio usage
- Message batching
- Adaptive broadcast intervals
- Priority-based message queues

Critical messages are transmitted first.

---

## 12. Security Model

Security is enforced at the protocol layer.

Core protections:

- Message integrity checks
- Device identity verification
- Replay protection
- Optional end-to-end encryption
- Tamper detection support

Untrusted devices cannot corrupt the global ledger.

---

## 13. Privacy Considerations

The mesh protocol minimizes metadata leakage.

Design choices:

- No global addressing
- No centralized logs
- No real-time tracking
- Encrypted payloads where required

Devices do not reveal user identities by default.

---

## 14. Failure Handling

The protocol is resilient to:

- Device loss
- Power failures
- Partial network partitions
- Corrupted messages

Failures degrade performance but do not compromise correctness.

---

## 15. Extensibility

The protocol is versioned and extensible.

Future support includes:

- New message types
- Improved compression
- Alternative radio backends
- Gateway bridging to internet systems

Backward compatibility is maintained whenever possible.

---

## 16. Summary

The Seed Mesh Protocol enables a fully decentralized financial system to operate in environments where traditional infrastructure does not exist. By prioritizing offline-first design, deterministic convergence, and power efficiency, the protocol ensures that Seed devices can securely exchange value across a resilient mesh network without relying on the internet or centralized institutions.
