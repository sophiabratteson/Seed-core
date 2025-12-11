# AML/CFT Overview  
Anti-Money Laundering (AML) & Countering the Financing of Terrorism (CFT)

This document outlines how Seed can operate responsibly within global financial-crime prevention frameworks while still serving low-connectivity and underbanked populations. Because Seed functions without internet, traditional server-based monitoring is not possible. Therefore, Seed’s AML/CFT model focuses on **local controls, behavioral analytics, trust-based mechanisms, and structured off-ramps** that align with risk-proportionate regulatory expectations.

---

# 1. Why AML/CFT Matters for Seed

- Seed enables **financial value transfer** across a decentralized, offline mesh network.  
- Even though Seed is not a bank, regulators consider any system that moves or stores value as part of the broader AML ecosystem.  
- To launch pilots and eventually scale internationally, Seed must demonstrate:
  - Risk-based controls  
  - Transaction auditability  
  - Identity-verification pathways  
  - Fraud and abuse prevention mechanisms  

Seed’s design must therefore balance:
- **Inclusion** → enabling unbanked users to participate in the economy  
- **Compliance** → ensuring the platform cannot be easily exploited by bad actors  

---

# 2. AML/CFT Risk Model for Seed

Seed’s AML risk is shaped by six unique system attributes:

1. **Offline-first operation** – No server logging, no centralized oversight  
2. **Mesh-based communication** – P2P data transfer complicates traceability  
3. **Device-based identities** – Users do not need government IDs  
4. **Group-savings features** – Could be misused for “layering” without controls  
5. **Cash-onboarding** – Physical cash introduces inherent AML risk  
6. **Geographic deployment** – Some regions have elevated AML concerns  

To manage these risks, Seed uses proportional controls aligned with FATF (Financial Action Task Force) guidance for low-risk, low-value financial services.

---

# 3. Approaches to Identity & Verification

Seed supports **multiple tiers of user identity**, allowing compliance without excluding people lacking formal documents.

### Tier 0: Device-Only Identity  
- Identity = secure hardware chip + fingerprint sensor  
- Used for low-value transactions  
- Minimal regulatory burden  

### Tier 1: Community-Verified Identity  
- Local leaders or organizations vouch for user identity  
- Similar to humanitarian KYC models used by NGOs  
- Suitable for medium-value transfers  

### Tier 2: Full KYC  
- Government ID or NGO-verified credential  
- Required only when users seek connection to formal banking or high-value transfers  

This tiered model satisfies AML/CFT expectations while maintaining accessibility.

---

# 4. Transaction Monitoring in an Offline System

Traditional AML monitoring uses servers and real-time analytics.  
Seed cannot rely on that — but it *can* provide equivalent risk controls using:

## 4.1 Local Device Heuristics  
Devices maintain behavioral profiles:
- Sudden large transfers  
- Rapid movement of funds across many hops  
- Unusual trust-score manipulation  
- Suspicious group-savings withdrawals  

## 4.2 Trust Score Integration  
Users who behave anomalously:
- Lose trust score  
- Are temporarily throttled  
- May be flagged for manual review at a syncing kiosk or NGO partner site  

## 4.3 Encrypted Audit Trails  
Every Seed device maintains:
- A tamper-evident ledger  
- Locally encrypted transaction history  
- Optional periodic upload to partner organizations (when internet becomes available)

This ensures transparency without violating user privacy.

---

# 5. Cash Onboarding & Offboarding Controls

Since Seed users may deposit or withdraw physical cash, controls must exist to prevent abuse.

### 5.1 NGO-Run or Partner-Run Cash Points  
These operate like micro-branches:
- Users exchange physical currency for Seed credits  
- Staff maintain logs and apply ID requirements proportionate to transaction size  

### 5.2 Transaction Caps  
- Daily and monthly limits reduce AML exposure  
- Higher tiers unlock higher limits  

### 5.3 Automated Risk Rules  
Examples:
- Repeated maximum-limit deposits  
- Cash-ins inconsistent with user's income pattern  
- Structuring patterns (multiple small transactions to avoid limits)

---

# 6. International AML/CFT Standards Alignment

Seed’s compliance model aligns with guidance from:

- **FATF Recommendation 1** — Risk-based approach  
- **FATF Recommendation 10** — Customer Due Diligence (adapted for low-value accounts)  
- **FATF Recommendation 15** — New technologies  
- **FATF Recommendation 16** — Wire transfer rules (applied proportionately to mesh transfers)  
- **FATF Recommendation 22 & 23** — DNFBP requirements for cash-handling agents  

Because Seed is offline and decentralized, it fits into the category of **“Innovative Financial Inclusion Services”**, where FATF allows more flexible, risk-proportionate controls.

---

# 7. Prevention of Terrorist Financing (CFT)

Core principles:

- **Device-based identity** makes anonymous mass-account creation costly  
- **Mesh-range limits** reduce scalability of illicit networks  
- **Trust-score penalties** flag unusual patterns  
- **NGO or partner oversight** of onboarding ensures accountability  
- **Audit trails** allow retrospective analysis  

---

# 8. Red Flag Patterns for Seed

AML teams or partner organizations should watch for:

- Frequent device-to-device transfers with no economic purpose  
- Transactions occurring across an unusually wide geographic spread  
- Manipulation of group-savings pools  
- Sudden balance spikes  
- High turnover of devices within a single identity group  
- Suspicious trust-score gaming  

---

# 9. Reporting & Escalation Process

Seed’s AML/CFT system requires partnerships with regulated institutions or NGOs.

### Step 1: Device detects anomaly  
A risk score is triggered automatically.

### Step 2: Local review  
At next kiosk or sync point, flagged data is reviewed.

### Step 3: Escalation  
If warranted, case is referred to:
- Banking partner  
- NGO compliance team  
- Local regulatory authority  

### Step 4: SAR/STR Filing  
Suspicious Activity Reports or Suspicious Transaction Reports are filed per regional law.

---

# 10. Future Enhancements

- Machine-learning anomaly detection running fully offline  
- Zero-knowledge proofs for privacy-preserving AML  
- Blockchain-backed audit log for cross-partner accountability  
- Integration with humanitarian identity systems (ID2020, MOSIP)  

---

# 11. Summary

Seed’s AML/CFT framework ensures the system can scale responsibly while remaining accessible to the unbanked. The approach prioritizes:

- Risk-proportionate identity  
- Local transaction heuristics  
- Trust-score-based behavioral analysis  
- Human-in-the-loop cash operations  
- Secure, tamper-evident audit trails  

This enables Seed to meet global compliance expectations without compromising its mission of financial inclusion.
