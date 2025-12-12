# Failure Detection

This document defines how Seed devices and the Seed network detect, classify, and respond to failures in a fully offline-first, distributed environment. Because Seed operates without constant internet access or centralized servers, failure detection must be local, resilient, and capable of operating under extreme constraints.

Failure detection is critical to:
- Protect user funds and data
- Maintain ledger consistency
- Preserve trust in the system
- Enable safe recovery without centralized intervention

---

## 1. Failure Detection Philosophy

Seed follows a **local-first, evidence-based** failure detection model:

- Devices do not assume global visibility.
- Failures are inferred through repeated local signals.
- No single missed message or event is treated as catastrophic.
- Devices prioritize user safety and data integrity over availability.

Failures are categorized, logged, and acted upon using deterministic rules.

---

## 2. Categories of Failures

Seed detects failures across five primary categories:

### 2.1 Power Failures
- Sudden power loss
- Battery depletion below safe thresholds
- Charging circuit malfunction
- Solar or hand-crank input failure

### 2.2 Storage Failures
- Corrupted ledger files
- Failed write or read operations
- Secure storage access errors
- Checkpoint mismatch or rollback failure

### 2.3 Radio and Communication Failures
- Repeated packet transmission failures
- Loss of known neighbors
- Excessive packet loss or retries
- Invalid or malformed incoming messages

### 2.4 Software Failures
- Application crashes or hangs
- Invalid state transitions
- Memory allocation errors
- Watchdog timer triggers

### 2.5 Security and Integrity Failures
- Invalid signatures
- Replay attempts
- Tamper detection triggers
- Secure element communication errors

---

## 3. Failure Signals and Indicators

Seed devices monitor the following indicators to infer failure states:

- Battery voltage trends
- Flash write error counts
- Radio retry counters
- Message checksum failures
- Ledger validation errors
- Missed heartbeat intervals
- Watchdog resets
- Secure element error flags

Each indicator contributes to a **failure confidence score** rather than triggering immediate shutdown.

---

## 4. Failure Confidence Model

Failures are detected using a confidence-based model:

- Each failure signal increments a confidence score
- Scores decay over time if signals stop occurring
- Actions are triggered only when thresholds are crossed

Example thresholds:
- Low confidence → log only
- Medium confidence → restrict certain operations
- High confidence → enter protective mode

This prevents false positives in unstable environments.

---

## 5. Failure Detection Mechanisms

### 5.1 Watchdog Timers
- Hardware watchdog resets device if main loop stalls
- Reset cause is logged and analyzed on reboot

### 5.2 Health Counters
- Persistent counters track repeated failures across reboots
- Prevents infinite crash-restart loops

### 5.3 Heartbeat Monitoring
- Devices expect periodic heartbeats from neighbors
- Missing heartbeats over multiple cycles indicate link degradation

### 5.4 Ledger Consistency Checks
- Ledger validated on startup and after sync
- Any inconsistency triggers isolation mode

---

## 6. Failure States

When failures are detected, devices may enter one of the following states:

### 6.1 Normal
- No active failures
- All subsystems operational

### 6.2 Degraded
- Limited functionality (e.g., no new transactions)
- Sync may be paused
- User notified of degraded status

### 6.3 Isolated
- Device stops accepting external data
- Ledger becomes read-only
- Used during suspected corruption or attack

### 6.4 Recovery
- Device attempts self-healing actions
- Replays checkpoints
- Re-validates ledger and keys

### 6.5 Locked
- Critical security failure detected
- Requires user authentication or admin recovery

---

## 7. Failure Response Actions

Depending on failure type and severity, Seed may:

- Pause transaction creation
- Delay sync operations
- Roll back to last valid checkpoint
- Disable radio temporarily
- Reduce power usage aggressively
- Notify the user via screen or audio
- Trigger emergency wipe if tampering is confirmed

Actions are deterministic and auditable.

---

## 8. Logging and Auditability

All failures are logged locally with:
- Failure type
- Timestamp (relative, not wall-clock)
- Affected subsystem
- Recovery actions taken

Logs are:
- Stored securely
- Read-only once written
- Shareable during sync for network health analysis

---

## 9. Network-Level Failure Awareness

While Seed has no central server, devices can share:
- Aggregated failure statistics
- Anonymized health summaries
- Mesh reliability indicators

This allows the network to:
- Avoid unreliable nodes
- Adjust routing strategies
- Improve overall resilience

No raw failure logs containing sensitive data are shared.

---

## 10. User Experience During Failures

Seed prioritizes clarity and trust:

- Users are informed in simple language
- No technical jargon is shown
- Clear guidance is provided (e.g., “Recharge device”)
- Funds are never silently altered

Failure handling is designed to **build trust**, not confusion.

---

## 11. Security Considerations

Failure detection mechanisms are hardened against abuse:

- Attackers cannot trigger false failures remotely
- Thresholds prevent denial-of-service via malformed packets
- Tamper detection is handled in hardware
- Failure states cannot be escalated without evidence

---

## 12. Testing and Validation

Failure detection logic is tested via:
- Simulated power cuts
- Corrupted storage injections
- Radio jamming scenarios
- Malicious packet fuzzing
- Long-duration offline tests

Results are documented and reviewed regularly.

---

## 13. Future Improvements

Planned enhancements include:
- Predictive failure modeling
- Cross-device failure correlation
- Adaptive thresholds based on environment
- Machine-learning-assisted anomaly detection (optional)

---

## 14. Summary

Seed’s failure detection system enables reliable operation in environments where traditional assumptions fail. By using local signals, confidence-based thresholds, and deterministic responses, Seed maintains safety, integrity, and trust — even without internet access or centralized control.

Failure is expected. Recovery is built in.
