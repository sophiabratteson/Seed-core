# Group Savings Mechanism

This document defines the Seed group savings mechanism, its data structures, rules, incentives, conflict-resolution logic, and offline synchronization behavior. The goal is to provide a clear, investor-level explanation of how Seed enables rotating and pooled savings groups in areas with no internet access, no banking infrastructure, and low trust environments.

---

# 1. Purpose of Group Savings in Seed

- Enable small communities to pool money securely without a bank.
- Provide rotating access to lump-sum funds (ROSCA-style).
- Build trust and creditworthiness through transparent contributions.
- Work fully offline using device-to-device mesh sync.
- Reduce the risk of theft, loss, or manipulation common in cash-based systems.
- Provide a foundation for microcredit and small business investment.

Group savings is one of Seed’s most important financial primitives, because it replaces many functions of microfinance institutions with a completely decentralized, device-based alternative.

---

# 2. Types of Group Savings Supported

## 2.1 Pooled Contribution Model
- Every member contributes a fixed amount at a set interval (for example, weekly).
- Funds accumulate in a group pot.
- Pot can be:
  - withdrawn by a designated member for investment or emergencies
  - locked until a goal is met
  - used to provide small loans to group members based on trust score

## 2.2 Rotating Savings and Credit Association (ROSCA)
- Each member contributes the same amount each cycle.
- At each cycle, one member receives the full pot.
- Rotation order may be:
  - predetermined (order list)
  - auction-based (members bid for the pot)
  - trust-score-weighted

## 2.3 Hybrid Models
- Group chooses flexible rules:
  - Minimum contribution only
  - Rolling payout eligibility
  - Emergency override for medical or urgent needs

Seed is designed to support all three without needing internet or a bank.

---

# 3. Data Structures

## 3.1 Group Definition
```
{
  "group_id": "G123",
  "creator_device_id": "NODE_A",
  "members": ["A", "B", "C", "D"],
  "contribution_amount": 1.00,
  "cycle_length_days": 7,
  "model": "rosca" or "pooled",
  "rotation_order": ["A", "B", "C", "D"],
  "current_cycle_index": 0,
  "group_balance": 0.0,
  "history": [...],
  "metadata": { "purpose": "business", "region": "village_12" }
}
```

## 3.2 Contribution Transaction
```
{
  "tx_id": "...",
  "type": "group_contribution",
  "group_id": "G123",
  "sender": "B",
  "amount": 1.00,
  "lamport": 42,
  "device_id": "NODE_B",
  "signature": "..."
}
```

## 3.3 Payout Transaction
```
{
  "tx_id": "...",
  "type": "group_payout",
  "group_id": "G123",
  "recipient": "C",
  "amount": 4.00,
  "cycle": 2,
  "lamport": 51,
  "device_id": "NODE_C",
  "signature": "..."
}
```

All group activity is represented as transactions in the global ledger like any other financial operation. This keeps the system unified and auditable.

---

# 4. Group Logic and Rules

## 4.1 Contribution Validation
A contribution is valid if:
- The sender is an active member of the group.
- The amount matches the required contribution.
- Signature is valid.
- Sender has sufficient balance.

Invalid contributions are ignored and marked with an error state.

## 4.2 Payout Validation
A payout is valid if:
- The correct number of contributions for the cycle have been made.
- The recipient is the correct next participant.
- Amount matches pot size.
- Group is not already in payout-complete state for this cycle.

## 4.3 Rotation Rules (ROSCA Model)
The rotation order determines which member receives the pot in each cycle.
- Devices verify that payouts follow the rotation order.
- A payout executed out of order is invalid.
- If the scheduled member opts out, the group may reassign using:
  - simple voting
  - trust-score weighting
  - highest-need selection

These options can be implemented as additional transaction types.

---

# 5. Trust Score Integration

Trust scores influence:
- Contribution reminders
- Missed contribution penalties
- Eligibility for early payouts
- Access to microloans from the group pot
- Group confidence during conflict resolution

## 5.1 Trust Score Updates
Every contribution updates trust:
- On-time contribution: +1 to +3
- Late contribution: -1
- Missed contribution: -3
- Volunteer extra contribution: +2
- Fraudulent activity: large negative penalty

Each update is itself a ledger entry.

---

# 6. Offline Sync Behavior

Seed groups must function even when members sync at different times.

## 6.1 Contribution Sync
- Members submit contributions locally.
- When devices meet, contributions merge.
- Ledger sorts by lamport clock and device ID.
- Group pot is recalculated.

## 6.2 Payout Sync
- Payout is only executed once per cycle.
- If two devices propose different recipients due to partial sync, conflict resolution ensures:
  - the payout with higher lamport timestamp wins
  - if tie persists, device ID alphabetical ordering is used
- Losing payout is archived as invalid but kept for audit.

This ensures deterministic convergence across all devices.

---

# 7. Example Scenario

Village group of 4 members: A, B, C, D  
Contribution: $1 weekly  
Model: ROSCA  

Week 1:
- All contribute $1  
- Total pot = $4  
- Rotation order says A receives first payout  
- Payout transaction: recipient A, amount $4  

Week 2:
- All contribute again  
- pot = $4  
- Next payout: B  

Even if B was offline for week 1:
- When B syncs with C or D, their ledgers merge
- Payout history updates locally
- B sees correct state without internet or server

---

# 8. Security Model

## 8.1 Signature Requirements
Every group action requires:
- device private key
- user identity authentication (PIN or fingerprint)

## 8.2 Fraud Prevention
- Duplicate contributions are rejected.
- Payout amounts must match computed pot.
- A device cannot issue a payout without having the correct lamport ordering.
- Offline devices cannot rewrite group history due to deterministic merge rules.

## 8.3 Audit Trail
- All contributions and payouts are stored.
- Trust-score updates reflect member reliability.
- Ledger snapshots show the entire group history.

---

# 9. Integration with Full Seed Economy

Group savings interacts with:
- Wallet balance subsystem
- Trust score engine
- Microloan module
- Offline sync protocol
- Secure signing module

Long-term, group savings becomes a foundation for:
- Micro-insurance pools
- Cooperative farming funds
- Community business investments
- Village-wide guarantee networks

This is a core differentiator of Seed.

---

# 10. Future Enhancements

- Dynamic contribution amounts based on income.
- Smart ROSCA with automatic rotation adjustments.
- Group health metrics (participation rate, contribution reliability).
- Geo-tagged groups with migration support.
- Emergency override logic for urgent payouts.
- Gamified trust and participation scoring.

---

# 11. Summary

Seed’s group savings mechanism provides a decentralized, secure, offline-first alternative to banking cooperatives and microfinance institutions. By embedding contributions, payouts, rotation order, trust updates, and conflict resolution directly into the ledger, Seed enables communities to manage shared wealth reliably—even with no internet, no bank, and minimal infrastructure.

This module is essential for demonstrating Seed’s impact on financial inclusion, community resilience, and local economic growth.
