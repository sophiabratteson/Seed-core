# Authentication Model

This document defines the authentication architecture for Seed devices. Because Seed operates without internet, without servers, and often without formal identity documents, authentication must be secure, offline-first, tamper-resistant, and usable in low-infrastructure environments. Seed uses a combination of hardware-rooted identity, biometric gating, local cryptographic keys, and secure-element enforcement to ensure that every transaction originates from a verified device owner.

---

# 1. Goals of Authentication

- Protect users from impersonation  
- Ensure transactions originate from a legitimate device  
- Enable secure authentication without requiring internet or external servers  
- Support users without formal ID documentation  
- Prevent lost or stolen devices from being misused  
- Maintain extremely low power consumption while providing strong security guarantees  

---

# 2. Identity Architecture Overview

Seed authentication is built on *three mutually reinforcing layers*:

1. **Device Identity Layer**  
   - Each device contains a unique cryptographic identity generated at manufacturing.  
   - Stored in a secure element (tamper-resistant chip).  
   - Used to sign all ledger transactions.

2. **User Authentication Layer**  
   - User verifies themselves with a **capacitive fingerprint sensor**.  
   - Triggers unlocking of the wallet, trust-score, and group-savings features.  
   - No biometric data ever leaves the device.

3. **Mesh Identity Verification Layer**  
   - Other devices verify transaction signatures.  
   - Prevents forged messages and impersonation across the mesh.

---

# 3. Identity Creation and Storage

## Device Keypair Generation
Each Seed device generates:
- A **private key** (stored only inside secure element)  
- A **public key** (shared across the mesh network)

Keypair type:
- Ed25519 (fast, light, ideal for low-power hardware)  
or  
- secp256r1 (if regional requirements mandate it)

## Secure Element Responsibilities
- Store cryptographic keys in non-extractable memory  
- Handle signature operations internally  
- Enforce PIN or biometric gate before enabling signing  
- Detect tampering attempts and trigger emergency wipe  

## Why Secure Elements?
Seed must operate in:
- High-theft regions  
- Disaster zones  
- Refugee camps  
- Areas with hostile governments or armed groups  

A secure element ensures:
- No attacker can extract keys  
- A stolen device cannot authorize payments  

---

# 4. Biometric Authentication

## Fingerprint Sensor Workflow
1. User places finger on capacitive scanner  
2. Template comparison is performed *locally*  
3. Fingerprint is never stored raw—only hashed and encrypted  
4. On match, a temporary session token is unlocked  
5. Session expires after ≈ 30–90 seconds of inactivity  

## Why Fingerprint?
- Extremely low literacy requirements  
- Fast  
- Works offline  
- Hard to share or forge  

## Backup Authentication (when biometrics fail)
- PIN code fallback (4–8 digits)  
- Optional “trusted friend unlock” for extreme cases  

---

# 5. Authentication in the Transaction Lifecycle

### Step 1 — User unlocks device  
Via fingerprint or PIN.

### Step 2 — Ledger engine requests authorization  
The secure element asks: “Is user authenticated?”

### Step 3 — Secure element signs transaction  
- Private key never leaves chip  
- Signature binds:
  - device_id  
  - lamport timestamp  
  - amount  
  - sender  
  - receiver  
  - trust-score updates  
  - group-savings updates  

### Step 4 — Other devices validate signature  
Any Seed device can confirm:
- Signature is valid  
- device_id matches known public key  
- Transaction was not tampered with  

This enables a **fully serverless authentication ecosystem**.

---

# 6. Mesh-Level Authentication Logic

When Device A sends a transaction to Device B:

1. B checks that signature matches A’s public key  
2. B checks lamport timestamp to prevent replay  
3. B checks if the message format matches schema  
4. B appends transaction to pending ledger  
5. B spreads updated ledger to neighbors  

Because every node can verify every message independently, the system requires **no bank, no server, and no cloud authority.**

---

# 7. Security Against Common Threats

## Lost or Stolen Device
- Without fingerprint/PIN, attacker cannot sign transactions  
- Secure element blocks key extraction  
- Emergency-wipe mode can be triggered manually or by tamper detection

## Replay Attacks
- Lamport timestamps prevent reuse of old signed messages  
- Devices ignore transactions with stale or duplicated counters  

## Fake Devices / Impersonation
- Only devices with valid secure-element signatures are accepted  
- Mesh devices maintain allowlists of known public keys (optional)

## Man-in-the-Middle Attacks
- All messages are encrypted  
- Signatures protect authenticity  
- Device ID ensures messages cannot be forged  

---

# 8. Authentication for Special Features

## Group Savings
- Each contribution is authenticated by the contributor’s device  
- Withdrawal round-robins require the selected member’s biometric unlock  
- Prevents fraudulent group claims

## Trust Score
- Updates are signed by the user’s device  
- Other devices validate them the same way as transactions  

## Training Assistant (AI Coach)
- Sensitive personal data stored only locally  
- Access requires biometric authentication session  

---

# 9. Decentralized Identity (Seed DID) — Future Expansion

Planned identity upgrades include:
- Hierarchical keypairs  
- Rotating session keys  
- Verifiable credentials issued by community leaders  
- Zero-knowledge proofs for selective identity disclosure  
- Anonymous but accountable identities for high-risk areas  

Seed eventually becomes a **portable, privacy-preserving identity system** for people without documents.

---

# 10. Summary

Seed’s authentication model enables secure financial operations in environments with:

- No internet  
- No phones  
- No SIM cards  
- No banks  
- No centralized identities  

By combining biometrics, secure hardware, and cryptographic signatures, Seed ensures that every transaction is trustworthy, offline-verifiable, and resistant to theft or coercion.

Seed authentication is not just safe—it is *foundational* to delivering financial dignity in the world’s most underserved regions.
