# Data Encryption Strategy for Seed

This document describes how Seed protects sensitive financial data across device storage, mesh communication, and offline synchronization. Seed operates without servers or internet access, making local encryption, secure key handling, and tamper-resistant storage core security requirements. The system is designed so that even if a device is lost, stolen, or forcibly accessed, no meaningful user data can be extracted.

---

# 1. Encryption Goals

- Protect all financial data at rest on Seed devices.
- Ensure messages transmitted over the mesh network cannot be intercepted or altered.
- Prevent any party (including local attackers, thieves, or adversarial nodes) from reading ledger contents without proper keys.
- Provide tamper resistance even with low-cost hardware.
- Enable secure multi-device syncing without needing online infrastructure.
- Prevent impersonation or transaction forgery.
- Preserve user privacy, anonymity, and safety in politically sensitive or high-risk environments.

---

# 2. Threat Model Summary

Seed must protect against:

- Physical theft of devices.
- Extraction of flash memory or debugging pins.
- Radio interception of LoRa packets.
- Malicious nodes injecting fake transactions.
- Replay of old messages.
- Offline brute-force attempts against stored data.
- Tampering during group savings, trust-score updates, and ledger merges.

Seed does not assume:

- Users have internet.
- Devices have secure cloud backup.
- Devices have trusted execution environments (high-end TEEs).

Therefore, Seed must rely on strong local encryption and deterministic verification logic.

---

# 3. Encryption Layers

Seed uses a three-layer protection model.

## 3.1 Storage Encryption (Data at Rest)

All sensitive data stored on the device is encrypted using:

- AES-256 in GCM mode
- Keys stored inside a Secure Element chip
- Unique per-device master key
- Additional derived keys for:
  - ledger state
  - user identity
  - fingerprint templates
  - transaction history

The secure element prevents extraction of keys even with physical access.

Encrypted storage includes:

- Ledger database
- User balances
- Group savings state
- Trust score history
- Private keys for signing
- Fingerprint hashes
- Cached offline sync messages

Unencrypted storage includes only:

- Device configuration
- Firmware binaries
- Radio settings

## 3.2 Mesh Transmission Encryption (Data in Transit)

Every mesh packet is encrypted end-to-end using:

- XChaCha20-Poly1305 or AES-GCM
- Nonce derived from Lamport clock and device ID
- Message authentication codes (MACs)

This ensures:

- No attacker can read transaction contents
- No attacker can modify packets unnoticed
- No attacker can impersonate another device

## 3.3 Application-Level Encryption

High-level structures (transactions, trust updates, group deposits) are additionally signed using:

- Ed25519 or P-256 signatures
- Per-device private signing key
- Public keys broadcast openly for verification

Even if mesh encryption were broken, signatures protect integrity.

---

# 4. Key Management

## 4.1 Key Types

Seed devices store several cryptographic keys:

- Device identity keypair (public is shared, private never leaves secure element)
- Ledger encryption key
- Transaction signing key
- Group-savings shared keys (optional future feature)
- Mesh session keys

## 4.2 Key Generation

Keys are generated:

- On-device
- Inside the secure element
- Without external input
- Without ever exposing private keys in RAM

## 4.3 Key Backup

Because Seed is offline-first:

- Keys cannot rely on cloud backup
- Users may optionally export encrypted backup phrases
- Backup requires fingerprint + PIN (two-factor offline auth)
- Backup data is encrypted with Argon2-derived keys

---

# 5. Encryption of Ledger and Transactions

## 5.1 Transaction Encryption Process

When a transaction is created:

1. Device increments Lamport clock.
2. Device constructs transaction object.
3. Device signs transaction with private signing key.
4. Transaction is encrypted with ledger encryption key.
5. Ciphertext is stored in local ledger file.
6. Encrypted packet version is sent across mesh.

## 5.2 Ledger Encryption Format

The ledger file uses:

- AES-GCM envelopes per entry
- Nonces derived from transaction ID
- Authentication tag appended to each blob

This ensures:

- Tamper detection
- Replay detection
- Integrity validation
- Confidentiality even on stolen hardware

---

# 6. Mesh Network Encryption

## 6.1 Packet Structure

A minimal encrypted mesh packet contains:

- Header (unencrypted)
  - sender device ID
  - message type
  - protocol version
- Encrypted payload
  - transaction or sync data
- MAC authentication tag

## 6.2 Replay Protection

Seed prevents replay attacks using:

- Lamport clock window enforcement
- Duplicate packet detection
- Nonce uniqueness requirements
- Ledger merge logic rejecting older conflicting states

## 6.3 Forward Secrecy (Optional Future Feature)

Seed can later adopt:

- Double ratchet mechanisms
- Per-hop session keys

This increases security in long-lived networks.

---

# 7. Secure Element Responsibilities

The secure element chip handles:

- Key storage
- Random number generation
- AES encryption/decryption
- Signature creation
- Tamper resistance
- Self-destruct behavior upon brute-force attempts
- Response rate limiting

This hardware is essential for:

- Protecting low-income users from device theft risks
- Ensuring attackers cannot take funds by copying phones or device memory
- Maintaining trust in offline environments

---

# 8. Emergency Wipe Encryption Strategy

If a user activates panic mode:

1. Device wipes ledger encryption key from secure element.
2. Encrypted data becomes unrecoverable.
3. Fingerprint templates are deleted.
4. Device enters locked state until re-provisioned.

Because data is encrypted at rest, wiping keys is instant and secure.

---

# 9. Compliance and Regional Requirements

Seed encryption follows:

- NIST AES recommendations
- FIPS 140-3 compatible secure-element hardware
- EU GDPR principles of data minimization
- Standards for offline mobile money in humanitarian deployments

These compliance considerations allow Seed to be piloted safely in:

- Refugee camps
- Disaster zones
- Remote regions with governance risk

---

# 10. Future Enhancements

Seed’s encryption framework can expand to support:

- Zero-knowledge proofs for private balances
- Secure multi-party computation for community banking
- Encrypted group wallets
- Mix-net style anonymity routing
- Privacy-preserving trust-score updates

---

# 11. Summary

Seed’s encryption system is designed for the most challenging environments on Earth. By combining:

- AES-GCM encrypted storage
- End-to-end encrypted mesh packets
- Digital signatures on all transactions
- Secure hardware for key management

Seed ensures that all financial activity remains private, tamper-proof, and secure even without internet, servers, or traditional banking infrastructure. This cryptographic foundation is essential for creating a safe, global, offline-first financial platform.
