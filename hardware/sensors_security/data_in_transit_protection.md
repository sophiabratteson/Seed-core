# Data in Transit Protection

This document defines how Seed devices secure all transmitted data over the mesh network. Because Seed operates in environments without internet, servers, or centralized infrastructure, every radio transmission must be protected at the device level. These protections ensure confidentiality, integrity, authenticity, and resistance to replay or tampering.

Seed relies on lightweight cryptography suitable for solar-powered, low-frequency, resource-constrained devices while maintaining security guarantees comparable to modern digital banking systems.

---

# 1. Security Goals

- Prevent any third party from reading transaction contents.
- Ensure that all messages are authenticated and originate from legitimate devices.
- Detect and prevent tampering or message modification.
- Prevent replay attacks where old messages are resent to confuse devices.
- Maintain security even if adversaries have high-power radio equipment.
- Provide resilience in environments with surveillance, censorship, or low trust.

---

# 2. Threat Model

Seed devices assume the following adversarial conditions:

- Attackers may intercept all radio messages within range.
- Attackers may attempt to impersonate a Seed device.
- Attackers may attempt jamming, replay, injection, or modification of messages.
- Attackers may possess stolen devices but not internal secure keys.
- Attackers may analyze traffic patterns to infer user activity.

Protection mechanisms must operate under these assumptions while remaining computationally efficient.

---

# 3. Cryptographic Foundations

Seed’s radio layer uses the following primitives:

## Symmetric Encryption  
- AES-256 in GCM mode (authenticated encryption)  
- Ensures confidentiality and built-in message authentication  
- Low computational overhead for microcontrollers  

## Asymmetric Keys  
- ECC-based device identity keys (Curve25519 or secp256r1)  
- Used for initial key exchange and device-to-device trust establishment  

## Hash Functions  
- SHA-256 or BLAKE3 depending on hardware support  
- Used for integrity checks and ledger hashing  

---

# 4. Key Management

Each Seed device includes:

- A permanently stored private identity key inside the secure element  
- A public identity key broadcast as part of device metadata  
- A rotating session key shared between communicating neighbors  

## Key Establishment Flow  
1. Device A sends a handshake packet with its public key.  
2. Device B responds with its own public key.  
3. Both derive a shared symmetric session key using ECDH.  
4. All future communication uses the derived symmetric key.  

Session keys rotate periodically or after a fixed number of packets to prevent long-term exposure.

---

# 5. Message-Level Protections

Every Seed packet transmitted over LoRa or mesh network contains:

- Encrypted payload  
- Nonce (prevents replay)  
- Authentication tag (ensures tamper-detection)  
- Sender device ID (pseudonymous, not linked to real identity)  
- Lightweight metadata for routing and sync logic  

## Encryption Flow  
1. Payload is prepared (transaction, ledger fragment, heartbeat).  
2. A cryptographically secure nonce is generated.  
3. AES-GCM encrypts the payload using the session key and nonce.  
4. Authentication tag is appended.  
5. Packet is transmitted over radio.

## Validation Flow  
1. Receiving device checks the nonce (rejects duplicates).  
2. Decrypts using session key.  
3. Verifies GCM tag to ensure the message was not altered.  
4. Processes the message only if it is authenticated and valid.

---

# 6. Anti-Replay Mechanisms

Seed uses multiple mechanisms to ensure replayed packets cannot affect ledger state:

- Nonce-matching: each device stores a short history of seen nonces.  
- Lamport timestamps embedded in transactions.  
- Ledger rejects any transaction whose ordering violates logical causality.  
- State commitment prevents accepting old ledger fragments.

Replay attempts fail silently and do not affect device behavior.

---

# 7. Traffic Obfuscation (Optional Future Layer)

To reduce metadata leakage, Seed can optionally support:

- Randomized packet padding  
- Variable transmission timing  
- Pseudorandom routing paths to mask sender/receiver  

These features particularly benefit high-risk environments such as refugee camps or politically unstable regions.

---

# 8. Resource Constraints and Optimization

Because Seed operates with:

- E-ink screens  
- Solar + hand-crank power  
- Low RAM microcontrollers  
- Low-bandwidth LoRa radios  

All cryptography is optimized for:

- Minimal CPU cycles  
- Minimal radio airtime  
- Minimal power draw  
- Deterministic timing  

AES-GCM and Curve25519 are specifically chosen because they are efficient even on low-power MCUs.

---

# 9. Integration with Secure Element

The secure element chip:

- Stores long-term identity keys  
- Performs ECC operations internally  
- Prevents extraction even under physical attacks  
- Tracks monotonic counters used as part of nonce generation  

This hardware-backed security makes Seed devices comparable to modern smartphones and payment terminals.

---

# 10. Failure Modes and Recovery

If decryption or authentication fails:

- Packet is discarded  
- Nonce is not updated  
- Device logs a warning for debugging  
- No ledger impact occurs  

If session key is lost or corrupted:

- Devices re-establish a new key through another handshake  
- No human input required  

---

# 11. Summary

Seed ensures robust end-to-end data protection entirely without internet or centralized infrastructure. Every packet on the mesh is encrypted, authenticated, replay-protected, and tamper-evident. This security model enables Seed to serve as a globally trustworthy financial platform, even in the lowest-connectivity environments.

Seed’s offline, distributed encryption approach makes it safe for personal finance, group savings, loans, and economic activity — all resilient to surveillance, interception, and hostile networks.
