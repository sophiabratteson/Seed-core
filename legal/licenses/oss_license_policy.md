# Open Source Software (OSS) License Policy

This document describes Seed’s policy for using, integrating, contributing to, and releasing open-source software (OSS). Seed relies on a combination of custom code, embedded firmware, hardware drivers, cryptographic libraries, and mesh-networking stacks. To ensure legal compliance, security, and long-term maintainability, this policy establishes guidelines that all contributors must follow.

---

## 1. Goals of the OSS License Policy

- Protect Seed from legal and licensing risks.
- Ensure that third-party libraries are used in accordance with their licenses.
- Allow Seed to maintain optional closed-source components (e.g., secure-element firmware) when necessary.
- Enable controlled release of Seed components to the open-source community.
- Maintain transparency for partners, researchers, and auditors.

---

## 2. Allowed License Types

Seed permits the use of third-party software ONLY if the license falls into one of the following categories:

### Permissive Licenses (Preferred)
- MIT License
- BSD 2-Clause / BSD 3-Clause
- Apache License 2.0
- ISC License

These licenses allow commercial usage with minimal restrictions and are preferred for prototypes and production releases.

### Weak Copyleft (Allowed With Review)
- LGPL 2.1 / LGPL 3.0

These may be used ONLY if they are dynamically linked and do not require Seed’s proprietary firmware to be open-sourced.

### Strong Copyleft (Restricted)
- GPLv2
- GPLv3
- AGPL

These licenses require strict review because they may force Seed to open-source internal firmware or hardware-level code. They may only be used in:
- isolated developer tools, or
- optional companion utilities.

They may NOT be used in embedded firmware, mesh protocol logic, or the ledger engine without legal approval.

---

## 3. Prohibited License Types

Seed strictly prohibits:

- Any license requiring disclosure of proprietary code (e.g., certain copyleft licenses in embedded systems).
- Licenses containing “patent retaliation” clauses that conflict with hardware partnerships.
- Libraries with unclear or missing licenses.
- Libraries with known supply chain risks or abandoned maintenance.

---

## 4. Requirements for Using OSS in Seed

### Every OSS dependency must include:
- License text in its directory or in a LICENSES file.
- Version pinning in dependency manifests.
- A security review for cryptographic libraries.
- Documentation of origin and modification status.

### Contributors must:
- Avoid copying code from the internet (e.g., StackOverflow) without verifying the license.
- Record all OSS usage in the Third-Party License Register.
- Notify the engineering lead before adding new dependencies.

---

## 5. Requirements for Modifying OSS

If Seed modifies an OSS library, the following must be documented:

- Description of the modification.
- Timestamp and commit reference.
- Justification for modification.
- Whether the modification must be disclosed publicly.

Modified OSS must always preserve the original copyright notices.

---

## 6. Seed Components Intended for Open-Sourcing

The following components may be released as open source after internal approval:

### Candidate Open Source Components
- Mesh protocol specifications.
- Radio abstraction layer.
- Non-sensitive ledger simulation tools (Python prototype).
- Educational documentation for offline-first networking.
- Testing harnesses and visualization scripts.

### Components That Will NOT Be Open-Sourced
- Secure-element firmware integrations.
- Proprietary ledger conflict-resolution optimizations.
- Supply-chain security processes.
- Hardware manufacturing instructions and proprietary schematics.
- Device-level trust-score calculation models.

---

## 7. Compliance Verification Process

### Each release must undergo:

#### Legal Review
- Verify that all dependencies comply with Seed’s policy.
- Confirm that no restricted licenses appear in critical components.

#### Security Review
- Check that OSS cryptographic libraries have no known CVEs.
- Validate supply-chain integrity.

#### Documentation Review
- Ensure THIRD_PARTY_LICENSES.md is updated.
- Confirm LICENSE file in repository root is correct.

---

## 8. OSS Contribution Policy

Seed team members may contribute to external OSS projects ONLY if:

- The contribution does not disclose proprietary methodologies.
- The contribution is approved by the engineering lead.
- The contribution does not create licensing obligations for Seed’s internal code.

Contributions should be made under personal name unless representing Seed is specifically authorized.

---

## 9. Dual Licensing Strategy (Optional Future Phase)

Seed may eventually adopt a dual-license model:

- **Open-source community license** for research, education, and non-profit use.
- **Commercial license** for governments, NGOs, financial partners, and enterprise deployments.

This approach supports innovation while preserving revenue opportunities and IP protection.

---

## 10. Governance and Updates

This policy will be reviewed quarterly by:
- CTO
- Legal counsel
- Lead firmware engineer
- Security lead

All changes require written approval and must be communicated to the entire team.

---

## 11. Summary

Seed embraces open-source technology while protecting its proprietary innovations, device security, and mission-critical infrastructure. This policy ensures compliant, secure, and transparent use of OSS across the entire Seed ecosystem. By following this policy, the team can move quickly while maintaining long-term legal and technical stability.
