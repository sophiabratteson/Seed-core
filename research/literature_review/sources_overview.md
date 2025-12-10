# Sources Overview

This document summarizes the key categories of research sources that inform the Seed project. Because Seed spans financial inclusion, offline networking, distributed systems, cryptography, hardware engineering, and humanitarian development, the literature review draws on multiple academic and industry domains. This overview identifies the categories, why they matter, and the types of insights they provide.

---

# 1. Financial Inclusion and Development Economics

These sources examine barriers to financial access in low-income or infrastructure-limited regions.

- Unbanked and underbanked population statistics
- Structural causes of financial exclusion
- Cash-dominant economies and informal lending circles
- Household saving behaviors in emerging markets
- Credit access gaps and SME financing barriers

Why this matters for Seed:
- Validates the scale of the problem
- Defines user pain points Seed directly solves
- Offers data needed for TAM/SAM/SOM modeling

---

# 2. Digital Payments, Mobile Money, and Alternative Banking Models

These sources cover systems such as M-Pesa, bKash, GCash, and offline-capable payment solutions.

- Mobile-money adoption patterns
- Agent-based cash-in/cash-out ecosystems
- Success factors and failures of digital wallets
- Regulatory models for low-connectivity finance
- Offline payment architectures (SD cards, NFC, Bluetooth, USSD)

Why this matters for Seed:
- Shows how financial systems succeed without full banking infrastructure
- Helps refine Seed’s cash-to-digital flow and vendor onboarding
- Provides reference benchmarks for user trust and engagement

---

# 3. Distributed Systems and Offline-First Ledger Models

These sources inform how Seed maintains an offline mesh-based ledger.

- Lamport clocks and causal ordering
- CRDTs (Conflict-Free Replicated Data Types)
- Eventual consistency in distributed databases
- Peer-to-peer synchronization protocols
- Blockchain fundamentals (without requiring full blockchain overhead)

Why this matters for Seed:
- Guides conflict resolution, sync correctness, and tamper detection
- Ensures ledgers converge even with partial connectivity
- Enables a lightweight alternative to blockchain

---

# 4. Mesh Networking and Low-Power Long-Range Wireless Systems

These sources include LoRa, LoRaWAN, Bluetooth Mesh, 802.11s, Serval, DisasterRadio, and Meshtastic.

- Long-range radio propagation models
- Mesh topologies (flooding, gossip, routing tables)
- Power consumption characteristics
- Firmware patterns for intermittent connections
- Performance limits of unlicensed spectrum

Why this matters for Seed:
- Determines Seed’s realistic communication range
- Guides hardware selection and antenna design
- Ensures reliable sync under rural or constrained conditions

---

# 5. Low-Power Embedded Hardware and Device Architecture

These sources relate to building durable, offline-capable consumer devices.

- E-ink display power models
- Battery performance in extreme temperatures
- Secure elements and hardware encryption modules
- Solar and hand-crank power generation
- Rugged device manufacturing standards

Why this matters for Seed:
- Ensures device can operate for years in off-grid conditions
- Defines energy budgets and firmware efficiency targets
- Guides BOM cost and manufacturability

---

# 6. Cryptography, Secure Storage, and Identity Models

These sources provide foundations for device authentication and transaction integrity.

- Public-key cryptography for constrained devices
- Secure enclaves and tamper-resistant chips
- Key rotation and identity derivation
- Message signing and verification
- Threat modeling for offline devices

Why this matters for Seed:
- Ensures strong security even without internet access
- Protects users from fraud, impersonation, and data theft
- Informs device stolen protocol and emergency wipe features

---

# 7. Behavioral Economics, Trust Systems, and Group Lending

These sources study how communities manage savings, loans, and trust.

- ROSCAs (Rotating Savings and Credit Associations)
- Group lending dynamics (e.g., Grameen Bank model)
- Informal trust networks
- Incentive systems for repayment
- Social credit heuristics in cash economies

Why this matters for Seed:
- Directly informs the trust score system
- Guides design of group savings and lending tools
- Helps Seed integrate with existing community financial norms

---

# 8. Humanitarian Tech, Digital Public Infrastructure, and ICT4D

These sources examine tech deployed in challenging environments.

- Offline-first educational tools
- Solar-powered computing systems
- Aid-distribution identity systems
- Rural network deployments
- Ethical design for vulnerable populations

Why this matters for Seed:
- Provides practical lessons for durability and resilience
- Identifies risks in deploying financial tech in fragile regions
- Helps ensure Seed aligns with humanitarian safety standards

---

# 9. Industry Reports and Market Data

Relevant commercial sources include:

- GSMA Mobile Money Index
- World Bank Global Findex Database
- ITU connectivity reports
- UN digital inclusion research
- NGO field studies (e.g., Mercy Corps, CARE)

Why this matters for Seed:
- Supplies investor-grade data for market size
- Validates demand in low-connectivity regions
- Supports go-to-market strategy

---

# 10. Academic Databases Used

Seed’s literature review primarily draws from:

- JSTOR
- IEEE Xplore
- ACM Digital Library
- SSRN
- NBER
- CEPR
- Google Scholar
- UN and World Bank research portals

Each offers peer-reviewed or high-quality studies used to justify architecture, user needs, and technical decisions.

---

# 11. Summary

This overview ensures all research for Seed is:

- Organized
- Traceable
- Comprehensive
- Mapped to specific design decisions

By using financial, technical, behavioral, and humanitarian sources together, Seed builds a deeply informed vision grounded in evidence rather than assumptions.
