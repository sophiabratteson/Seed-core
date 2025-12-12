# Repair Guidelines

This document defines standardized, field-ready repair procedures for Seed devices. The goal is to ensure that devices can be safely diagnosed, repaired, and returned to service in low-resource environments without requiring specialized tools, continuous internet access, or advanced technical training.

---

## 1. Repair Philosophy

Seed devices are designed with **repairability as a first-class requirement**.

Repair principles:
- Modular components over monolithic assemblies
- Clear fault isolation before part replacement
- Minimal tooling requirements
- Safe handling of power, radio, and secure elements
- Preference for repair over replacement whenever possible

Repairs should:
- Restore full device functionality
- Preserve user data and ledger integrity whenever possible
- Avoid compromising security guarantees
- Be documented for fleet-wide learning

---

## 2. Authorized Repair Levels

### Level 1: Field Repair (Non-Technical)
Performed by:
- Community operators
- NGO staff
- Trained local facilitators

Allowed actions:
- Battery replacement
- Screen replacement (e-ink module)
- External button replacement
- Antenna reseating or replacement
- Enclosure repair or replacement

Restrictions:
- No access to secure element
- No firmware flashing
- No cryptographic key access

---

### Level 2: Technical Repair (Certified Technician)
Performed by:
- Regional technicians
- Partner repair centers

Allowed actions:
- Radio module replacement
- Power subsystem repair
- Sensor replacement (fingerprint, tamper)
- Firmware reinstallation
- Diagnostic log extraction

Restrictions:
- Secure element replacement requires explicit authorization

---

### Level 3: Secure Repair (Factory or Central Authority)
Performed by:
- Manufacturer
- Secure repair partner

Allowed actions:
- Secure element replacement
- Device identity re-provisioning
- Cryptographic key regeneration
- Full device refurbishment

---

## 3. Safety Precautions

Before any repair:
- Power off the device completely
- Disconnect battery and solar input
- Discharge capacitors if applicable
- Work in a dry, dust-free environment

Never:
- Short battery terminals
- Apply power during open-casing repairs
- Attempt to probe secure element pins
- Bypass tamper detection circuits

---

## 4. Diagnostic Workflow

### Step 1: Symptom Identification
Common symptoms include:
- Device does not power on
- Screen does not refresh
- Radio communication failure
- Input buttons unresponsive
- Authentication failure
- Ledger sync errors

---

### Step 2: Power System Check
- Inspect battery voltage
- Verify charging input (solar/hand-crank)
- Check power management IC indicators
- Confirm no visible corrosion or swelling

If power fails → resolve before proceeding.

---

### Step 3: Display and Input Check
- Trigger manual screen refresh
- Check ribbon cable seating
- Test input buttons individually
- Verify fingerprint sensor response

---

### Step 4: Radio and Sync Check
- Confirm antenna connection
- Verify regional frequency configuration
- Check neighbor discovery logs
- Test short-range mesh communication

---

### Step 5: Security and Identity Check
- Verify secure boot status
- Confirm device identity intact
- Check tamper flags
- Ensure ledger integrity hashes match

---

## 5. Component-Specific Repair Procedures

### Battery Replacement
1. Power off device
2. Open enclosure using approved tool
3. Disconnect old battery
4. Inspect connector and wiring
5. Install new battery of approved specification
6. Close enclosure and perform power test

---

### E-Ink Display Replacement
1. Remove front enclosure panel
2. Release display ribbon connector
3. Install replacement display
4. Secure ribbon with locking tab
5. Perform display refresh test

---

### Radio Module Replacement
1. Confirm radio failure via diagnostics
2. Remove shielding if present
3. Replace module with region-matched part
4. Reflash radio configuration if required
5. Perform mesh connectivity test

---

### Fingerprint Sensor Replacement
1. Disable authentication attempts
2. Remove sensor housing
3. Install replacement sensor
4. Re-enroll user fingerprints
5. Validate authentication flow

---

## 6. Firmware Repair and Recovery

### Safe Firmware Reinstallation
- Use signed firmware only
- Verify firmware checksum before flashing
- Preserve ledger and user data partitions
- Never overwrite secure element memory

If firmware fails:
- Enter recovery mode
- Restore last known good version
- Log failure reason

---

## 7. Data Preservation Rules

During repair:
- Ledger data must not be modified manually
- Encrypted storage must remain sealed
- No copying of user data off-device unless authorized
- Emergency wipe may be triggered only with owner consent

If data corruption is detected:
- Flag device
- Attempt ledger reconciliation
- Escalate to Level 2 or Level 3 repair

---

## 8. Post-Repair Validation Checklist

After repair, confirm:
- Device powers on reliably
- Display refreshes correctly
- Inputs respond as expected
- Mesh communication works
- Authentication succeeds
- Ledger sync completes
- Tamper flags are clear (if appropriate)

---

## 9. Documentation and Reporting

Every repair must record:
- Device ID
- Repair level
- Components replaced
- Firmware version
- Observed failure mode
- Resolution outcome

Reports are stored locally and synced when possible.

---

## 10. When to Replace Instead of Repair

Replace device if:
- Secure element is irreversibly damaged
- Structural damage compromises safety
- Repeated failures exceed threshold
- Cost of repair exceeds replacement threshold

---

## 11. Summary

Seed repair guidelines prioritize:
- Safety
- Data integrity
- Security preservation
- Community-level maintainability

By designing for repair from day one, Seed ensures long-term resilience, trust, and sustainability in the environments that need it most.
