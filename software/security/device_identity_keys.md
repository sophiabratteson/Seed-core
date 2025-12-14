# Device Identity and Cryptographic Keys

This document defines how each Seed device establishes, stores, and uses a unique cryptographic identity. Device identity is foundational to security, trust scoring, transaction validation, and mesh-network authentication in an offline-first environment.

---

## Purpose of Device Identity

Each Seed device must be able to:

- Prove that it is a legitimate device
- Sign transactions and messages
- Authenticate itself to nearby devices
- Prevent impersonation and replay attacks
- Maintain long-term identity without relying on servers or internet access

Device identity replaces traditional accounts, usernames, or centralized authentication systems.

---

## Device Identity Model

Each Seed device has a **single, permanent cryptographic identity** created at provisioning time.

A device identity consists of:

- A unique Device ID (public identifier)
- A public-private key pair
- Optional device metadata (non-sensitive)

The private key **never leaves the device**.

---

## Key Types Used

### 1. Device Identity Key Pair

- Algorithm: Ed25519 (preferred) or equivalent elliptic curve
- Generated once during device provisioning
- Stored inside secure storage or secure element

Used for:
- Signing transactions
- Signing mesh messages
- Authenticating device during peer discovery

### 2. Session Keys (Ephemeral)

- Derived temporarily during device-to-device communication
- Used to encrypt short-lived message sessions
- Discarded after session ends

Used for:
- Reducing exposure of long-term keys
- Protecting radio traffic confidentiality

---

## Device ID Format

The Device ID is derived from the public key.

Example:

DEVICE_ID = HASH(public_key)[0:16]

Properties:

- Deterministic
- Collision-resistant
- Non-reversible
- Does not reveal private key material

The Device ID is shared openly in the mesh network.

---

## Key Generation Process

1. Device boots for the first time
2. Secure random number generator initializes
3. Device generates identity key pair
4. Public key is hashed to create Device ID
5. Private key is stored in secure storage
6. Public key and Device ID are saved for messaging

This process occurs **offline** and requires no external systems.

---

## Key Storage

### Secure Storage Requirements

- Private keys stored in:
  - Secure element chip OR
  - Encrypted flash protected by hardware root-of-trust
- Keys are non-exportable
- Direct memory access is restricted

### Backup Policy

- Device identity keys are **not backed up**
- Loss of device = loss of identity
- New device must generate a new identity

This prevents identity cloning and fraud.

---

## Message Signing

All outbound messages are signed using the device’s private key.

Signed elements include:

- Message payload
- Lamport timestamp
- Sender Device ID

Signature format:

signature = SIGN(private_key, message_hash)

Receiving devices verify signatures using the sender’s public key.

---

## Transaction Signing

Each transaction includes:

- Sender Device ID
- Transaction payload
- Lamport timestamp
- Digital signature

Transactions without valid signatures are rejected immediately.

---

## Authentication Between Devices

When two devices communicate:

1. Devices exchange Device IDs and public keys
2. Each device verifies message signatures
3. Trust is established cryptographically
4. Optional session key is negotiated

No passwords, PINs, or servers are involved.

---

## Protection Against Attacks

### Impersonation Prevention

- Only devices with valid private keys can generate valid signatures
- Forged Device IDs fail signature verification

### Replay Attack Prevention

- Lamport timestamps included in signed payloads
- Duplicate or stale messages are discarded

### Device Cloning Prevention

- Private keys cannot be exported
- Secure element prevents duplication

---

## Relationship to Trust Score

- Trust score is tied to Device ID
- Consistent behavior increases trust
- Malicious behavior degrades trust
- Trust does not transfer across devices

This ensures accountability without real-world identity exposure.

---

## Device Reset and Key Destruction

If a device is reset:

- Identity keys are wiped
- Ledger data is erased
- Trust score is reset
- Device becomes a new identity

Emergency wipe triggers the same process.

---

## Regulatory and Privacy Considerations

- Device identity is pseudonymous
- No personal data required
- No centralized identity registry
- Complies with privacy-by-design principles

---

## Future Extensions

- Hardware-backed attestation
- Multi-key rotation strategies
- Group identity keys for cooperatives
- Threshold signatures for shared custody

---

## Summary

Seed’s device identity system enables secure, offline, serverless authentication using cryptographic keys. By binding trust, transactions, and communication to hardware-backed identities, Seed achieves strong security guarantees without sacrificing accessibility, privacy, or decentralization.

