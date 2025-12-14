# Hardware-in-the-Loop (HIL) Testing

This document defines the Hardware-in-the-Loop (HIL) testing strategy for Seed. HIL testing validates that firmware, hardware, and system logic function correctly together under realistic physical conditions. These tests bridge the gap between pure software simulation and real-world deployment.

---

## Purpose of Hardware-in-the-Loop Testing

Hardware-in-the-Loop testing ensures that:

- Firmware behaves correctly when running on real Seed hardware
- Software assumptions match physical hardware behavior
- Radio, power, storage, and input components interact correctly
- Edge cases caused by hardware limitations are discovered early
- Failures can be safely reproduced before field deployment

HIL testing is essential for Seed because the system operates offline, in harsh environments, and without continuous supervision.

---

## Scope of HIL Testing

HIL tests cover the following system layers:

- Core firmware execution
- Power management and energy harvesting
- Radio communication and mesh behavior
- Secure storage and cryptographic operations
- User input and device interaction
- Display rendering and feedback
- Fault handling and recovery logic

Each test combines real hardware with controlled software inputs.

---

## Test Environment Setup

### Required Hardware

- Seed prototype device (or dev board equivalent)
- LoRa radio module with antenna
- E-ink display
- Battery (LiFePO4 or LiPo)
- Solar panel or hand-crank generator (if applicable)
- Secure element / fingerprint sensor (if present)
- Debug interface (USB, SWD, UART)

### Required Software

- Compiled Seed firmware image
- Host-side test controller (laptop or test harness)
- Serial logging and debugging tools
- Power measurement tools (optional but recommended)

---

## Core HIL Test Categories

### 1. Boot and Initialization Tests

- Device boots from cold power-off state
- Secure boot validation succeeds
- Configuration files load correctly
- Device identity is initialized
- No unintended resets occur

Expected Outcome:
- Device reaches idle state with no errors

---

### 2. Power System Tests

- Battery voltage reading accuracy
- Charging behavior under solar input
- Hand-crank input handling
- Low-power sleep transitions
- Brownout and sudden power loss recovery

Fault Injection:
- Disconnect battery mid-operation
- Simulate low-voltage conditions

Expected Outcome:
- No data corruption
- Safe shutdown or recovery behavior

---

### 3. Radio and Mesh Communication Tests

- Packet transmission and reception
- Neighbor discovery
- Message retries and acknowledgments
- Partial packet loss handling
- Multi-device relay behavior

Test Scenarios:
- Two devices exchanging transactions
- Three or more devices forming a mesh
- Temporary radio interference

Expected Outcome:
- Messages eventually deliver
- Ledger remains consistent

---

### 4. Ledger and Storage Tests

- Transaction creation on device
- Ledger persistence across power cycles
- Conflict resolution on sync
- Corruption detection and recovery

Fault Injection:
- Interrupt write operations
- Inject malformed transactions

Expected Outcome:
- Ledger integrity preserved
- Invalid data rejected safely

---

### 5. Security and Authentication Tests

- Key generation and storage
- Message signing and verification
- Secure element communication
- Fingerprint authentication flow

Attack Simulations:
- Replay old signed messages
- Attempt unauthorized access

Expected Outcome:
- Unauthorized actions rejected
- No private key leakage

---

### 6. User Interface and Input Tests

- Button press handling
- Long-press vs short-press logic
- Display updates on state change
- Audio or visual alerts (if applicable)

Expected Outcome:
- Inputs map correctly to actions
- UI remains responsive

---

### 7. Failure and Recovery Tests

- Forced firmware crash
- Watchdog reset behavior
- Storage corruption scenarios
- Radio module failure

Expected Outcome:
- Device recovers to known safe state
- Errors logged appropriately

---

## Test Automation Strategy

- Test scripts trigger firmware actions via serial or radio
- Host machine validates responses
- Logs are collected for post-test analysis
- Reproducible test cases are versioned

HIL tests may be semi-automated initially and become more automated over time.

---

## Metrics Collected

- Boot time
- Power consumption per state
- Radio transmission success rate
- Sync convergence time
- Error and reset frequency

These metrics inform hardware revisions and firmware optimization.

---

## Test Documentation and Traceability

For each HIL test:

- Test ID
- Hardware configuration
- Firmware version
- Expected result
- Actual result
- Pass/Fail status
- Notes and anomalies

All results are logged in the repository for auditability.

---

## Exit Criteria

Hardware-in-the-Loop testing is considered successful when:

- All critical tests pass consistently
- No unrecoverable failures are observed
- Ledger integrity is maintained across all scenarios
- Device behavior matches system specifications

---

## Summary

Hardware-in-the-Loop testing validates that Seed is not just theoretically correct, but physically reliable. By combining real hardware with controlled test inputs, Seed ensures resilience, security, and correctness before large-scale deployment.

HIL testing is a foundational step toward safe field trials and investor-ready demonstrations.
