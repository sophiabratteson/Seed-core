# Binary Serialization Format

This document defines the binary serialization format used by Seed for transmitting data efficiently across low-bandwidth, offline-first mesh networks. Binary encoding is essential for minimizing packet size, reducing transmission time, conserving power, and improving reliability in constrained environments.

---

## 1. Purpose of Binary Serialization

Binary serialization is used when:
- Transmitting data over LoRa or similar low-bandwidth radios
- Synchronizing ledgers between devices
- Exchanging heartbeat, trust score, and group savings updates
- Operating in high-latency or lossy environments

Binary encoding complements JSON serialization by providing a compact, machine-optimized alternative when human readability is not required.

---

## 2. Design Goals

The binary format is designed to:
- Minimize packet size
- Be deterministic and versioned
- Support forward and backward compatibility
- Allow partial parsing and validation
- Be resilient to packet loss and corruption
- Avoid dynamic memory allocation where possible

---

## 3. High-Level Structure

Every binary message follows this structure:

- Header
- Payload
- Integrity Footer

```
| Header | Payload | CRC |
```

---

## 4. Header Format

The header provides metadata required to parse the payload.

| Field | Size (bytes) | Description |
|------|-------------|-------------|
| Protocol Version | 1 | Binary protocol version |
| Message Type | 1 | Enumerated message type |
| Flags | 1 | Compression, encryption, priority flags |
| Payload Length | 2 | Length of payload in bytes |
| Device ID Hash | 4 | Truncated hash of sender device ID |

Total header size: **9 bytes**

---

## 5. Message Type Enumeration

Message types are encoded as single-byte values:

| Value | Message Type |
|------|--------------|
| 0x01 | Transaction Message |
| 0x02 | Ledger Sync Message |
| 0x03 | Heartbeat Message |
| 0x04 | Group Savings Message |
| 0x05 | Trust Score Update |
| 0x06 | Error Report |
| 0x07 | System Control |

---

## 6. Payload Encoding Rules

Payloads follow strict field ordering and fixed-size or length-prefixed fields.

### Common Encoding Rules
- Integers: Little-endian
- Booleans: 1 byte (0x00 or 0x01)
- Strings: Length-prefixed (1 or 2 bytes)
- Arrays: Count-prefixed followed by entries
- Floating point: IEEE 754 (32-bit)

---

## 7. Transaction Payload Format

Example transaction payload:

| Field | Size | Description |
|-----|------|-------------|
| Transaction ID | 16 bytes | UUID |
| Sender ID Hash | 4 bytes | Sender identifier |
| Receiver ID Hash | 4 bytes | Receiver identifier |
| Amount | 4 bytes | Fixed-point integer |
| Lamport Clock | 4 bytes | Logical timestamp |
| Flags | 1 byte | Transaction attributes |

Total typical payload size: **33 bytes**

---

## 8. Compression Strategy

Compression is optional and indicated by header flags.

- Lightweight dictionary-based compression
- Applied only to payload
- Disabled for small messages
- Must be reversible without heap allocation

---

## 9. Encryption Layer

If enabled, payload is encrypted after serialization.

- Header remains unencrypted
- Payload encrypted using symmetric session key
- Authentication tag appended before CRC
- Encryption flag set in header

---

## 10. Integrity and CRC

Every binary message ends with a CRC-16 checksum.

- CRC computed over header + payload
- Detects corruption and truncation
- Messages failing CRC are discarded silently

---

## 11. Fragmentation and Reassembly

If payload exceeds radio MTU:

- Payload is fragmented
- Each fragment includes:
  - Fragment index
  - Total fragment count
- Reassembly occurs before parsing
- Incomplete messages are discarded after timeout

---

## 12. Backward Compatibility

- Protocol version byte governs parsing logic
- Unknown fields are skipped using length prefixes
- Devices may ignore unsupported message types

---

## 13. Example Binary Message Layout

```
[01][02][00][00 21][A3 B2 C1 D0]
[TX_PAYLOAD_BYTES...]
[CRC16]
```

---

## 14. Security Considerations

- Binary parsing uses strict bounds checking
- No trust in payload lengths without validation
- Replay protection enforced at higher protocol layers
- Corrupt or malformed messages never alter state

---

## 15. Summary

Binary serialization enables Seed to function in extreme connectivity environments by minimizing bandwidth usage and power consumption. This format ensures deterministic parsing, secure transmission, and scalable communication across a fully offline mesh financial network.
