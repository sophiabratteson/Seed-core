# Mesh Network Privacy Model  
This document defines Seed’s end-to-end privacy architecture for decentralized, offline-first mesh communication. It explains how user identity, financial activity, and device metadata are protected across a distributed network that has no central authority, no internet dependency, and no external trust assumptions.

---

## 1. Privacy Principles
Seed’s privacy model is built on five core principles:

### 1.1 Data Minimization  
- Devices collect **only what is strictly required** for financial operations.  
- No GPS, no personal demographics, no behavioral analytics.  
- No data is shared with external servers—**the mesh is fully peer-to-peer**.

### 1.2 Local-First Data Storage  
- All data remains **encrypted and stored on-device**.  
- Syncing happens as **encrypted payloads** exchanged between devices.  
- Loss or theft does not reveal transaction history due to strong encryption and secure hardware.

### 1.3 Ephemeral Mesh Communication  
- Mesh messages are **not stored** by relay nodes.  
- Nodes pass encrypted packets without reading or caching them.  
- No routing device can map social graphs or transaction patterns.

### 1.4 Anonymous-by-Design Network Identity  
- Devices use **rotating, pseudonymous identifiers** ("Mesh IDs").  
- These identifiers do **not** contain personally identifiable information.  
- Relationship graphs remain intentionally opaque.

### 1.5 User-Controlled Disclosure  
- Users choose whether to reveal identity to:  
  - Lending groups  
  - Community leaders  
  - NGOs or local institutions  
- Disclosure is **optional** and stored locally, not on the mesh.

---

## 2. Identity Model

### 2.1 Device Identity Keys  
Every Seed unit ships with:  
- A **Device Keypair (DK)** stored in the secure element  
- A **Rotating Mesh ID** derived from the device key, updated periodically  

### 2.2 Pseudonymity  
- Transactions reference **Mesh IDs**, not names or phone numbers.  
- Even if a message is intercepted, it cannot be linked to a real-world person.

### 2.3 Optional Human Identity  
Used only for:  
- Account recovery  
- Community governance in savings groups  
- NGO verification during onboarding  

Stored locally and **never broadcast**.

---

## 3. Transaction Privacy

### 3.1 On-Device Ledger Encryption  
The ledger is encrypted using:  
- AES-256 for data at rest  
- SHA-256 for integrity  
- Tamper-protected secure element for keys  

### 3.2 Transmission Privacy  
Every transaction sent over the mesh is:  
- End-to-end encrypted  
- Signed with the sender’s private key  
- Obfuscated to hide metadata size and structure  

### 3.3 Metadata Minimization  
Mesh packets conceal:  
- Sender identity  
- Receiver identity  
- Transaction type  
- Causal dependencies  

Only encrypted blobs move across the network.

---

## 4. Mesh Communication Privacy

### 4.1 No Central Logs  
Because Seed uses a **distributed mesh**:  
- No single point can track or record communications  
- Nodes forward packets without knowing content  
- Communication persists even if governments disable internet  

### 4.2 Randomized Routing  
Packets may hop through:  
- Random neighbors  
- Multiple paths  
- Opportunistic relays  

This prevents adversaries from tracing origin or destination.

### 4.3 Unlinkability  
Two different transactions from the same user:  
- Use different Mesh IDs  
- Are encrypted with fresh nonces  
- Cannot be linked unless voluntarily disclosed  

---

## 5. Threat Scenarios and Mitigations

### 5.1 Adversary: Local Observer  
**Goal:** Determine who is transacting.  
**Protection:**  
- Encrypted packets  
- Randomized routing  
- Rotating Mesh IDs  

### 5.2 Adversary: Compromised Relay Node  
**Goal:** Analyze passing traffic.  
**Protection:**  
- No readable metadata  
- No transaction type leakage  
- Uniform message sizes  

### 5.3 Adversary: Device Seizure  
**Goal:** Read stored ledger.  
**Protection:**  
- Secure chip prevents key extraction  
- Full storage encryption  
- Emergency wipe mode  

### 5.4 Adversary: Network Censorship  
**Goal:** Disable financial communication.  
**Protection:**  
- Works on radio, not internet  
- Multi-hop mesh keeps running offline  
- Devices sync opportunistically  

---

## 6. Privacy in Group Savings & Trust Score Systems

### 6.1 Privacy-Preserving Group Participation  
Groups only learn:  
- Member Mesh IDs  
- Group contribution amounts  
- Rotation schedule  

They do **not** learn:  
- Total asset holdings  
- Transaction history  
- Other group memberships  

### 6.2 Trust Score Privacy  
- Trust score updates are **locally computed**.  
- Only aggregated trust signals are shared—not detailed logs.  
- Trust scores are bound to pseudonymous Mesh IDs, not names.

---

## 7. Developer and Research Access Controls

### 7.1 No Telemetry  
Seed devices do **not** send:  
- Usage analytics  
- Crash logs  
- Behavioral profiles  
- Network maps  

### 7.2 Research Mode (Optional)  
For NGO pilot studies only:  
- Must be user-opt-in  
- Uses aggregated, anonymized data  
- Stored off-device only with explicit consent  

---

## 8. Regulatory Alignment

### 8.1 GDPR & Global Data Privacy Norms  
Seed aligns with major frameworks by ensuring:  
- Data minimization  
- Right to local deletion  
- No unnecessary identifiable data  

### 8.2 Financial Compliance Strategy  
Because Seed is **not a bank**,  
- It stores no user identity  
- It performs no remote KYC  
- It holds no centralized transaction servers  

However, optional partner integrations can layer compliance if needed.

---

## 9. Summary  
Seed’s mesh privacy model makes it possible to run a financial system:  
- Without internet  
- Without centralized logging  
- Without risking user identities  
- Even in dangerous or low-connectivity regions  

By combining encrypted storage, pseudonymous routing, randomized mesh behavior, and a secure hardware root of trust, Seed delivers **financial privacy that is safer than traditional mobile banking**, while remaining fully decentralized and resilient.

Seed enables people to participate in the global economy with dignity, anonymity, and safety—even in the most vulnerable environments.
