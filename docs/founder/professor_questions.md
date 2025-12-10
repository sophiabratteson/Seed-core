# Questions for Professors and Technical Advisors

This document contains the structured, high-impact questions intended for academic mentors, researchers, and technical advisors who can provide guidance on Seed’s architecture, feasibility, and long-term research potential.

---

# 1. System Architecture & Feasibility

## 1.1 Mesh Network Design
- Does Seed’s proposed mesh architecture align with known limitations of LoRa or other low-bandwidth long-range radios?
- Are there existing research papers or projects whose designs Seed should analyze or model?
- Given the constraints of offline-first operation, what failure cases are we not yet considering?

## 1.2 Ledger Consistency
- Are Lamport clocks and deterministic merge rules sufficient for maintaining global ledger consistency in intermittently connected networks?
- Would vector clocks provide meaningful advantages, or unnecessary complexity?
- Are there known academic models for eventual consistency in low-resource environments that we should study?

## 1.3 Data Structures
- Is our current transaction format optimal for extremely low bandwidth?
- Are there compression or encoding techniques you recommend for sub-1kb messages?
- How should we design for forward compatibility if we evolve the protocol?

---

# 2. Hardware Guidance

## 2.1 Board Selection
- Do you recommend using ESP32-LoRa boards for early prototypes, or should we move earlier toward custom PCB development?
- What pitfalls should we expect when mixing LoRa, e-ink displays, and energy harvesting?

## 2.2 Power System Feasibility
- Is a hand-crank + solar hybrid system realistic for continuous low-power operation?
- Are there ultra-low-power chipsets or architectures we should explore beyond ESP32/SX1276?

## 2.3 Sensor Integration
- What is the best low-power approach for fingerprint authentication on resource-constrained devices?
- Are there any known issues with combining secure elements with mesh radios in harsh field conditions?

---

# 3. Security & Cryptography

## 3.1 Device Identity
- What is the recommended minimal cryptographic identity scheme for offline, low-power devices?
- How should we store private keys on constrained hardware without exposing them to tampering?

## 3.2 Ledger Integrity
- Are there cryptographic primitives better suited than signatures + lamport ordering for this environment?
- Should we explore Merkle proofs or authenticated data structures?

## 3.3 Threat Modeling
- Are there threat vectors unique to humanitarian/off-grid deployments that we should account for?

---

# 4. Economics & Game Theory

## 4.1 Trust Score System
- How should we mathematically design the trust score so it is stable, cheat-resistant, and culturally fair?
- Are there known models in distributed or informal finance that we should study?

## 4.2 Group Savings Logic
- What is the most academically grounded way to structure rotating savings groups digitally?
- Are there models for preventing collusion or defaults in offline, trust-based financial groups?

---

# 5. User Behavior & Deployment Strategy

## 5.1 Adoption Questions
- What behavioral patterns should we expect from users with limited digital literacy?
- Are there research methods you recommend to understand trust formation in non-banked communities?

## 5.2 Scaling Strategy
- How can we test mesh density, network coverage, and ledger convergence in small pilot deployments?
- Is simulation sufficient for early validation, or should we test with real hardware as soon as possible?

---

# 6. Research Collaboration & Opportunities

## 6.1 Potential Academic Partnerships
- Would this system qualify for interdisciplinary research between computing, economics, and humanitarian engineering?
- Are there labs on campus doing work in distributed systems, cryptography, technology for development, wireless systems, or embedded hardware who might be interested in Seed?

## 6.2 Publication Potential
- Which aspects of Seed are novel enough to pursue publication?
- What data would be required to justify a formal academic study?

---

# 7. Open-Ended Questions

- Based on what you know so far, what is the biggest flaw or risk in Seed’s design?
- What would you change or simplify if you were architecting this system from scratch?
- Which assumptions am I making that are unrealistic?
- What is the most important next technical milestone you think I should aim for over the next 60–90 days?

---

# 8. Closing

I am aiming to combine:
- distributed systems,
- mesh networking,
- low-power hardware,
- financial inclusion,
- and offline-first design

into a single system that can function reliably even where banks or internet cannot.

Any feedback, critiques, warnings, or guidance — no matter how small — will help shape Seed into a system that is technically feasible, secure, and academically rigorous.
