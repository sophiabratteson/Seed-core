# Storage Encryption

This document defines how Seed encrypts all sensitive data stored locally on a device. Because Seed operates without guaranteed connectivity and may be deployed in high-risk environments, strong local encryption is required to protect users if a device is lost, stolen, or physically compromised.

---

## Purpose

The goals of storage encryption in Seed are:

- Protect user balances, transaction history, and trust scores
- Prevent unauthorized access to financial data
- Ensure data remains secure even if hardware is captured
- Enable safe offline-first operation without relying on cloud services
- Support emergency wipe and device lockout scenarios

Encryption is mandatory for all persistent data on the device.

---

## Data Covered by Encryption

All data written to non-volatile storage MUST be encrypted, including:

- Ledger data (transactions, balances, checkpoints)
- Trust score records
- Group savings participation data
- Device identity keys and credentials
- Configuration files containing security settings
- Cached AI personalization data
- Sync metadata and message logs

No sensitive data is ever stored in plaintext.

---

## Encryption Model

Seed uses a **layered encryption approach**:

- Hardware-backed root key (secure element)
- Device-level encryption key
- File-level encryption contexts

This design ensures that even if one layer is compromised, higher layers remain protected.

---

## Key Hierarchy

### 1. Root Device Key

- Generated at manufacturing or first boot
- Stored inside a secure element or trusted execution environment
- Never readable by application code
- Used only to derive lower-level keys

### 2. Device Storage Key

- Derived from the root key using a key derivation function (KDF)
- Unique per device
- Used to encrypt all persistent storage
- Automatically rotated on major security events

### 3. Session Keys (Optional)

- Short-lived keys derived for specific operations
- Used for temporary buffers or active transactions
- Destroyed on power loss or reboot

---

## Encryption Algorithms

Recommended algorithms:

- AES-256-GCM for data at rest
- ChaCha20-Poly1305 for low-power devices
- HKDF for key derivation
- SHA-256 or SHA-3 for hashing and integrity checks

Algorithm selection may vary by hardware capability, but minimum security strength must be maintained.

---

## Storage Architecture

Encrypted storage is organized as follows:

- Each file or data block is encrypted independently
- Metadata includes:
  - Nonce / initialization vector
  - Authentication tag
  - Version identifier
- No plaintext headers revealing content type

This prevents pattern leakage and limits the impact of partial corruption.

---

## Read / Write Flow

### Writing Data

1. Application prepares plaintext data
2. Encryption module requests storage key
3. Data is encrypted in memory
4. Ciphertext is written to flash or persistent storage
5. Plaintext buffers are securely wiped from RAM

### Reading Data

1. Encrypted data is loaded from storage
2. Authentication tag is verified
3. Data is decrypted in memory
4. Plaintext is passed to application logic
5. Plaintext buffers are cleared after use

---

## Integrity and Tamper Detection

- All encrypted data includes authentication tags
- Failed decryption immediately flags corruption or tampering
- Repeated failures trigger security escalation:
  - Device lockout
  - Emergency wipe (if configured)
  - Alert flags for audit

Seed never attempts to “repair” encrypted data silently.

---

## Emergency Wipe Support

Storage encryption enables instant wipe by:

- Destroying the device storage key
- Invalidating derived keys
- Rendering all stored ciphertext unrecoverable

This operation completes in milliseconds and does not require overwriting storage.

---

## Backup and Recovery Considerations

- Encrypted backups may be shared via mesh sync
- Backups are encrypted with recipient-specific keys
- Devices cannot decrypt backups without proper authorization
- Lost devices cannot be restored without cryptographic approval

There is no global master key.

---

## Performance Considerations

- Encryption is optimized for low-power hardware
- Bulk operations use streaming encryption
- Idle-time rekeying minimizes user impact
- Cryptographic operations are hardware-accelerated when possible

Security is never traded for performance.

---

## Threat Model Coverage

Storage encryption protects against:

- Physical device theft
- Flash memory extraction
- Cold boot attacks
- Offline brute-force attempts
- Unauthorized firmware access

It does NOT protect against:

- Compromised firmware with valid keys
- User-authorized data sharing
- Side-channel attacks beyond hardware capabilities

These are addressed in other security layers.

---

## Compliance Alignment

The storage encryption design aligns with:

- Data minimization principles
- Financial privacy requirements
- Humanitarian deployment standards
- Best practices for offline financial systems

This ensures Seed can be deployed responsibly across diverse regulatory environments.

---

## Summary

Storage encryption is a foundational security layer in Seed. By combining hardware-backed keys, strong cryptography, and strict handling rules, Seed ensures that user data remains protected even in the most hostile conditions. Without encryption, an offline financial system cannot be trusted — with it, Seed becomes resilient, private, and secure by design.
