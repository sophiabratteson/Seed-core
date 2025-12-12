# Device Health Metrics

This document defines the health metrics that Seed devices track locally and, when possible, share across the mesh network to ensure reliability, safety, and long-term sustainability. Because Seed operates in offline, low-infrastructure environments, device health monitoring must be lightweight, resilient, and privacy-preserving.

---

## 1. Purpose of Device Health Metrics

The goals of device health monitoring in Seed are to:

- Detect early signs of hardware or software failure.
- Enable preventative maintenance instead of reactive replacement.
- Support fleet-level insights without centralized servers.
- Preserve user trust by avoiding invasive monitoring.
- Maintain system reliability in harsh environments.

All metrics are designed to be:
- Locally computed
- Intermittently shared
- Safe to store offline
- Resistant to tampering

---

## 2. Core Health Metric Categories

Seed device health metrics are grouped into five major categories:

1. Power and Energy
2. Hardware Integrity
3. Radio and Network Health
4. Software and Ledger Health
5. Environmental Conditions

Each category contains metrics that can be sampled periodically or event-driven.

---

## 3. Power and Energy Metrics

Power reliability is critical for Seed’s usability.

Tracked metrics include:

- Battery State of Charge (percentage)
- Battery Voltage
- Charge/Discharge Cycles Count
- Estimated Battery Health (capacity degradation)
- Charging Source Activity:
  - Solar input detected
  - Hand-crank input detected
  - External USB input detected
- Average Daily Power Consumption
- Low-Power Events Count
- Emergency Shutdown Events

Use cases:
- Predict battery replacement needs
- Detect failing solar or hand-crank subsystems
- Optimize duty cycles

---

## 4. Hardware Integrity Metrics

These metrics track the physical condition of the device.

Tracked metrics include:

- Secure Element Status:
  - Initialized
  - Locked
  - Error detected
- Fingerprint Sensor Health:
  - Enrollment success rate
  - Read failure count
- Button/Input Health:
  - Missed presses
  - Stuck button detection
- Display Health:
  - Refresh failure count
  - Ghosting detection (e-ink specific)
- Internal Storage Health:
  - Write error count
  - Corruption detection
- Tamper Detection Events:
  - Case open events
  - Secure element tamper triggers

Use cases:
- Detect compromised or damaged devices
- Trigger protective actions (lockdown, wipe)
- Support warranty and replacement decisions

---

## 5. Radio and Network Health Metrics

These metrics evaluate how well the device communicates with the mesh.

Tracked metrics include:

- Neighbor Count (active peers)
- Successful Packet Transmissions
- Failed Packet Transmissions
- Average Retries per Packet
- Signal Strength (RSSI)
- Signal-to-Noise Ratio (SNR)
- Last Successful Sync Timestamp
- Message Queue Backlog Size
- Mesh Partition Detection Events

Use cases:
- Diagnose connectivity issues
- Optimize routing and sync frequency
- Identify isolated or failing nodes

---

## 6. Software and Ledger Health Metrics

These metrics ensure financial integrity and software stability.

Tracked metrics include:

- Ledger Size (number of transactions)
- Pending Transactions Count
- Orphaned Transactions Count
- Invalid Transaction Rejections
- Conflict Resolution Events
- Last Successful Ledger Checkpoint
- Storage Usage Percentage
- Firmware Version
- Firmware Integrity Check Result (hash validation)
- Unexpected Reset Count
- Watchdog Trigger Events

Use cases:
- Detect ledger corruption
- Identify firmware instability
- Support safe upgrades and rollbacks

---

## 7. Environmental Metrics

Seed devices often operate in extreme conditions.

Tracked metrics include:

- Internal Temperature
- External Temperature (if available)
- Overheat Events
- Cold Start Failures
- Humidity Exposure (if sensor present)
- Dust/Water Exposure Flags (from enclosure sensors)

Use cases:
- Improve enclosure design
- Adjust operating parameters
- Prevent damage in unsafe conditions

---

## 8. Metric Sampling and Storage Strategy

To conserve power and storage:

- Metrics are sampled at configurable intervals.
- Critical events are logged immediately.
- Historical data is summarized (rolling averages).
- Raw logs are pruned automatically.
- Metrics are stored in encrypted local storage.

---

## 9. Sharing Health Metrics Across the Mesh

Health metrics may be shared in limited form to support system-level resilience.

Rules:
- Only non-personal metrics are shared.
- Metrics are anonymized by device ID.
- Sharing is opportunistic and low-frequency.
- Users can opt out of health sharing.
- Aggregated metrics only (no raw logs).

Shared metrics may include:
- Battery health category (Good / Warning / Critical)
- Connectivity health status
- Firmware version distribution
- Failure pattern alerts

---

## 10. Privacy and Trust Considerations

Seed health monitoring is designed to avoid surveillance risks.

Safeguards include:
- No GPS or location tracking
- No usage profiling tied to identity
- No continuous telemetry
- No central collection by default
- Clear user-facing explanations of metrics

Health metrics exist to protect users, not monitor them.

---

## 11. Automated Responses and Alerts

Devices may take automatic actions based on health metrics:

- Enter low-power mode
- Reduce sync frequency
- Disable non-essential features
- Warn user via display or audio
- Lock device on tamper detection
- Trigger emergency wipe if compromised

---

## 12. Example Health Summary Snapshot

Device ID: NODE_A
Battery: 72% (Healthy)
Charge Cycles: 312
Radio: 4 neighbors, stable
Ledger: 2,143 transactions
Pending TXs: 0
Firmware: v0.3.1 (verified)
Temperature: 31°C
Tamper Events: none
Overall Status: Healthy

---

## 13. Investor and System Impact Summary

Robust device health metrics enable:

- Lower operational costs
- Longer device lifespan
- Higher trust in offline financial systems
- Scalable deployments without constant support
- Data-driven improvements without central servers

This health framework is a foundational layer for Seed’s resilience and long-term viability.

---

## 14. Future Extensions

Planned enhancements include:

- Predictive failure modeling
- Health-based routing decisions
- Community repair indicators
- Automated warranty validation
- Health-aware trust scoring (non-financial)

---

## 15. Summary

Device health metrics ensure that Seed devices remain reliable, secure, and trustworthy in environments where traditional monitoring is impossible. By combining local intelligence, privacy-preserving design, and mesh-based sharing, Seed maintains system health without sacrificing user autonomy or safety.
