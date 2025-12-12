# Rollback Procedure

This document defines how Seed safely rolls back firmware, configuration, or protocol updates in the event of failure, instability, or security risk. Because Seed operates in offline, low-connectivity, and high-risk environments, rollback must be automatic, local-first, and survivable without internet access.

---

## 1. Purpose and Design Principles

The rollback procedure ensures that:
- Devices remain functional even after failed updates
- Users never lose access to funds or ledger history
- Bricked devices are avoided in remote environments
- Rollbacks do not require internet connectivity
- Security is maintained during downgrade operations

Design principles:
- Fail-safe by default
- Offline-first
- Deterministic behavior
- Minimal user intervention
- Tamper-resistant execution

---

## 2. What Can Be Rolled Back

Seed supports rollback for the following components:

- Device firmware
- Mesh protocol logic
- Ledger engine logic
- Device configuration parameters
- User interface application code

Rollback does **not** delete:
- Ledger transaction history
- User balances
- Trust scores
- Cryptographic identity keys

User financial data is always preserved across rollbacks.

---

## 3. Versioning Model

Each device maintains three firmware slots:

- **Active Version**  
  The currently running firmware.

- **Previous Stable Version**  
  The last known good version.

- **Staged Update Version**  
  The newly installed but not yet committed version.

Each version is tagged with:
- Version number
- Build hash
- Release timestamp
- Compatibility flags

---

## 4. Update Lifecycle with Rollback Support

Firmware updates follow this sequence:

1. New firmware is received (via mesh or physical transfer)
2. Firmware is written to the staged slot
3. Integrity checks are performed
4. Device reboots into staged firmware
5. Health checks run during a probation window
6. If successful, staged firmware is promoted to active
7. If failure occurs, rollback is triggered automatically

No update is committed until the probation window completes.

---

## 5. Automatic Rollback Triggers

Rollback is automatically initiated if any of the following occur:

- Device fails to boot within timeout
- Watchdog timer expires repeatedly
- Mesh radio fails to initialize
- Ledger engine fails validation checks
- Power consumption exceeds safety thresholds
- UI becomes non-responsive
- Security module reports integrity violation

Automatic rollback requires no user action.

---

## 6. Manual Rollback Triggers

Users or administrators may manually trigger rollback via:

- Physical button sequence during boot
- Secure menu option (authenticated)
- Trusted service mode (maintenance access)

Manual rollback is protected by:
- Device authentication
- Rate limiting
- Tamper detection monitoring

---

## 7. Rollback Execution Flow

When rollback is triggered:

1. Device enters rollback mode
2. Active firmware is marked invalid
3. Previous stable firmware is restored
4. Configuration compatibility is checked
5. Ledger and user data are reattached
6. Device reboots into restored version
7. Rollback event is logged locally

Rollback always preserves user funds and identity.

---

## 8. Ledger Safety During Rollback

Ledger protection rules:
- Ledger data is stored in a separate partition
- Ledger format must be backward compatible
- Ledger schema version is checked before downgrade
- If schema mismatch exists, read-only mode is enabled

In worst-case scenarios:
- Device allows balance viewing
- Device blocks new transactions
- Funds remain safe until update compatibility restored

---

## 9. Security Protections

Rollback protections include:

- Firmware signature verification
- Secure boot enforcement
- Rollback version allowlist
- Prevention of downgrade attacks
- Protection against malicious firmware injection

Devices will not roll back to:
- Known vulnerable versions
- Blacklisted firmware hashes
- Unsigned or tampered builds

---

## 10. Power-Failure Handling

Rollback is resilient to power loss:

- Flash writes are transactional
- Version pointers are updated atomically
- Power loss during rollback resumes safely
- No partial firmware states are committed

This ensures safe operation in unstable power environments.

---

## 11. Mesh Network Awareness

After rollback:
- Device advertises its version to neighbors
- Mesh peers adjust compatibility behavior
- Incompatible message types are ignored
- Ledger sync continues safely

Rollback does not fragment the mesh network.

---

## 12. Logging and Auditability

Rollback events are logged locally with:
- Timestamp
- Trigger reason
- Firmware versions involved
- Outcome status

Logs can be:
- Reviewed by the user
- Exported for diagnostics
- Used in field failure analysis

---

## 13. User Experience Considerations

User-facing behavior during rollback:
- Clear visual indication
- Minimal technical jargon
- No exposure of sensitive data
- Automatic recovery without panic prompts

Users are never required to understand firmware internals.

---

## 14. Failure Scenarios and Recovery

If rollback fails:
- Device enters safe recovery mode
- Minimal UI is enabled
- Ledger remains readable
- Device awaits trusted recovery firmware

This prevents permanent device loss.

---

## 15. Investor and Operational Impact

This rollback system:
- Reduces operational risk
- Enables safe remote updates
- Supports large-scale deployments
- Lowers support costs
- Increases regulator confidence

Robust rollback capability is critical for trust in decentralized financial infrastructure.

---

## 16. Summary

Seed’s rollback procedure ensures that devices remain reliable, secure, and financially safe even in the face of failed updates, power instability, or malicious conditions. By separating firmware from user data, enforcing strict validation, and prioritizing offline-first recovery, Seed delivers resilient financial infrastructure for the most challenging environments.

Rollback is not an edge case — it is a core system guarantee.
