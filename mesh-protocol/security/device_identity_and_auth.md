# Mesh Protocol – Key Exchange

This document defines how Seed devices securely establish cryptographic trust with one another in a fully offline, peer-to-peer mesh network. Because Seed operates without centralized servers, continuous internet access, or trusted authorities, key exchange must be local, resilient, and secure against interception, replay, and impersonation.

---

## 1. Objectives of Key Exchange

The key exchange mechanism must:

- Enable two Seed devices to securely communicate without prior contact
- Function fully offline with no internet or central server
- Prevent impersonation and man-in-the-middle attacks
- Support long-lived device identities
- Allow re-keying and trust revocation
- Minimize computational and power cost

---

## 2. Cryptographic Foundations

Each Seed device is provisioned with the following cryptographic materials at manufacture or initialization:

- A unique device identity key pair:
  - Private Key (never leaves secure element)
  - Public Key (shareable)
- A device identifier derived from the public key hash
- Secure random number generator (hardware-backed)

Key algorithms (initial reference set):

- Elliptic Curve Cryptography (ECC)
- Curve: X25519 or secp256r1
- Hash: SHA-256
- Symmetric encryption: AES-256-GCM

---

## 3. Identity Model

Seed uses **device-centric identity**, not user-centric identity.

- Each physical device is a cryptographic identity
- Users authenticate locally to their device (fingerprint, PIN, etc.)
- Devices trust other devices, not accounts or phone numbers

This avoids reliance on government IDs, SIM cards, or online registries.

---

## 4. Trust Levels Between Devices

Each peer device relationship exists in one of the following states:

- Unknown: No cryptographic interaction yet
- Handshaking: Key exchange in progress
- Trusted: Secure channel established
- Limited Trust: Communication allowed with restrictions
- Revoked: Device explicitly blocked

Trust states are stored locally and shared only when required.

---

## 5. Initial Key Exchange Flow

### Step-by-Step Handshake

1. Device A discovers Device B via mesh beacon
2. Device A sends:
   - Public key
   - Device ID
   - Supported protocol versions
3. Device B responds with:
   - Its public key
   - Device ID
   - Nonce (random challenge)
4. Device A generates:
   - Ephemeral session key
   - Response signed with its private key
5. Device B verifies signature
6. Both devices derive a shared symmetric session key
7. Secure channel is established

No shared secrets are transmitted.

---

## 6. Ephemeral Session Keys

- Each session uses a fresh ephemeral key
- Session keys are discarded after timeout or power cycle
- Long-term identity keys are never used directly for encryption

This provides **forward secrecy**.

---

## 7. Secure Channel Properties

Once key exchange completes, the secure channel guarantees:

- Confidentiality (encrypted messages)
- Integrity (tamper detection)
- Authenticity (verified sender)
- Replay protection (nonces + counters)

All mesh messages are encrypted after handshake.

---

## 8. Replay and Impersonation Protection

To prevent attacks:

- Each message includes:
  - Session counter
  - Message nonce
  - Sender device ID
- Duplicate counters are rejected
- Invalid signatures immediately downgrade trust

Devices never accept unsigned control messages.

---

## 9. Trust Persistence and Storage

- Trusted peer public keys are stored encrypted at rest
- Stored inside secure element when available
- Trust records include:
  - Device ID
  - Public key fingerprint
  - First-seen timestamp
  - Trust level
  - Last interaction timestamp

---

## 10. Re-Keying and Session Renewal

Session keys are renewed when:

- Session timeout expires
- Power cycle occurs
- Suspicious behavior detected
- Explicit re-key command issued

Re-keying does not require full re-authentication unless trust is revoked.

---

## 11. Trust Revocation

A device may revoke trust when:

- Malicious behavior detected
- Ledger violations occur
- Physical compromise suspected
- User explicitly revokes trust

Revocation effects:

- Secure channel immediately terminated
- Future messages rejected
- Revocation record added to local policy store

---

## 12. Group Context Key Exchange

For group features (e.g., group savings):

- Group-specific symmetric keys are derived
- Keys distributed via encrypted peer-to-peer messages
- Group membership changes trigger key rotation

This prevents ex-members from accessing group data.

---

## 13. Power and Performance Considerations

Key exchange is optimized to:

- Use minimal radio airtime
- Avoid large payloads
- Limit CPU usage
- Prefer hardware acceleration when available

Handshake messages are intentionally compact.

---

## 14. Failure Handling

If key exchange fails:

- Devices revert to untrusted state
- Retry occurs with exponential backoff
- Failure logs stored locally
- No plaintext fallback is allowed

Security is never degraded for availability.

---

## 15. Future Extensions

Planned enhancements include:

- Trust score–weighted key acceptance
- Multi-hop trust delegation
- Zero-knowledge device attestations
- Post-quantum key exchange readiness

---

## 16. Summary

Seed’s key exchange protocol enables secure, offline, peer-to-peer communication without central authorities. By combining device-based identity, strong cryptography, ephemeral session keys, and deterministic trust rules, Seed ensures secure financial coordination even in the most disconnected environments.

This protocol forms the cryptographic foundation of the entire Seed mesh network.
