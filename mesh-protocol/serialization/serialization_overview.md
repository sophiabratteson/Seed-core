# Serialization Overview

This document defines how Seed serializes, compresses, and transmits data across the mesh network. Because Seed operates in low-bandwidth, offline, and energy-constrained environments, serialization is a critical component of system performance, reliability, and security.

Serialization ensures that all devices interpret transmitted data identically, regardless of hardware, firmware version, or message arrival order.

---

## Goals of Serialization

- Minimize packet size to conserve bandwidth and power
- Ensure deterministic interpretation across devices
- Support offline-first operation with delayed delivery
- Enable forward compatibility with future protocol versions
- Allow graceful degradation on low-capability hardware
- Preserve security and data integrity during transmission

---

## Design Principles

- Compact over verbose
- Deterministic over flexible
- Explicit over implicit
- Backward-compatible wherever possible
- Failure-tolerant and recoverable
- Versioned at every layer

---

## Serialization Layers

Seed uses a layered serialization approach:

1. Application Data Layer
2. Protocol Message Layer
3. Transport Packet Layer
4. Radio Frame Layer

Each layer adds structure without duplicating data.

---

## Supported Serialization Formats

Seed supports multiple serialization formats depending on device capability and network conditions.

### Primary Format: Compact JSON

Used for:
- Prototyping
- Debugging
- Two-laptop demo
- Early field pilots

Advantages:
- Human-readable
- Easy to debug
- Widely supported

Disadvantages:
- Larger payload size
- Higher parsing cost

---

### Secondary Format: Binary Compact Encoding

Used for:
- Production devices
- High-density mesh environments
- Low-power operation

Characteristics:
- Fixed-length fields where possible
- Integer-based enums
- Compact type identifiers
- Minimal delimiters

Binary encoding is deterministic and faster to parse on embedded devices.

---

## Message Envelope Structure

All serialized messages share a common envelope:

- protocol_version
- message_type
- sender_device_id
- lamport_clock
- payload_length
- payload
- checksum

This envelope allows devices to:
- Reject unsupported versions
- Route messages correctly
- Detect corruption
- Reorder messages deterministically

---

## Protocol Versioning

- Every serialized message includes a protocol_version field
- Devices reject messages with incompatible major versions
- Minor version differences allow backward-compatible parsing
- Version negotiation occurs implicitly through message exchange

---

## Payload Serialization Rules

- All numeric values use fixed-width integers where possible
- Floating point values are avoided unless necessary
- Strings are UTF-8 encoded
- Optional fields must be explicitly marked
- Missing fields default to safe null values

---

## Transaction Serialization

Transactions are serialized with:

- Unique transaction ID
- Sender ID
- Receiver ID
- Amount
- Lamport timestamp
- Causal references
- Signature

Field order is fixed to ensure deterministic hashing and signing.

---

## Ledger Sync Serialization

Ledger synchronization messages may include:

- Full transaction sets
- Partial diffs
- Bloom filters or summaries
- Checkpoint hashes

Devices select the smallest valid sync format available.

---

## Compression Strategy

Seed applies compression only when beneficial.

- Small payloads are sent uncompressed
- Large payloads use lightweight compression
- Compression algorithms are deterministic
- Compression metadata is included in the envelope

---

## Integrity and Validation

- Every serialized message includes a checksum
- Critical messages include cryptographic signatures
- Invalid or corrupted messages are discarded
- Replay attempts are detected via Lamport clocks

---

## Error Handling

If a device cannot parse a serialized message:

- The message is discarded
- An error_report_message may be sent
- The device continues operating without interruption
- No global failure occurs

---

## Forward Compatibility

Serialization design allows:

- New message types without breaking older devices
- Optional fields for future extensions
- Graceful fallback to known fields only
- Progressive feature rollout

---

## Example Serialized Flow

1. Device creates a transaction
2. Transaction is serialized into payload
3. Envelope is added
4. Payload is compressed if needed
5. Checksum is calculated
6. Packet is transmitted over radio
7. Receiver validates and deserializes
8. Transaction enters reconciliation pipeline

---

## Security Considerations

- Serialization order is deterministic to prevent signature ambiguity
- Sensitive fields are encrypted before serialization
- No private keys are ever serialized
- Metadata leakage is minimized

---

## Summary

Serialization is the backbone of Seed’s offline-first mesh protocol. By prioritizing compactness, determinism, and resilience, Seed ensures that financial data can move reliably across disconnected environments while preserving consistency, security, and future extensibility.
