# Secure Element Chip

## Overview
The secure element (SE) is a tamper-resistant hardware component that stores cryptographic keys, performs sensitive operations, and guarantees that critical security functions remain protected even in hostile or low-trust environments. In Seed, the secure element is central to device identity, transaction signing, trust-score enforcement, and anti-counterfeiting measures.

Because Seed devices are deployed in regions with limited infrastructure and higher risks of theft, coercion, or tampering, the secure element provides the foundation for Seed's offline security model.

## Core Responsibilities
- Store long-term private keys for the device
- Generate and verify cryptographic signatures
- Perform secure random number generation
- Protect keys against extraction, probing, and side-channel attacks
- Enforce transaction integrity and replay-prevention
- Enable secure boot and firmware authenticity checks
- Support encrypted storage for ledger checkpoints
- Provide hardware-backed identity for participation in the Seed mesh

## Hardware Requirements for Seed
A suitable secure element for Seed must include the following properties:

### 1. Hardware Key Storage
- Non-exportable private keys
- Support for multiple key slots (device identity, group keys, escrow keys)
- Tamper-responsive memory protection

### 2. Cryptographic Operations
- ECDSA or Ed25519 signing for ledger transactions
- SHA-256 or SHA-3 hashing
- HKDF or PBKDF2 key-derivation functions
- Secure random number generator with hardware entropy

### 3. Tamper Resistance
- Resistance to power glitching
- Shielding against physical probing
- Zeroization on tamper detection
- Protection against cold-boot and side-channel leakage

### 4. Secure Boot Support
The secure element should verify:
- Bootloader authenticity
- Firmware version integrity
- Rollback-prevention counters

This prevents malicious firmware from altering ledger rules or injecting fraudulent transactions.

### 5. Offline Authentication
Seed relies heavily on offline mesh communication. The SE must:
- Sign transactions without server involvement
- Validate peer signatures during sync
- Maintain monotonic counters (Lamport clock authentication)
- Provide anti-replay guarantees

### 6. Compatibility Requirements
The SE must integrate with:
- Low-power microcontrollers (ESP32, STM32, nRF52, etc.)
- I2C or SPI communication buses
- Low-power design (<5 mA during operations)
- Harsh environmental conditions (heat, humidity, dust)

## Recommended Components
Candidate secure elements suitable for Seed prototypes:

### Microchip ATECC608B
- ECDSA signing support
- Hardware-protected private keys
- Built-in certificate handling
- Tamper-resistant design
- Excellent power efficiency for ultra-low-resource environments

### NXP SE050
- Broader cryptographic suite
- Secure key provisioning
- Trusted platform module (TPM)-like features
- High security rating (Common Criteria)

### STSAFE-A110
- Designed for IoT authentication
- Good integration support
- Supports mutual authentication with peers

These options allow flexibility for different price points and manufacturing capabilities.

## Role in the Seed Protocol
The secure element enables several critical Seed features:

### Device Identity
Each Seed device generates or receives a hardware-bound keypair. The public key becomes its unique identity in the mesh network.

### Transaction Signing
Every ledger transaction is signed inside the secure element. The private key never leaves the chip.

### Ledger Integrity Enforcement
Nodes verify signatures before accepting incoming transactions. SE-backed signatures guarantee:
- Authenticity of sender
- Protection from forgery
- Non-repudiation

### Trust Score Enforcement
Trust score updates are cryptographically bound to each user. Only the SE can authorize these updates, preventing manipulation.

### Emergency Wipe Support
The SE can enforce:
- Secure erasure of private keys
- Triggered wipe on tampering or user distress input
- Partial wipe logic that preserves anonymized ledger states

## Integration with Seed Firmware
The firmware communicates with the secure element through a dedicated driver that manages:
- Key generation (setup stage)
- Secure element provisioning
- Signing API (sign_transaction, sign_sync_packet)
- Verification cache
- Firmware integrity checks via secure boot

Firmware modules using the SE include:
- security_module.c
- ledger_manager.c
- mesh_protocol.c
- device_identity.c

## Failure Modes and Mitigations
### SE Unavailable
Fallback:
- Disable signing functions
- Prevent outgoing transactions
- Allow read-only ledger operations

### SE Tamper Alert
Device must:
- Immediately zeroize all volatile keys
- Enter emergency lockout mode
- Require physical reset or re-provisioning

### Communication Errors (I2C/SPI)
- Retries with exponential backoff
- Manual recovery instructions for field technicians

## Manufacturing Considerations
- Keys can be injected during production or generated on-device
- Anti-counterfeiting ensured through certificate chains
- Mass-production workflows require secure key provisioning servers or HSMs

## Long-Term Upgradability
Seed’s architecture allows:
- Migration to post-quantum secure elements when available
- Rotation of network keys
- Key revocation and reputation-based identity recovery

## Summary
The secure element is the single most important hardware security component in the Seed ecosystem. It protects keys, enforces consistency, prevents fraud, enables offline authentication, and ensures that even in low-trust environments the device, user, and ledger remain secure. A robust SE implementation makes Seed credible for financial use in areas without internet, electricity, or institutional trust—creating the foundation for a resilient, offline-first global economic network.
