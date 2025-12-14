# Unit Test Plan

This document defines the unit testing strategy for the Seed software stack. Unit tests verify that individual software components function correctly in isolation, without reliance on hardware radios, mesh peers, or external systems. This plan ensures correctness, safety, and predictability at the lowest level of the system.

---

## 1. Goals of Unit Testing

The unit test program is designed to:

- Verify correctness of core logic before integration
- Detect regressions early during development
- Ensure deterministic behavior across devices
- Validate security-critical code paths
- Enable safe refactoring and iteration
- Support investor and auditor confidence in system reliability

Unit tests are required for all non-trivial logic that affects funds, identity, trust scores, synchronization, or security.

---

## 2. Scope of Unit Tests

Unit tests cover logic that can be executed without:

- Radio hardware
- Mesh neighbors
- External clocks
- Persistent storage devices

The following areas are in scope:

- Ledger engine logic
- Transaction validation
- Conflict resolution
- Trust score calculations
- Message parsing and serialization
- Cryptographic helpers
- Configuration loading
- Error handling paths

Out of scope:

- Radio transmission timing
- Power consumption
- User interface rendering
- Full device-to-device sync (covered in integration tests)

---

## 3. Unit Test Categories

### 3.1 Ledger Engine Tests

- Transaction creation
- Ledger insertion
- Duplicate transaction rejection
- Balance tracking
- Deterministic ordering
- Checkpoint generation
- Ledger replay correctness

### 3.2 Transaction Validation Tests

- Valid transaction acceptance
- Insufficient balance rejection
- Malformed transaction rejection
- Invalid signature rejection
- Replay protection
- Lamport clock validation

### 3.3 Conflict Resolution Tests

- Same tx_id, different content
- Same lamport, different device_id
- Parallel spending attempts
- Out-of-order arrival
- Missing causal dependencies
- Idempotent re-application

Each test must assert identical final ledger state regardless of input order.

---

## 4. Trust Score Unit Tests

- Trust score increment on successful repayment
- Trust score decrement on default
- Group savings participation scoring
- Upper and lower bound enforcement
- Non-negative score guarantee
- Deterministic updates across devices

Trust score logic must be fully testable without mesh communication.

---

## 5. Mesh Protocol Parsing Tests

- Message header parsing
- Payload decoding
- Invalid message rejection
- Checksum verification
- Unknown message type handling
- Backward compatibility checks

No radio transmission is required; tests operate on raw byte buffers.

---

## 6. Cryptography and Security Tests

- Signature generation and verification
- Key loading and storage
- Tampered message detection
- Replay attack detection
- Secure wipe trigger logic
- Failed authentication handling

All cryptographic tests use deterministic test keys, never production keys.

---

## 7. Configuration and State Tests

- Default configuration loading
- Invalid config detection
- Missing parameter handling
- Safe fallback behavior
- State persistence serialization
- State restoration correctness

---

## 8. Error Handling Tests

- Graceful handling of malformed inputs
- Recovery from partial state corruption
- Safe failure on invalid operations
- No silent failure conditions
- Logged error generation

Every error path must be exercised by at least one unit test.

---

## 9. Test Structure and Organization

Unit tests are organized by module:

- ledger/
- mesh/
- security/
- utils/
- config/

Each module includes:

- test_<module>.c or test_<module>.py
- Clear test naming
- Independent test execution
- No shared mutable state

---

## 10. Determinism Requirements

All unit tests must:

- Produce identical results on every run
- Avoid reliance on system time
- Avoid randomness unless explicitly seeded
- Avoid platform-specific behavior

Determinism is required to support offline convergence guarantees.

---

## 11. Continuous Testing Strategy

- Unit tests run on every commit
- Tests must pass before merge
- Failed tests block releases
- Coverage reports generated regularly
- Critical modules require near-100% coverage

---

## 12. Deliverables

This unit test plan produces:

- A comprehensive unit test suite
- Reproducible test results
- Audit-ready evidence of correctness
- A stable foundation for integration testing

---

## 13. Summary

Unit testing is the foundation of Seed’s reliability. By rigorously testing core logic in isolation, Seed ensures that higher-level behaviors—such as offline synchronization, trust scoring, and financial safety—are built on provably correct components. This approach reduces risk, accelerates development, and increases investor confidence.
