# Serialization Format Specification

This document defines how Seed devices serialize, compress, transmit, and reconstruct data across the offline-first mesh network. Serialization is a critical layer that ensures messages remain small, reliable, secure, and interoperable across heterogeneous hardware with extreme bandwidth and power constraints.

---

## 1. Goals of the Serialization Layer

The serialization format is designed to:

- Minimize data size for low-bandwidth radio links
- Support offline-first, delay-tolerant synchronization
- Preserve deterministic behavior across devices
- Enable forward compatibility and extensibility
- Allow graceful degradation on low-memory hardware
- Maintain security and integrity of transmitted data

Serialization must function reliably in environments with packet loss, intermittent connectivity, and long propagation delays.

---

## 2. Supported Serialization Formats

Seed supports **multiple serialization formats**, selected dynamically based on device capability and link conditions.

### Primary Formats

- **Compact Binary Format (Primary)**
- **JSON (Secondary / Debug / Interop)**

Binary encoding is used for production mesh traffic. JSON is used for debugging, development, testing, and interoperability with external systems.

---

## 3. Binary Serialization Format (Primary)

### Overview

The binary format is a compact, schema-driven encoding optimized for:

- Low payload size
- Predictable parsing
- Minimal heap allocation
- Deterministic decoding

### General Structure

Each serialized message follows this structure:

- Message Header
- Message Metadata
- Payload Body
- Integrity Footer

### Message Header Fields

- Protocol version (1 byte)
- Message type (1 byte)
- Serialization format ID (1 byte)
- Payload length (2 bytes)
- Flags (1 byte)

### Metadata Fields (Variable)

- Device ID hash
- Lamport clock
- Message sequence number
- Optional group or ledger context

Metadata fields are ordered deterministically and omitted if not required for the message type.

---

## 4. Payload Encoding Rules

### Field Encoding

- Integers: Variable-length encoding (LEB128-style)
- Floats: Fixed 32-bit IEEE format
- Strings: UTF-8 with length prefix
- Booleans: Single-bit flags
- Arrays: Length-prefixed followed by ordered elements
- Maps: Sorted key-value pairs for deterministic parsing

### Ordering Rules

- All fields must appear in schema-defined order
- Optional fields must appear only if present
- Field absence must not shift positional meaning

This guarantees that identical inputs always produce identical serialized outputs.

---

## 5. JSON Serialization Format (Secondary)

### Purpose

JSON serialization is used for:

- Developer tooling
- Simulation and testing
- External system bridges
- Human-readable inspection

JSON is **never used for production radio traffic** except in debug modes.

### JSON Requirements

- UTF-8 encoding
- Strict schema validation
- Sorted object keys
- No floating-point rounding variance
- Explicit null handling

JSON messages mirror the binary schema exactly to avoid divergence.

---

## 6. Compression Strategy

### Compression Goals

- Reduce radio airtime
- Minimize battery consumption
- Avoid CPU-intensive algorithms

### Supported Compression

- Lightweight dictionary-based compression
- Field elision for repeated values
- Delta encoding for sequential messages
- Optional run-length encoding for arrays

Compression is applied **after serialization** and **before encryption**.

---

## 7. Fragmentation and Reassembly

Because radio packets have strict size limits:

- Messages may be split into fragments
- Each fragment includes:
  - Message ID
  - Fragment index
  - Total fragment count
- Fragments may arrive out of order
- Reassembly buffers are size-limited and time-bound

Incomplete messages are discarded safely without corrupting state.

---

## 8. Backward and Forward Compatibility

### Versioning Rules

- Every message includes a protocol version
- Devices must reject unsupported major versions
- Minor versions may introduce optional fields
- Unknown fields must be safely ignored

### Schema Evolution

- Fields may be added but never reordered
- Deprecated fields remain readable indefinitely
- Field IDs are never reused

This allows long-lived devices to interoperate across generations.

---

## 9. Error Handling

### Serialization Errors

- Invalid length
- Unknown message type
- Malformed payload
- Unsupported encoding

Invalid messages are:

- Rejected safely
- Logged locally
- Never forwarded to peers

### Corruption Detection

- Length validation
- Structural sanity checks
- Integrity verification (see next section)

---

## 10. Integrity and Validation

Every serialized message includes:

- CRC or checksum (unencrypted)
- Cryptographic signature (encrypted layer)

Checksums detect accidental corruption. Signatures detect tampering or forgery.

Messages failing validation are discarded before reaching higher protocol layers.

---

## 11. Interaction with Security Layer

Serialization occurs in the following order:

1. Application constructs message object
2. Message is serialized (binary or JSON)
3. Serialized bytes are compressed
4. Compressed payload is encrypted
5. Encrypted payload is transmitted

On receipt, this process is reversed exactly.

---

## 12. Performance Targets

- Serialization time: < 5 ms per message on low-power MCU
- Memory overhead: < 2 KB peak usage
- Typical transaction message size: < 200 bytes compressed
- Fragment reassembly buffer: capped and configurable

---

## 13. Example Serialized Flow (Conceptual)

Transaction object → Binary encoding → Compression → Encryption → Radio transmission → Decryption → Decompression → Parsing → Ledger application

Every device performing this pipeline deterministically arrives at the same reconstructed message.

---

## 14. Security Considerations

- Serialization does not expose plaintext secrets
- No dynamic code execution or deserialization hooks
- Strict bounds checking on all inputs
- Malformed data cannot cause memory corruption

---

## 15. Summary

Seed’s serialization format is purpose-built for extreme environments: low power, low bandwidth, offline operation, and high security. By combining deterministic binary encoding, optional JSON interoperability, lightweight compression, and strict validation, Seed enables reliable financial communication without relying on the internet or centralized infrastructure.

This serialization layer is a foundational component enabling the entire Seed network to function securely and consistently at global scale.
