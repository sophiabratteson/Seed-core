# Heartbeat Message Specification

This document defines the **Heartbeat Message** used in the Seed mesh protocol. Heartbeat messages enable devices to maintain awareness of nearby peers, assess network health, and support offline-first synchronization without relying on continuous connectivity.

Heartbeat messages are lightweight, periodic broadcasts that do **not** contain financial data.

---

## 1. Purpose of Heartbeat Messages

Heartbeat messages serve the following core functions:

- Announce device presence to nearby Seed nodes
- Enable neighbor discovery and liveness tracking
- Support mesh routing decisions
- Provide basic device health signals
- Allow gradual network convergence in low-connectivity environments
- Prevent unnecessary retransmissions to offline or dead nodes

Heartbeat messages are **non-transactional** and **non-sensitive**.

---

## 2. Design Principles

Heartbeat messages are designed to be:

- Low power
- Small in size
- Periodic but adaptive
- Safe to broadcast publicly
- Useful even without full mesh participation

They must not reveal private financial data or user identity.

---

## 3. When Heartbeat Messages Are Sent

A Seed device sends a heartbeat:

- On device boot
- Periodically during idle operation
- After waking from sleep
- When radio connectivity changes
- Before attempting ledger synchronization
- During mesh discovery phases

Heartbeat frequency may vary based on power state and network density.

---

## 4. Heartbeat Message Structure

### JSON Representation

```
{
  "message_type": "heartbeat",
  "device_id": "NODE_A",
  "device_class": "seed_device",
  "protocol_version": "1.0",
  "timestamp_counter": 1452,
  "power_state": "normal",
  "ledger_height": 284,
  "sync_capable": true,
  "capabilities": {
    "supports_groups": true,
    "supports_trust_scores": true,
    "supports_ai_assistant": false
  },
  "signature": "BASE64_SIGNATURE"
}
```

---

## 5. Field Definitions

- `message_type`  
  Identifies this message as a heartbeat.

- `device_id`  
  A pseudonymous, cryptographic device identifier.

- `device_class`  
  Indicates the type of Seed device (e.g. handheld, kiosk, gateway).

- `protocol_version`  
  Ensures compatibility across firmware versions.

- `timestamp_counter`  
  A local monotonic counter (not wall-clock time).

- `power_state`  
  One of: `low_power`, `normal`, `charging`.

- `ledger_height`  
  Number of valid transactions currently applied.

- `sync_capable`  
  Indicates whether the device can participate in sync right now.

- `capabilities`  
  Flags indicating supported protocol features.

- `signature`  
  Cryptographic signature validating message authenticity.

---

## 6. Security Properties

Heartbeat messages:

- Are digitally signed
- Do not contain balances or transaction data
- Do not reveal real-world identity
- Are safe to receive from untrusted peers

Devices reject heartbeats with invalid signatures or unsupported protocol versions.

---

## 7. Device Behavior on Receiving a Heartbeat

When a Seed device receives a heartbeat:

1. Validate signature
2. Check protocol compatibility
3. Update neighbor table entry
4. Record last-seen timestamp
5. Compare ledger height
6. Decide whether sync is beneficial
7. Adjust routing priorities if needed

Heartbeat reception does **not** trigger automatic ledger sync.

---

## 8. Power and Rate Control

Heartbeat frequency adapts based on:

- Battery level
- Solar charging availability
- Mesh density
- Recent activity

Typical behavior:
- High power: every 30–60 seconds
- Low power: every 5–10 minutes
- Charging: temporarily increased frequency

---

## 9. Failure and Edge Cases

- Missing heartbeats result in gradual neighbor expiry
- Duplicate heartbeats are ignored
- Outdated protocol versions are logged but not synced
- Malformed messages are dropped silently

No user-visible errors are shown.

---

## 10. Relationship to Other Message Types

Heartbeat messages complement:

- Ledger sync messages
- Transaction messages
- Group savings updates
- Trust score updates

They do **not** replace explicit sync or transaction communication.

---

## 11. Future Extensions

Potential future additions include:

- Encrypted capability negotiation
- Network congestion hints
- Optional geographic coarse hints (privacy-preserving)
- Relay willingness indicators

These extensions must preserve low power and privacy guarantees.

---

## 12. Summary

Heartbeat messages are the foundation of Seed’s offline mesh awareness. By providing a secure, lightweight signal of device presence and readiness, they enable robust peer discovery, efficient routing, and resilient operation in environments with limited or no connectivity.

Heartbeat messages ensure the Seed network stays alive — even when the internet is not.
