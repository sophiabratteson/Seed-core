# Usage Profiles

This document defines the expected device usage patterns for Seed devices and explains how different user behaviors affect power consumption. These profiles are used to simulate battery life, solar/hand-crank requirements, and duty-cycle constraints under real-world conditions.

---

## Purpose of Usage Profiles

Usage profiles allow Seed to:
- Estimate realistic battery life under different behaviors
- Design power-saving strategies that match real users
- Validate that Seed can function reliably without grid electricity
- Compare worst-case and best-case power scenarios
- Support investor and regulator questions about feasibility

Each profile represents a **typical daily behavior pattern**, not an edge case.

---

## Core Assumptions

Unless otherwise stated, all profiles assume:
- Device uses an e-ink display (no backlight)
- LoRa radio operates in low-power mode by default
- Device sleeps whenever idle
- Solar or hand-crank charging is available intermittently
- Battery capacity is fixed per device spec

All simulations are conservative and intentionally under-promise performance.

---

## Profile 1: Minimal User (Low Activity)

### Description
- User checks balance occasionally
- Rare transactions
- Minimal group participation
- Device is idle most of the day

### Daily Activity
- Screen refreshes: 5–10
- Transactions created: 0–1
- Mesh sync events: 1–2
- Radio active time: < 2 minutes total
- Button presses: minimal

### Power Characteristics
- Dominant power usage: standby + occasional screen refresh
- Battery drain is extremely low
- Solar charging easily exceeds daily usage

### Expected Outcome
- Multi-week battery life without recharge
- Ideal baseline profile for feasibility validation

---

## Profile 2: Typical Individual User

### Description
- Small business owner or individual
- Sends and receives payments
- Participates in basic group savings
- Uses device daily

### Daily Activity
- Screen refreshes: 20–40
- Transactions created: 3–6
- Mesh sync events: 5–10
- Radio active time: 5–10 minutes total
- Occasional fingerprint authentication

### Power Characteristics
- Balanced power consumption across radio and display
- Battery drains slowly but predictably
- Solar or hand-crank charging required every few days

### Expected Outcome
- Stable long-term operation
- Primary target usage profile for MVP

---

## Profile 3: Group Organizer / Power User

### Description
- Manages group savings
- Frequently syncs with other devices
- Acts as a mesh relay node in the community

### Daily Activity
- Screen refreshes: 50–80
- Transactions created: 10–20
- Mesh sync events: 15–30
- Radio active time: 20–40 minutes total
- Frequent authentication events

### Power Characteristics
- Radio dominates power usage
- Higher duty cycle
- Requires daily or near-daily recharging

### Expected Outcome
- Still feasible with solar assistance
- Drives design of power throttling and relay limits

---

## Profile 4: Community Relay Node

### Description
- Device placed in high-traffic location
- Acts primarily as a mesh bridge
- Minimal direct user interaction

### Daily Activity
- Screen refreshes: < 5
- Transactions created: 0–2
- Mesh sync events: continuous bursts
- Radio active time: 1–3 hours total
- Minimal input usage

### Power Characteristics
- Radio is primary drain
- Requires aggressive power management
- Solar charging is essential

### Expected Outcome
- Validates relay feasibility
- Informs rules for mesh participation limits

---

## Profile 5: Worst-Case Stress Scenario

### Description
- Heavy usage
- Poor solar conditions
- Frequent sync retries
- High packet loss environment

### Daily Activity
- Screen refreshes: 100+
- Transactions created: 20+
- Mesh sync events: 50+
- Radio active time: > 3 hours
- Repeated retries and conflicts

### Power Characteristics
- Maximum drain scenario
- Used only for stress testing
- Not representative of normal use

### Expected Outcome
- Device may throttle features
- Confirms system fails safely, not catastrophically

---

## Simulation Inputs Derived from Profiles

Each usage profile feeds into:
- Duty cycle assumptions
- Average current draw estimates
- Sleep vs active ratios
- Recharge interval models
- Feature throttling rules

Profiles are parameterized so they can be adjusted without changing simulation logic.

---

## Design Implications

Usage profiles directly influence:
- Battery size selection
- Solar panel minimum wattage
- Hand-crank energy targets
- Mesh participation limits
- UI interaction constraints
- Background sync scheduling

Power-aware design decisions are always grounded in these profiles.

---

## Future Extensions

Planned improvements include:
- Seasonal usage variation
- Cultural and regional behavior differences
- Emergency/disaster usage patterns
- Adaptive profiles based on learned behavior
- Trust-score-weighted relay participation

---

## Summary

Usage profiles are the foundation of Seed’s power feasibility. By modeling realistic human behavior instead of idealized assumptions, Seed ensures that its offline financial infrastructure remains usable, resilient, and trustworthy in the environments it is designed to serve.
