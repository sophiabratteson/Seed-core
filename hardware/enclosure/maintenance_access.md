# Enclosure: Maintenance Access

This document defines the design requirements, service philosophy, and structural features that enable safe, reliable, and low-skill maintenance of the Seed device in the field. Because Seed is intended for use in regions with limited infrastructure, the enclosure must support simple, tool-minimal service actions without compromising security, water resistance, or device integrity.

---

## 1. Maintenance Philosophy

- Enable **basic field maintenance** with minimal tools.
- Protect all **critical security components** from unauthorized tampering.
- Ensure the enclosure can be opened only at **designated service points**.
- Make common replacements (battery, buttons, gasket) possible without specialized training.
- Maintain core durability features: dust resistance, splash resistance, heat tolerance.

---

## 2. Components Requiring Periodic Maintenance

### 2.1 Battery Replacement
- LiFePO₄ cell is designed for long lifespan (2,000+ cycles) but must still be replaceable.
- Battery should be accessible under a secured internal panel.
- Electrical connection via locking JST or Molex connector.
- Clear alignment keys prevent incorrect installation.

### 2.2 Gasket & Seal Inspection
- Dust/water ingress gasket around the perimeter requires occasional inspection.
- Gasket channel must be shallow, clearly visible, and removable.
- Replacement gaskets must be field-installable without adhesives.

### 2.3 Button & Switch Components
- Physical buttons (power, sync, emergency-wipe trigger) are high-frequency touchpoints.
- Button domes should be replaceable without disassembling the entire device.
- Use standardized tact-switch modules with long actuation life.

### 2.4 External Connectors
- Charging port and solar/hand-crank input ports may wear over time.
- Ports must be modular and removable via internal screws.

---

## 3. Service Access Zones

The enclosure should define **three levels of access**:

### Level 1: User Maintenance (No Tools)
- Clean device exterior.
- Access charging port covers.
- Activate emergency wipe mode.

### Level 2: Field Technician Access (1 Tool: Torx T5 or T6)
- Remove outer backplate.
- Access battery compartment.
- Inspect internal seals.

### Level 3: Authorized Secure Access
- Requires security screw + internal tamper shield.
- Access secure element, radio board, MCU, mesh antenna chamber.
- Tamper shield logs event to secure storage.

---

## 4. Physical Design Features Supporting Maintenance

### 4.1 Backplate Access
- Four recessed screws using Torx (T5/T6) to discourage casual tampering.
- Screw bosses integrated into frame for structural strength.
- Backplate detaches as a single module.

### 4.2 Modular Internal Frames
- Electronics mounted on a sub-frame that slides out vertically.
- Battery bay separated from primary PCB to minimize risk of accidental damage.
- Ribbon cables use zero-insertion-force (ZIF) connectors for easy servicing.

### 4.3 Tamper Authentication Layer
- Secure element and fingerprint sensor shielded under a metal cage.
- Opening cage triggers:
  - Physical break-wire signal.
  - Secure wipe flag stored in hardware.
  - Optional device disablement until re-provisioning.

### 4.4 Weatherproofing Structure
- Gasket channel runs along the full perimeter.
- Clamping force evenly distributed via internal posts.
- Vent membrane prevents pressure buildup during charging or altitude changes.

---

## 5. Tool Requirements

### Minimal Tool List
- Torx T5/T6 driver.
- Plastic prying tool (non-metal).
- Anti-static wrist strap (recommended but not required in the field).

### No Proprietary Tools Required
- All service actions must be understandable by NGOs, repair centers, and local technicians.

---

## 6. Safety Requirements During Maintenance

- Battery compartment must include short-circuit protection.
- Technicians should not be exposed to raw LiFePO₄ terminals.
- No maintenance action should expose users to sharp internal edges.
- PCB should remain isolated unless Level 3 access is granted.

---

## 7. Maintenance Workflow

### Routine Inspection
1. Remove backplate.
2. Check gasket for wear.
3. Verify battery seating & connector integrity.
4. Wipe dust using dry cloth.
5. Reassemble with even torque on screws.

### Battery Replacement
1. Open backplate.
2. Disconnect battery connector.
3. Replace battery module with keyed replacement.
4. Reseat gasket.
5. Reseal device and perform self-test.

### Connector Replacement
1. Remove sub-frame screws.
2. Detach charging/solar/hand-crank port module.
3. Replace with OEM part.
4. Validate via diagnostics menu.

---

## 8. Tamper Detection & Maintenance Logging

Whenever Level 3 access is attempted:

- Secure element logs timestamp and event type.
- Device warns: “Service Access Detected.”
- Ledger sync pauses until device is re-authenticated.
- Optional NGO or admin override required to restore operation.

This ensures:
- User data remains secure.
- Ledger integrity is never compromised by unauthorized service.

---

## 9. Design Guidelines for Manufacturability

- Enclosure should be injection-molded for mass production.
- Internal ribs must:
  - Allow airflow around battery.
  - Provide crush resistance.
- Screw posts thickened for repeated servicing cycles.
- Uniform wall thickness prevents warping in high temperatures.

---

## 10. Summary

The maintenance-access design ensures that Seed devices can be repaired and serviced even in remote or resource-limited environments. By combining:

- Modular internal architecture  
- Clear levels of secure access  
- Weatherproofing  
- Replaceable batteries and connectors  
- Strong tamper protections  

…the enclosure supports long-term durability, sustainability, and user trust — all essential for Seed’s mission as a globally deployable offline financial infrastructure.
