# MVP Constraints

The MVP (Minimum Viable Product) for Seed must operate under realistic technical, economic, and user-environment limitations. These constraints ensure the MVP remains practical, buildable, and testable in low-resource communities while validating the core value proposition of Seed: reliable offline financial access without dependence on banks, smartphones, or the internet.

---

# 1. Hardware Constraints

## Limited Power Availability
- Devices must function with **no stable electricity grid**.
- Power sources include:
  - Small solar panel
  - Hand-crank generator
  - Rechargeable LiFePO4 battery
- Power budget must support:
  - E-ink screen refreshes  
  - LoRa radio transmissions  
  - Occasional AI voice/response processing  
- No power-intensive components (LCDs, GPS, WiFi, Bluetooth).

## Restricted Processing Capability
- Microcontroller must be low-power (e.g., ESP32-S3 or STM32 class).
- Limited RAM and flash require:
  - Lightweight ledger algorithms  
  - Tokenized/compact transaction storage  
  - Efficient mesh communication formats  

## Minimal Bill of Materials (BOM)
- Target BOM must remain under **$20–$35 per device** for eventual mass production.
- Early MVP units may cost more, but architecture must assume low-cost scalability.

---

# 2. Connectivity Constraints

## No Internet Requirement
- Devices must operate fully offline.
- Only optional upgrades may enable intermittent WiFi when available.

## Low Bandwidth Mesh Networking
- Mesh radios (e.g., LoRa) offer:
  - Very limited throughput (bytes per message)
  - Long range but slow data propagation
- This constrains:
  - Message formats  
  - Ledger synchronization cadence  
  - Real-time data expectations  

## No Central Server
- Ledger synchronization cannot rely on cloud infrastructure.
- All consensus and reconciliation must be **device-driven** and deterministic.

---

# 3. Ledger & Storage Constraints

## Limited Storage
- Typical MCU flash < 16 MB.
- Ledger must be:
  - Compressed
  - Checkpointed
  - Archived when full

## Deterministic Conflict Resolution
- Must operate strictly offline.
- Cannot depend on:
  - Global timestamps  
  - Internet clock synchronization  
  - Third-party validation services  

## Transaction Volume Limits
- Early MVP supports hundreds–thousands of transactions per device, not millions.

---

# 4. Security Constraints

## No Cloud-Based Key Management
- All private keys stored locally on the device.
- Secure element (if used) must fit within power and size limits.

## Lightweight Encryption
- Must use algorithms that fit MCU constraints:
  - Curve25519 / Ed25519  
  - AES-GCM  
  - SHA-256  
- Cannot use computation-heavy blockchain features like PoW, zk-proofs, etc.

## Basic Tamper Protection
- MVP includes:
  - Emergency wipe  
  - PIN or fingerprint entry  
  - Local signature validation  
- Advanced tamper detection may come in later versions.

---

# 5. User Experience Constraints

## Low Literacy / Multilingual Requirements
- Device must support:
  - Simple UI
  - Voice guidance
  - Icons rather than text-heavy interfaces

## No Smartphone Required
- UX must assume:
  - No app store
  - No pairing
  - No QR scanning
- Only physical Seed device interactions.

## Minimal Training Time
- Users should become functional with **< 15 minutes of training**.

---

# 6. Deployment & Distribution Constraints

## Low-Cost Maintenance
- Field deployment must not require skilled technicians.
- Data recovery and device resets must be simple and safe.

## No Formal Banking Partnerships Required (Initially)
- MVP must operate in markets **without**:
  - Local banks
  - ATMs
  - Credit bureaus
- Cash-in/cash-out handled through local community stewards, not institutions.

## Decentralized Rollout
- Devices must be usable and valuable even with:
  - Only 2–10 units deployed in an entire village
  - No national-scale network

---

# 7. Organizational Constraints

## Small Development Team
- Architecture must be buildable by:
  - 1–3 engineers  
  - Limited resources  
  - No massive infrastructure

## Limited Funding
- MVP should require:
  - Minimal backend infrastructure
  - Inexpensive hardware
  - Low ongoing maintenance cost

---

# 8. Regulatory & Compliance Constraints

## MVP Cannot Operate as a Registered Bank
- Avoids early regulatory burdens.
- Device must:
  - Not hold fiat deposits  
  - Not issue regulated credit  
- Instead, ledger operates as:
  - Community-managed  
  - Peer-to-peer  
  - Non-custodial  

## Avoid High-Risk Jurisdictions Initially
- MVP should launch in areas with:
  - Friendly fintech innovation policies  
  - Minimal telecom regulation hurdles  
  - Clear humanitarian use-case exemption potential  

---

# 9. Scope Constraints

## Features Included in MVP
- Offline ledger  
- Device-to-device sync  
- Wallet functionality  
- Trust score  
- Group savings  
- Basic AI assistance  
- E-ink UI  
- Fingerprint or PIN security  

## Features Excluded From MVP
- Internet-based payments  
- Blockchain anchoring  
- Large storage of historical records  
- Formal identity verification (KYC)  
- Complicated financial products  
- Cloud dashboard  
- Smartphone integrations  

---

# 10. Summary

The MVP for Seed is intentionally narrow, simple, and extremely robust. These constraints keep the project feasible for rapid development and field testing, while still validating Seed’s groundbreaking value:

**A resilient, offline financial system that empowers people without banks, without smartphones, and without internet.**

These constraints are not limitations—they are the foundation of Seed’s competitive advantage and long-term scalability.
