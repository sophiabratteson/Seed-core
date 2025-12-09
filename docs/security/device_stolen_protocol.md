# Device Stolen Protocol

This document defines Seed’s security procedures, cryptographic safeguards, and user-facing workflows for handling a stolen, lost, or confiscated device. Seed is designed for deployment in regions with limited infrastructure and heightened physical-security risks. Because devices may be seized or lost in the field, the system includes protective layers that prevent unauthorized access to funds, identity, or ledger data.

---

# 1. Objectives

- Protect user funds even if an attacker physically controls the device.
- Prevent the thief from impersonating the user or issuing fraudulent transactions.
- Minimize the amount of recoverable data stored on the physical hardware.
- Ensure safe user recovery and re-issuance of credentials.
- Guarantee that the global ledger remains consistent and resistant to tampering.
- Enable optional emergency-wipe actions when the user is under duress.

---

# 2. Security Layers

Seed devices implement multiple independent security defenses:

## Hardware Level
- Secure Element (SE) stores private keys.
- Fingerprint or PIN gatekeeping prevents unauthorized device usage.
- Tamper detection triggers key invalidation on casing breach.
- Memory encryption protects all at-rest data.

## Software Level
- Rate-limited unlock attempts reduce guessing attacks.
- Ledger access requires successful biometric or PIN authentication.
- Signing keys never leave the secure chip.
- Emergency fake-profile unlock triggers decoy mode.

## Network / Ledger Level
- Every transaction requires a valid cryptographic signature.
- Mesh peers reject transactions signed by a flagged or revoked device.
- Trust-score penalties propagate automatically if suspicious activity occurs.

---

# 3. Threat Scenarios

## Scenario 1: Device stolen while locked
- Thief cannot unlock due to biometric/PIN.
- Secure element blocks signing operations.
- All ledger data remains encrypted.
- User marks device as stolen on a secondary Seed or trusted kiosk.
- Device ID is immediately added to the revocation list.

## Scenario 2: Device stolen while unlocked
- Attacker has temporary access.
- Transaction signing still requires SE approval.
- If attacker tries to move large amounts, anomaly detection flags the event.
- User can remotely revoke the device through:
  - Another Seed device
  - A community kiosk
  - A trusted group savings administrator

## Scenario 3: Hostile actor forces user to unlock device
- User activates “decoy identity” by using a special finger or PIN variation.
- Device enters a restricted mode:
  - Shows empty or low-value balance
  - Blocks high-value transfers
  - Prevents ledger synchronization
  - Records the coercion event internally (optional)
- When safely out of danger, user restores normal mode.

## Scenario 4: State seizure or confiscation
- Fingerprint/PIN required to open the wallet.
- Ledger records purged of unnecessary metadata.
- Device-wide encryption prevents forensics recovery.
- SE blocks extraction of private keys even with physical lab equipment.

---

# 4. Emergency Wipe Logic

Seed devices include an erase-on-threat mechanism.

## Trigger Conditions
- Incorrect PIN entered multiple times.
- Forced unlock detected by tamper sensor.
- User activates panic gesture or fake fingerprint.
- Remote wipe signal received via mesh network.

## Wipe Actions
- Overwrite all encrypted payloads with random bytes.
- Destroy private keys stored in the secure element.
- Remove transaction cache (ledger can be recovered from peers).
- Reset device to provisioning mode.

## Post-Wipe Behavior
- Device becomes unusable for attackers.
- Ledger integrity remains unaffected because wiped keys cannot sign new transactions.
- User re-registers on a new Seed device and recovers balance from community peers.

---

# 5. Device Revocation Protocol

When a device is confirmed lost or stolen:

## Step 1: User reports incident
- Via another Seed device
- Via trusted community kiosk
- Via group-savings host device
- Via partner NGO handset

## Step 2: Mesh propagation
- Revocation notice (signed by group authority or user backup key) spreads across the mesh.
- All devices cache the revocation entry.

## Step 3: Enforcement
- Any future transaction signed by the revoked device is automatically rejected.
- Trust-score penalties applied for attempted fraudulent activity.

## Step 4: Restoration on new device
- User’s identity is re-issued using recovery protocol.
- Group savings state, trust-score, and balances restored from peer checkpoints.

---

# 6. Backup Keys and Recovery

Seed uses a community-based recovery system instead of cloud accounts.

## Backup Mechanisms
- 3-out-of-5 recovery phrase distribution across trusted local members.
- Offline QR-style “key shard” cards.
- Optional NGO escrow service for extremely vulnerable populations.

## Recovery Steps
- User gathers required recovery shards.
- New device is provisioned and identity confirmed.
- Ledger state rebuilt using peer synchronization.

---

# 7. Special Protections for High-Risk Environments

Seed is built for conflict zones, refugee camps, and unstable regions. Additional measures include:

- No GPS or cellular radio to avoid location tracking.
- Minimal personal data stored.
- Anonymous mesh addressing when operating in stealth mode.
- Randomized device identifiers to reduce profiling.
- Ledger-sync throttling to avoid radio fingerprinting.

---

# 8. Edge Cases and Advanced Safeguards

## Forgotten PIN
- Recovery via backup-shard process.
- No “password reset” via cloud, protecting privacy.

## Multiple stolen devices in a region
- Mesh nodes throttle suspicious transaction bursts.
- Community validation committees prevent mass theft impact.

## Device duplication attempt
- Cryptographic attestation prevents copy attacks.
- Secure element ensures keys cannot be cloned.

---

# 9. Summary

The Seed stolen-device protocol ensures that even if hostile actors gain full physical control of a device, they cannot:

- Spend user funds
- Extract sensitive data
- Impersonate the user
- Corrupt the ledger
- Spread fraudulent transactions across the mesh

The combination of encrypted hardware, offline-first cryptography, deterministic revocation, and community-driven recovery makes Seed resilient in environments where traditional digital wallets and banking systems would fail.

Seed remains safe, private, and recoverable — even under extreme conditions.
