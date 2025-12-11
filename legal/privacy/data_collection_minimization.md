# Data Collection Minimization Policy

This document defines Seed’s approach to strict data-minimization across all devices, firmware, and backend-optional systems. Because Seed operates in low-connectivity and high-risk environments, minimizing what data is collected, stored, or transmitted is essential for user safety, regulatory compliance, and long-term trust.

---

# 1. Philosophy of Data Minimization

Seed follows four core principles:

1. Collect the absolute minimum data required for device functionality.
2. Store all necessary data locally and encrypted by default.
3. Never transmit data unless intentionally required for mesh synchronization.
4. Ensure users understand what the device holds and how to purge it at any time.

Seed is designed to work even when **no identifying personal data exists on the device**. This allows the platform to operate safely in refugee camps, rural communities, crisis zones, or areas with sensitive political situations.

---

# 2. Categories of Data Seed Does and Does Not Collect

## 2.1 Data Collected (Strict Minimum)

### Device-Level
- Device ID (randomly generated, non-personal)
- Public key used for signing transactions
- Local Lamport clock counter
- Encrypted ledger state
- Trust score (non-personal behavior metric)
- Group savings membership references (group ID, not names)

### Transaction-Level
- Sender ID (pseudonymous)
- Receiver ID (pseudonymous)
- Amount
- Timestamp-equivalent Lamport value
- Causal references (previous transaction IDs)
- Optional memos (never required)

### Behavior-Level (Optional and Local Only)
- Spending patterns for **local-only AI coaching**, never transmitted

No data in this category leaves the device unless explicitly included in a transaction broadcast.

---

## 2.2 Data Seed Does *Not* Collect

### No Personal Identity Data
- No legal names  
- No addresses  
- No phone numbers  
- No government IDs  
- No biometric templates stored in plaintext  

The fingerprint scanner only stores a **mathematical hash**, not a raw fingerprint image.

### No Location Tracking
- No GPS  
- No triangulation  
- No mesh-topology location inference  

### No Usage Tracking
- No analytics uploaded to servers  
- No engagement metrics  
- No centralized logs  

### No Third-Party Data Access
Seed devices do not report data to any cloud service by default.

---

# 3. Data Retention Limits

## Transaction History
Seed stores local ledger data necessary for:
- Validating future transactions  
- Catching double-spending  
- Replaying sync history if a device has been offline  

Older blocks may be compressed or checkpointed to reduce device storage footprint.

## AI Coaching Data
- Maintained strictly on-device  
- Automatically pruned after configurable intervals  
- Never shared across mesh or externally  

## Group Savings Data
Only minimal identifiers (group ID and indices for rotation) are stored.

---

# 4. Data Flow Controls

Seed enforces a tight control system ensuring only necessary data moves across devices:

1. Transactions are the only data broadcast over mesh.
2. Everything else remains local unless encrypted, signed, and user-authorized.
3. Mesh packets contain no personal metadata.
4. Each sync message is deterministic and minimal.

Special-case flows (such as reading trust score updates) use pseudonymous identifiers only.

---

# 5. User Control Over Data

## Local Controls
Users may:
- Trigger a secure wipe at any time
- Delete transaction history beyond required windows
- Opt out of AI personalization entirely
- Reset the device to factory state

## Emergency Wipe
A covert “safe fingerprint” triggers the following:
- Switch to a decoy profile
- Hide or encrypt ledger state
- Present fake balances and history
- Disable radio temporarily

This ensures real data is protected in dangerous environments.

---

# 6. Security Techniques Enabling Minimization

Seed combines data minimization with high security:

## Encryption
- All data at rest encrypted using secure element hardware
- All data in transit signed and optionally encrypted

## Isolation
- Ledger stored separately from device settings
- Fingerprint math template stored in secure chip memory partition

## Anonymous Signatures
Seed signatures are tied to device identity, not personal identity.

## Zero-Knowledge Concepts (Future Roadmap)
- Proofs for verifying balance sufficiency without revealing balance  
- Group membership checks without disclosing member details  

---

# 7. Regulatory Alignment

This model aligns with:

- GDPR Data Minimization & Storage Limitation Principles
- CCPA “right to delete” requirements
- Humanitarian data-protection guidelines (UN OCHA, ICRC)
- Low-connectivity financial inclusion frameworks (World Bank, ITU)

Because Seed avoids collecting personal data, regulatory exposure is drastically reduced.

---

# 8. Risks Addressed by Minimization

- Reduced attack surface for theft or surveillance
- Protection against forced data handover in oppressive regions
- Lower liability for operators or NGOs deploying devices
- Increased user trust due to transparent and minimal footprint
- Prevents Seed from becoming a tool for profiling or monitoring communities

---

# 9. Summary

Seed's data collection strategy is intentionally narrow. By collecting only what the device absolutely needs for financial operations, keeping all data encrypted locally, and preventing any unnecessary transmission, Seed protects users—even in the most vulnerable environments.

Data minimization is not just a safety feature; it is core to Seed’s mission: empowering people with financial tools while safeguarding their dignity, privacy, and autonomy.
