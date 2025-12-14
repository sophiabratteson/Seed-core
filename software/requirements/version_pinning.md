# Software Version Pinning Strategy

This document defines Seed’s version pinning strategy across software, firmware, tooling, and dependencies. Version pinning ensures reproducibility, stability, security, and long-term maintainability in environments where updates may be infrequent, delayed, or impossible due to limited connectivity.

Seed is designed to operate in offline-first and low-connectivity contexts, making deterministic software behavior critical.

---

## 1. Objectives of Version Pinning

The version pinning strategy aims to:

- Ensure deterministic behavior across devices in the field
- Prevent breaking changes caused by upstream dependency updates
- Enable reproducible builds across development, testing, and deployment
- Support long-term device lifecycles without forced upgrades
- Simplify debugging and forensic analysis of device behavior
- Allow controlled, deliberate upgrade paths

---

## 2. Scope of Version Pinning

Version pinning applies to the following layers:

- Device firmware
- Mesh protocol implementations
- Ledger and sync logic
- Cryptographic libraries
- Build toolchains
- Simulation and prototype environments
- Developer tooling

Each layer has different pinning strictness based on risk and update frequency.

---

## 3. Firmware and Embedded Dependencies

### 3.1 Microcontroller SDKs

- MCU SDK versions are pinned exactly (major.minor.patch)
- No automatic SDK upgrades are allowed
- SDK upgrades require:
  - Full regression testing
  - Power consumption re-validation
  - Security review
  - Radio behavior re-testing

Example:
- ESP-IDF v5.1.2 (pinned)
- Nordic SDK v17.1.0 (pinned)

---

### 3.2 Radio Drivers

- LoRa driver versions are pinned per chipset
- Firmware includes driver version metadata
- Driver updates require:
  - RF compliance re-check
  - Range and latency re-testing
  - Backward compatibility validation

---

### 3.3 Cryptographic Libraries

- Cryptographic primitives are pinned to audited versions only
- No floating versions allowed
- Hash, signature, and encryption implementations must remain stable across device lifetime

Examples:
- SHA-256 implementation vX.Y.Z
- ECDSA library vA.B.C

---

## 4. Mesh Protocol Versioning

### 4.1 Protocol Version Field

- Every mesh message includes:
  - protocol_version
  - schema_version

Devices refuse to process messages from incompatible protocol versions unless explicitly configured for backward compatibility.

---

### 4.2 Backward Compatibility Rules

- Minor version updates must be backward compatible
- Major version updates require explicit migration logic
- Devices running older versions may continue operating locally without forced upgrades

---

## 5. Ledger and Data Schema Pinning

### 5.1 Transaction Schema Versions

- JSON schemas are versioned and immutable once released
- Ledger entries store schema_version metadata
- New schema versions may be added, never modified retroactively

---

### 5.2 Conflict Resolution Logic Versions

- Conflict resolution algorithms are version-pinned
- Deterministic behavior must remain identical across devices
- Any change requires:
  - Formal proof of determinism
  - Migration simulation
  - Explicit rollout policy

---

## 6. Simulation and Prototype Environments

### 6.1 Python Dependencies

- All Python dependencies use exact version pins
- requirements.txt includes full dependency graph
- No version ranges allowed

Example:
- python==3.12.10
- numpy==1.26.4

---

### 6.2 Simulation Reproducibility

- Simulation outputs must be reproducible across machines
- Randomness is seeded explicitly
- Version metadata is embedded in simulation outputs

---

## 7. Build Toolchain Pinning

### 7.1 Compiler Versions

- Compiler versions are pinned exactly
- Build artifacts record compiler version hashes

Examples:
- GCC ARM Embedded 12.2.1
- Clang 16.0.6

---

### 7.2 Build Scripts

- Build scripts are versioned alongside source
- CI pipelines enforce pinned toolchains
- No “latest” tags allowed

---

## 8. Upgrade and Migration Policy

### 8.1 Controlled Upgrades

Upgrades occur only when:

- A critical security fix is required
- Regulatory changes demand updates
- Verified performance or stability improvements exist

---

### 8.2 Offline Upgrade Constraints

- Devices must remain functional without upgrades
- Upgrade packages are:
  - Cryptographically signed
  - Version-locked
  - Backward compatible where possible

---

## 9. Version Metadata Storage

Each device stores:

- Firmware version
- Protocol version
- Schema versions
- Dependency hashes
- Build timestamp

This metadata supports diagnostics, audits, and incident response.

---

## 10. Risk Management

Risks mitigated by version pinning:

- Silent behavior changes
- Supply chain attacks
- Inconsistent ledger behavior
- Debugging ambiguity
- Regulatory violations

---

## 11. Summary

Seed’s version pinning strategy ensures stability, security, and predictability across the entire system lifecycle. By tightly controlling software versions and upgrade paths, Seed remains reliable even in environments where connectivity is limited and failure recovery is costly.

Version pinning is a foundational requirement for Seed’s offline-first, trust-based financial infrastructure.
