# Power Saving Strategies

This document defines how the Seed mesh protocol minimizes power consumption while maintaining reliable, secure, and eventually consistent communication across an offline-first LoRa mesh network. Power efficiency is a core requirement because Seed devices operate in environments with limited electricity, relying on batteries, solar input, and hand-crank generation.

---

## 1. Design Goals

- Maximize device uptime under constrained power conditions
- Minimize radio transmission and reception costs
- Avoid unnecessary wake cycles and redundant messages
- Preserve ledger consistency without constant connectivity
- Enable graceful degradation under extreme low-power scenarios

Power-saving strategies must never compromise ledger correctness or security.

---

## 2. Power Cost Model

Seed treats power as a scarce resource with the following relative costs:

- Radio transmission: Very high cost
- Radio reception: High cost
- CPU processing: Medium cost
- Storage read/write: Low cost
- E-ink display refresh: Very low cost (one-time cost per update)
- Idle sleep: Minimal cost

All routing decisions prioritize reducing radio usage above all else.

---

## 3. Duty Cycling Strategy

### 3.1 Radio Duty Cycling

Each Seed device operates its radio on a duty cycle:

- Default state: Radio OFF
- Wake windows occur at fixed or adaptive intervals
- Radio is enabled only during:
  - Scheduled sync windows
  - User-initiated actions
  - Neighbor discovery intervals
  - Emergency or high-priority events

Duty cycle parameters are configurable based on deployment environment.

---

### 3.2 Adaptive Duty Cycling

Devices dynamically adjust duty cycle based on:

- Battery level
- Recent successful sync activity
- Network density
- Time since last ledger update

Examples:
- High battery + sparse network → longer listen windows
- Low battery + dense network → shorter, less frequent windows

---

## 4. Event-Driven Communication

Seed avoids continuous listening by using event-driven messaging:

- Outgoing messages are queued locally
- Messages are transmitted only during radio-on windows
- Incoming messages are processed only when radio is enabled

This prevents constant idle listening, which is a major power drain.

---

## 5. Message Batching

### 5.1 Transaction Batching

Instead of sending individual transactions:

- Multiple transactions are bundled into a single message
- Ledger diffs are transmitted instead of full ledgers
- Reduces overhead and transmission count

Batch size is capped to avoid packet fragmentation.

---

### 5.2 Sync Window Bundling

During a sync window:
- Neighbor discovery
- Ledger sync
- Heartbeat updates

are performed together to amortize radio costs.

---

## 6. Gossip Suppression

Seed limits redundant transmissions using gossip suppression rules:

- Each message includes a hop count and message ID
- Devices do not re-forward messages they have already seen
- Duplicate suppression tables are stored in memory with expiration

This prevents exponential broadcast storms.

---

## 7. Priority-Based Messaging

Messages are assigned priority levels:

- Critical: Ledger conflicts, security alerts
- High: Transactions, group savings updates
- Medium: Trust score updates
- Low: Heartbeats, diagnostics

Low-priority messages may be:
- Delayed
- Dropped under low battery
- Aggregated into later syncs

---

## 8. Low-Power Modes

### 8.1 Sleep States

Seed devices support multiple sleep states:

- Light sleep: CPU idle, radio off
- Deep sleep: CPU off, memory retained
- Emergency sleep: Only secure clock and tamper detection active

State selection depends on power availability and risk conditions.

---

### 8.2 Wake Triggers

Devices wake from sleep due to:
- Scheduled timers
- User input
- Tamper detection
- Emergency broadcast signals

---

## 9. Neighbor Quality Scoring

To avoid wasted transmissions:

- Devices track neighbor reliability
- Neighbors with low success rates are deprioritized
- Routes favor stable, power-efficient peers

This reduces repeated failed transmission attempts.

---

## 10. Store-and-Forward Optimization

Seed favors store-and-forward behavior:

- Devices carry messages until an efficient sync opportunity arises
- Opportunistic syncing replaces constant polling
- Users moving between locations naturally propagate data

This aligns with real-world mobility patterns.

---

## 11. Power-Aware Routing Decisions

Routing logic incorporates power metadata:

- Devices may advertise low-power status
- Low-power devices are excluded from routing paths
- High-power devices act as temporary relays

This prevents draining vulnerable nodes.

---

## 12. User-Configurable Power Profiles

Seed supports selectable profiles:

- Performance Mode
- Balanced Mode
- Ultra-Low Power Mode

Profiles adjust:
- Sync frequency
- Duty cycle length
- Message batching thresholds

Defaults favor safety and longevity.

---

## 13. Failure and Recovery Behavior

If a device enters critical power state:

- Ledger state is checkpointed
- Radio disabled except for emergencies
- Sync deferred until power recovers

No data is lost during power exhaustion.

---

## 14. Security Considerations

Power-saving features must not:
- Skip signature validation
- Accept unauthenticated messages
- Disable tamper detection

Security modules remain active even in deep sleep.

---

## 15. Summary

Seed’s power-saving strategies enable months-long operation in extreme environments by:

- Minimizing radio usage
- Leveraging batching and opportunistic sync
- Adapting behavior based on power availability
- Preserving correctness and security at all times

These strategies allow Seed to function reliably without constant electricity, internet access, or centralized infrastructure.
