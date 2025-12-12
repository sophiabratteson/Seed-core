 # Research Gaps

This document captures the most important unanswered questions and “missing links” in existing research that Seed must address to be credible to funders, pilots, and eventual regulators. It also translates those gaps into clear hypotheses, experiments, and deliverables Seed can produce.

---

## 1. Why This Matters

Most academic and industry work on financial inclusion assumes at least one of the following exists:

- Reliable phone ownership
- Continuous network coverage (2G/3G/4G/Wi-Fi)
- A formal KYC/ID pathway
- A functioning banking partner or agent network
- Stable electricity for charging

Seed’s claim is different: **a practical, offline-first financial system that can operate in harsh infrastructure conditions using local device-to-device sync**. That means Seed sits at the intersection of multiple research areas—each with known limitations when combined.

---

## 2. Seed’s Unique “Gap Intersection”

Seed is not *just*:
- Mobile money (needs network + agents)
- A digital wallet (often needs phones)
- A blockchain (often needs connectivity + compute)
- A radio mesh (often only designed for messaging, not value transfer)
- A lending model (often assumes centralized credit data)

Seed is **the integration** of:
- Low-power device UX (e-ink + minimal UI)
- Offline identity + secure storage
- Mesh sync + ledger convergence
- Cash-in/cash-out bridging
- Trust/reputation scoring for communities
- Group savings + rotating credit models

Most literature treats these as separate systems.

---

## 3. Core Research Gaps (What’s Missing Today)

## 3.1 Offline Value Transfer Without Phones
### What the literature covers
- Mobile money adoption and impact
- Agent networks for cash-in/cash-out
- Digital wallets and payment rails

### What’s missing
- A robust model for **offline device-based wallet usage** when phones are not reliable or not present
- UX patterns for financial actions on ultra-simple interfaces (e-ink, button-driven)

### What Seed must prove
- Users can complete critical actions (receive, send, save, repay) with low literacy and minimal UI
- The system remains usable without constant “updates” or app installs

---

## 3.2 Practical Mesh Ledger Convergence Under Real Constraints
### What the literature covers
- Mesh networks in disaster response
- Gossip/flood routing strategies
- Distributed systems consistency theory

### What’s missing
- “Ledger-grade” reconciliation rules designed for:
  - high packet loss
  - intermittent connectivity
  - long offline periods
  - partial views of history
  - constrained storage and compute

### What Seed must prove
- Devices converge on the same ledger state **eventually**, even when sync is irregular
- Sync cost is bounded (battery + bandwidth)
- Conflict resolution remains deterministic and auditable

---

## 3.3 Offline Double-Spend and Fraud Mitigation in the Real World
### What the literature covers
- Cryptographic signatures
- Secure elements and tamper resistance
- Fraud models in digital finance

### What’s missing
- A realistic model of **fraud in offline communities** where:
  - attackers can steal devices
  - users share devices
  - coercion is possible
  - “identity” may be informal
  - connectivity-based fraud monitoring is absent

### What Seed must prove
- Loss/stolen-device protocols are survivable for users
- Coercion-resistant modes (e.g., “panic/fake wallet”) reduce harm
- Replay and double-spend attempts are caught in reconciliation or constrained by design

---

## 3.4 Cash-In / Cash-Out in Low-Trust or Low-Bank Environments
### What the literature covers
- Agent banking and last-mile distribution
- Community savings groups (ROSCAs)
- Microfinance

### What’s missing
- A credible “bridge” model for:
  - converting cash to ledger value (and back)
  - without requiring a full formal bank system
  - while maintaining integrity and preventing counterfeit value issuance

### What Seed must prove
- A viable bridging operator model exists (NGO, merchant, kiosk partner, or roaming agent)
- Issuance/redemption rules are enforceable and audit-friendly
- The bridge can scale without becoming a traditional bank too early

---

## 3.5 Trust Score / Reputation Systems Without Formal Credit Infrastructure
### What the literature covers
- Credit scoring and alternative data
- Group lending dynamics
- Social collateral frameworks

### What’s missing
- A “trust score” approach that is:
  - explainable to users
  - resistant to gaming/collusion
  - fair across different communities
  - privacy-preserving
  - useful for small loans and group accountability

