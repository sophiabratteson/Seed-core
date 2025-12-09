# MVP Scope

This document defines the Minimum Viable Product (MVP) for Seed — a hardware-based, offline-first financial tool designed for populations without consistent access to banks, internet, or electricity. The MVP focuses on proving technical feasibility, validating core user behaviors, and demonstrating early economic impact in a controlled pilot environment.

---

# 1. MVP Goals

- Demonstrate offline peer-to-peer money transfer between two Seed devices.
- Validate that users can store, send, and receive balances securely without internet.
- Prove that a mesh-based sync model can update ledger states reliably across multiple devices.
- Test ease of use for low-literacy and low-tech populations.
- Establish early trust-score and group-savings behaviors.
- Collect data to inform regulatory, UX, and hardware refinements.

---

# 2. MVP User Capabilities

## Core Financial Actions
- Create a personal Seed account tied to a device ID and fingerprint.
- View balance and recent transactions on an e-ink display.
- Send value to another Seed user offline.
- Receive value from another Seed user offline.
- Cash-in and cash-out via designated “Seed Stewards” (local trusted vendors).
- Store funds securely using on-device encryption.

## Group + Community Features
- Join a small group savings pool (4–12 users).
- Contribute a fixed weekly amount into the shared pot.
- Rotate the payout among members using deterministic logic.
- View transparent group contribution history.

## Trust Score (Simplified MVP Version)
- Increase score for:
  - On-time group contributions
  - Completing transfers successfully
  - Maintaining consistent device uptime
- Decrease score for:
  - Failed transactions due to insufficient balance
  - Missed group contributions
- Display trust score as a simple number (0–100).

---

# 3. MVP Hardware Requirements

- Microcontroller with LoRa/SX1262 or SX1276 radio.
- E-ink display (2.13” or similar).
- Rechargeable LiFePO4 battery.
- Solar trickle-charging panel OR hand crank input (prototype may use USB).
- Secure element chip (ATECC608A or equivalent).
- Fingerprint sensor for identity verification.
- Minimal buttons (confirm, scroll, home).

Hardware targets:
- 5–7 day battery life (light usage).
- Durable enclosure suitable for heat and dust.
- Replaceable battery capability.

---

# 4. MVP Software Requirements

## Ledger Engine
- Lamport timestamp–based transaction ordering.
- Deterministic conflict resolution.
- Signed transactions stored in append-only ledger.
- Lightweight JSON-based transaction format.

## Mesh Sync Protocol
- Offline-first design.
- Periodic radio broadcasts of:
  - Outbox transactions not yet known by peers
  - Checkpoints
  - Device heartbeat
- Ability to reconcile partial histories across peers.

## Device Applications
- Wallet App (balance, send, receive).
- Group Savings App (contribute, view pot, payout rotation).
- Trust Score App (view score + simple explanations).
- Settings App (language, brightness, device info).

## Security Requirements
- Local storage encryption.
- Private key stored in secure element.
- Tamper-detection triggers emergency wipe workflow.
- Signed transactions with replay protection.

---

# 5. MVP Implementation Scope (What *Is* Included)

- Two to five prototype devices communicating via LoRa.
- Local ledger storage and secure boot.
- Minimal UI with e-ink and 2–3 buttons.
- Basic group savings prototype with fixed schedules.
- Offline-only sync workflow.
- Ability to run a controlled pilot with <20 users.
- A simple steward onboarding flow for cash-in/out operations.

---

# 6. Out of Scope for MVP (Future Versions)

These features should NOT be built yet, but are planned for later stages:

- Full mobile app ecosystem.
- Multi-currency support.
- AI financial assistant embedded on-device.
- Large-scale routing optimization for 100+ node networks.
- Government ID integration or KYC workflows.
- Full cloud backup and analytics backend.
- Production-grade enclosure and waterproofing.
- Large-scale manufacturing readiness.

Keeping these out of MVP ensures speed, cost-efficiency, and laser-focus.

---

# 7. Success Metrics

## Technical Metrics
- >90% transaction sync success rate in offline conditions.
- Ledger convergence across all devices within 24 hours.
- Battery lasts at least 3 days in normal usage.

## User Metrics
- 80% of pilot users complete at least one transaction.
- 70% participate in a group savings cycle.
- <10% report difficulty understanding device workflow.

## Impact Metrics
- Demonstrated ability to store value digitally without internet.
- Evidence that trust score and group savings reinforce positive financial habits.
- Quantitative reduction in cash loss/theft vs baseline.

---

# 8. MVP Pilot Plan (High-Level)

- **Phase 1:** Build 5–10 functional prototypes.
- **Phase 2:** Onboard a small community partner (NGO, village leader, microfinance agent).
- **Phase 3:** Distribute devices to 10–20 participants.
- **Phase 4:** Run a 4–6 week trial.
- **Phase 5:** Collect qualitative + quantitative data.
- **Phase 6:** Iterate on hardware, UX, and ledger rules.

---

# 9. Summary

The MVP focuses on proving Seed’s core insight:

A simple, rugged, ultra-low-power hardware wallet can enable financial participation, savings discipline, and value exchange **without banks, without internet, and without electricity**.

The MVP is purposely narrow, technically feasible, and immediately testable — designed to de-risk the vision and pave the way for a scalable, global Seed ecosystem.
