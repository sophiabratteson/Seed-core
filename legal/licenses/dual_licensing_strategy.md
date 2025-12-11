# Dual Licensing Strategy

This document outlines Seed’s dual licensing approach, designed to balance open innovation, community trust, commercial viability, and long-term sustainability. Seed operates at the intersection of social impact, secure offline financial tooling, and mesh-network technology. Licensing must therefore protect critical intellectual property while still enabling wide adoption and independent third-party verification.

## 1. Purpose of Dual Licensing

- Support open collaboration for non-profit, humanitarian, and academic use.
- Protect Seed’s commercial model when deployed by companies, vendors, NGOs at scale, or hardware partners.
- Ensure regulatory-grade trust by allowing public review of core protocols.
- Prevent unauthorized commercial clones or exploitative uses.
- Align incentives for partners who want to build on the Seed ecosystem.

## 2. Components Covered Under Dual Licensing

### Open License Portion
These components are intended to be open source under a permissive license (MIT, Apache-2.0, or similar):

- Protocol specifications (transaction format, sync logic, mesh routing).
- Reference Python implementations of ledger behavior.
- Documentation describing system architecture and threat models.
- Educational prototypes (two-laptop demo, Figma mockups, research simulators).
- Non-production libraries used for community experimentation.

### Commercial License Portion

The following components should remain commercial or source-available with restrictions:

- Firmware running on Seed hardware devices.
- Hardware schematics, PCB designs, and production files.
- Secure element integrations, key-management flows, and tamper-protection logic.
- Production-grade mesh-sync algorithms and optimization heuristics.
- Trust-score logic with anti-manipulation rules.
- Backend analytics used for monitoring pilot deployments.
- Branding assets (Seed name, iconography, device aesthetic).

## 3. Recommended License Structure

### Open Source License
- Apache-2.0 recommended due to strong patent protection.
- Allows global academic and humanitarian usage.
- Encourages external audits and transparency.

### Commercial License
- Proprietary license with paid or permission-based usage.
- Required for:
  - Manufacturing hardware using Seed designs.
  - Selling Seed devices commercially.
  - Deploying Seed at population scale (NGO, government).
  - Integrating Seed into fintech platforms.
- Includes explicit clauses preventing:
  - Forking for competing commercial devices.
  - Removing Seed trademarks.
  - Circumventing secure element protections.

## 4. Licensing Model Examples

### Example A: Humanitarian NGO Deployment
- NGO receives discounted or no-fee commercial license.
- Must comply with privacy and safety restrictions.
- Allowed to integrate Seed devices into aid programs.

### Example B: Commercial Manufacturer
- Pays licensing fees per device.
- May not alter secure element behavior.
- Must meet manufacturing and security compliance requirements.

### Example C: Academic Research Partner
- Granted open-source license for research.
- Cannot commercialize without obtaining a commercial license.

## 5. Source Availability vs Full Open Source

Seed may publish portions of the firmware as “source-available” under a non-commercial license:

- Code can be inspected and audited.
- Code cannot be redistributed or sold.
- Useful for building trust and transparency while protecting IP.

## 6. Trademark and Branding Controls

To prevent confusion or insecure imitators:

- “Seed,” “Seed Device,” and associated marks require explicit permission to use.
- Forks may not imply affiliation.
- Branding assets covered by separate trademark guidelines.

## 7. IP Protection Considerations

- Patent select novel components (mesh-sync without internet, emergency-wipe logic, offline trust-score model).
- Maintain trade secrets around hardware manufacturing and secure boot pipeline.
- Regular compliance checks for partners.

## 8. Governance and Ethics

- Dual licensing ensures that commercial growth does not compromise humanitarian access.
- A governance board (eventually) may oversee license approvals for sensitive regions.
- Prioritize safety and ethical usage in low-resource environments.

## 9. Long-Term Sustainability Model

Licensing revenue supports:

- Manufacturing improvements.
- Security audits.
- Maintaining open specifications.
- Providing global support infrastructure.

This hybrid approach ensures Seed remains:

- Trustworthy
- Auditable
- Secure
- Financially sustainable
- Accessible to the communities that need it most
