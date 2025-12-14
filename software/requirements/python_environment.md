# Python Environment Requirements

This document defines the Python environment used for Seed’s early-stage software development, simulations, tooling, and prototype validation. Python is used exclusively for **non-device** workflows such as simulations, modeling, developer tooling, and early MVP validation. Embedded firmware runs separately and is not dependent on Python.

---

## Purpose of the Python Environment

The Python environment supports the following Seed activities:

- Ledger behavior simulations
- Conflict resolution testing
- Mesh synchronization modeling
- Power consumption simulations
- Two-device and multi-device prototype demos
- Developer tooling and automation
- Research and analysis scripts

Python is **not** required on the Seed device itself.

---

## Supported Python Version

Seed standardizes on:

- Python 3.12.x

Requirements:

- Must be an official CPython release
- Installed locally on developer machines
- Compatible across macOS, Windows, and Linux

Earlier versions (≤3.10) are not officially supported due to missing language and performance features.

---

## Environment Isolation Strategy

Each Seed developer environment must be isolated to ensure reproducibility.

Accepted isolation methods:

- venv (recommended)
- virtualenv
- conda (allowed, not preferred)

Recommended setup:

- One virtual environment per repository
- No global Python dependencies
- Environment recreated from requirements file

---

## Required Core Packages

The following packages are required across all Python-based Seed tooling:

- json (standard library)
- uuid (standard library)
- hashlib (standard library)
- dataclasses (standard library)
- typing (standard library)
- pathlib (standard library)

No external dependencies are required for the base simulation stack.

---

## Optional Development Packages

These packages may be used during advanced simulations and research work:

- numpy (numerical modeling)
- matplotlib (visualization)
- pandas (data analysis)
- networkx (graph-based mesh modeling)
- pytest (testing)

Optional packages are not required for MVP validation.

---

## Environment Setup Workflow

Standard setup process:

1. Install Python 3.12.x
2. Create a virtual environment
3. Activate the environment
4. Install required packages (if any)
5. Run simulations or tools

This workflow ensures consistency across all contributors.

---

## Version Pinning Strategy

Seed follows conservative version pinning:

- Python version pinned at major.minor level
- Patch updates allowed
- External packages pinned only when required

This minimizes breakage while allowing security updates.

---

## Reproducibility and Portability

All Python-based Seed tools must:

- Run without internet access
- Execute deterministically
- Produce identical outputs across platforms
- Avoid OS-specific behavior

This mirrors Seed’s offline-first philosophy.

---

## Security Considerations

Python tooling must:

- Never store private keys in plaintext
- Never transmit sensitive data over network interfaces
- Avoid dynamic code execution
- Use deterministic file-based input/output

Python tools are treated as **trusted local developer tools**, not production endpoints.

---

## Relationship to Embedded Firmware

Important distinction:

- Python is used for simulations and tooling
- Firmware is written in C/C++ and runs independently
- No Python runtime exists on Seed devices

This separation ensures device reliability and security.

---

## Future Evolution

Potential future uses of Python include:

- Large-scale mesh simulations
- Automated regression testing
- Protocol fuzz testing
- Developer education tooling

Any expansion will maintain isolation from production firmware.

---

## Summary

The Python environment enables rapid experimentation, validation, and simulation while maintaining strict separation from production device firmware. This approach allows Seed to iterate quickly without compromising security, determinism, or device reliability.
