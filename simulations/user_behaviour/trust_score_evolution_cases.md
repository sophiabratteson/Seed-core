# Trust Score Evolution Cases

This document simulates how Seed’s trust score system evolves over time under real-world user behaviors. The goal is to validate that the trust score meaningfully reflects reliability, discourages abuse, and enables access to group savings and credit without requiring formal banking infrastructure.

---

## Purpose of This Simulation

- Validate fairness and robustness of trust score logic
- Demonstrate resilience to fraud and gaming attempts
- Show gradual trust accumulation rather than instant privilege
- Model how trust decays, recovers, and compounds
- Provide evidence for investor and regulator review

---

## Core Trust Score Assumptions

- Trust scores are **local-first** and computed on-device
- Scores sync across the mesh using deterministic rules
- No centralized authority assigns or modifies trust
- Trust is earned through behavior, not identity
- Trust cannot increase instantly and cannot be transferred

---

## Trust Score Inputs (Recap)

Trust score adjustments are based on:

- On-time repayment of group loans
- Participation consistency in group savings
- Transaction completion without disputes
- Mesh participation (sync reliability, forwarding)
- Account age and historical consistency
- Penalizations for defaults, disputes, or fraud flags

Scores are bounded between **0.0 and 1.0**.

---

## Case 1: New User, Slow Trust Accumulation

### Scenario
A new Seed user joins with no prior history.

### Behavior
- Joins a savings group
- Contributes small amounts weekly
- No missed payments
- No borrowing initially

### Trust Score Evolution
- Week 0: 0.10 (baseline)
- Week 4: 0.22
- Week 8: 0.34
- Week 16: 0.48

### Outcome
- Gains eligibility for small group loans
- Still restricted from large withdrawals
- Demonstrates gradual, earned trust

---

## Case 2: Reliable Borrower with Positive History

### Scenario
User has six months of consistent participation.

### Behavior
- Takes group loan
- Repays early
- Continues contributing regularly

### Trust Score Evolution
- Start: 0.55
- Post-loan approval: 0.57
- Post-repayment: 0.66
- After 3 months: 0.72

### Outcome
- Increased borrowing limits
- Preferred participant in group rotations
- Reduced collateral requirements

---

## Case 3: Missed Payment and Recovery

### Scenario
User experiences financial stress and misses a payment.

### Behavior
- Misses one weekly contribution
- Resumes payments the following week
- Communicates within group (non-technical signal)

### Trust Score Evolution
- Before miss: 0.60
- After miss: 0.52
- After 4 consistent weeks: 0.56
- After 12 consistent weeks: 0.62

### Outcome
- Temporary restrictions applied
- No permanent penalty
- System rewards recovery behavior

---

## Case 4: Repeated Defaults and Trust Collapse

### Scenario
User repeatedly borrows and fails to repay.

### Behavior
- Takes loan
- Misses repayment
- Attempts another loan via different group

### Trust Score Evolution
- Start: 0.50
- After first default: 0.35
- After second default: 0.18
- After third attempt: 0.08

### Outcome
- Borrowing disabled
- Group participation restricted
- User must rebuild trust through contributions only

---

## Case 5: Mesh Abuse Attempt

### Scenario
User attempts to inflate trust by spamming transactions.

### Behavior
- Sends many low-value transactions
- Minimal real economic activity
- Attempts rapid trust increase

### Trust Score Evolution
- Start: 0.20
- Detected anomaly: no increase
- Penalization applied: 0.15

### Outcome
- Rate-limited trust accrual
- Anti-gaming protections triggered
- No impact on honest users

---

## Case 6: Long-Term Dormant User Returns

### Scenario
User stops using Seed for several months.

### Behavior
- No transactions
- No group activity
- Device offline

### Trust Score Evolution
- Before dormancy: 0.68
- After 6 months inactivity: 0.60
- After return and activity: gradual recovery

### Outcome
- Trust decays slowly, not catastrophically
- Encourages long-term engagement
- Prevents abandoned accounts from retaining high privilege

---

## Case 7: Group Trust Reinforcement

### Scenario
User participates in a highly reliable group.

### Behavior
- Group has near-perfect repayment record
- User contributes consistently
- Group rotates loans fairly

### Trust Score Evolution
- Individual trust increases faster within bounds
- Group trust score reinforces individual confidence

### Outcome
- Strong incentive to form healthy groups
- Social accountability improves outcomes
- No single user can dominate trust system

---

## Edge Case Handling

- Trust scores never jump more than a capped delta per sync
- Conflicting trust updates resolved via lamport ordering
- Malicious trust packets rejected via signature validation
- Trust score history is auditable but privacy-preserving

---

## Simulation Conclusions

- Trust evolves gradually and predictably
- Bad behavior is penalized faster than good behavior is rewarded
- Recovery is possible but not instant
- System resists gaming and Sybil-style abuse
- Trust becomes a reliable proxy for economic reliability

---

## Relevance to Seed’s Mission

This trust model enables:
- Credit without credit bureaus
- Accountability without surveillance
- Inclusion without formal IDs
- Financial resilience in low-connectivity environments

Trust becomes a shared social asset — earned, protected, and respected across the Seed network.

---
