# Monitoring Overview

This document defines how Seed monitors device health, network integrity, and system performance in environments with limited or no internet connectivity. Monitoring is designed to be offline-first, privacy-preserving, and resilient, while still enabling operators to detect failures, abuse, or degradation across deployments.

Seed does not rely on centralized, real-time dashboards. Instead, monitoring data is collected locally, summarized on-device, and propagated opportunistically through the mesh network or during periodic gateway sync events.

---

## 1. Monitoring Goals

The monitoring system is designed to achieve the following objectives:

- Detect hardware failures before they cause user data loss
- Identify degraded network performance or mesh fragmentation
- Track power health to prevent unexpected device shutdowns
- Surface security anomalies or suspicious behavior
- Enable post-hoc analysis without continuous connectivity
- Preserve user privacy and financial confidentiality
- Operate reliably in low-power, low-bandwidth environments

---

## 2. Monitoring Philosophy

Seed monitoring follows these principles:

- Offline-first: All monitoring works without internet access
- Local-first: Devices self-monitor and log their own health
- Event-driven: Logs are triggered by state changes, not constant polling
- Minimal data: Only operational metadata is collected
- Mesh-propagated: Summaries move through the mesh opportunistically
- Human-readable: Logs can be reviewed locally by operators
- Fail-safe: Monitoring failure never blocks financial operations

---

## 3. Monitoring Layers

Monitoring occurs at multiple layers of the Seed system.

### Device Layer
Tracks the physical health of each Seed device.

### Firmware Layer
Tracks internal software behavior and error states.

### Ledger Layer
Tracks ledger integrity and synchronization status.

### Mesh Network Layer
Tracks connectivity and message propagation.

### Operational Layer
Tracks deployment-wide patterns and risks.

Each layer generates its own monitoring signals.

---

## 4. Device Health Metrics

Each device continuously monitors the following parameters:

- Battery voltage and charge state
- Charge source availability (solar, hand crank)
- Temperature thresholds
- Power consumption rate
- Unexpected power resets
- Secure element availability
- Peripheral sensor availability (fingerprint, buttons, display)

Metrics are logged locally and summarized periodically.

Critical thresholds trigger immediate alerts.

---

## 5. Firmware and Software Monitoring

The firmware records:

- Boot cycles and crash counts
- Watchdog resets
- Memory usage and allocation failures
- Flash write errors
- Firmware version and checksum
- Update success or rollback events

Error states are categorized by severity:

- Informational
- Warning
- Critical
- Fatal

Fatal errors trigger safe-mode behavior.

---

## 6. Ledger Integrity Monitoring

Ledger monitoring ensures financial correctness without revealing balances or identities.

Tracked indicators include:

- Ledger checkpoint frequency
- Validation failures
- Conflict resolution frequency
- Orphaned transaction counts
- Replay attempt detection
- Signature verification failures

Only metadata is logged. No transaction amounts or identities are exposed.

---

## 7. Mesh Network Monitoring

Mesh-related metrics include:

- Neighbor count
- Link stability duration
- Packet loss rate (estimated)
- Message retry counts
- Gossip propagation latency
- Network partition detection

Devices generate periodic mesh summaries that can be exchanged during sync events.

---

## 8. Monitoring Data Storage

Monitoring data is stored locally using a ring-buffer model:

- Fixed-size storage to prevent flash exhaustion
- Oldest records overwritten first
- Critical events are pinned until acknowledged
- Logs are cryptographically signed

Storage is encrypted at rest using device keys.

---

## 9. Monitoring Data Propagation

Monitoring data moves through the system in three ways:

1. Local review on the device
2. Opportunistic mesh propagation (summaries only)
3. Gateway sync during maintenance or audits

Raw logs never broadcast automatically.

---

## 10. Alerts and Escalation

Devices trigger alerts under the following conditions:

- Repeated failed boots
- Critical power degradation
- Secure element failure
- Ledger corruption detection
- Suspected tampering
- Persistent mesh isolation

Alerts are displayed locally and flagged for operator review during sync.

---

## 11. Operator Access Model

Monitoring access is role-based:

- End users see only device health indicators
- Field operators see operational summaries
- Administrators see aggregated anonymized metrics
- Auditors see signed historical logs

Access never exposes financial transaction data.

---

## 12. Abuse and Anomaly Detection

Monitoring supports detection of:

- Abnormally high transaction rejection rates
- Repeated replay attempts
- Suspicious trust score manipulation
- Malicious firmware downgrade attempts
- Coordinated mesh flooding behavior

Detected anomalies are flagged for investigation but do not halt normal operation automatically.

---

## 13. Failure Handling Strategy

If monitoring systems fail:

- Core financial operations continue uninterrupted
- Monitoring restarts automatically on reboot
- Logs resume from last valid checkpoint
- Devices enter degraded monitoring mode if necessary

Monitoring failure never bricks a device.

---

## 14. Privacy and Compliance Considerations

Monitoring explicitly avoids:

- Personal identifiers
- Financial balances
- Transaction contents
- User behavior profiling

All collected data complies with minimal-data and purpose-limitation principles.

---

## 15. Future Enhancements

Planned improvements include:

- Predictive battery failure modeling
- Mesh health heatmaps via gateway aggregation
- Zero-knowledge proofs for integrity checks
- Automated maintenance recommendations
