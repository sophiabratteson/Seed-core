# Message Signing

This document defines how Seed devices cryptographically sign all messages and transactions exchanged across the mesh network. Message signing ensures authenticity, integrity, non-repudiation, and protection against tampering in a fully offline, decentralized environment.

---

## 1. Purpose of Message Signing

Message signing in Seed serves four critical goals:

1. Verify that a message truly originated from a legitimate Seed device
2. Ensure that message contents were not altered in transit
3. Prevent impersonation or spoofing of devices
4. Enable trust evaluation and accountability without centralized servers

Because Seed operates without continuous internet connectivity, all security guarantees must be enforced locally and deterministically on each device.

---

## 2. What Is Signed

The following data types MUST be signed before transmission:

- Financial transactions
- Ledger synchronization messages
- Group savings updates
- Trust score updates
- Device status or heartbeat messages
- Error and anomaly reports

Unsigned messages are rejected by default unless explicitly allowed for non-sensitive system broadcasts.

---

## 3. Cryptographic Model

Each Seed device is provisioned with a unique asymmetric key pair:

- Private Key
  - Generated on-device during secure provisioning
  - Never leaves the device
  - Stored inside the secure element or protected storage
- Public Key
  - Shared with other devices during mesh discovery
  - Used to verify signatures

Seed uses asymmetric cryptography to avoid shared secrets and enable device-level identity.

Recommended algorithms:

- Elliptic Curve Digital Signature Algorithm (ECDSA)
- Curve: secp256r1 or ed25519 (implementation-dependent)

---

## 4. Signature Creation Process

When a device prepares a message:

1. The message payload is serialized into a canonical format
2. A cryptographic hash of the payload is generated
3. The hash is signed using the device’s private key
4. The signature is appended to the message metadata

The payload itself is not encrypted by signing alone; signing guarantees integrity and authenticity, not confidentiality.

---

## 5. Signature Verification Process

Upon receiving a message:

1. The receiver extracts the sender’s device ID
2. The sender’s public key is retrieved from the local trust store
3. The message payload is hashed using the same algorithm
4. The signature is verified against the hash and public key
5. If verification fails, the message is discarded and logged

Verification must be deterministic and offline-capable.

---

## 6. Canonical Message Format

To ensure consistent verification across devices, Seed defines a canonical message structure:

- Fixed field ordering
- Explicit data types
- No optional fields during signing
- No whitespace or formatting ambiguity

This prevents signature failures caused by serialization differences.

---

## 7. Replay Attack Protection

Message signing alone does not prevent replay attacks. Seed combines signing with:

- Lamport logical timestamps
- Unique message identifiers
- Ledger state references (when applicable)

Messages with stale timestamps or duplicate identifiers are rejected even if signatures are valid.

---

## 8. Interaction With Ledger Engine

For financial transactions:

- Signature verification occurs before transaction validation
- Invalid signatures result in immediate rejection
- Valid signatures do not guarantee acceptance; ledger rules still apply

Signature status is stored as metadata alongside transaction records for auditability.

---

## 9. Key Rotation and Revocation

Seed supports key lifecycle management:

- Devices may rotate keys periodically or after compromise
- Old keys are retained for historical verification
- Revocation notices are signed and propagated across the mesh
- Trust scores may be impacted by abnormal key behavior

No central authority is required for revocation enforcement.

---

## 10. Failure Handling

If message signing or verification fails:

- The message is discarded
- The event is logged locally
- Repeated failures may reduce trust score
- Severe anomalies may trigger device isolation

Devices never attempt to “fix” invalid signatures.

---

## 11. Security Guarantees

Message signing ensures:

- Authentic device identity
- Immutable transaction history
- Resistance to tampering and forgery
- Deterministic verification across all nodes
- Offline-first cryptographic security

Even in hostile or disconnected environments, Seed devices can independently verify the legitimacy of all critical communications.

---

## 12. Summary

Message signing is the cryptographic backbone of Seed’s decentralized trust model. By requiring every meaningful message to be signed and verified locally, Seed eliminates reliance on centralized servers while maintaining strong security guarantees. This design enables a resilient, offline-capable financial network that remains secure even under extreme conditions.
