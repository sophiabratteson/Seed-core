# Field Test Plan

This document defines the structured plan for Seed’s first real-world field tests. The purpose of these tests is to validate hardware reliability, mesh network performance, user understanding, financial feature correctness, and offline-first behavior in environments similar to Seed’s target markets.

---

# 1. Objectives of the Field Test

Seed’s field tests pursue the following goals:

- Validate device-to-device mesh communication under real environmental constraints.
- Measure offline financial transaction success rates, sync times, and ledger consistency.
- Evaluate user comprehension of the interface (e-ink, buttons, prompts, audio).
- Test trust-score and group savings mechanisms in real community dynamics.
- Understand user habits, edge cases, and misunderstandings.
- Evaluate battery life under typical usage patterns (sunlight, partial shade, hand-crank use).
- Identify hardware failure points: heat, dust, impacts, moisture.
- Verify the backup-and-sync protocols work in unpredictable connectivity.
- Collect quantitative and qualitative data to guide MVP refinement.
- Build confidence for investors, partners, and future pilots.

---

# 2. Test Site Selection

Seed’s first field test should include controlled and semi-controlled environments.

## Priority Regions
- Rural communities with low or intermittent internet.
- Markets with active cash-based micro-entrepreneurship.
- Environments with high device-to-device interactions (markets, farms, pop-up stalls).

## Selection Criteria
- Safe, stable political environment.
- Established local partners (NGOs, universities, local councils).
- Accessibility for repeat visits.
- Users who represent Seed’s target personas: small vendors, gig workers, students, farmers, families.

---

# 3. Participant Recruitment

## Participant Types
- Small merchants (food stands, farmers, pop-up vendors).
- Community leaders (trusted mediators for group savings).
- Students or young adults (tech-comfortable early adopters).
- Low-tech households (critical for UI validation).

## Recruitment Strategy
- Work with local organizations to invite participants.
- Provide a short orientation session explaining Seed.
- Ensure balanced user groups (age, income, occupation).

## Participant Count
- Minimum: 8–12 participants.
- Ideal: 20–30 for network density testing.

---

# 4. Test Equipment

Each participant receives:

- 1 Seed prototype device.
- 1 protective case.
- 1 solar panel strip for charging.
- 1 hand-crank accessory.
- 1 printed quick-start guide.
- Optional: lanyard + dust-proof pouch.

Team equipment:

- Diagnostic laptop/tablet for reading device logs.
- USB backup kit.
- Local “kiosk” device for baseline calibration.
- Extra batteries.
- Radio interference scanner (optional).
- Consent and documentation materials.

---

# 5. Test Scenarios

The test will simulate real use cases Seed must eventually support.

## Scenario A: Basic Money Transfers
- Users send small amounts to each other.
- Validate:
  - Transaction creation success
  - Ledger update correctness
  - Sync times across mesh

## Scenario B: Vendor Payments
- Users “purchase” items from a test vendor.
- Validate:
  - Speed of payment flow
  - Accuracy of balance updates
  - Reliability of fingerprint unlock

## Scenario C: Offline Sync in Motion
- Users walk around a village/market.
- Validate:
  - Radio range
  - Packet loss
  - Mesh multi-hop behavior
  - Time until full ledger convergence

## Scenario D: Group Savings Pot
- 5–10 users create a rotating savings group.
- Validate:
  - Group join/leave flows
  - Money pot contributions
  - Rotation payout logic
  - Conflict resolution if contributions collide

## Scenario E: Trust Score Updates
- Users send/repay micro-loans or repeated payments.
- Validate:
  - Trust score increase/decrease rules
  - Protection against gaming
  - Display clarity for users

## Scenario F: Power and Charging
- Devices left in sun, partial shade, and indoors.
- Validate:
  - Solar recharge rate
  - Battery longevity
  - Hand-crank emergency charging
  - Overheat protections

## Scenario G: Stress and Failure Tests
- Users drop devices from pocket height.
- Devices left in dusty or humid conditions.
- Validate:
  - Hardware resilience
  - E-ink durability
  - Secure chip tamper protection

---

# 6. Data Collection Plan

## Quantitative Metrics
- Transaction success rate (%)
- End-to-end sync latency (seconds)
- Battery drain and recharge rates
- Radio packet loss
- Device uptime
- Number of conflicts detected and resolved
- Trust score behavior over time
- Group savings payout predictability
- Time to ledger convergence across all nodes

## Qualitative Metrics
- User understanding of UI
- Pain points when navigating menus
- Trust levels in the system
- Perceived value vs. cash
- Friction points in group usage
- Device comfort (weight, grip, readability)
- Cultural alignment with financial flows

## Tools for Logging
- On-device diagnostic file
- Researcher observations
- Participant interviews
- Usage diaries (optional)
- Sync logs from periodic kiosk check-ins

---

# 7. Ethical and Safety Considerations

- Ensure voluntary participation.
- Protect privacy: all data pseudonymized.
- No real money used — field tokens only.
- Avoid risk of conflict or financial stress.
- Provide full device retrieval after the study.
- Clear explanation of emergency wipe functionality.
- Local partner review of study plan.

---

# 8. Success Criteria

Seed’s MVP is considered validated if:

- 90%+ of transactions succeed without errors.
- 95%+ of devices converge to same ledger within expected sync window.
- Mesh connectivity remains stable in real world patterns.
- Battery lasts 24–48 hours under normal use.
- Users report that the system is:
  - Easy to learn
  - Trustworthy
  - Useful in their real life
- No critical hardware failures occur.
- Group savings and trust-score features behave predictably.
- Researchers observe organic social adoption behaviors.

---

# 9. Risks and Mitigation

- Hardware overheating → implement throttling and testing schedule.
- Radio interference → adjust frequency settings.
- User confusion → redesign UI flows.
- Incorrect trust score outcomes → refine algorithm weighting.
- Slow sync → adjust packet size / retry logic.
- Battery drain → adjust duty cycle and sleep modes.

---

# 10. Field Test Timeline

## Week 1: Preparation
- Finalize hardware kits.
- Train field facilitators.
- Prepare participant materials.

## Week 2: Deployment
- Orientation sessions.
- Device setup and distribution.

## Week 3–4: Active Testing
- Real-world use.
- Daily logging.
- Mid-test interviews.

## Week 5: Retrieval and Debrief
- Collect devices.
- Conduct final interviews.
- Download and analyze logs.

## Week 6: Synthesis
- Compile results into:
  - Technical evaluation report
  - User insights report
  - Recommendations for MVP updates
  - Investor-ready field test summary

---

# 11. Output Deliverables

- Field Test Report (technical + UX findings)
- Ledger consistency analysis
- Mesh performance summary
- Hardware durability assessment
- User feedback matrix
- Recommended MVP improvements
- Investor-ready results deck
- Updated product roadmap

---

# 12. Summary

This field test is a critical milestone for Seed. It validates whether offline payments, mesh communication, trust scores, and group savings work outside simulated environments and inside the economic reality of communities Seed aims to empower. The data collected here informs hardware revisions, software refinements, and investor readiness.

Seed becomes real when it works reliably in the hands of real people — this plan ensures we learn everything necessary to reach that point.
