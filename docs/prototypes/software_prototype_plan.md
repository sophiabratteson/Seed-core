# Software Prototype Plan

This document outlines the phased plan for developing the Seed software prototype, including goals, technical milestones, constraints, and success metrics. The software prototype serves as the foundation for validating Seed’s offline-first financial system, mesh networking behavior, AI assistant interactions, and device-level security model.

---

# 1. Goals of the Software Prototype

- Demonstrate functional offline-first transaction creation and syncing.
- Validate deterministic ledger logic across multiple devices.
- Implement a minimal mesh communication layer.
- Test trust-score updates, group-savings logic, and user workflows.
- Prove that Seed can function without internet, servers, or real-time clocks.
- Prepare for integration with actual hardware firmware.
- Provide a testbed for stakeholder demos, field tests, and early pilots.

---

# 2. Prototype Scope

The software prototype will focus on the following components:

## Ledger Engine (Core)
- Transaction creation
- JSON-based transaction schema
- Lamport clock management
- Conflict resolution logic
- Deterministic ledger merge
- Local storage of ledger state

## Mesh Sync Simulator
- Offline file-based sync between devices
- Optional: local Wi-Fi or Bluetooth as placeholder for LoRa
- Eventual integration with real LoRa radio drivers

## Group Savings Module
- Weekly rotation logic
- Contribution tracking
- Default contribution reminders
- Group transparency mechanisms

## Trust Score Module
- Behavior-based score adjustments
- Positive and negative event scoring
- Validation hooks for future machine learning models

## User Interface (Minimal)
- Terminal UI for early prototypes
- Optional: Figma blueprint for eventual embedded UI

## AI Assistant (Stub Version)
- Rule-based assistant responses
- Placeholder model for on-device inference
- Logging and training-data generation

---

# 3. Development Phases

## Phase 1: Foundation
- Set up folder structure in GitHub
- Create ledger engine in Python
- Implement deterministic transaction logic
- Build a basic CLI for user input
- Validate ledger consistency across two-laptop demo

## Phase 2: Offline Sync Simulation
- Export/import JSON outboxes
- Build reconciliation workflow
- Test conflict cases (parallel transactions, missing history, replays)
- Add signature placeholders

## Phase 3: Group Savings + Trust Score
- Implement group savings ledger events
- Add trust-score adjustment rules
- Validate group logic under conflict conditions

## Phase 4: AI Assistant Stub
- Provide rule-based structured responses
- Add hooks for personalization logic
- Create logging format for future training

## Phase 5: Mesh Networking Abstraction
- Abstract send/receive interface
- Add dummy radio driver
- Simulate packet loss, delays, and gossip sync

## Phase 6: UI / Experience Prototype
- Convert terminal flows to:
  - simple menus
  - screens for wallet balance, group savings, trust score
- Integrate with Figma visual blueprint

## Phase 7: Hardware Integration Prep
- Convert functional Python logic into C modules for firmware
- Map components to hardware functions:
  - radio driver
  - storage manager
  - battery/power manager
  - input controls
  - e-ink rendering layer

---

# 4. Required Components

## Programming Languages
- Python 3.12+ for prototype
- C for firmware-ready modules

## Libraries
- Standard Python libraries only:
  - json
  - uuid
  - time
  - os
- Optional: cryptography library for signing

## Tools
- GitHub repository
- Figma for UI mockups
- Two laptops for offline sync demo
- Planned hardware: LILYGO LoRa board + e-ink module

---

# 5. Prototype Outputs

By the end of the software prototype, Seed will have:

- A fully functioning ledger that works offline.
- Deterministic reconciliation logic demonstrated across two devices.
- Early versions of:
  - group savings flows
  - trust-score computation
  - AI assistant dialogue logic
- A documented sync protocol
- A clear path toward firmware implementation
- Demo-ready workflows for investors and advisors.

---

# 6. Success Criteria

- Two devices can exchange ledger updates without internet.
- Ledger state converges deterministically after conflicts.
- Group savings operation executes correctly across multiple sync cycles.
- Trust scores adjust consistently based on user behavior.
- Assistant module provides value-added guidance.
- Prototype can run in a field-test environment with no connectivity.

---

# 7. Risks and Mitigations

## Risk: Missing transactions or broken chains.
Mitigation:
- Use causal references.
- Validate chains before acceptance.

## Risk: Security not implemented early enough.
Mitigation:
- Add signing placeholders early.
- Integrate secure element during firmware stage.

## Risk: Mesh networking too complex at prototype stage.
Mitigation:
- Use file-based sync abstraction first.
- Replace backend driver later.

## Risk: Scope creep.
Mitigation:
- Strictly limit prototype to ledger, sync, group savings, trust score, and AI stub.

---

# 8. Next Steps

- Implement missing ledger tests.
- Expand two-device demo into multi-device simulation.
- Integrate mesh abstraction layer.
- Prepare a minimal graphical UI mockup.
- Begin translating validated Python modules into C for firmware.

---

# 9. Summary

The software prototype is the backbone of the Seed platform. It validates every fundamental principle of Seed: offline-first finance, local trust propagation, self-contained ledger state, deterministic syncing, and a user-guiding assistant. With this prototype, Seed proves its technical viability and prepares for hardware integration, investment readiness, and pilot deployment.
