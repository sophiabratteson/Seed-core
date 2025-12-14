# Dependencies Overview

This document defines the software dependency philosophy and specific dependency requirements for Seed. Because Seed is designed to operate in low-connectivity, offline-first, and resource-constrained environments, dependency selection is treated as a core architectural decision rather than an implementation detail.

Seed prioritizes minimalism, auditability, long-term maintainability, and resilience over feature richness.

---

## 1. Dependency Philosophy

Seed follows five core dependency principles:

1. Offline-first operation  
2. Minimal external reliance  
3. Deterministic behavior  
4. Long-term maintainability  
5. Security-first design  

Every dependency must justify its inclusion against these principles.

Seed intentionally avoids:
- Heavy runtime frameworks
- Cloud-dependent SDKs
- Auto-updating libraries
- Large dependency trees
- Closed-source critical components (where alternatives exist)

---

## 2. Dependency Categories

Dependencies are grouped into the following categories:

- Firmware-level dependencies
- Embedded system libraries
- Cryptographic primitives
- Development and build tooling
- Simulation and testing dependencies
- Documentation and analysis tooling

Each category is treated independently to limit blast radius and reduce system coupling.

---

## 3. Firmware-Level Dependencies

Firmware dependencies are intentionally minimal and are typically vendored directly into the repository.

### Characteristics:
- Written in C or C-compatible subsets
- No dynamic memory requirements unless unavoidable
- No network assumptions
- Deterministic execution
- Portable across microcontrollers

### Examples:
- Lightweight JSON parsing (custom or minimal implementation)
- CRC and checksum utilities
- Timekeeping utilities using monotonic counters
- Hardware abstraction layers (radio, display, storage)

Firmware dependencies are frozen per release to ensure reproducibility.

---

## 4. Embedded Cryptography Dependencies

Cryptographic functionality is required for:
- Device identity
- Message signing
- Ledger integrity
- Secure storage

### Requirements:
- Open-source
- Well-audited
- Suitable for embedded systems
- No reliance on system clocks or internet access

### Typical dependency types:
- Hash functions (e.g. SHA-256)
- Symmetric encryption (e.g. AES)
- Digital signature schemes
- Secure random number generation

Whenever possible, cryptographic operations are delegated to hardware secure elements rather than software libraries.

---

## 5. Mesh and Radio Dependencies

Seed does not depend on external mesh frameworks at runtime.

Instead:
- Radio drivers are tightly scoped and hardware-specific
- Mesh logic is implemented in-house for determinism and auditability
- Protocol behavior is fully documented and versioned

Optional development-time tools may be used to test radio behavior, but they are not runtime dependencies.

---

## 6. Simulation and Testing Dependencies

Simulation dependencies are used only during development and research phases.

### Acceptable characteristics:
- Desktop-only
- No impact on production firmware
- Replaceable or removable

Examples:
- Python standard library modules
- Lightweight plotting or analysis tools
- Deterministic simulation frameworks

Simulation dependencies are isolated to the `simulations/` directory and never included in production builds.

---

## 7. Build and Toolchain Dependencies

Seed supports multiple build environments but enforces consistency through documented toolchains.

### Common requirements:
- Cross-compilers for target microcontrollers
- Linkers and flash tools
- Minimal scripting environments

Build tools are:
- Documented with exact versions
- Pin-able via configuration files
- Never auto-updated without review

---

## 8. Documentation Dependencies

Documentation is written in plain Markdown.

Optional tools may be used for:
- Static site generation
- PDF export
- Diagram rendering

Documentation dependencies are optional and non-blocking. The repository remains readable without any tooling beyond a text editor.

---

## 9. Dependency Review Process

Before adding any new dependency, the following questions must be answered:

1. Can this functionality be implemented internally with reasonable effort?
2. Does this dependency introduce hidden connectivity assumptions?
3. Is the dependency actively maintained?
4. Is the license compatible with Seed’s licensing strategy?
5. Can the dependency be audited?
6. Can it be removed or replaced later without breaking the system?

Dependencies that fail these checks are rejected.

---

## 10. Dependency Risk Management

Risks associated with dependencies include:
- Supply chain attacks
- Abandonware
- License conflicts
- Hidden network calls
- Excessive resource usage

Mitigation strategies:
- Vendoring critical code
- Pinning versions
- Reducing dependency surface area
- Maintaining internal forks when necessary

---

## 11. Future Dependency Strategy

As Seed evolves, dependencies may be added selectively to support:
- Advanced cryptographic primitives
- Formal verification tooling
- Hardware security modules
- Interoperability layers

Any expansion of dependencies must preserve Seed’s core values of resilience, decentralization, and independence from centralized infrastructure.

---

## 12. Summary

Seed treats dependencies as part of its threat model and architectural surface.

By minimizing external reliance and prioritizing transparency and determinism, Seed ensures that its financial infrastructure remains trustworthy, inspectable, and operable even in the most constrained and disconnected environments.