### What Seed must prove
- Trust score can predict repayment reliability better than pure social enforcement
- The scoring design avoids reinforcing inequality or excluding newcomers permanently
- The score can be used locally without needing central databases

---

## 3.6 Governance and Dispute Resolution in Community Finance
### What the literature covers
- Informal finance governance patterns
- Microfinance dispute practices

### What’s missing
- A defined governance mechanism for:
  - disputes (e.g., “I repaid but the device didn’t sync”)
  - mistaken transfers
  - group fraud or coercion
  - device confiscation or loss

### What Seed must prove
- Communities can resolve disputes with built-in transparency tools
- The system logs enough to support arbitration without exposing sensitive personal histories

---

## 3.7 Regulatory and Compliance Pathways for Offline-first Finance
### What the literature covers
- AML/CFT frameworks for digital finance
- E-money licensing structures
- Mobile money regulatory models

### What’s missing
- A realistic compliance model for a device mesh that is:
  - offline most of the time
  - not centrally mediated per-transaction
  - geographically distributed and potentially cross-border

### What Seed must prove
- A staged regulatory plan exists (pilot → partner program → licensed model)
- Risk controls can exist without constant online monitoring
- Transaction caps, thresholds, and audit exports can reduce regulatory risk in early pilots

---

## 4. Seed’s “Hypotheses” (Investor-Friendly)

Seed should treat each gap as a testable claim:

- **H1 (Usability):** Users can successfully complete basic wallet actions on e-ink + buttons with minimal training.
- **H2 (Convergence):** The ledger converges across devices after intermittent sync with deterministic conflict resolution.
- **H3 (Integrity):** Offline double-spend risk can be bounded via transaction rules + reconciliation + device security.
- **H4 (Bridge viability):** A low-cost kiosk/agent/merchant bridging model can sustain cash-in/out without full bank buildout.
- **H5 (Trust score usefulness):** Trust scores improve repayment rates and group reliability without requiring formal credit systems.
- **H6 (Dispute handling):** Built-in logs and group governance flows reduce disputes and speed resolution.
- **H7 (Compliance readiness):** Early pilots can operate safely within capped thresholds using auditable exports and controls.

---

## 5. Research-to-Deliverable Plan

Each gap should map to something Seed can produce quickly:

## 5.1 Documents (Credibility Assets)
- Offline-first ledger consistency + reconciliation spec
- Threat model tailored to offline finance
- Cash bridge operational model and controls
- Trust score governance and fairness policy
- Pilot compliance approach (caps, audit logs, partner roles)

## 5.2 Simulations (Proof of Logic)
- Multi-node sync convergence simulation under packet loss
- Conflict scenario library + deterministic outcomes
- Trust score evolution cases and anti-gaming tests

## 5.3 Prototype Tests (Evidence)
- Two-device radio message + transaction sync (bench)
- User flow testing (send/receive/save) with simple UI mockups
- Group savings workflow tests (contribution + rotation + missed payments)

---

## 6. Biggest “Unknown Unknowns” to Watch

These are high-risk areas where literature is thin and real-world behavior surprises teams:

- **Social dynamics:** fraud, coercion, device sharing, community trust breakdowns
- **Incentives:** why users participate in relay/sync behavior (mesh requires cooperation)
- **Bridge economics:** agents/kiosks need margins; pricing affects adoption
- **Governance:** disputes can destroy trust even if tech works
- **Regulatory friction:** “value storage” and “transfer” triggers licensing earlier than expected

Seed should continuously document what it learns here.

---

## 7. Summary

Seed’s advantage is not a single invention—it’s a system-level solution to a set of gaps that are rarely solved together. The most investor-relevant research gaps are:

- Offline value transfer UX
- Mesh ledger convergence at real constraints
- Offline fraud/double-spend mitigation
- Cash bridge models without becoming a bank immediately
- Trust score fairness + effectiveness
- Community governance and dispute handling
- Staged compliance pathway

Seed’s execution plan should be framed as: **prove each gap with a concrete test and a credible artifact**, then scale from there.
