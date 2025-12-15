# Release Engineering

This document defines how Seed software is built, versioned, released, and safely deployed across devices in low-connectivity, offline-first environments. Release engineering ensures that updates are reliable, secure, reversible, and compatible across a heterogeneous mesh network.

---

## 1. Goals of Release Engineering

- Ensure every Seed device runs verified, trusted firmware and software
- Enable safe updates in environments with limited or no internet
- Prevent device bricking or data loss during updates
- Allow staged rollouts and rollback in case of failures
- Maintain compatibility across mixed software versions in the mesh

---

## 2. Release Artifacts

Each release produces the following artifacts:

- Firmware binary (`.bin`) for embedded devices
- Signed firmware manifest
- Ledger schema version descriptor
- Mesh protocol compatibility version
- Changelog and release notes
- Checksum and cryptographic signature files

Artifacts are immutable once released.

---

## 3. Versioning Strategy

Seed uses semantic versioning with offline-safe constraints:

- MAJOR: Breaking changes to ledger, protocol, or security model
- MINOR: Backward-compatible feature additions
- PATCH: Bug fixes and security updates

Example:
- `v1.2.3`

Each firmware image embeds:
- Firmware version
- Ledger schema version
- Mesh protocol version
- Minimum compatible version

---

## 4. Release Channels

Seed supports multiple release channels:

- Stable: Fully tested, default for production devices
- Beta: Early access for field testing
- Dev: Experimental features for internal testing

Devices are provisioned with a default channel and may opt-in to others via secure authorization.

---

## 5. Offline Update Distribution

Updates are distributed through:

- Device-to-device mesh propagation
- Physical transfer (SD card, USB, kiosk)
- Intermittent internet gateways (when available)

Update packages are chunked and resumable to support unreliable links.

---

## 6. Update Verification

Before applying an update, devices verify:

- Cryptographic signature from trusted Seed root key
- Checksum integrity
- Compatibility with current hardware and ledger version
- Sufficient battery and storage availability

Updates failing any check are rejected.

---

## 7. Atomic Update Process

Firmware updates follow an atomic process:

1. Download update into inactive partition
2. Verify integrity and compatibility
3. Mark update as pending
4. Reboot into new firmware
5. Run health and sanity checks
6. Confirm success or trigger rollback

No update modifies the active partition until verification completes.

---

## 8. Rollback Strategy

Devices maintain at least one previous known-good firmware version.

Rollback triggers include:
- Boot failure
- Crash during initialization
- Ledger corruption detection
- Failed post-update health checks

Rollback restores:
- Firmware
- Configuration
- Ledger state (from secure checkpoint)

---

## 9. Mesh Compatibility During Rolling Updates

Seed devices tolerate mixed-version networks:

- Older devices can ignore unknown message fields
- Newer devices downgrade behavior when communicating with older peers
- Protocol version negotiation occurs during handshake

This allows gradual network-wide upgrades.

---

## 10. Release Approval Workflow

Before release to Stable:

- All unit and integration tests must pass
- Security review must be completed
- Backward compatibility must be validated
- Release artifacts must be signed

Approval is documented and auditable.

---

## 11. Emergency Security Releases

In case of critical vulnerabilities:

- Hotfix releases bypass normal cadence
- Devices prioritize security updates
- Mesh propagation favors emergency patches
- Users receive visible security notices

Emergency updates may disable vulnerable features temporarily.

---

## 12. Documentation and Traceability

Each release includes:

- Human-readable release notes
- Machine-readable manifest
- Migration notes (if applicable)
- Known limitations and risks

All releases are archived and traceable by version ID.

---

## 13. Long-Term Maintainability

Release engineering is designed to:

- Support devices in the field for 10+ years
- Minimize forced upgrades
- Allow gradual ecosystem evolution
- Preserve user trust and data integrity

---

## 14. Summary

Seed’s release engineering system enables secure, resilient, and scalable software evolution in environments where traditional update models fail. By combining cryptographic verification, atomic updates, rollback safety, and mesh-aware compatibility, Seed ensures that innovation never compromises reliability or trust.
