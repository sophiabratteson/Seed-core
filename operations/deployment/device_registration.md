# Device Registration

## Purpose

This document defines how a Seed device is securely registered into the Seed network for the first time.  
Device registration establishes device identity, ownership binding, cryptographic trust, and eligibility to participate in mesh transactions.

Registration is designed to work **offline-first**, without requiring continuous internet access, centralized servers, or formal banking infrastructure.

---

## Goals of Device Registration

- Assign a **unique, cryptographically verifiable identity** to each Seed device
- Bind a device to a **primary human owner or steward**
- Prevent counterfeit, duplicated, or tampered devices from joining the network
- Enable trust, accountability, and recovery without centralized control
- Support registration in **low-connectivity, rural, or disaster environments**

---

## Core Principles

- Offline-first by default
- Minimal personal data collection
- Cryptographic identity over legal identity
- Human-centered recovery paths
- Deterministic and auditable process

---

## Device Identity Components

Each Seed device is provisioned with the following identity elements:

- **Device ID**
  - Globally unique identifier (UUID or hardware-derived ID)
  - Generated during manufacturing or first boot

- **Hardware Root of Trust**
  - Secure element chip stores private keys
  - Keys never leave hardware boundary

- **Public Key**
  - Used to verify signatures, authenticate messages, and identify device in mesh

- **Registration State Flag**
  - Indicates whether device is unregistered, registered, suspended, or retired

---

## Registration Actors

- **Device Owner**
  - Human user claiming the device
  - Verified via fingerprint or physical possession

- **Registrar Device (Optional)**
  - Another Seed device that assists with onboarding
  - Acts as witness, not authority

- **Seed Network**
  - Mesh of existing devices that recognize registration events

---

## Registration Modes

### Mode 1: Self-Registration (Offline)

Used when no other Seed devices or internet access are available.

Steps:
1. Device boots for first time
2. Secure element generates key pair
3. Device creates a self-signed registration record
4. Device enters "probationary" trust state
5. Trust score increases gradually through normal usage

Use Case:
- Remote villages
- Disaster zones
- First devices in a new region

---

### Mode 2: Peer-Assisted Registration

Used when at least one existing Seed device is nearby.

Steps:
1. New device requests registration via mesh
2. Registrar device verifies physical presence
3. Registrar signs registration acknowledgment
4. Registration record is broadcast to mesh
5. Device enters standard trust state

Benefits:
- Faster trust establishment
- Reduced fraud risk
- Community-backed onboarding

---

### Mode 3: Internet-Assisted Registration (Optional)

Used when temporary internet access is available.

Steps:
1. Device connects via WiFi or cellular relay
2. Registration metadata is uploaded
3. Public key anchored for redundancy
4. Device returns to offline mode

Note:
- Internet is **never required**
- No centralized authority controls access

---

## Registration Data Record

Each registration creates an immutable record:

```
{
  "device_id": "SEED-UUID",
  "public_key": "BASE64_ENCODED",
  "registration_type": "self | peer | internet",
  "registrar_device_id": "optional",
  "timestamp": "lamport_clock",
  "signature": "device_signature"
}
```

Records are:
- Signed
- Gossip-synced across mesh
- Stored locally and redundantly

---

## Trust Initialization

After registration, devices start with a baseline trust score:

- Self-registered devices:
  - Lower initial trust
  - Gradual increase through transactions

- Peer-registered devices:
  - Higher initial trust
  - Backed by registrar device reputation

Trust score impacts:
- Transaction limits
- Group participation
- Loan eligibility

---

## Fraud and Abuse Prevention

- Duplicate device IDs rejected
- Invalid signatures discarded
- Registration flooding rate-limited
- Suspicious devices isolated without network-wide failure

---

## Lost or Replaced Device Handling

If a registered device is lost:

- Owner can:
  - Mark device as lost via another Seed device
  - Freeze funds
  - Transfer balances to new device

Old device:
- Trust score decays
- Transactions rejected
- Cannot rejoin without re-verification

---

## Privacy Considerations

- No names, addresses, or government IDs required
- Fingerprint data stored locally only
- Registration records reveal **device identity, not personal identity**

---

## Regulatory Flexibility

Registration system supports:
- NGO deployments
- Humanitarian programs
- Local cooperative models
- Future compliance layers without redesign

---

## Summary

Seed’s device registration system establishes trust without dependence on banks, governments, or constant connectivity.  
By anchoring identity in hardware, cryptography, and community verification, Seed enables secure participation in a global financial mesh — even in the most disconnected environments.

This system ensures:
- Integrity
- Scalability
- Human dignity
- Long-term resilience
