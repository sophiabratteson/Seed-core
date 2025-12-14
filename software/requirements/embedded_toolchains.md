# Embedded Toolchains

This document defines the embedded software toolchains required to develop, build, test, and deploy firmware for Seed devices. Because Seed operates in offline, low-resource, and hardware-constrained environments, the toolchain prioritizes reliability, reproducibility, low power optimization, and long-term maintainability.

---

## Purpose of the Embedded Toolchain

The embedded toolchain enables developers to:

- Compile firmware for low-power microcontrollers
- Interface with radio, storage, display, and security hardware
- Debug devices without persistent internet access
- Reproduce firmware builds across different machines and contributors
- Safely deploy updates to devices operating in the field

A standardized toolchain is critical to ensure device consistency, security, and auditability.

---

## Target Hardware Platforms

Seed firmware is designed to run on microcontrollers commonly used in low-power IoT and mesh networking environments.

Primary targets include:

- ARM Cortex-M series (M0+, M4, M33)
- ESP32-class microcontrollers (for early prototypes)
- Nordic nRF52 family (BLE + low power radio integration)
- STM32 low-power families

The toolchain must support cross-compilation for these architectures.

---

## Core Compiler Toolchains

### ARM GNU Toolchain

Primary compiler for production firmware.

- Toolchain: `arm-none-eabi-gcc`
- Language standards:
  - C11 for core firmware
  - Limited C++ (optional) for modular components
- Optimization flags:
  - Size optimization (`-Os`)
  - Link-time optimization (`-flto`)
- Deterministic builds enabled

This toolchain is widely supported, well-documented, and suitable for secure embedded deployments.

---

### ESP-IDF Toolchain (Prototype Phase)

Used during early development and proof-of-concept stages.

- Provided by Espressif
- Supports ESP32 and related chips
- Includes:
  - Compiler
  - Flashing tools
  - Debug utilities
- Enables faster iteration during early testing

ESP-IDF is not required for final production firmware but accelerates early validation.

---

## Build Systems

### CMake (Primary)

CMake is used to define and manage firmware builds.

Benefits:

- Cross-platform compatibility
- Clear separation of modules
- Reproducible builds
- Easy CI integration

CMake generates platform-specific build files (e.g., Makefiles) while maintaining a single source of truth.

---

### Make (Secondary / Legacy Support)

Makefiles may be used for:

- Minimal builds
- Debug-only configurations
- Legacy toolchain compatibility

Make is not the preferred long-term solution but remains supported.

---

## Flashing and Programming Tools

These tools are used to load firmware onto Seed devices.

### OpenOCD

- Used for:
  - Flashing firmware
  - Debugging via JTAG/SWD
- Supports most ARM-based microcontrollers
- Enables low-level inspection of memory and registers

---

### Vendor-Specific Flashers

Depending on hardware:

- `esptool.py` for ESP-based devices
- `nrfjprog` for Nordic chips
- `stm32flash` or ST-Link tools for STM32

These tools are used when OpenOCD is not available or optimal.

---

## Debugging Tools

### GDB (GNU Debugger)

- Used for:
  - Stepping through firmware
  - Inspecting variables and memory
  - Diagnosing crashes and faults
- Integrated with OpenOCD or vendor debug probes

Debugging is designed to work entirely offline.

---

### Serial Logging Tools

- UART-based logs
- Minimal logging framework built into firmware
- Tools:
  - `screen`
  - `minicom`
  - Platform serial monitors

Logging is intentionally lightweight to preserve power and storage.

---

## Firmware Packaging and Versioning

Firmware binaries are packaged with:

- Version identifiers
- Hardware compatibility metadata
- Cryptographic hashes

Toolchain supports:

- Deterministic firmware hashing
- Signed firmware images
- Rollback-safe update mechanisms

This enables secure field updates without centralized infrastructure.

---

## Continuous Integration Compatibility

The embedded toolchain is designed to integrate with CI systems.

Capabilities:

- Headless builds
- Automated linting
- Static analysis
- Unit tests (where applicable)
- Firmware size and power regression checks

CI environments mirror local developer setups to prevent divergence.

---

## Developer Environment Expectations

Developers working on Seed firmware are expected to have:

- A POSIX-compatible environment (macOS, Linux, or WSL)
- Python 3.x for tooling scripts
- USB or JTAG access to test devices
- No persistent internet dependency for builds

All required tools are documented and version-pinned.

---

## Long-Term Maintainability Strategy

The toolchain strategy emphasizes:

- Open-source tooling
- Avoidance of proprietary lock-in
- Clear documentation for onboarding
- Minimal hardware-specific assumptions
- Compatibility with future hardware revisions

This ensures Seed can be maintained, audited, and extended for years without reliance on fragile ecosystems.

---

## Summary

Seed’s embedded toolchain enables secure, low-power, offline-first firmware development across diverse hardware platforms. By standardizing compilers, build systems, flashing tools, and debugging workflows, the project ensures consistency, reliability, and investor-grade technical credibility from prototype through large-scale deployment.
