# Customs and Regulatory Compliance

This document outlines how Seed devices are transported across borders, cleared through customs, and maintained in compliance with international regulations. Because Seed targets low-connectivity and developing regions, regulatory planning is essential to avoid shipment delays, confiscation, or legal exposure.

---

## 1. Objectives

- Ensure Seed devices can be legally imported, exported, and distributed globally
- Minimize customs delays and regulatory risk
- Maintain compliance without requiring Seed to operate as a formal bank
- Enable rapid deployment in humanitarian, disaster, and emerging-market contexts
- Protect users and partners from legal and financial harm

---

## 2. Regulatory Classification Strategy

Seed is classified as a **consumer electronic device with offline data storage and radio communication**, not as a bank or financial institution.

Primary classifications:
- Consumer electronics
- Low-power radio device (LoRa)
- Offline financial record-keeping device

Seed explicitly avoids:
- Holding fiat currency custody
- Issuing legal tender
- Acting as a centralized payment processor

This positioning reduces regulatory burden while enabling broad deployment.

---

## 3. Customs Documentation Requirements

Each international shipment includes:

- Commercial Invoice
  - Device description: "Offline electronic device with low-power radio"
  - Declared value per unit
  - Country of origin
- Packing List
- Harmonized System (HS) Code
  - Typical category: 8517 (radio communication devices) or 8471 (data processing devices)
- Certificate of Origin (if required)
- Battery Compliance Documentation (see Section 5)

All documentation is standardized and pre-approved before shipment.

---

## 4. Radio Frequency Compliance

Seed devices operate on regionally permitted unlicensed ISM bands.

Compliance includes:
- FCC Part 15 (United States)
- CE / RED Directive (European Union)
- Regional equivalents (e.g., Anatel, ICASA, MIC)

Strategies:
- Region-specific firmware to enforce frequency limits
- Hardware SKU variants per regulatory region
- Clear labeling of operating frequencies

Seed does not require telecom licensing due to low-power, unlicensed operation.

---

## 5. Battery and Power Regulations

Seed uses Lithium Iron Phosphate (LiFePO4) batteries, chosen for safety and regulatory advantages.

Compliance standards:
- UN 38.3 battery transport testing
- IATA Dangerous Goods Regulations (air freight)
- IMDG Code (sea freight, if applicable)

Mitigations:
- Battery capacity kept below restricted thresholds
- Protective casing and short-circuit prevention
- Clear battery labeling and documentation

---

## 6. Import Restrictions and Sensitive Regions

Some regions impose heightened scrutiny on:
- Cryptography
- Radio communication devices
- Financial tools

Seed mitigates risk by:
- Using standard, approved cryptographic primitives
- Avoiding censorship-resistant messaging claims
- Positioning Seed as a local financial record and coordination tool

In high-risk regions:
- Pilot programs operate through NGOs or humanitarian partners
- Devices are imported under aid or development classifications when possible

---

## 7. AML, CFT, and Financial Oversight Considerations

Seed does not directly handle fiat currency or centralized accounts.

Key compliance points:
- Devices store user-controlled records only
- No centralized ledger or server
- No mandatory identity collection
- No transaction monitoring by Seed operators

This architecture reduces AML/CFT obligations while still allowing optional local compliance layers (e.g., kiosks or NGOs).

---

## 8. Labeling and Device Markings

Each Seed device includes:
- Country of manufacture
- Regulatory certification marks (FCC, CE, etc.)
- Battery safety markings
- Model and serial number

Labels are designed to:
- Survive harsh environments
- Be readable without electricity
- Support customs inspection

---

## 9. Partner and Distributor Responsibilities

Local partners are responsible for:
- Confirming local import requirements
- Filing import declarations
- Paying applicable duties or VAT
- Coordinating with customs officials

Seed provides:
- Pre-built compliance packets
- Regulatory guidance
- Technical documentation on request

---

## 10. Risk Management

Primary risks:
- Shipment seizure or delay
- Misclassification of device purpose
- Battery transport violations

Mitigation strategies:
- Conservative device descriptions
- Modular shipments (separating batteries when needed)
- Redundant compliance documentation
- Legal review before entering new regions

---

## 11. Long-Term Regulatory Strategy

As Seed scales:
- Regional regulatory experts are engaged
- Device SKUs are further localized
- Optional compliance modes may be introduced (e.g., regulated kiosks)

Seed maintains flexibility to operate:
- Independently
- Through NGOs
- Through governments or regulated institutions if required

---

## 12. Summary

Seed’s customs and regulatory strategy prioritizes safety, simplicity, and adaptability. By designing hardware, software, and logistics around existing consumer electronics and radio regulations, Seed enables global deployment without the overhead of a traditional financial institution—while remaining compliant, ethical, and resilient.
