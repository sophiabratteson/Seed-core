# Linting and Code Style Standards

This document defines the linting rules, formatting standards, and code style conventions used across the Seed software stack. Consistent style and automated linting are critical to maintaining security, reliability, and auditability in a distributed financial system.

These standards apply to all firmware, embedded software, simulation code, and supporting tools.

---

## 1. Goals of Linting and Style Enforcement

The linting and style system is designed to:

- Prevent common programming errors before deployment
- Improve readability and maintainability across contributors
- Reduce security vulnerabilities caused by undefined behavior
- Enable deterministic builds and reproducible binaries
- Support external audits, academic review, and investor diligence
- Ensure firmware quality suitable for safety-critical environments

Seed treats code quality as a first-order system requirement, not a cosmetic concern.

---

## 2. Scope of Style Enforcement

Linting and style rules apply to:

- Firmware (C)
- Embedded configuration headers
- Simulation and prototyping code (Python)
- Tooling and scripts
- Test harnesses
- Build and deployment scripts

Documentation files are excluded from linting but follow separate documentation style guidelines.

---

## 3. Firmware (C) Style Standards

### 3.1 Language Standard

- C standard: C11
- Compiler warnings treated as errors
- No compiler-specific extensions unless documented

### 3.2 Naming Conventions

- Functions: snake_case
- Variables: snake_case
- Constants: ALL_CAPS_WITH_UNDERSCORES
- Types and structs: CamelCase
- Files: snake_case.c / snake_case.h

Example:

uint32_t ledger_checkpoint_interval;
void radio_send_packet(…);

### 3.3 Formatting Rules

- Indentation: 4 spaces (no tabs)
- Line length: max 100 characters
- Braces on same line for functions
- One statement per line
- Explicit braces required for all conditionals

### 3.4 Memory Safety Rules

- No dynamic allocation without documented ownership
- All buffers must include explicit size parameters
- All memcpy / strcpy calls wrapped in safe utility functions
- NULL checks required for all pointer dereferences
- Stack usage must be bounded and documented

---

## 4. Firmware Linting Tools

The following tools are used for static analysis and linting:

- clang-tidy
- cppcheck
- compiler warning flags (-Wall, -Wextra, -Werror)
- custom rule checks for embedded constraints

Linting runs automatically during build and CI.

---

## 5. Python Code Style Standards

### 5.1 Language Version

- Python 3.12+
- No deprecated features allowed

### 5.2 Formatting Rules

- PEP8 compliant
- Indentation: 4 spaces
- Line length: max 88 characters
- Explicit typing preferred where reasonable

### 5.3 Naming Conventions

- Functions and variables: snake_case
- Classes: CamelCase
- Constants: ALL_CAPS
- Files: snake_case.py

---

## 6. Python Linting Tools

Python code uses the following tools:

- black (auto-formatter)
- flake8 (style and logic checks)
- mypy (optional static typing)
- pylint (optional deeper analysis)

Formatting tools are run automatically before commits.

---

## 7. Configuration and Header Files

- All configuration values must be centralized
- No magic numbers in logic code
- All configuration constants documented
- Default values explicitly defined
- Compile-time checks preferred over runtime checks

---

## 8. Security-Focused Style Rules

Additional constraints apply due to Seed’s security requirements:

- No undefined behavior allowed
- No reliance on uninitialized memory
- All cryptographic operations must be explicit and reviewed
- No hidden side effects in macros
- All error paths must be handled explicitly

Linting rules are stricter than typical consumer software due to the financial nature of the system.

---

## 9. Automated Enforcement

Linting and formatting are enforced through:

- Pre-commit hooks
- Continuous Integration pipelines
- Build-time checks
- Release gate requirements

Code that does not pass linting cannot be merged into protected branches.

---

## 10. Contributor Expectations

All contributors are expected to:

- Run linting tools locally before submitting changes
- Follow documented style conventions
- Justify any lint rule suppression explicitly
- Treat lint warnings as correctness issues, not suggestions

This ensures Seed remains trustworthy, auditable, and resilient over time.

---

## 11. Rationale for Investors and Auditors

Strict linting and style enforcement:

- Reduces long-term maintenance cost
- Lowers operational risk
- Improves onboarding of future engineering teams
- Enables third-party security audits
- Signals engineering maturity and discipline

For Seed, code quality is a core part of the product’s credibility.

---

## 12. Summary

Linting and style enforcement in Seed are not optional or cosmetic. They are foundational to building a secure, offline-first financial system that can operate reliably in extreme environments.

Every line of code must be readable, predictable, and defensible.
