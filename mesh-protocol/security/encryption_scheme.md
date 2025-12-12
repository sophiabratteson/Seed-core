# Encryption Scheme

This document defines how the Seed mesh protocol protects data confidentiality and integrity across a fully offline, peer-to-peer network. Because Seed operates without centralized servers or persistent internet connectivity, encryption must be lightweight, resilient, and enforceable entirely at the device level.

---

## 1. Goals of the Encryption Scheme

- Protect transaction data from unauthorized access.
- Ensure messages cannot be altered without detection.
- Prevent eavesdropping on mesh radio communications.
- Enable secure device-to-device communication without online key servers.
- Support long-term offline operation with periodic key refresh.
- Minimize power, memory, and compute overhead.

---

## 2. Threat Model Assumptions

The encryption scheme assumes:

- Attackers may listen to radio traffic.
- Devices may be lost, stolen, or temporarily compromised.
- No always-on trusted authority exists.
- Some devices may behave maliciously.
- Physical access attacks are possible but limited in duration.

The scheme does not assume trusted network infrastructure.

---

## 3. Cryptographic Primitives

Seed uses widely supported, well-audited primitives suitable for embedded systems:

- Symmetric encryption: AES-256-GCM
- Asymmetric encryption: Curve25519 (ECDH)
- Digital signatures: Ed25519
- Hashing: SHA-256
- Key derivation: HKDF-SHA256

These primitives are selected for security, efficiency, and availability on microcontrollers.

---

## 4. Device Identity Keys

Each Seed device generates the following at first boot:

- Device private key (Ed25519)
- Device public key
- Device identifier derived from public key hash

Properties:

- Private key never leaves the device.
- Public key may be shared freely.
- Device ID is deterministic and collision-resistant.

These keys form the root of trust for the device.

---

## 5. Session Key Establishment

When two devices communicate:

1. Devices exchange public keys.
2. An ECDH handshake (Curve25519) derives a shared secret.
3. The shared secret is passed through HKDF.
4. A temporary session key is produced.

Session keys are:

- Short-lived
- Unique per device pair
- Used only for encrypting messages between those two devices

---

## 6. Message Encryption Flow

For every mesh message:

1. Payload is serialized.
2. A unique nonce is generated.
3. Payload is encrypted using AES-256-GCM with the session key.
4. Authentication tag is appended.
5. Message header remains unencrypted for routing.

This provides both confidentiality and integrity.

---

## 7. Transaction-Level Encryption

Transactions stored on-device are encrypted separately from transport encryption.

- Ledger data is encrypted at rest.
- Encryption keys are derived from the device root key.
- Each transaction includes a signed hash.

This ensures:

- Ledger confidentiality if device storage is accessed.
- Tamper detection on stored records.

---

## 8. Group Encryption (Group Savings, Trust Groups)

For group-based features:

- A group symmetric key is generated.
- Group key is encrypted separately for each member using their public key.
- Group messages are encrypted using the group key.

If a member leaves the group:

- A new group key is generated.
- Old member can no longer decrypt future messages.

---

## 9. Replay Attack Protection

Seed prevents replay attacks by:

- Including Lamport timestamps in encrypted payloads.
- Rejecting messages with stale or duplicate timestamps.
- Tracking recent message hashes.

Even encrypted messages cannot be reused maliciously.

---

## 10. Key Rotation and Expiry

Keys are rotated under the following conditions:

- Device reboot after long offline period
- Detection of suspicious behavior
- Manual user-triggered reset
- Scheduled lifetime expiration

Old keys are securely wiped from memory.

---

## 11. Lost or Stolen Device Handling

If a device is suspected compromised:

- Local encryption keys are wiped via emergency protocol.
- Mesh peers mark the device ID as revoked.
- Future messages to that device are refused.

This prevents further access to encrypted data.

---

## 12. Performance Considerations

The encryption scheme is designed to:

- Operate on low-power microcontrollers.
- Minimize RAM usage.
- Avoid expensive public-key operations during normal operation.
- Use symmetric encryption for most traffic.

Asymmetric crypto is limited to session setup.

---

## 13. Failure Modes and Recovery

If encryption fails:

- Message is dropped.
- Error report message may be generated.
- No partial plaintext is processed.

Devices always fail safely.

---

## 14. Future Enhancements

Planned extensions include:

- Post-quantum key exchange options
- Zero-knowledge proofs for selective disclosure
- Hardware-backed secure enclaves for all cryptographic operations
- Anonymous credential systems layered on top of encryption

---

## 15. Summary

Seed’s encryption scheme enables secure, private, and resilient financial communication in environments without internet or centralized trust. By combining device identity keys, session-based encryption, and deterministic validation, the mesh network remains confidential and tamper-resistant even in hostile or disconnected environments.
