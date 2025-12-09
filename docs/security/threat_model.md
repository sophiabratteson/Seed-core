# Threat Model

This document defines the security threat model for Seed, an offline-first financial device designed for low-connectivity environments. The objective is to identify realistic attackers, their capabilities, potential vulnerabilities, and the defensive measures required to protect users, funds, and network integrity.

The threat model assumes Seed devices operate without continuous internet connectivity, banking infrastructure, or centralized servers. As a result, security must be embedded at the device and protocol level.

---

# 1. Security Goals

- Protect user funds from theft or tampering.
- Ensure ledger consistency across devices even without internet.
- Prevent malicious nodes from injecting fake transactions.
- Guarantee privacy of financial activity.
- Ensure device identity cannot be forged.
- Maintain system resilience in hostile environments (conflict zones, disaster zones, refugee camps, remote villages).
- Allow safe recovery from device loss or compromise.

---

# 2. Assets to Protect

- User balances
- Private keys stored in secure chips
- Ledger history (local and synchronized)
- Trust score values
- Group savings records
- Device identity and metadata
- Mesh communication packets
- Physical hardware integrity

---

# 3. Threat Actors

## Opportunistic Attackers
- Individuals attempting to steal a device and access stored funds.
- Local actors trying to impersonate another user.

## Malicious Insiders
- Users attempting to game group savings or trust scores.
- Individuals trying to double-spend while offline.

## Organized Criminal Groups
- Attempts to clone devices or extract private keys.
- Creating fraudulent devices to manipulate the ledger.

## Network-Level Attackers
- Actors injecting malformed messages into the mesh.
- Attempts to flood the network with spam to slow sync.

## State-Level Adversaries
- Seizing devices to identify activists, refugees, or dissidents.
- Attempting mass surveillance of mesh traffic.

---

# 4. Threat Categories

## Device Theft
Attackers gain physical access to a Seed device.

Risks:
- Access to user’s balance
- Viewing transaction history
- Identity takeover

Mitigations:
- Fingerprint or PIN unlock
- Secure element with encrypted key storage
- Emergency wipe mode using decoy fingerprint
- Limited offline spend without authentication

---

## Device Cloning or Identity Forgery
Attacker attempts to copy a device’s identity.

Risks:
- Double-spending attacks
- Ledger corruption attempts

Mitigations:
- Hardware-backed device keys inside secure element
- Non-exportable private keys
- Tamper sensors that zero keys on intrusion
- Signed transactions with verifiable origin

---

## Ledger Manipulation and Fraud
Attackers attempt to inject fake or modified transactions.

Risks:
- Artificial inflation of balances
- Double-spending
- Manipulating group savings cycles

Mitigations:
- Lamport clocks enforcing ordering
- Deterministic conflict resolution logic
- Signature verification on all transactions
- Causal chain validation for group events

---

## Replay Attacks
Attacker resends valid old transactions to re-trigger effects.

Mitigations:
- Unique transaction IDs
- Duplicate detection in local ledger
- Nonce values in protocol
- Checkpointed lamport timestamps

---

## Mesh Network Attacks

### Packet Injection
Attacker tries to inject invalid packets.

Mitigations:
- All packets must be signed
- Unknown signatures rejected
- Rate limiting and spam filtering

### Packet Flooding / Denial-of-Service
Attacker floods the mesh with noise.

Mitigations:
- Mesh gossip limits
- Priority queues for transaction packets
- Power-constrained retransmission rules

### Eavesdropping
Passive interception of radio traffic.

Mitigations:
- End-to-end encryption
- Rotating session keys
- Metadata minimization

---

## Side-Channel Attacks
Targeting secure hardware components.

Risks:
- Extracting cryptographic keys
- Inferring PIN/fingerprint match patterns

Mitigations:
- Secure element chip (Atecc608A-class)
- Randomized timing operations
- Tamper-resistant case structure
- Power anomaly detection

---

## Social Engineering
Attackers manipulate users.

Risks:
- Trick users into sending funds
- Gain access during device sharing

Mitigations:
- Clear confirmation dialogs
- Transaction-by-transaction authentication policies
- Built-in AI assistant warnings for common scams

---

# 5. Environmental Threats

Seed must operate in unstable environments.

Risks:
- High heat damaging batteries
- Physical damage from moisture or dust
- Governments shutting down connectivity
- Power scarcity affecting device lifetime

Mitigations:
- E-ink for low power
- Solar + hand-crank recharging
- Heat-resistant LiFePO4 batteries
- Fully offline ledger and sync logic

---

# 6. Trust Score Exploitation

Risks:
- Users colluding to boost each other’s trust scores
- Fake group savings cycles
- False-positive behaviors masking fraud

Mitigations:
- Trust events signed and cross-referenced
- Group savings requiring multi-signature participation
- Consistency rules enforced at ledger-level

---

# 7. Attack Surfaces Summary

- Mesh radio interface
- USB (if enabled)
- Physical device access
- Firmware update pathway
- Local storage
- Fingerprint/PIN authentication process

Each attack surface must be hardened before production deployment.

---

# 8. Defense in Depth Strategy

- Hardware secure element for identity
- On-device encryption for all sensitive data
- Signed firmware with secure boot
- Ledger consistency rules at protocol layer
- Anti-tamper housing
- Offline-only trust model
- Minimal user metadata storage
- Automatic suspicious behavior detection

---

# 9. Worst-Case Scenario Planning

Seed must remain safe even if:

- A user’s device is stolen
- Half of a village’s devices are compromised
- A malicious actor floods the mesh network
- A government attempts to surveil communications
- Connectivity is completely unavailable for months

Design principles supporting this:

- No central authority required for ledger validity
- Each device independently verifies every transaction
- Transactions cannot be forged or reordered
- Private keys never leave the secure element
- Users remain anonymous by design

---

# 10. Conclusion

The Seed threat model recognizes challenges unique to offline, low-infrastructure financial ecosystems. By combining secure hardware, strong cryptography, deterministic ledger logic, and resilient mesh-based communication, Seed ensures that even the most vulnerable populations can rely on a financial system that is safe, private, and tamper-resistant.

This threat model guides the design of every hardware, firmware, and protocol-level component of Seed and will evolve alongside real-world testing and adversarial analysis.
