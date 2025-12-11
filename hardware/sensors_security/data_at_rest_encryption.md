# Data-at-Rest Encryption

This document describes how Seed devices protect all sensitive information stored locally on the device. Because Seed is designed for low-connectivity and high-risk environments — including areas with theft, informal markets, and no formal identity systems — strong encryption at rest is a non-negotiable requirement. This protects the user’s financial history, identity keys, trust-score values, group-savings participation, and AI-assistant behavioral data.

---

# 1. Objectives

- Ensure that no readable user data remains on the device without cryptographic protection.
- Prevent attackers from reconstructing ledger history or user identities if the device is stolen.
- Support rapid “emergency wipe” features without compromising data integrity.
- Enable secure cold-storage of long-term financial history without external infrastructure.
- Protect device-identity keys used for signing transactions and validating trust-score logic.

---

# 2. Threats Addressed

- Device theft in markets, refugee camps, disaster zones, or dense urban environments.
- Physical tampering to extract the flash chip or probe internal buses.
- Attempts to clone a device identity.
- Reconstruction of ledger transactions for surveillance or extortion.
- Attacks aimed at modifying internal data (trust score, group fund amounts, wallet balance).

---

# 3. Encryption Architecture

Seed uses a layered encryption model:

## 3.1 Hardware Root of Trust
- Provided by the **secure element chip (ATECC608A or SE050-class)**.
- Stores master root keys that never leave the chip.
- All disk-encryption keys are derived inside the secure element using on-chip KDF functions.

## 3.2 Storage Encryption
All persistent storage is encrypted, including:
- Ledger entries
- Transaction history
- Group savings indexes
- Device configuration data
- User preferences
- Cached AI-model personalization data

### Algorithm
- **AES-256-GCM** for authenticated encryption
- 96-bit nonce per block
- 128-bit authentication tag to detect tampering

### Key Derivation
- Master key stored only inside secure element.
- File encryption keys derived using:
  - Device_ID
  - File namespace
  - Rolling monotonic counter to ensure forward secrecy

---

# 4. File Layout and Encryption Zones

The device separates storage into independently encrypted zones:

## 4.1 “Identity Zone”
- Stores device private key (never exported), trust-score seed values, key-rotation counters.
- Encrypted with a unique hardware key bound to secure element identity.

## 4.2 “Ledger Zone”
- Stores append-only ledger blocks.
- Each block encrypted separately so corruption is contained.
- Old blocks can be checkpointed and compressed.

## 4.3 “User Data Zone”
- Stores settings, training data for on-device AI model, language preferences.
- Lower security level, but still AES-256 encrypted.

## 4.4 “High-Risk Zone”
- Temporary data used for pending transactions.
- Automatically wiped after sync or device shutdown.

---

# 5. Emergency Wipe Logic

Seed includes a fast-response emergency wipe mechanism to protect users in dangerous or coercive situations.

## 5.1 Trigger Methods
- Entering a special “decoy fingerprint.”
- Holding two buttons for >3 seconds.
- Entering a predetermined pass gesture.

## 5.2 Wipe Procedure
- Secure element invalidates key derivation path.
- All encrypted storage instantly becomes unrecoverable.
- Decoy profile is displayed (empty balance, fake transaction history).

## 5.3 Recovery
- Only possible with seed-phrase backup (optional feature).
- Otherwise, wipe is cryptographically irreversible.

---

# 6. Secure Boot Integration

- The encryption system binds to secure boot.
- Firmware must be verified before the secure element releases any key material.
- Prevents attackers from booting modified OS images to dump encrypted storage.

---

# 7. Anti-Tamper Measures

- Voltage glitch detection.
- Case-opening sensor linked to secure element.
- Attempts to probe hardware reset the key ladder.
- Debug interfaces (JTAG/SWD) are permanently fused off.

---

# 8. Performance Considerations

- AES-GCM accelerated by hardware when available.
- Encryption is applied in fixed-size blocks to support e-ink’s low-power wake cycles.
- Journaled writes prevent corruption when battery dies mid-write.
- Filesystem optimized for low-capacity flash (4–16 MB typical).

---

# 9. Compliance and Privacy

Data-at-rest encryption supports compliance with:

- GDPR data minimization principles.
- ISO/IEC 27040 storage security guidelines.
- Emerging digital-identity frameworks in developing economies.

It also protects users from:
- Government overreach in unstable or authoritarian regions.
- Criminal targeting.
- Informal-sector exploitation.

---

# 10. Future Enhancements

- Post-quantum key exchange for long-term protection.
- Secure multi-party recovery system for shared business accounts.
- Encrypted differential backups for mesh-based “community vaults.”
- Ledger compression using Merkle-tree commitments.

---

# 11. Summary

Seed’s data-at-rest encryption is designed for extreme environments where conventional banking cannot operate. By binding storage to a secure element, encrypting all ledger and identity data, and providing fast emergency-wipe capability, Seed ensures users maintain full control of their financial information — even under theft, coercion, or power instability.
