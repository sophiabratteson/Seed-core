# Example User Personas Simulation

This document defines representative user personas used in Seed simulations to model real-world behavior across offline, low-connectivity, and trust-based financial environments. These personas are not fictional storytelling characters — they are behavioral models used to test ledger logic, trust score evolution, group savings dynamics, and mesh synchronization patterns.

The goal is to ensure Seed works reliably for diverse users under realistic constraints.

---

## 1. Purpose of User Personas in Simulation

User personas are used to:

- Stress-test ledger consistency under different behavior patterns
- Simulate trust score growth and decay over time
- Evaluate group savings reliability
- Identify edge cases caused by irregular usage
- Validate UX assumptions for low-literacy and offline users
- Model economic behavior in cash-heavy environments

Each persona is mapped to concrete simulation parameters.

---

## 2. Persona Categories Overview

Seed simulations model users across five primary dimensions:

- Connectivity access
- Financial stability
- Technical literacy
- Trust behavior
- Group participation patterns

---

## 3. Persona A: Rural Micro-Vendor

### Profile
- Occupation: Small market vendor
- Location: Rural village
- Connectivity: No internet, occasional mesh contact
- Literacy: Basic
- Device usage: Daily

### Behavioral Characteristics
- Performs many small transactions per day
- Accepts payments from multiple nearby users
- Frequently participates in group savings
- Highly sensitive to trust score changes
- Rarely disputes transactions

### Simulation Parameters
- Transactions per day: 10–25
- Average transaction value: Low
- Sync frequency: Opportunistic
- Trust score volatility: Low
- Group participation: High

### Failure Scenarios Tested
- Extended offline periods
- Power loss mid-transaction
- Duplicate transaction reception

---

## 4. Persona B: Migrant Worker

### Profile
- Occupation: Seasonal laborer
- Location: Moves between regions
- Connectivity: Intermittent
- Literacy: Moderate
- Device usage: Weekly bursts

### Behavioral Characteristics
- Sends money to family groups
- Uses delayed syncs
- Long offline gaps
- Occasionally changes devices

### Simulation Parameters
- Transactions per week: 3–6
- Average transaction value: Medium
- Sync frequency: Infrequent
- Trust score volatility: Medium
- Group participation: Medium

### Failure Scenarios Tested
- Conflicting balances after long offline periods
- Delayed trust score updates
- Device replacement recovery

---

## 5. Persona C: Community Savings Organizer

### Profile
- Occupation: Community leader
- Location: Semi-urban
- Connectivity: Mesh + occasional internet
- Literacy: High
- Device usage: Daily

### Behavioral Characteristics
- Manages group savings pools
- Tracks contributions
- Mediates disputes
- High interaction volume

### Simulation Parameters
- Transactions per day: 5–15
- Group updates per cycle: High
- Sync frequency: Frequent
- Trust score influence: High
- Group leadership role: Primary

### Failure Scenarios Tested
- Group update collisions
- Leadership device compromise
- Trust score abuse attempts

---

## 6. Persona D: New User with No History

### Profile
- Occupation: Varies
- Location: Any
- Connectivity: Unknown
- Literacy: Low–moderate
- Device usage: Inconsistent

### Behavioral Characteristics
- Small test transactions
- Hesitant group participation
- Rapid trust score changes
- High error rates

### Simulation Parameters
- Transactions per week: 1–3
- Average transaction value: Very low
- Trust score volatility: High
- Sync frequency: Random

### Failure Scenarios Tested
- Fraud detection sensitivity
- Trust score cold-start behavior
- UX error recovery

---

## 7. Persona E: Malicious or Exploit-Seeking User

### Profile
- Intent: Abuse system
- Connectivity: Opportunistic
- Literacy: High
- Device usage: Irregular

### Behavioral Characteristics
- Attempts replay attacks
- Creates conflicting transactions
- Tries to inflate trust score
- Exploits group dynamics

### Simulation Parameters
- Transaction timing: Adversarial
- Sync frequency: Strategic
- Trust score manipulation attempts: High
- Group behavior: Disruptive

### Failure Scenarios Tested
- Conflict resolution robustness
- Trust score decay effectiveness
- Abuse detection thresholds

---

## 8. Persona Interaction Scenarios

Simulations combine personas to test:

- Vendor ↔ Migrant remittances
- Organizer ↔ New user onboarding
- Malicious user ↔ Group savings disruption
- Dense mesh environments vs sparse networks

---

## 9. Metrics Observed Per Persona

For each persona, simulations track:

- Ledger convergence time
- Transaction success rate
- Trust score trajectory
- Group savings stability
- Sync retries and failures
- User-visible errors

---

## 10. Simulation Outputs

Each simulation produces:

- Time-series trust score graphs
- Ledger divergence/convergence logs
- Conflict resolution counts
- Group savings integrity checks
- Persona-specific failure reports

---

## 11. Future Persona Extensions

Planned additions include:

- Refugee camp users
- Disaster response workers
- Small NGOs using Seed for aid distribution
- Cross-border traders

---

## 12. Summary

User personas anchor Seed’s simulations in real human behavior. By modeling diverse economic roles, trust patterns, and connectivity realities, Seed ensures its ledger, mesh protocol, and trust systems work not just in theory — but in the real world where infrastructure is limited and reliability matters most.
