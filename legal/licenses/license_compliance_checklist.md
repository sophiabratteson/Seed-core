# License Compliance Checklist

This document defines the procedures Seed must follow to remain compliant with all open-source and proprietary licenses used in the Seed device, firmware, mesh protocol, applications, and supporting tools. It is designed to help engineering, legal, and product teams ensure that all third-party code is used correctly and that Seed maintains a clean, investable IP position.

---

# 1. Inventory of Third-Party Dependencies

- Maintain an always-up-to-date list of all libraries, drivers, binaries, and tools.
- Include:
  - Name of dependency
  - Version number
  - Source repository link
  - License type
  - Purpose and where it is used
- Require documentation for:
  - Firmware dependencies (embedded C libraries, radio drivers)
  - Python and backend tools (simulation, testing)
  - Mesh networking components
  - Build tools and compilers
  - UI/UX assets or icon libraries

---

# 2. Validate License Types

For each dependency, confirm:

- Compatibility with Seed’s intended license model
- Whether the dependency allows:
  - Commercial use
  - Modification
  - Distribution
  - Static or dynamic linking
- Special attention required for:
  - GPL licenses (strong copyleft)
  - LGPL licenses (weak copyleft)
  - Apache 2.0 (patent clause requirements)
  - MIT/BSD (permissive)
  - Proprietary elements

If a dependency is incompatible, mark it for replacement.

---

# 3. Source Code Attribution Requirements

- Provide required attribution text in:
  - Device firmware documentation
  - GitHub repository
  - Website open-source disclosures
  - Any distributed binary or documentation materials
- Ensure attribution text includes:
  - License name
  - Copyright holder
  - Link to original source (if required)
- Keep a folder containing all license texts:
  - licenses/third_party_notices/

---

# 4. Modification Tracking

If Seed modifies a library:

- Track all modifications using version control
- Store delta documentation explaining:
  - What was changed
  - Why it was changed
  - How modifications affect compatibility
- Ensure modified components do not violate redistribution rules

---

# 5. Compliance for Distributed Firmware

If Seed distributes firmware binaries:

- Include all required license texts in the firmware image or release bundle
- Include a machine-readable SOFTWARE_NOTICE file
- If required by license:
  - Provide instructions for obtaining the source code
  - Provide build instructions to reproduce the firmware from source

---

# 6. Compliance for Mesh Protocol Implementations

If protocol components derive from existing open-source mesh frameworks:

- Verify that protocol usage does not require open-sourcing proprietary logic
- Document whether serialization formats, networking stacks, or radio abstractions contain licensed code
- Ensure all RF driver code complies with original licensing terms before embedding in secure storage or bootloader

---

# 7. Compliance for AI/ML Components

For Seed’s offline AI assistant:

- Confirm dataset licensing allows:
  - Commercial use
  - Distribution embedded on device
- Confirm model file licensing for:
  - Trained weights
  - Training code
  - Inference libraries used on-device
- Maintain records of:
  - Dataset sources
  - Training scripts
  - Model configuration files

---

# 8. Compliance for Hardware Design Files

If Seed releases hardware schematics or PCB design files:

- Identify any licenses applied to:
  - KiCad libraries
  - Component footprints
  - 3D enclosure models
- Confirm distribution rights for:
  - EDA tool assets
  - Reference designs (LoRa chips, microcontrollers)

---

# 9. Contributor License Agreements (CLAs)

Before accepting contributions:

- Require contributors to sign the Contributor License Agreement
- Confirm:
  - Contributor owns the code
  - Code is original work
  - Code does not contain proprietary or infringing material

---

# 10. Ongoing License Scanning

- Run automated license scanners periodically
- Recommended tools:
  - FOSSA
  - Black Duck
  - GitHub License Scan
  - OpenSSF Scorecard
- Document all scanner output and remediation steps

---

# 11. Release Checklist

Before releasing any version of Seed’s firmware, software, or documentation:

- Verify:
  - All dependencies are recorded
  - All licenses are included
  - All attributions are correct
  - No prohibited licenses are included
  - CLA compliance for all contributors
  - Source bundles meet licensing requirements
- Perform manual review for:
  - Copyleft contamination
  - Patent clauses
  - Security or tamper-protection obligations

---

# 12. Governance and Ownership

- Legal and engineering teams share responsibility
- Maintain internal training on:
  - License types
  - Open-source obligations
  - Risks of improper mixing of licenses
- Update this checklist annually or when:
  - New dependencies are added
  - Licensing strategy changes
  - Product expands into new markets

---

# 13. Summary

This checklist ensures that Seed stays legally protected, compliant with open-source obligations, and attractive to enterprise, NGO, and investor partners. Proper license governance supports scalable hardware manufacturing, global software deployment, and long-term defensibility of Seed’s intellectual property.
