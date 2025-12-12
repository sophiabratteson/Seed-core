# Neighbor Discovery

This document defines how Seed devices discover, identify, and maintain awareness of nearby peers in a fully offline mesh network. Neighbor discovery is foundational to Seed’s ability to synchronize ledgers, route messages, conserve power, and operate without centralized infrastructure.

---

## 1. Purpose of Neighbor Discovery

Neighbor discovery enables a Seed device to:

- Detect nearby Seed devices within radio range
- Learn basic capabilities of peers (battery level, software version, sync state)
- Establish temporary communication links
- Maintain a dynamic view of the local mesh topology
- Support routing and synchronization decisions

Neighbor discovery operates continuously but opportunistically, balancing responsiveness with extreme power efficiency.

---

## 2. Design Constraints

Neighbor discovery must function under the following constraints:

- No internet connectivity
- No fixed infrastructure
- No global device registry
- Extremely low bandwidth
- Intermittent connectivity
- Devices may be powered off for long periods
- Devices may join or leave the network unpredictably

The protocol must tolerate partial information and stale data while remaining safe and deterministic.

---

## 3. Device Identity Model

Each Seed device has a persistent, cryptographically derived identity:

- device_id: Public identifier derived from device keypair
- device_pubkey: Public key used for message verification
- device_nonce: Rotating short-term identifier to reduce tracking

Neighbor discovery messages never expose private keys or sensitive user data.

---

## 4. Neighbor Discovery Message (HELLO)

Devices discover neighbors by broadcasting lightweight HELLO messages at configurable intervals.

### HELLO Message Fields

- message_type: "HELLO"
- device_id
- rotating_nonce
- firmware_version
- protocol_version
- battery_state (coarse-grained)
- last_sync_lamport
- timestamp (logical or monotonic, not wall-clock)
- message_signature

HELLO messages are intentionally small to reduce airtime and collision risk.

---

## 5. Discovery Timing and Frequency

Discovery operates on an adaptive schedule:

- Default interval: Low-frequency periodic broadcast
- Accelerated discovery:
  - On device wake
  - After prolonged offline period
  - When user initiates a sync
- Suppressed discovery:
  - Low battery conditions
  - Thermal or power stress
  - No recent mesh activity

All timing parameters are configurable per deployment.

---

## 6. Passive Listening Mode

In addition to broadcasting, Seed devices spend most of their time in passive listening mode:

- Devices listen for HELLO messages from others
- No response is required to every HELLO
- Discovery is symmetric and opportunistic

Passive listening minimizes power usage while enabling organic mesh growth.

---

## 7. Neighbor Table Structure

Each device maintains a local Neighbor Table containing:

- device_id
- last_seen_timestamp
- signal_strength (RSSI/SNR)
- estimated link quality
- battery_state (last known)
- protocol_version
- sync_state_summary
- trust_score_hint (optional, coarse)

Entries are soft-state and expire automatically if not refreshed.

---

## 8. Neighbor Table Lifecycle

### Entry Creation
- Created upon receiving a valid HELLO message

### Entry Update
- Updated when receiving subsequent HELLOs or data messages

### Entry Expiration
- Removed after timeout period with no activity
- Timeout duration adapts based on network density

No permanent neighbor relationships exist.

---

## 9. Authentication and Validation

Every HELLO message must:

- Be cryptographically signed
- Match expected protocol version constraints
- Pass replay protection checks
- Respect nonce rotation rules

Invalid or malformed discovery messages are silently dropped.

---

## 10. Privacy Protections

Neighbor discovery is designed to resist tracking and surveillance:

- Rotating nonces prevent long-term tracking
- No user identity or balance data exposed
- No location data transmitted
- Broadcasts are indistinguishable from generic mesh traffic

Discovery does not reveal social or financial relationships.

---

## 11. Power-Aware Behavior

Discovery behavior adapts to power state:

- High battery: normal discovery cadence
- Medium battery: reduced broadcast frequency
- Low battery: listen-only mode
- Critical battery: discovery disabled entirely

Devices always prioritize user funds and data integrity over connectivity.

---

## 12. Interaction with Routing Layer

Neighbor discovery feeds directly into routing decisions:

- Routing layer consumes neighbor table
- Routes prefer:
  - Higher link quality
  - More recent neighbors
  - Better battery states
- Discovery does not imply routing commitment

Routing remains probabilistic and fault-tolerant.

---

## 13. Failure Modes and Recovery

### Missed Discovery
- Devices may temporarily disappear
- Mesh heals automatically upon rediscovery

### Network Partition
- Separate clusters form independently
- Merge seamlessly when partitions reconnect

### Malicious Spam
- Rate-limited processing
- Signature verification prevents poisoning

---

## 14. Example Discovery Flow

1. Device A wakes from sleep
2. Device A broadcasts HELLO
3. Device B hears HELLO and updates neighbor table
4. Device B optionally responds with its own HELLO
5. Both devices now recognize each other as neighbors
6. Higher-level sync may be initiated later

No immediate data exchange is required.

---

## 15. Future Enhancements

- Bloom-filter based neighbor summaries
- Adaptive discovery based on movement detection
- Group-based discovery suppression
- Trust-weighted discovery prioritization

---

## 16. Summary

Neighbor discovery in Seed is lightweight, privacy-preserving, and power-aware. It enables organic mesh formation without infrastructure, allowing devices to find each other, exchange value, and synchronize state in the most constrained environments on earth.

Discovery is probabilistic, resilient, and designed for real human conditions—not ideal networks.
