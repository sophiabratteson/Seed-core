# Adversarial Testing Plan

This document defines adversarial testing scenarios for the Seed mesh protocol. The goal is to evaluate how the system behaves under malicious, faulty, or unexpected conditions and to ensure that the network remains safe, resilient, and convergent even when individual nodes act incorrectly or maliciously.

Adversarial testing assumes that some devices in the network may be compromised, misconfigured, or intentionally attempting to disrupt the system.

---

## 1. Goals of Adversarial Testing

- Detect and prevent double-spending attempts
- Ensure ledger convergence despite malicious inputs
- Prevent replay and message injection attacks
- Limit the blast radius of compromised devices
- Preserve network functionality under partial attack
- Validate that security and conflict-resolution rules are enforced consistently

---

## 2. Threat Model Assumptions

Adversarial tests are designed under the following assumptions:

- Attackers may control one or more Seed devices
- Attackers do not have access to private keys of uncompromised devices
- Attackers can replay, delay, or reorder messages
- Attackers can attempt to flood the network with traffic
- Physical capture of a device is possible
- Internet access is not required for any attack

---

## 3. Categories of Adversarial Tests

### 3.1 Ledger-Level Attacks

These tests target the financial and accounting logic.

#### Double-Spend Attempt
- A device creates two transactions spending the same balance
- Transactions are broadcast to different parts of the mesh
- Expected outcome:
  - Only one transaction is accepted
  - The other is marked invalid during deterministic replay

#### Conflicting Transaction Content
- Same tx_id with altered fields is injected
- Expected outcome:
  - Signature validation fails
  - Altered transaction is rejected

#### Lamport Clock Manipulation
- Device attempts to artificially increase lamport values
- Expected outcome:
  - Transactions are accepted but do not override valid history
  - No ability to retroactively alter balances

---

### 3.2 Network-Level Attacks

These tests target message transport and routing behavior.

#### Message Replay Attack
- Previously valid messages are rebroadcast repeatedly
- Expected outcome:
  - Duplicate messages are ignored
  - No ledger changes occur

#### Message Flooding
- A device sends excessive messages at high frequency
- Expected outcome:
  - Rate limiting activates
  - Neighbor reputation is degraded
  - Messages may be dropped

#### Routing Poisoning
- Device advertises false routing information
- Expected outcome:
  - Neighbor table validation rejects inconsistent routes
  - Gossip convergence corrects topology over time

---

### 3.3 Identity and Authentication Attacks

These tests target device identity and trust.

#### Device Impersonation
- Attacker attempts to send messages claiming another device_id
- Expected outcome:
  - Signature mismatch causes rejection
  - No trust score impact on victim device

#### Sybil Attack
- Attacker introduces many fake device identities
- Expected outcome:
  - New devices have minimal trust
  - Group participation and lending is restricted
  - Trust accrual requires time and valid behavior

---

### 3.4 Group Savings and Trust Attacks

These tests target social and cooperative mechanisms.

#### Group Contribution Skipping
- Device claims contribution without sending funds
- Expected outcome:
  - Group ledger validation fails
  - Contribution is rejected

#### Trust Score Manipulation
- Device attempts to fabricate trust updates
- Expected outcome:
  - Updates without valid backing transactions are rejected
  - Trust score remains unchanged

---

### 3.5 Physical Capture Scenarios

These tests assume an attacker has physical access.

#### Device Theft
- Attacker attempts to read stored data
- Expected outcome:
  - Encrypted storage prevents data access
  - No private keys are exposed

#### Forced Interaction
- Attacker attempts to coerce device usage
- Expected outcome:
  - Emergency wipe or decoy mode activates
  - Sensitive data is hidden or erased

---

## 4. Test Execution Methodology

- Simulate adversarial behavior using controlled test nodes
- Inject malformed or malicious messages
- Observe ledger convergence across honest nodes
- Verify that no honest device diverges in state
- Measure recovery time after attack ends

---

## 5. Success Criteria

An adversarial test is considered successful if:

- Ledger remains consistent across honest nodes
- No unauthorized balance changes occur
- Network continues functioning for non-malicious users
- Attacks are contained and do not cascade
- Compromised devices can be isolated or ignored

---

## 6. Logging and Evidence Collection

During adversarial tests, devices should log:

- Rejected messages and reasons
- Rate-limiting events
- Trust score changes
- Ledger validation failures
- Security-related state transitions

Logs are used for post-test analysis and protocol improvement.

---

## 7. Iteration and Hardening

Results from adversarial testing feed directly into:

- Protocol rule refinement
- Trust score weighting adjustments
- Rate-limiting thresholds
- Future hardware security enhancements

Adversarial testing is an ongoing process and must be repeated as the protocol evolves.

---

## 8. Summary

Adversarial testing ensures that Seed remains safe and reliable in real-world conditions where not all participants can be trusted. By systematically testing malicious scenarios, the Seed mesh protocol is hardened against fraud, abuse, and disruption while maintaining accessibility and decentralization.
