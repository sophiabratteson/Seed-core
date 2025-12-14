# Radio Abstraction Layer (RAL)

This document defines the Radio Abstraction Layer (RAL) used by Seed. The RAL provides a clean, hardware-agnostic interface between the Seed software stack and the underlying radio hardware (e.g., LoRa transceivers). It ensures that higher-level components such as mesh routing, ledger sync, and application logic remain independent of specific radio chipsets or vendors.

---

## 1. Purpose and Design Goals

The Radio Abstraction Layer exists to:

- Decouple Seed software from specific radio hardware implementations
- Enable portability across different LoRa and sub-GHz radios
- Provide a consistent interface for sending and receiving mesh messages
- Simplify testing, simulation, and future hardware upgrades
- Support low-power operation in constrained environments

The RAL is a foundational component that enables Seed’s offline-first, device-to-device communication model.

---

## 2. Position in the Software Stack

The RAL sits between the physical radio driver and the mesh networking layer.

Stack position (bottom to top):

- Physical Radio Hardware (LoRa chip, antenna)
- Hardware Driver (SPI/I2C, interrupts, power control)
- **Radio Abstraction Layer (RAL)**
- Mesh Stack (routing, retries, neighbor discovery)
- Ledger Sync & Applications

Higher layers must never communicate directly with hardware drivers.

---

## 3. Supported Radio Capabilities

The RAL assumes the following minimum radio capabilities:

- Packet-based transmission
- Configurable frequency band
- Adjustable transmit power
- Adjustable bandwidth and spreading factor
- Receive callbacks or polling
- RSSI and signal quality reporting
- Sleep / wake power states

These assumptions align with common LoRa chipsets (e.g., SX127x, SX126x).

---

## 4. Core Responsibilities

The Radio Abstraction Layer is responsible for:

- Initializing radio hardware
- Configuring radio parameters
- Sending outbound packets
- Receiving inbound packets
- Reporting signal metrics
- Managing radio power states
- Handling radio errors and retries (at a low level)

It does **not** implement routing, ledger logic, or application behavior.

---

## 5. Public Interface Overview

The RAL exposes a minimal, consistent API to higher layers.

Key operations include:

- radio_init()
- radio_configure(params)
- radio_send(packet)
- radio_receive()
- radio_sleep()
- radio_wake()
- radio_get_metrics()

All functions must behave deterministically and fail gracefully.

---

## 6. Packet Model

The RAL treats all transmitted data as opaque packets.

Packet properties:

- Byte array payload
- Fixed maximum size (radio-dependent)
- No interpretation of packet contents
- No knowledge of message types or protocols

Packet structure is defined by higher layers (mesh stack).

---

## 7. Configuration Parameters

Radio configuration parameters include:

- Frequency (regional compliance)
- Transmit power level
- Bandwidth
- Spreading factor
- Coding rate
- Preamble length
- CRC enable/disable

The RAL translates abstract configuration requests into hardware-specific commands.

---

## 8. Power Management Strategy

Power efficiency is critical for Seed devices.

The RAL supports:

- Explicit sleep mode when idle
- Timed wake windows for receive
- Duty-cycle enforcement
- Fast wake for emergency messages

Higher layers request sleep/wake states, but the RAL enforces safe transitions.

---

## 9. Error Handling and Resilience

The RAL must handle:

- Transmission failures
- Receive timeouts
- CRC failures
- Hardware faults
- Invalid configuration requests

Errors are reported upward via standardized error codes. The RAL must never crash the system.

---

## 10. Metrics and Telemetry

The RAL provides radio metrics to higher layers, including:

- RSSI (signal strength)
- SNR (signal-to-noise ratio)
- Packet success/failure counts
- Channel busy indicators

These metrics support adaptive routing and power optimization.

---

## 11. Multi-Radio and Future Expansion

The RAL is designed to support:

- Multiple radio backends
- Future radio technologies
- Software-defined radio adapters
- Simulation backends for testing

Adding a new radio requires implementing the RAL interface, not changing higher layers.

---

## 12. Security Considerations

The RAL itself does not encrypt data.

Security responsibilities:

- Encryption occurs above the RAL
- RAL must not leak raw packets
- Radio configuration must prevent regulatory violations
- Packet metadata must not expose sensitive identifiers

The RAL assumes all packets are already signed and encrypted when transmitted.

---

## 13. Testing and Simulation Support

The RAL supports mock and simulated backends:

- File-based packet exchange
- Loopback radio simulation
- Fault injection testing

This allows full mesh and ledger testing without physical hardware.

---

## 14. Failure Modes and Safeguards

In extreme conditions, the RAL must:

- Fail safely into receive-only or sleep mode
- Prevent uncontrolled transmission loops
- Protect hardware from overheating or power drain
- Allow system recovery after reset

The RAL is a safety-critical boundary between software and hardware.

---

## 15. Summary

The Radio Abstraction Layer is the bridge that enables Seed’s software to operate across diverse radio hardware while maintaining reliability, security, and power efficiency. By isolating hardware-specific complexity, the RAL allows Seed to evolve its mesh protocol and applications without redesigning the physical device.

This abstraction is essential for scaling Seed across regions, manufacturers, and future generations of hardware.
