# Offline Sync Metrics

This document defines the metrics used to measure, monitor, and validate the performance, reliability, and integrity of Seed’s offline-first synchronization system. These metrics are designed to work without continuous internet connectivity and to support field deployments in low-resource, low-observability environments.

---

## 1. Purpose of Offline Sync Metrics

Offline sync metrics serve four primary goals:

- Verify that devices reliably exchange and merge data without internet access
- Detect sync failures, delays, or data inconsistencies early
- Enable field operators and developers to assess network health over time
- Provide investor- and regulator-ready evidence of system robustness

Metrics are designed to be lightweight, locally computable, and exportable when connectivity becomes available.

---

## 2. Metric Collection Principles

All offline sync metrics follow these principles:

- **Offline-first**: Metrics are collected locally without network dependency
- **Low overhead**: Minimal storage, CPU, and power usage
- **Privacy-preserving**: No personally identifiable information is stored
- **Deterministic**: Metrics are calculated the same way on all devices
- **Deferred reporting**: Metrics sync opportunistically when possible

---

## 3. Core Sync Performance Metrics

### 3.1 Sync Attempt Count
- Number of attempted ledger synchronization events
- Incremented whenever a device initiates or responds to a sync exchange
- Used to measure engagement frequency and network activity

### 3.2 Successful Sync Count
- Number of sync attempts that complete without error
- A sync is considered successful when ledgers converge deterministically
- Used to compute sync success rate

### 3.3 Sync Success Rate
- Calculated as:  
  successful_syncs / total_sync_attempts
- Indicates overall mesh reliability
- Tracked per device and per time window

---

## 4. Sync Latency Metrics

### 4.1 Sync Duration
- Time elapsed between sync initiation and completion
- Measured using local monotonic clocks
- Stored as a rolling average to reduce storage overhead

### 4.2 Transaction Propagation Delay
- Time between transaction creation and first observation on another device
- Estimated using Lamport clock deltas rather than wall-clock time
- Indicates mesh responsiveness

---

## 5. Data Integrity Metrics

### 5.1 Duplicate Transaction Rate
- Percentage of received transactions already present in ledger
- High rates may indicate excessive rebroadcasting or inefficient routing

### 5.2 Conflict Encounter Rate
- Number of detected ledger conflicts per sync
- Includes double-spend attempts, ordering conflicts, and causal gaps
- Used to evaluate conflict resolution effectiveness

### 5.3 Conflict Resolution Success Rate
- Percentage of conflicts resolved deterministically without manual intervention
- Target: 100%

---

## 6. Ledger Convergence Metrics

### 6.1 Ledger Hash Agreement
- Devices compute a cryptographic hash of final ledger state
- Agreement indicates convergence
- Disagreement triggers resync or audit mode

### 6.2 Orphan Transaction Count
- Number of transactions missing causal parents
- Expected to decrease over time as network connectivity improves
- Persistent orphans may indicate dropped messages or malicious behavior

---

## 7. Resource Usage Metrics

### 7.1 Sync Power Cost
- Estimated energy used per sync event
- Derived from radio on-time and CPU usage
- Used to optimize duty cycles and power budgeting

### 7.2 Storage Growth Rate
- Rate at which ledger and metric logs consume storage
- Used to determine pruning and checkpointing schedules

---

## 8. Failure and Degradation Metrics

### 8.1 Sync Failure Count
- Number of failed sync attempts
- Categorized by failure reason:
  - Corrupted payload
  - Signature verification failure
  - Incomplete transfer
  - Protocol version mismatch

### 8.2 Retry Rate
- Average number of retries required per successful sync
- High values may indicate poor radio conditions or routing inefficiencies

---

## 9. Metric Persistence and Export

- Metrics are stored locally in compressed, append-only logs
- Periodic checkpoints summarize historical data
- When internet or gateway access becomes available:
  - Metrics may be exported for diagnostics, research, or investor reporting
- Export is optional and user-controlled

---

## 10. Field Monitoring Use Cases

Offline sync metrics enable:

- Comparing performance across regions and environments
- Identifying hardware or firmware regressions
- Demonstrating system resilience to partners and funders
- Supporting audits and pilot evaluations

---

## 11. Security and Privacy Considerations

- Metrics contain no user balances, identities, or transaction details
- All metric logs are integrity-protected
- Metric export is authenticated and encrypted
- Tampering with metrics is detectable via checksum mismatch

---

## 12. Future Extensions

Planned enhancements include:

- Mesh-wide aggregate metrics via gossip
- Anomaly detection for malicious nodes
- Adaptive sync tuning based on observed conditions
- Visualization dashboards for field operators

---

## 13. Summary

Offline sync metrics provide the quantitative foundation for validating Seed’s core promise: a reliable, secure, and scalable financial system that functions without internet infrastructure. These metrics ensure that performance, integrity, and resilience can be measured even in the most connectivity-constrained environments.
