# Checksums and Integrity

This document defines how Seed’s mesh protocol detects corruption, tampering, truncation, and accidental bit-flips in messages sent over unreliable, low-bandwidth radio links.

Seed uses **layered integrity**:
- **Link-layer integrity** (radio hardware/driver CRC, if available)
- **Packet-level checksum** (fast corruption detection)
- **Message authentication** (cryptographic integrity + authenticity)
- **Ledger-level integrity** (hash chaining / checkpoints for history consistency)

This doc focuses on the **packet/message integrity layer** for mesh transport.

---

## 1. Goals

- Detect accidental corruption (noise, partial packets, dropped bytes).
- Detect replay or modification attempts (tampering).
- Allow nodes to reject bad packets cheaply (before heavy parsing).
- Keep overhead small (LoRa payload limits).
- Keep behavior deterministic across devices.

Non-goals (for MVP):
- Perfect anonymity against a global adversary.
- Full privacy without cryptography (privacy requires encryption/MAC).

---

## 2. Where Integrity Lives in the Stack

Seed message path:

1. **Radio driver** receives raw bytes (may already have a hardware CRC).
2. **Packet framing** checks length + version + packet checksum.
3. **Message parsing** validates schema and field constraints.
4. **Authentication** verifies MAC/signature.
5. **Ledger validation** checks transaction rules.

**Reject as early as possible**:
- If packet checksum fails → drop immediately.
- If MAC/signature fails → drop and optionally rate-limit the sender.
- If schema invalid → drop and optionally send an error report.

---

## 3. Integrity Mechanisms Overview

Seed uses these integrity fields:

### 3.1 Packet Checksum (fast, non-cryptographic)
- Purpose: detect random corruption quickly.
- Recommended: **CRC32C** (Castagnoli) or **CRC16-CCITT** for smaller overhead.
- Output:
  - CRC16: 2 bytes overhead
  - CRC32C: 4 bytes overhead

**Rule**: The checksum covers the packet header + payload (excluding the checksum field itself).

### 3.2 Message Authentication Code (cryptographic)
- Purpose: detect tampering and authenticate sender (if shared keys exist).
- Recommended for MVP: **HMAC-SHA256**, truncated to 16 bytes to save space.
- Output: 16 bytes overhead (128-bit tag).

**Rule**: The MAC covers the canonical bytes of the message fields (or the raw payload bytes) and includes a domain separator.

### 3.3 Digital Signatures (optional, heavier)
- Purpose: non-repudiation, no shared secrets needed (public key verification).
- Recommended later: Ed25519 (64 bytes signature).
- Not required for earliest radio simulations due to bandwidth overhead.

---

## 4. Packet Format (Integrity Fields)

Seed packets should be framed in a small binary header, even if the payload is JSON.

### 4.1 Minimal Frame Layout

- `magic` (2 bytes) — constant to detect misalignment (e.g., 0x53 0x44 "SD")
- `version` (1 byte)
- `msg_type` (1 byte)
- `flags` (1 byte)
- `sender_id` (4 bytes) — short ID (hash prefix or assigned ID)
- `seq` (4 bytes) — sender sequence number (anti-replay + ordering)
- `payload_len` (2 bytes)
- `payload` (N bytes) — JSON or binary
- `checksum` (2 or 4 bytes) — CRC16 or CRC32C over header+payload
- `auth_tag` (0 or 16 bytes) — HMAC tag, if enabled by flags

### 4.2 Flags
- bit 0: `HAS_CRC32` (else CRC16)
- bit 1: `HAS_AUTH_TAG`
- bit 2: `PAYLOAD_JSON` (else binary)
- bit 3: `ACK_REQUIRED`
- other bits reserved

---

## 5. How Nodes Validate Integrity

Nodes validate in this exact order:

### Step 1 — Frame sanity checks
- `magic` matches
- `version` supported
- `payload_len` within max allowed
- total frame length matches expected layout

If any fail: **drop silently**.

### Step 2 — Checksum verification (CRC)
- Compute CRC over bytes `[magic .. end_of_payload]`
- Compare with checksum field

If fail: **drop silently**.

### Step 3 — Authentication verification (MAC/signature)
If `HAS_AUTH_TAG`:
- Look up shared key for `sender_id` (or group key)
- Compute HMAC over `domain || header_fields || payload`
- Compare in constant-time

If fail:
- **drop**
- increment “auth_fail” counter
- optional: temporarily rate-limit that sender

