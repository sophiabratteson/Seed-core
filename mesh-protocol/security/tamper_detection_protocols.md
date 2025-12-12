# Tamper Detection Protocols

This document defines how the Seed mesh protocol detects, responds to, and recovers from physical and logical tampering attempts on Seed devices. Because Seed operates in adversarial environments (low trust, offline, high theft risk), tamper detection is a first-class security primitive rather than an optional feature.

---

## 1. Objectives

- Detect physical attempts to open, modify, or probe the device.
- Detect logical tampering with firmware, memory, or stored ledger data.
- Protect user funds and private data if a device is compromised.
- Prevent compromised devices from poisoning the mesh network.
- Enable graceful recovery and network containment after tampering events.

---

## 2. Threat Model

Tamper detection assumes the following realistic attack scenarios:

- Device theft or confiscation.
- Physical opening of enclosure to access PCB or debug ports.
- Memory probing or chip removal.
- Firmware replacement or downgrade attacks.
- Ledger manipulation or transaction injection.
- Side-channel attacks attempting key extraction.

Seed does **not** assume attackers have unlimited time or nation-state resources, but does assume access to basic electronics tools.

---

## 3. Physical Tamper Detection Mechanisms

### 3.1 Enclosure Breach Detection

- Tamper-evident enclosure design using:
  - Internal conductive traces or breakable seals.
  - Mechanical switches triggered when enclosure is opened.
- Opening the enclosure triggers a hardware tamper interrupt.

### 3.2 Secure Element Tamper Flags

- Secure element chips monitor:
  - Voltage anomalies.
  - Clock glitches.
  - Temperature spikes.
- Any anomaly triggers internal tamper flags that cannot be cleared without full re-provisioning.

### 3.3 Debug Interface Protection

- JTAG/SWD interfaces are:
  - Permanently disabled after manufacturing.
  - Or cryptographically locked behind secure element authentication.
- Any attempt to re-enable debug interfaces is treated as a tamper event.

---

## 4. Logical Tamper Detection

### 4.1 Secure Boot Verification

- On every boot:
  - Firmware signature is verified using hardware-rooted keys.
  - Hashes are compared against expected values stored in secure memory.
- Failure results in immediate lockdown mode.

### 4.2 Ledger Integrity Checks

- Ledger data is protected by:
  - Hash chaining.
  - Merkle-style integrity checks.
- Any mismatch indicates unauthorized modification.

### 4.3 Configuration and Key Validation

- Device identity keys and configuration parameters are:
  - Signed.
  - Versioned.
- Invalid or downgraded configurations are rejected.

---

## 5. Tamper Event Classification

Seed classifies tamper events into three severity levels:

### Level 1: Suspicious
- Non-fatal anomalies (e.g., clock drift spikes).
- Device continues operation with increased monitoring.

### Level 2: Confirmed Tamper
- Enclosure breach.
- Firmware verification failure.
- Ledger integrity failure.
- Device enters restricted mode.

### Level 3: Critical Compromise
- Secure element tamper flag set.
- Key extraction attempt detected.
- Device performs immediate emergency wipe.

---

## 6. Tamper Response Actions

### 6.1 Emergency Lockdown

Triggered on Level 2 or higher events:

- Disable transaction signing.
- Freeze ledger modifications.
- Block mesh message transmission except tamper alerts.

### 6.2 Emergency Wipe

Triggered on Level 3 events or user-initiated panic:

- Erase private keys from secure element.
- Wipe encrypted ledger storage.
- Reset device to unprovisioned state.

### 6.3 Tamper Broadcast

- Device emits a signed tamper alert to the mesh network.
- Alert includes:
  - Device ID.
  - Tamper severity.
  - Timestamp (logical clock).
- Other devices reduce trust or quarantine messages from the compromised node.

---

## 7. Mesh-Level Containment

To prevent network poisoning:

- Tampered devices are:
  - Temporarily blacklisted.
  - Permanently banned if compromise is confirmed.
- Trust score penalties are applied automatically.
- Ledger updates originating from compromised devices are rejected.

---

## 8. User Safety and Data Protection

- Users are protected by:
  - Encrypted storage.
  - Minimal plaintext data retention.
- Emergency wipe ensures attackers cannot access:
  - Balances.
  - Transaction history.
  - Identity metadata.

For illiterate or at-risk users, panic actions can be triggered via:
- Hidden button sequences.
- Fake authentication paths.

---

## 9. Recovery and Re-Provisioning

After a tamper event:

- Device must be:
  - Physically inspected.
  - Re-flashed with trusted firmware.
  - Re-provisioned with new cryptographic identity.
- Old identity is permanently revoked across the mesh.

---

## 10. Audit and Forensics

- Non-sensitive tamper metadata may be retained for:
  - Security audits.
  - Device failure analysis.
- Sensitive user data is never retained post-wipe.

---

## 11. Future Enhancements

Planned upgrades include:

- Active mesh-based tamper correlation.
- Zero-knowledge proofs of device integrity.
- Trusted manufacturing attestation chains.
- Hardware-backed usage anomaly detection.

---

## 12. Summary

Tamper detection in Seed is proactive, layered, and irreversible by design. By combining physical sensors, secure boot, cryptographic integrity checks, and mesh-level containment, Seed ensures that a single compromised device cannot undermine the safety, trust, or financial integrity of the broader offline network.

This approach enables Seed to operate safely in environments where traditional banking infrastructure cannot exist.
