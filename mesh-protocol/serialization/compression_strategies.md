# Compression Strategies

This document defines how Seed minimizes data size for all mesh protocol messages to operate efficiently in low-bandwidth, low-power, and high-latency environments. Compression is essential to ensure reliable communication over LoRa-based mesh networks while preserving security, determinism, and data integrity.

---

## 1. Objectives of Compression

Seed’s compression layer is designed to achieve the following goals:

- Reduce packet size to fit within LoRa payload constraints.
- Minimize airtime to conserve battery and reduce collision risk.
- Enable reliable syncing in environments with packet loss.
- Preserve deterministic decoding across all devices.
- Avoid heavy CPU or memory usage on constrained hardware.

Compression must be lightweight, predictable, and fully reversible.

---

## 2. Constraints and Design Principles

Seed operates under strict constraints:

- Very limited bandwidth (often < 300 bytes per packet).
- Devices may have limited RAM and flash storage.
- Messages must remain verifiable and tamper-resistant.
- Compression must not depend on shared external state.

Design principles:

- Prefer structural compression over generic algorithms.
- Use schema-aware encoding rather than blind compression.
- Optimize for repeated patterns common in financial data.
- Fail safely if compressed data cannot be decoded.

---

## 3. Compression Layers

Seed applies compression in multiple layers:

1. Field-level compression
2. Schema-based compaction
3. Optional binary encoding
4. Payload chunking (if required)

Each layer is independent and modular.

---

## 4. Field-Level Compression

### 4.1 Field Name Shortening

Human-readable field names are replaced with short tokens.

Examples:

- `transaction_id` → `t`
- `device_id` → `d`
- `lamport_clock` → `l`
- `amount` → `a`
- `signature` → `s`

A shared, versioned field dictionary ensures all devices interpret tokens identically.

---

### 4.2 Numeric Encoding

Numeric values are encoded efficiently:

- Integers use variable-length encoding.
- Monetary values are stored as fixed-point integers (e.g., cents).
- Boolean flags use single-bit encoding.

This avoids expensive string parsing.

---

## 5. Schema-Based Compression

### 5.1 Message Type Templates

Each message type has a predefined structure.

Examples:

- Transaction message
- Ledger sync message
- Trust score update
- Group savings update

Instead of transmitting field names, devices transmit:

- Message type ID
- Ordered list of values

This reduces redundancy and ensures deterministic decoding.

---

### 5.2 Optional Fields Mask

Optional fields are represented using a bitmask.

- Each bit represents presence or absence of a field.
- Devices decode only fields marked as present.

This avoids sending null or empty values.

---

## 6. Binary Encoding (Optional)

For environments requiring maximum efficiency, Seed supports binary serialization.

Characteristics:

- Fixed field ordering.
- Explicit length prefixes.
- No delimiters or whitespace.
- Endianness explicitly defined.

Binary encoding is optional and negotiated per network.

---

## 7. Chunking and Fragmentation

If a compressed payload exceeds maximum packet size:

- The message is split into numbered fragments.
- Each fragment includes:
  - Message ID
  - Fragment index
  - Total fragment count
  - Checksum

Fragments are reassembled before validation and processing.

---

## 8. Compression and Security Interaction

Compression is applied **before encryption**.

This ensures:

- Maximum compression efficiency.
- Encrypted payloads do not reveal structure.
- Integrity checks validate decompressed content.

Order of operations:

1. Construct message
2. Compress payload
3. Encrypt payload
4. Add checksum and metadata
5. Transmit

---

## 9. Error Handling and Resilience

If decompression fails:

- The message is rejected.
- An error report message may be generated.
- The device does not apply partial updates.

Devices never guess or infer missing data.

---

## 10. Determinism Guarantees

Compression must be deterministic:

- Same input → same compressed output
- Same compressed input → same decompressed output

This is critical for ledger consistency and conflict resolution.

All compression algorithms are versioned to prevent incompatibility.

---

## 11. Performance Considerations

Compression algorithms are chosen to:

- Run in bounded time.
- Use minimal heap allocations.
- Avoid recursion.
- Be safe on low-frequency microcontrollers.

Devices may disable advanced compression if power is critically low.

---

## 12. Future Enhancements

Planned extensions include:

- Adaptive compression based on link quality.
- Delta compression for repeated ledger syncs.
- Merkle-based state diff transmission.
- Compression profiles for different deployment contexts.

All enhancements must preserve backward compatibility.

---

## 13. Summary

Seed’s compression strategy enables secure, reliable financial communication over extremely constrained networks. By combining schema-aware compaction, efficient encoding, and deterministic decoding, Seed ensures that every byte transmitted carries maximum value while maintaining system integrity, security, and global consistency.
