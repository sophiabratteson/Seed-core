# Mesh Packet Format Specification

This document defines the standardized packet structure used by Seed devices to exchange data across the offline-first mesh network. The packet format is designed to be compact, resilient to packet loss, secure against tampering, and flexible enough to support multiple message types (transactions, sync, trust updates, etc.).

The packet format is a core building block of Seed’s ability to operate without internet, servers, or continuous connectivity.

---

## 1. Design Goals

The Seed mesh packet format is designed to:

- Minimize packet size for low-bandwidth radio links
- Support fragmentation and reassembly
- Allow deterministic parsing on low-power devices
- Enable secure authentication and integrity verification
- Support multiple message types using a unified structure
- Function reliably under high packet loss conditions

---

## 2. High-Level Packet Structure

Each packet transmitted over the mesh follows the same high-level structure:

1. Header
2. Routing Metadata
3. Payload
4. Integrity Check

This structure allows devices to quickly validate, route, and process packets without inspecting the full payload unless necessary.

---

## 3. Packet Header

The header provides essential metadata required to interpret the packet.

Fields:

- protocol_version  
  - Identifies the version of the mesh protocol
  - Allows backward compatibility as the protocol evolves

- message_type  
  - Specifies the type of payload contained
  - Examples:
    - TRANSACTION
    - LEDGER_SYNC
    - TRUST_SCORE_UPDATE
    - GROUP_SAVINGS_UPDATE
    - HEARTBEAT
    - ERROR_REPORT

- packet_id  
  - Unique identifier for this packet
  - Used to detect duplicates and track reassembly

- sender_device_id  
  - Unique identifier of the originating device
  - Used for authentication and routing decisions

- sequence_number  
  - Monotonically increasing counter per sender
  - Enables ordering and replay protection

---

## 4. Routing Metadata

Routing metadata enables mesh propagation without centralized coordination.

Fields:

- hop_count  
  - Number of hops the packet has traversed
  - Used to limit flooding and conserve power

- max_hops  
  - Maximum allowed hops before packet is dropped

- previous_hop_id  
  - Device ID of the last forwarding node
  - Helps prevent routing loops

- ttl_expiry  
  - Logical expiration window for the packet
  - Prevents stale packets from circulating indefinitely

---

## 5. Payload Section

The payload contains the application-level data encoded according to the message type.

Payload properties:

- Variable length
- Interpreted only after header validation
- Can be encrypted depending on message type

Examples of payload contents:

- Transaction records
- Ledger state hashes
- Trust score deltas
- Group savings contributions
- Sync acknowledgements

Payload encoding is defined in separate message-type-specific documents.

---

## 6. Fragmentation and Reassembly

Because LoRa and similar radios have strict payload size limits, large messages may be split across multiple packets.

Fragmentation fields:

- fragment_index  
  - Index of this fragment within the message

- fragment_count  
  - Total number of fragments for this message

- fragment_group_id  
  - Shared identifier linking fragments together

Reassembly rules:

- Fragments are buffered until all parts are received
- Incomplete fragment sets expire after a timeout
- Reassembled payloads are validated before processing

---

## 7. Security and Authentication Fields

Each packet includes cryptographic protections to prevent tampering and spoofing.

Fields:

- signature  
  - Digital signature or MAC over header + payload
  - Verifies sender authenticity

- public_key_id  
  - Reference to the sender’s public key
  - Used for signature verification

- nonce  
  - Random value to prevent replay attacks

---

## 8. Integrity Check

To detect transmission errors:

- checksum  
  - Lightweight CRC or hash over the packet
  - Allows rapid detection of corrupted packets

Packets failing integrity checks are discarded immediately.

---

## 9. Deterministic Parsing Rules

All Seed devices parse packets deterministically:

1. Validate protocol_version
2. Validate checksum
3. Validate signature
4. Inspect message_type
5. Route or process payload accordingly

No device behavior depends on arrival timing or radio signal order.

---

## 10. Packet Size Targets

Design targets for packet size:

- Ideal packet size: under 200 bytes
- Maximum packet size: radio-dependent (e.g., LoRa limits)
- Fragmentation used only when necessary

Keeping packets small improves reliability and power efficiency.

---

## 11. Failure Handling

If packet processing fails:

- Invalid header → discard packet
- Invalid signature → discard and flag sender
- Missing fragments → wait until timeout
- Duplicate packet → ignore silently

Devices never crash or block due to malformed packets.

---

## 12. Future Extensions

The packet format supports future enhancements, including:

- Priority flags for emergency messages
- Compression flags
- Multi-recipient encryption
- Zero-knowledge payload validation

Backward compatibility is preserved through protocol_version negotiation.

---

## 13. Summary

The Seed mesh packet format provides a secure, efficient, and deterministic foundation for offline-first communication. By standardizing how data moves through the mesh, Seed enables financial coordination without internet, servers, or trusted intermediaries — even in the most constrained environments.