### Step 4 — Parse + schema validation
- Parse JSON (if JSON payload)
- Validate required fields and types
- Check message-specific constraints (see per-message docs)

If fail:
- drop
- optional: send `ERROR_REPORT` if we have a trusted channel and rate limits allow

---

## 6. Canonicalization Rules (to avoid MAC mismatch)

If the MAC is computed over JSON text, different whitespace/key ordering can break verification.

Seed should do one of these:

### Option A (recommended): MAC over raw payload bytes
- Sender computes MAC over the exact payload bytes it sends.
- Receiver verifies MAC over the same bytes it received (after CRC passes).

Pros: simple.
Cons: any gateway that transforms JSON (pretty-print) would break MAC.

### Option B: MAC over canonical JSON encoding
- Use deterministic ordering:
  - keys sorted lexicographically
  - no insignificant whitespace
  - UTF-8 encoding
  - consistent number formatting (e.g., fixed decimal handling)

Pros: robust to re-serialization if canonicalized.
Cons: more implementation complexity.

**MVP recommendation**: Option A.

---

## 7. Anti-Replay and Duplicate Detection

Integrity alone doesn’t stop replay unless you also track freshness.

Seed uses:
- `seq` (sequence number) per sender_id
- `seen_cache` (sliding window) to avoid storing unbounded history

### 7.1 Rules
- Each sender increments `seq` for every message it emits.
- Receiver stores the highest seen `seq` per sender, plus a small bitmap window (e.g., last 64).
- If a message arrives with a `seq` already seen → drop as duplicate.
- If `seq` is too far behind and outside the window → drop as stale.

This prevents simple replay attacks and reduces redundant traffic.

---

## 8. Integrity at the Ledger Layer (Checksums for State)

In addition to per-packet integrity, Seed should maintain ledger-level integrity so nodes can verify they converged.

### 8.1 Checkpoint Hash
Periodically compute:
- `checkpoint_hash = HASH(sorted_tx_ids || sorted_tx_hashes || balances_snapshot_version)`

Nodes can exchange:
- checkpoint hash
- range summaries (e.g., Merkle root later)

If checkpoint hashes differ:
- trigger a targeted resync (request missing tx IDs).

### 8.2 Transaction Hash
Each transaction includes:
- `tx_hash = HASH(canonical_tx_fields)`

This allows detection of “same tx_id different content” corruption/tampering.

---

## 9. Recommended Choices for MVP

To balance “works on tiny devices” + “secure enough to be credible”:

- Packet checksum: **CRC16-CCITT** (2 bytes)
- Authentication: **HMAC-SHA256**, truncated to **16 bytes**
- Replay protection: `sender_id + seq + sliding window`
- Ledger integrity: transaction hash + periodic checkpoint hash

---

## 10. Failure Handling and Observability

Nodes should track counters for:
- `rx_total`
- `rx_crc_fail`
- `rx_auth_fail`
- `rx_parse_fail`
- `rx_accepted`
- `rx_duplicate_dropped`

If the device UI allows:
- show “Signal quality / message health”
- show “Last sync time”
- show “Integrity failures (last 24h)”

This builds trust and helps debugging in field pilots.

---

## 11. Security Notes and Threats Addressed

### Addressed
- Random corruption → CRC detects
- Tampering without key → HMAC detects
- Simple replay → seq/window detects
- Partial/truncated frames → length+CRC detects

### Not fully addressed (future work)
- Key compromise (stolen device keys)
- Advanced traffic analysis
- Sybil attacks (many fake nodes) — needs identity governance + rate limits
- Denial-of-service via radio jamming — operational mitigation needed

---

## 12. Implementation Checklist

- [ ] Implement CRC16 (or CRC32C) in firmware utils
- [ ] Define frame header struct and pack/unpack
- [ ] Add strict bounds checks for payload length
- [ ] Implement constant-time tag comparison
- [ ] Maintain per-sender seq windows (small RAM footprint)
- [ ] Add metrics counters and expose them in logs/UI
- [ ] Add transaction hash + checkpoint hash mechanisms

---

## 13. Summary

Seed’s mesh protocol integrity is built on:
- **CRC** to cheaply detect corruption
- **HMAC/signatures** to prevent tampering
- **Sequence windows** to prevent replay
- **Ledger hashes** to detect divergence over time

This layered approach keeps the system lightweight, field-ready, and credible for offline financial synchronization.
