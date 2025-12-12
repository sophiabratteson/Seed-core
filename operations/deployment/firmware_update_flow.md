# Firmware Update Flow

This document defines how Seed devices receive, verify, and apply firmware updates in a fully offline-first, low-connectivity environment. The update system is designed to work without continuous internet access, centralized servers, or smartphones, while preserving security, reliability, and device integrity.

---

## 1. Goals

- Enable safe firmware updates without requiring internet access.
- Prevent malicious or unauthorized firmware installation.
- Allow updates to propagate gradually through the mesh network.
- Ensure devices can recover safely from failed updates.
- Support long-term maintainability of deployed Seed devices.

---

## 2. Update Philosophy

Seed firmware updates follow an **offline-first, trust-minimized distribution model**:

- Updates are packaged as signed firmware bundles.
- Any device can carry an update package.
- Updates propagate opportunistically through the mesh.
- Devices independently verify updates before installing.
- No device is required to trust the sender of an update.

There is no “central server” dependency at runtime.

---

## 3. Firmware Update Package Structure

Each firmware update is distributed as a signed package with the following fields:

- firmware_version
- target_hardware_revision
- firmware_binary (compressed)
- firmware_hash (SHA-256)
- signing_key_id
- digital_signature
- release_notes
- minimum_required_bootloader_version
- rollback_supported (true/false)

Packages are immutable once signed.

---

## 4. Update Distribution Methods

Seed supports multiple update transport mechanisms:

- Mesh broadcast between Seed devices
- Physical transfer (USB, SD card, kiosk)
- Trusted provisioning stations
- Field technician devices

Devices do not distinguish how an update arrived — only whether it is valid.

---

## 5. Update Discovery Process

1. Device periodically listens for update metadata broadcasts.
2. Device compares advertised firmware version with its current version.
3. If newer and compatible, the device requests the update package.
4. If storage allows, the package is downloaded or copied locally.
5. The update remains inactive until verified.

Devices may defer updates based on power, storage, or policy constraints.

---

## 6. Verification and Security Checks

Before installation, the device performs all of the following checks:

- Digital signature verification using embedded public keys
- Firmware hash integrity check
- Hardware compatibility verification
- Bootloader version compatibility check
- Rollback policy validation

If **any** check fails, the update is rejected and logged.

---

## 7. Installation Flow

1. Device enters update-ready state.
2. Active applications are gracefully shut down.
3. Firmware is written to an inactive partition.
4. Integrity is re-verified after write.
5. Device updates boot flags.
6. Device reboots into new firmware.

The previous firmware is preserved if rollback is supported.

---

## 8. Safe Boot and Rollback Mechanism

On reboot:

- Bootloader performs a health check.
- If the new firmware fails to initialize correctly:
  - The device automatically rolls back to the previous firmware.
  - The failed update is marked invalid.
  - A failure report is generated.

This guarantees devices never become permanently bricked.

---

## 9. Update Policies and Constraints

Firmware updates may be delayed or blocked if:

- Battery level is below a safe threshold
- Device is in active financial operation
- Storage space is insufficient
- Update is not approved for the region
- Update violates governance rules

Policies are configurable via firmware configuration files.

---

## 10. Audit Logging

All update actions are logged locally:

- Update received
- Verification success or failure
- Installation attempt
- Rollback events
- Final firmware state

Logs are encrypted and can be shared during diagnostics or audits.

---

## 11. Governance and Trust Model

- Only firmware signed by authorized Seed keys can be installed.
- Keys are rotated via governance-approved procedures.
- Emergency revocation lists can be distributed through the mesh.
- No single device can force an update on others.

This prevents both centralized abuse and local coercion.

---

## 12. Failure Scenarios and Recovery

Handled failure cases include:

- Interrupted transfers
- Corrupted firmware packages
- Power loss during installation
- Incompatible hardware targets
- Malicious update attempts

In all cases, the device returns to a safe, known-good state.

---

## 13. Future Enhancements

Planned extensions include:

- Differential (delta) firmware updates
- Multi-signature firmware approval
- Region-specific firmware branches
- Update simulation and staging modes
- Long-term support (LTS) firmware tracks

---

## 14. Summary

Seed’s firmware update flow ensures that devices can evolve securely over time without sacrificing resilience, decentralization, or user safety. By combining cryptographic verification, offline-first distribution, and robust rollback mechanisms, Seed devices remain trustworthy even in the most constrained environments.
