# Sync Frequency Specification

This document defines how often Seed devices attempt to synchronize ledger data, how synchronization adapts to environmental conditions, and how sync behavior preserves battery life, privacy, and ledger consistency in a fully offline-first mesh network.

This specification applies to all Seed devices, regardless of deployment region, connectivity level, or user role.

---

## 1. Purpose of Sync Frequency Control

Seed operates without continuous internet access, centralized servers, or guaranteed connectivity. As a result, synchronization must be:

- Opportunistic rather than continuous
- Power-aware and battery-safe
- Deterministic and eventually consistent
- Privacy-preserving
- Scalable from two devices to large community meshes

Sync frequency determines when and how often devices exchange data and is a core driver of system performance, reliability, and user trust.

---

## 2. Core Sync Principles

Seed synchronization follows five core principles:

1. Offline-first: Sync never assumes network availability.
2. Opportunistic: Sync occurs when conditions allow, not on fixed schedules.
3. Deterministic: Sync order does not affect final ledger state.
4. Energy-aware: Sync respects battery, power input, and device usage.
5. User-transparent: Sync happens automatically without requiring user action.

---

## 3. Sync Triggers

Seed devices initiate synchronization based on trigger events rather than fixed time intervals.

### 3.1 Proximity-Based Trigger
- Activated when two Seed devices come within radio range.
- Triggered by mesh heartbeat detection or neighbor discovery.
- Primary sync mechanism in offline environments.

### 3.2 Transaction-Based Trigger
- Triggered when a device creates one or more new transactions.
- Device schedules sync attempts to propagate new data.
- Sync attempts are rate-limited to avoid flooding.

### 3.3 Power-State Trigger
- Triggered when:
  - Solar charging becomes available
  - Hand-crank charging occurs
  - Battery level crosses a safe threshold
- Enables higher sync frequency during energy abundance.

### 3.4 Time-Based Fallback Trigger
- Used only when other triggers are unavailable.
- Low-frequency periodic check (e.g., once every several hours).
- Prevents indefinite isolation in sparse networks.

---

## 4. Adaptive Sync Frequency Model

Seed devices dynamically adjust sync frequency based on local conditions.

### 4.1 Battery Level Tiers

- Critical (0–15%):
  - Sync disabled except for emergency or trust-critical updates.
- Low (15–35%):
  - Sync only when explicitly triggered by proximity.
- Normal (35–70%):
  - Standard opportunistic sync enabled.
- High (70–100% or charging):
  - Aggressive sync allowed.

### 4.2 Network Density Awareness

Devices estimate local mesh density based on:
- Number of neighbors detected
- Frequency of recent syncs
- Volume of incoming messages

Behavior adjusts as follows:
- Sparse mesh:
  - More aggressive syncing when peers appear.
- Dense mesh:
  - Reduced frequency to avoid redundant propagation.

---

## 5. Sync Frequency Limits

To protect the network and devices, Seed enforces hard limits.

- Minimum interval between sync attempts per peer
- Maximum number of transactions sent per sync window
- Cooldown periods after failed sync attempts
- Randomized jitter to prevent synchronization storms

These limits are deterministic and applied uniformly across devices.

---

## 6. Sync Granularity

Synchronization is incremental, not full-state.

- Only unknown transactions are exchanged.
- Devices advertise transaction summaries before requesting full data.
- Checkpoints allow partial syncs to resume later.

This minimizes bandwidth usage and power consumption.

---

## 7. Group-Specific Sync Behavior

Group-based features (e.g., group savings, trust pools) may request higher sync priority.

- Group-critical updates are flagged with elevated sync urgency.
- Sync frequency increases temporarily to propagate group state.
- Priority decays after convergence is reached.

---

## 8. Failure Handling and Retry Strategy

If synchronization fails:

- Device backs off using exponential delay.
- Failure does not block other device functions.
- Partial progress is saved locally.
- Retry occurs only when conditions improve.

Repeated failures trigger diagnostic logging but do not degrade user experience.

---

## 9. Security and Privacy Considerations

Sync frequency policies support privacy by:

- Avoiding identifiable timing patterns
- Limiting broadcast behavior
- Supporting anonymous device identifiers
- Preventing forced sync requests from untrusted peers

Sync never leaks transaction content without explicit validation.

---

## 10. Deterministic Convergence Guarantee

Regardless of sync frequency variation:

- All valid transactions eventually propagate.
- All devices converge on identical ledger state.
- Order of sync events does not affect final outcomes.

This property is guaranteed by:
- Lamport logical clocks
- Deterministic conflict resolution
- Idempotent transaction application

---

## 11. Future Extensions

Planned enhancements include:

- User-configurable sync aggressiveness profiles
- Environmental learning (e.g., habitual sync locations)
- Trust-weighted sync prioritization
- Cross-network bridge sync policies

These extensions will remain backward-compatible with this specification.

---

## 12. Summary

Seed’s sync frequency model balances reliability, power efficiency, and scalability in environments where continuous connectivity is impossible. By relying on adaptive, trigger-based synchronization, Seed enables a resilient financial network that functions effectively across rural, disaster-prone, and infrastructure-limited regions.

This specification ensures that synchronization strengthens the network without burdening devices, users, or communities.
