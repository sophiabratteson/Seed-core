# Tamper Detection System

This document describes the tamper-detection architecture for the Seed device. Because Seed operates in high-risk environments where theft, coercion, attempted hardware modification, and data extraction are realistic threats, the device requires a multilayered tamper-response framework. The goal is to ensure that sensitive financial data, private keys, trust-score history, and group-savings records remain secure even under physical attack.

# 1. Objectives

- Protect user identity and financial data from forced extraction.
- Prevent attackers from accessing secure storage or modifying critical firmware.
- Detect physical opening, drilling, shorting, or probing of the device.
- Automatically trigger controlled responses such as memory wipe, key invalidation, or lockdown.
- Provide graceful degradation (device stays safe even if fully compromised).
- Maintain low power consumption suitable for Seed’s off-grid design.

# 2. Threat Model

Seed’s tamper-detection system is designed with the following threat assumptions:

- Attackers may attempt to physically open the enclosure.
- Attackers may try to read memory directly by attaching external probes.
- Attackers may freeze or heat the device to bypass security elements.
- Attackers may try to clone identity keys from stored flash data.
- Attackers may coerce users and attempt forced unlocking.
- Attackers may steal devices in bulk in an attempt to reverse-engineer the Seed hardware.

The system should detect these attempts and respond deterministically.

# 3. Layers of Tamper Detection

Seed uses a layered strategy so that no single mechanism becomes a point of failure.

## 3.1 Mechanical Tamper Switch

- Spring-loaded or pressure-sensitive switch placed inside the enclosure.
- Triggered when the case is opened or loosened.
- Runs on an interrupt pin monitored by the secure microcontroller.
- If activated:
  - Device enters tamper lockdown mode.
  - Sensitive keys are wiped or invalidated.
  - The event is logged in a one-way audit counter.

## 3.2 Conductive Mesh Tamper Grid

- Thin conductive traces embedded under the enclosure surface.
- Breaking, drilling, or cutting the case interrupts the circuit.
- The secure element monitors line continuity.
- If continuity is lost:
  - Secure element clears cryptographic keys.
  - Device becomes unusable without reprovisioning.

## 3.3 Secure Element Anti-Probe Detection

Many secure elements (for example Microchip ATECC608B or NXP SE050) support:

- Voltage anomaly detection
- Frequency glitch detection
- Clock manipulation detection
- Rapid-temperature-change detection

When such anomalies occur:

- Device refuses cryptographic operations.
- Sensitive memory regions are internally zeroized.

## 3.4 Memory Encryption and Ephemeral Keys

Even if flash memory is accessed directly:

- User financial data is encrypted with keys stored only inside the secure element.
- Trust-score and ledger checkpoints use authenticated encryption.
- Removing the secure element makes the stored data unreadable.

## 3.5 Fingerprint Sensor Duress Mode

Seed integrates a duress fingerprint mode:

- User registers a secondary fingerprint designated as a "safe unlock" under coercion.
- When used:
  - A fake ledger state is displayed.
  - Real data becomes hidden.
  - No tamper logs are triggered to avoid alerting coercive attackers.
- This protects users under force or threat.

## 3.6 Firmware Integrity and Secure Boot

- Bootloader verifies firmware signature at startup.
- Any modification or tampering results in:
  - Boot halt
  - Secure memory wipe
  - Enforced re-provisioning sequence

This prevents attackers from loading modified software that bypasses security rules.

# 4. Tamper Response Logic

When a tamper event is detected, the Seed device follows a strict response sequence.

## 4.1 Event Classification

- Level 1: Suspicious anomaly (minor voltage glitch, quick enclosure pressure shift)
- Level 2: Confirmed tampering (enclosure open, mesh grid broken)
- Level 3: Critical breach (probe attempt, secure element alarm)

## 4.2 Response Actions

- Level 1:
  - Lock UI temporarily.
  - Require higher-assurance re-authentication.
- Level 2:
  - Immediately revoke session keys.
  - Zeroize all device identity keys.
  - Stop ledger operations until reprovisioned.
- Level 3:
  - Wipe secure element memory.
  - Destroy mesh identity.
  - Mark device permanently compromised.
  - Device becomes read-only for audit extraction by authorized personnel.

# 5. Tamper Logging and Audit Trail

All tamper events are tracked:

- Write-once, monotonic counters
- Stored in secure element
- Cannot be erased by attacker
- Logged events include:
  - Timestamp offset (logical clock index)
  - Type of tamper
  - Response action taken

These counters help:

- Field administrators detect compromised units.
- Researchers analyze widespread tampering in hostile regions.

# 6. Environmental Hardening

Seed operates in tropical heat, dust, humidity, and vibration.

Tamper detection must remain reliable under:

- Extreme temperature swings
- Dust infiltration
- High humidity
- Mechanical shock from dropping or transport
- Solar-powered charging fluctuations

Components must be low-power and robust.

# 7. User Experience Considerations

Tamper detection should never create fear or confusion for normal users.

Design principles:

- Hidden from user under normal operation.
- No accidental triggers from everyday handling.
- Duress mode must feel seamless and safe.
- Reset/recovery processes must be available for legitimate repairs.

# 8. Future Extensions

Seed’s tamper-detection roadmap includes:

- Light sensors detecting case penetration by drilling.
- Accelerometer-based motion-pattern anomaly detection.
- Epoxy-bonded secure element encapsulation.
- Temperature-stable cryptographic counters.
- Remote tamper attestation during mesh sync.

# 9. Summary

Seed’s tamper-detection system blends mechanical, electrical, cryptographic, and user-centric security methods. It treats physical security as a first-class requirement due to off-grid, high-risk deployment environments. The combination of enclosure sensors, conductive mesh, secure-element anti-probe defenses, duress fingerprint unlock, and integrity-enforced firmware ensures that no attacker can compromise user data without detection.

This makes Seed a resilient financial device suitable for humanitarian, rural, disaster-zone, and low-trust environments.
