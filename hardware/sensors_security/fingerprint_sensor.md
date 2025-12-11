# Fingerprint Sensor Module

This document describes the role, requirements, implementation details, and integration plan for the fingerprint sensor used in the Seed device. The fingerprint module is a core part of Seed’s security architecture, enabling offline user authentication without passwords, servers, or external identity infrastructure.

---

# 1. Purpose of the Fingerprint Sensor

- Provide secure, offline user authentication.
- Serve as the primary identity verification method when unlocking the device.
- Prevent unauthorized access to financial data, trust scores, and stored balances.
- Enable quick, intuitive access in low-literacy populations.
- Allow biometric confirmation for high-risk actions such as sending money, borrowing from group savings, performing a device reset, or accessing encrypted backups.

The sensor must function reliably in harsh environments and under minimal power availability.

---

# 2. Hardware Requirements

- Capacitive fingerprint sensor rated for embedded low-power systems.
- Operating voltage matching Seed’s power architecture (typically 3.3 V).
- Integrated secure template storage or compatibility with the secure element chip.
- Fast acquisition time under 300 ms for smooth user experience.
- Resistant to dust, moisture, and temperature fluctuation.
- SPI or UART interface for predictable performance and ease of firmware integration.
- Finger detection wake function to reduce idle power usage.
- Scratch-resistant surface for long-term durability.

---

# 3. Enrollment Workflow

1. User powers on the device for the first time.
2. Fingerprint module enters enrollment mode.
3. User taps the sensor several times to collect a complete template.
4. Firmware extracts features and generates a fingerprint template.
5. Template is encrypted using the secure element’s hardware key.
6. Encrypted template is stored in protected flash memory.
7. Device assigns biometric identity to that user profile and generates a device identity keypair.

No biometric data ever leaves the device. The template is not recoverable into an image.

---

# 4. Authentication Workflow

1. User places finger on the sensor.
2. Sensor wakes the MCU and provides raw feature data.
3. Firmware compares features with the stored encrypted template.
4. If authenticated:
   - Device unlocks.
   - Access is granted to wallet, group savings, trust score, and other apps.
5. If authentication fails:
   - Device denies access.
   - After multiple failures, device may require a rate-limit cooldown.

Authentication is performed entirely offline, with no dependency on servers.

---

# 5. Security Model

- Templates are encrypted using the secure element via hardware keys.
- Template matching occurs inside the MCU; raw data is never transmitted.
- Protected memory regions prevent unauthorized reads even with physical access.
- Replay attacks are mitigated because raw sensor data changes with each scan.
- Brute-forcing is rate-limited to protect against automated attacks.
- Emergency wipe mechanism can be triggered using an alternate fingerprint gesture or sequence.

---

# 6. Integration With the Secure Element

- The secure element stores:
  - Template encryption key
  - Device identity private key
  - Derived authentication secrets
- Fingerprint template is only decrypted momentarily inside RAM during local authentication.
- Template updates (such as re-enrollment) must be signed using the device’s own key to prevent tampering.

---

# 7. Power Consumption Requirements

- Must support duty-cycling for ultra-low-power operation.
- Wake-on-touch mode allows the MCU to sleep until finger detection.
- Typical expected power consumption:
  - Idle: < 10 microamps
  - Active scan: 20–70 milliamps depending on model
- Integration with the power manager ensures battery longevity even in solar-only environments.

---

# 8. Environmental Considerations

- Surface materials must resist abrasion from heavy use.
- Must tolerate:
  - High humidity
  - Dust and debris
  - Temperature swings typically found in developing regions
- Protective ring or raised lip recommended to shield the sensor from impacts.

---

# 9. Failure Handling and Edge Cases

- If sensor is dirty:
  - Device prompts user to clean finger or surface.
- If template becomes corrupted:
  - User must re-enroll using their backup PIN or trusted peer-verified recovery.
- If fingerprint cannot be read due to injury:
  - Device supports optional secondary authentication (PIN or trusted-group unlock).
- If user is in danger:
  - Device supports fake fingerprint or emergency unlock pathway that loads a decoy wallet.

---

# 10. Firmware Interface Requirements

The fingerprint module firmware must provide:

- init_sensor()
- enroll_fingerprint()
- match_fingerprint()
- delete_template()
- read_status()
- low_power_wake()

Drivers should be abstracted through the hardware layer so the module can be swapped with alternatives during prototyping.

---

# 11. Vendor Options Under Consideration

- Capacitive sensors from suppliers such as:
  - FPC1020 series
  - Goodix capacitive modules
  - MicroMatch-compatible UART fingerprint modules
- Selection criteria:
  - Cost under $5–$8 per unit at scale
  - Reliable dry-finger performance
  - Strong open documentation for firmware integration
  - Global availability

---

# 12. Long-Term Vision

The fingerprint sensor enables Seed to work in areas without:

- Government IDs
- Phones
- Internet
- Formal banks

Future extensions may include:

- Multi-finger enrollment
- Role-based privileges (shop owners, cooperatives, community treasurers)
- Shared device mode with multiple local users
- Hardware tamper alarms triggered by sensor manipulation

The sensor is fundamental to Seed’s promise: secure identity and financial autonomy anywhere in the world.
