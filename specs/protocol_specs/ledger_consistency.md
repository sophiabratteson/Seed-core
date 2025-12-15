# Ledger Consistency Specification

This document defines how Seed guarantees that all devices in the network eventually converge to the same ledger state, despite operating offline, without central servers, unreliable connectivity, or synchronized clocks. Ledger consistency is the foundational property that enables Seed to function as a trusted financial system in low-infrastructure environments.

---

## 1. Purpose and Scope

The purpose of this specification is to define:

- What “ledger consistency” means within Seed
- The guarantees Seed provides (and does not provide)
- The mechanisms used to achieve convergence
- The rules that ensure all devices reach identical outcomes
- The limits and trade-offs of an offline-first design

This specification applies to:
- Individual wallet balances
- Group savings pools
- Trust score updates
- Any future ledger-backed state (credits, vouchers, subsidies)

---

## 2. Definition of Ledger Consistency

A Seed ledger is considered **consistent** when:

- All valid transactions known to the network are present
- Transactions are ordered deterministically
- The same validation rules are applied
- All devices compute the same final balances and states

Consistency in Seed is **eventual**, not instantaneous.

This means:
- Devices may temporarily disagree
- Devices may hold partial views
- Given enough sync opportunities, all honest devices converge

---

## 3. Consistency Model

Seed uses an **eventual consistency model with deterministic convergence**.

Characteristics:
- No central authority
- No global clock
- No leader election
- No permanent forks

Instead:
- Every device independently validates
- Every device independently merges
- All devices follow the same merge rules

If two devices see the same data, they will compute the same result.

---

## 4. Deterministic Ordering Rules

Ledger consistency relies on strict, deterministic ordering rules.

Transactions are globally ordered by:
1. Lamport logical timestamp (ascending)
2. Device ID (lexicographic order)
3. Transaction ID (final tie-breaker)

This ordering guarantees:
- No ambiguity
- No dependence on arrival order
- Identical sorting across devices

---

## 5. Transaction Uniqueness

Each transaction must have:
- A globally unique transaction ID
- A single originating device
- An immutable payload

Duplicate transactions are:
- Detected by transaction ID
- Ignored if already applied

This ensures idempotent merges.

---

## 6. Validation Before Application

A transaction is only applied if:
- Its format is valid
- Its signature is valid
- Its dependencies are satisfied
- Its execution does not violate balance rules

Invalid transactions:
- Remain recorded for audit
- Do not affect balances
- Do not block other transactions

---

## 7. Handling Partial Knowledge

Devices may:
- Miss transactions
- Receive transactions out of order
- Be offline for extended periods

Seed handles this by:
- Allowing pending transactions
- Tracking unresolved dependencies
- Re-evaluating validity after each sync

No transaction is permanently rejected solely due to timing.

---

## 8. Conflict Resolution and Consistency

Conflicts (e.g., double spending) are resolved deterministically.

Rules:
- Transactions are applied in global order
- Earlier valid transactions consume available balance
- Later conflicting transactions become invalid

All devices reach the same conclusion because:
- They use the same ordering
- They use the same validation logic

---

## 9. Group Ledger Consistency

For group savings and shared pools:
- All contributions and withdrawals are ledger entries
- Group state is derived from transaction history
- No group state is stored separately from the ledger

This ensures:
- No divergence between members
- Full auditability
- Deterministic outcomes for rotations and payouts

---

## 10. Trust Score Consistency

Trust scores are:
- Computed from ledger history
- Not manually editable
- Recomputed deterministically

Given the same ledger, all devices compute the same trust score.

This prevents:
- Score manipulation
- Selective reporting
- Inconsistent reputations

---

## 11. No Forks, No Rollbacks

Seed does not support:
- Ledger forks
- Rewriting history
- Chain reorganization

Once a transaction is:
- Validated
- Ordered
- Applied

It becomes permanent.

Corrections occur via new transactions, not reversals.

---

## 12. Security Assumptions

Ledger consistency assumes:
- Honest majority behavior
- Cryptographic integrity
- Devices follow protocol rules

Malicious devices:
- Cannot rewrite history
- Cannot force divergence
- Can only introduce invalid data, which is ignored

---

## 13. Failure Scenarios

Ledger consistency holds under:
- Power loss
- Network partitions
- Intermittent connectivity
- Device loss or theft

Consistency may be delayed but not broken.

---

## 14. Limitations

Seed does not guarantee:
- Real-time consistency
- Instant settlement
- Global ordering speed

These trade-offs are intentional to enable:
- Offline operation
- Low power usage
- Infrastructure independence

---

## 15. Summary

Ledger consistency in Seed is achieved through:
- Deterministic ordering
- Immutable transactions
- Local validation
- Eventual convergence

This design allows Seed to operate as a reliable financial system without servers, internet, or centralized control, while still maintaining correctness, security, and trust across the network.
