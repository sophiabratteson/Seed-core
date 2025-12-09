# Trust Score Logic

This document defines the trust score system used by Seed devices. The trust score is a lightweight, offline-compatible indicator of a user’s financial reliability based on behavior recorded in the local ledger and validated through mesh-based synchronization. It serves as a decentralized credit proxy for individuals without access to formal banking or identification systems.

The goal of the trust score is to support micro-lending, group savings cycles, peer-to-peer transactions, and general financial reputation in environments without connectivity or centralized authorities.

---

# 1. Purpose of the Trust Score System

- Provide a consistent, deterministic measure of user reliability.
- Allow communities to extend microcredit without centralized banks.
- Enable group savings pools to operate safely and transparently.
- Allow users with no formal identity documents to build financial credibility.
- Work fully offline using only the ledger data stored on Seed devices.
- Resist manipulation, tampering, or Sybil-style impersonation attacks.
- Allow simple calculations on devices with limited hardware.

---

# 2. Foundations of Trust Scoring

The trust score is driven by five major categories of user behavior:

- Transaction reliability
- Loan repayment reliability
- Group savings participation
- Mesh contribution
- Device reputation and security integrity

Each category contributes positively or negatively to the trust score. All devices use identical deterministic scoring rules to ensure consistent output regardless of device order or sync latency.

The trust score is recalculated during every ledger checkpoint.

---

# 3. Trust Score Components

## 3.1 Transaction Reliability

Transaction reliability measures whether a user behaves consistently and honestly in everyday payments.

Positive indicators:
- Successful outgoing transactions
- Confirmed incoming transactions
- No double-spend attempts
- Correct signature verification
- Active transaction frequency

Negative indicators:
- Failed outgoing transactions due to insufficient balance
- Multiple rapid conflicting spend attempts
- Suspicious transaction bursts

Contribution:
- Each validated transaction adds +1
- Each invalid or rejected transaction subtracts -3
- Double-spend attempts subtract -10

---

## 3.2 Loan Repayment Reliability

This category tracks microloans within groups or between individuals.

Positive indicators:
- On-time repayments
- Early repayments
- No missed or skipped installments

Negative indicators:
- Missed repayments
- Partial repayments without group approval
- Disputes logged in the ledger

Contribution:
- On-time repayment adds +5
- Early repayment adds +7
- Missed repayment subtracts -15
- Delayed repayment subtracts -8

---

## 3.3 Group Savings Participation

Group savings cycles (rotating savings associations) require trust and transparency.

Positive indicators:
- Regular deposits
- No skipped deposit cycles
- Taking group payouts only when it is the user’s assigned turn

Negative indicators:
- Failing to contribute on required cycle
- Attempting to claim payout early
- Conflicts flagged by other group members

Contribution:
- Each deposit adds +2
- Successful completion of a savings round adds +10
- Missing a deposit subtracts -6
- Attempting early withdrawal subtracts -12

---

## 3.4 Mesh Contribution Score

Seed devices strengthen the network when they forward packets, relay transactions, or assist in gossip propagation.

Positive indicators:
- Relaying transactions from other devices
- Syncing ledger fragments with peers
- Acting as a bridge between disconnected clusters

Negative indicators:
- Refusing to relay transactions
- Tampering with relayed packets
- Repeated failure to broadcast valid updates

Contribution:
- Each successful relay event adds +0.2
- Each detected dropped or altered relay subtracts -3
- Devices offline for extended periods have no penalty unless suspicious behavior is detected

---

## 3.5 Device Reputation and Integrity

Devices maintain a local record of digital integrity signals.

Positive indicators:
- Valid secure boot
- Untampered secure element
- Unbroken signature chains
- No mismatched device IDs

Negative indicators:
- Failed secure boot check
- Suspicious key resets
- Signature mismatches across transactions

Contribution:
- Successful integrity checks add +3
- A failed integrity check subtracts -25
- Resetting identity keys subtracts -40 unless migration procedure is followed

---

# 4. Trust Score Formula

Every Seed device calculates the trust score using the same deterministic formula:

trust_score =
(tansaction_points)
- (loan_points)
- (savings_points)
- (mesh_points)
- (integrity_points)

Boundaries:

- Minimum score: 0
- Maximum score: 1000
- Default new user score: 50

Scores above 300 indicate reliable participation.  
Scores above 600 indicate excellent creditworthiness.  
Scores below 100 indicate high risk.

---

# 5. Offline Calculation Rules

All scoring must work offline, so Seed uses the following rules:

- Trust score is recomputed after each ledger merge.
- Devices do not rely on time; they use lamport order and checkpoint indexes.
- All score contributions are based purely on events in the ledger.
- If a device is missing relevant transactions, scores remain provisional until sync.
- When devices sync, the full ledger reconstructs the correct trust score identically on all devices.

---

# 6. Conflict Handling for Trust Score

Because trust score depends on transaction history, conflicts can influence scoring. Seed uses deterministic rules.

## Scenario A: Conflicting repayment records
- Use lamport ordering.
- If both remain valid, choose the earliest repayment and mark the conflicting one invalid.

## Scenario B: Conflicting group savings actions
- If two deposits are made for the same cycle:
  - Choose the higher lamport, then device ID.
- If a user both deposits and fails a deposit:
  - Treat deposit as valid unless failure record has higher lamport.

## Scenario C: Different devices report mismatched relay activity
- If one device reports a broken relay, and another reports success:
  - The record with higher lamport wins.
  - If equal, pick by device ID.

Once conflicts resolve, trust score recomputes immediately.

---

# 7. Checkpointing and Saving Trust Scores

Trust scores are stored in encrypted local storage with:

- Last computed trust score
- Trust score history for auditability
- Failure logs
- Group savings participation records
- Loan repayment schedules

Incremental updates are applied as ledger changes occur.

---

# 8. Displaying Trust Score to Users

To avoid misinterpretation:

- Devices show trust score as a simple bar or rating category:
  - Low, Medium, High, Excellent
- Raw numerical score is optional
- Score changes include short explanations:
  - "Missed group deposit"
  - "Completed savings cycle"
  - "Good mesh participation"
  - "Suspicious activity detected"

The goal is clarity without overwhelming inexperienced users.

---

# 9. Preventing Abuse and Gaming

The trust score system discourages manipulation by design.

Protections include:
- Signature validation
- Lamport ordering
- Causal references to prevent fabricated histories
- Secure identity keys
- Group consensus for disputes
- Rate limits on identity resets

No single device can alter someone’s trust score without producing verifiable ledger events.

---

# 10. Future Extensions

Planned enhancements include:

- Weighted scores based on peer reputation
- Multi-device corroboration for disputed events
- Zero-knowledge verification for privacy-preserving scoring
- Community-endorsed trust bumps for exceptional contributions
- Integration with external identity systems (optional)

---

# 11. Summary

The trust score system enables Seed to operate as a decentralized financial reputation protocol without central banks, internet, or formal credit infrastructure. By relying on deterministic scoring rules, cryptographic validation, and mesh-synchronized events, every device independently computes identical trust scores. This makes Seed robust, transparent, and fair in even the most disconnected environments.
