# Attack Scenarios Catalog

This document catalogs potential security attack scenarios relevant to the Seed system and defines how they are simulated, detected, and mitigated. The goal is to proactively evaluate how Seed behaves under adversarial conditions in offline, low-trust, and high-risk environments.

---

## Purpose of This Document

- Enumerate realistic threat scenarios Seed may face
- Define attacker capabilities and constraints
- Map attacks to system components
- Inform mitigation strategies and protocol hardening
- Support investor, auditor, and regulator review

This catalog feeds directly into security design, simulations, and field testing.

---

## Threat Model Assumptions

- Attackers may control one or more Seed devices
- Attackers may physically steal devices
- Attackers may inject malformed or malicious packets
- Attackers do not have access to secure element private keys
- Attackers may collude across multiple devices
- Network connectivity is intermittent and untrusted

---

## Attack Scenario Categories

1. Transaction Manipulation Attacks
2. Ledger Consistency Attacks
3. Identity & Impersonation Attacks
4. Network-Level Attacks
5. Physical Device Attacks
6. Group Savings Abuse Attacks
7. Trust Score Manipulation Attacks
8. Denial-of-Service & Resource Exhaustion Attacks

---

## Scenario 1: Transaction Replay Attack

### Description
An attacker rebroadcasts an old valid transaction in an attempt to duplicate funds or alter balances.

### Attack Vector
- Captured transaction message
- Re-injected into mesh network

### Simulation Method
- Re-send identical transaction payload multiple times
- Observe ledger state across devices

### Expected Defense
- tx_id uniqueness enforcement
- Idempotent transaction application
- Lamport clock comparison rejects duplicates

### Outcome Criteria
- Ledger state remains unchanged
- No balance inflation occurs

---

## Scenario 2: Double-Spend Attempt (Offline)

### Description
A malicious user attempts to spend the same balance across multiple offline devices before syncing.

### Attack Vector
- Parallel transactions created while isolated
- Delayed sync with the mesh

### Simulation Method
- Create two conflicting transactions
- Merge ledgers during sync

### Expected Defense
- Deterministic conflict resolution
- Balance validation at apply time
- One transaction invalidated

### Outcome Criteria
- Only one transaction is accepted
- Invalid transaction is flagged and archived

---

## Scenario 3: Ledger Fork Injection

### Description
A device attempts to introduce a divergent ledger history to override prior transactions.

### Attack Vector
- Modified ledger export
- Tampered transaction ordering

### Simulation Method
- Inject reordered or missing transaction chains

### Expected Defense
- Causal reference validation
- Missing dependency detection
- Fork rejection

### Outcome Criteria
- Forked history rejected
- Device flagged as suspicious

---

## Scenario 4: Device Impersonation

### Description
An attacker attempts to spoof another device’s identity.

### Attack Vector
- Forged device_id field
- Unsigned or improperly signed messages

### Simulation Method
- Inject messages with mismatched identity and signature

### Expected Defense
- Secure element key validation
- Message signature verification

### Outcome Criteria
- Message rejected
- Event logged locally

---

## Scenario 5: Malicious Trust Score Inflation

### Description
A user attempts to artificially inflate trust score via collusion or fake transactions.

### Attack Vector
- Repeated micro-transactions
- Colluding group members

### Simulation Method
- Simulate dense transaction graph among small group

### Expected Defense
- Rate limiting
- Trust decay functions
- Group diversity weighting

### Outcome Criteria
- Trust score growth capped
- Anomalies flagged

---

## Scenario 6: Group Savings Hijack

### Description
A participant attempts to withdraw group funds out of rotation.

### Attack Vector
- Malformed group withdrawal message
- Manipulated index counters

### Simulation Method
- Inject early withdrawal attempt

### Expected Defense
- Rotation index validation
- Group consensus rules

### Outcome Criteria
- Withdrawal rejected
- Group state remains intact

---

## Scenario 7: Packet Flooding (Mesh DoS)

### Description
An attacker floods the mesh with excessive messages to drain power or block sync.

### Attack Vector
- High-frequency broadcast spam

### Simulation Method
- Simulate rapid message bursts

### Expected Defense
- Rate limiting
- Duty-cycle enforcement
- Neighbor throttling

### Outcome Criteria
- Device remains responsive
- Battery impact within acceptable bounds

---

## Scenario 8: Malformed Packet Injection

### Description
Attacker sends corrupted or oversized packets to crash devices.

### Attack Vector
- Invalid serialization
- Oversized payloads

### Simulation Method
- Inject malformed packets

### Expected Defense
- Strict schema validation
- Safe parsing routines

### Outcome Criteria
- No crash
- Packet dropped safely

---

## Scenario 9: Physical Device Theft

### Description
A Seed device is stolen and attacker attempts to extract funds or data.

### Attack Vector
- Physical possession
- Offline access attempts

### Simulation Method
- Assume attacker bypasses UI
- Attempt data extraction

### Expected Defense
- Secure element key protection
- Encrypted storage
- Emergency wipe triggers

### Outcome Criteria
- No private keys exposed
- Funds remain secure

---

## Scenario 10: Emergency Wipe Abuse

### Description
An attacker attempts to abuse the emergency wipe mechanism.

### Attack Vector
- Trigger spoofing
- Fake distress signals

### Simulation Method
- Trigger emergency mode incorrectly

### Expected Defense
- Physical interaction requirement
- Multi-step confirmation

### Outcome Criteria
- No unauthorized wipe occurs

---

## Cross-Scenario Metrics

For all attack simulations, the following are measured:

- Ledger integrity
- Device stability
- Power consumption impact
- Sync convergence time
- False positive rate
- User fund safety

---

## Integration with Testing Pipeline

- Linked to adversarial tests in mesh-protocol/testing
- Results feed into threat model updates
- Used for investor due diligence and audits

---

## Summary

This attack scenarios catalog ensures Seed is designed defensively from day one. By simulating realistic adversarial behavior across financial, network, and physical layers, Seed validates that its offline-first architecture remains secure, resilient, and trustworthy in real-world conditions.

This document is a living artifact and will evolve as new threats are identified.
