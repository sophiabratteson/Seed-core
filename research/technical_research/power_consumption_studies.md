# Power Consumption Studies

This document collects the power-related research, assumptions, and test plans needed to prove that **Seed can run reliably with minimal power** in low-infrastructure environments (limited electricity, intermittent charging, high heat, dust, etc.). It is written to be both **engineering-useful** and **investor-readable**.

---

## 1. Why Power Is a Core Risk (and a Core Advantage)

Seed’s value proposition depends on being usable when phones, internet, and stable electricity are not available. That means the device must be:

- **Ultra-low power at idle** (most of its life)
- **Predictable during transmit bursts** (LoRa / mesh radio)
- **Safe in heat** (battery + charging)
- **Chargeable from “weak” sources** (small solar, hand crank, shared power)

Power is also an investor-facing advantage: if Seed can operate for days/weeks between charges, it becomes dramatically more deployable than phone-based solutions.

---

## 2. What “Power Consumption” Means for Seed

Power is not one number. It depends on the device’s “modes”:

- **Sleep / standby**: device is mostly off, waiting for a button press or periodic wake
- **UI interaction**: user is reading screen, pressing buttons, confirming actions
- **Radio transmit**: sending packets to neighbors
- **Radio receive / listening**: scanning for neighbors or receiving packets
- **Sync burst**: multiple messages exchanged to reconcile ledgers
- **Secure operations**: signature checks, encryption/decryption, secure storage writes

A realistic power model must measure each mode and then multiply by how often it happens.

---

## 3. Power Budget Goals (Targets)

These are “design targets” you can refine once hardware arrives.

### 3.1 Usability targets
- **Minimum 3–7 days** of normal use without charging (baseline target)
- **1–2 weeks** in “light use” (ideal target)
- **At least 50–100 transactions/day** with periodic sync, without constant charging

### 3.2 Safety targets
- Battery should remain stable and safe in hot climates (design preference: **LiFePO₄**)
- Charging should be **current-limited** and **thermally aware**
- Device should degrade gracefully (e.g., reduce radio duty cycle if battery is low)

### 3.3 Charging targets (practical)
- A small solar panel should produce “meaningful progress” daily in typical conditions
- A hand crank should provide emergency charge (even if inefficient)

---

## 4. Key Hardware Components That Drive Power

These are the major power drivers and the levers you can pull:

### 4.1 Display (E-Ink)
- **Very low power** once the image is on screen
- Power spikes during refresh
- Strategy: update only when needed; use partial refresh where possible

### 4.2 Radio (LoRa / Mesh)
- TX bursts can be power-expensive
- Listening can also be expensive if always-on
- Strategy: duty-cycled listening, scheduled sync windows, acknowledgements + retries tuned conservatively

### 4.3 Microcontroller (MCU)
- Sleep current and wake efficiency matter
- Strategy: spend as much time in deep sleep as possible; keep active CPU bursts short

### 4.4 Storage (Flash)
- Writing to flash costs power and also impacts longevity
- Strategy: batch writes; use checkpoints; avoid writing on every minor event

### 4.5 Security chip / secure element (optional early; important later)
- Can add overhead but improves trust and safety
- Strategy: use for keys/signatures while keeping the main MCU in low-power modes as much as possible

---

## 5. Operating Profiles (Realistic Usage Scenarios)

To estimate battery life, define a few profiles.

### 5.1 Profile A: Light use
- 5 transactions/day
- 1 sync/day
- Device asleep 99% of time
- UI interaction: < 5 minutes/day

### 5.2 Profile B: Normal use
- 25–50 transactions/day
- 3–6 sync windows/day
- UI interaction: 15–30 minutes/day
- Some radio listening during daylight hours

### 5.3 Profile C: Heavy / market day
- 100–300 transactions/day
- Frequent sync (vendors interacting constantly)
- UI interaction: 1–2 hours/day
- Many radio transmissions and receives

### 5.4 Profile D: Disaster / emergency mode
- Messaging and sync prioritized
- Possibly higher transmit power
- More frequent listening windows
- Battery preservation policies become critical

---

## 6. Measurement Plan (What You Will Actually Test)

This section is what makes it “real” for engineering and investors.

### 6.1 What you need to measure
- Sleep current (deep sleep)
- Wake + UI current (buttons + screen update)
- Radio TX current (at different power levels)
- Radio RX/listen current (duty cycle settings)
- Full “transaction lifecycle” energy (create → sign → store → transmit → confirm)

### 6.2 Tools for measurement (simple first)
- USB power meter (quick, approximate for dev boards)
- Multimeter + inline current measurement (better)
- Optional: dedicated power profiler (best, later)

### 6.3 Test method (repeatable)
For each mode:
1. Put device in the mode
2. Measure current draw (mA) and time spent (seconds)
3. Compute energy per event:
   - **mAh per event = (mA × seconds) / 3600**
4. Multiply by daily frequency from a usage profile
5. Compare against battery capacity

---

## 7. Battery Life Estimation (How to Calculate)

### 7.1 Basic math
- Battery capacity is in **mAh** (milliamp-hours)
- Your daily usage consumes **mAh/day**
- Estimated runtime:
  - **days ≈ battery_mAh / usage_mAh_per_day**

### 7.2 Example template (fill later with real measurements)
- Sleep: 2 mA for 23 hours/day → 46 mAh/day
- UI: 40 mA for 20 minutes/day → 13.3 mAh/day
- TX: 120 mA for 200 seconds/day → 6.7 mAh/day
- RX/listen: 30 mA for 30 minutes/day → 15 mAh/day  
Total ≈ 81.7 mAh/day  
If battery is 2000 mAh → ~24 days

(These numbers are placeholders—your tests will produce real ones.)

---

## 8. Solar Input Scenarios (Practical Assumptions)

Solar output depends heavily on location, shading, panel angle, and weather. For planning:

### 8.1 Solar “rules of thumb” (planning-only)
- Small panels (5–10W) can meaningfully charge small batteries over a day
- Real-world output is often far below the rated wattage due to conditions

### 8.2 What you should document (investor-friendly)
- Panel size used in prototype (W)
- Hours/day of “useful sun” tested
- Net energy added to battery per day
- Whether the device can remain net-positive in Profile A/B

---

## 9. Hand Crank Input Scenarios

Hand cranks are “emergency power,” not primary power for most people.

### 9.1 What to evaluate
- How many minutes of cranking produce:
  - 1 transaction?
  - 10 transactions?
  - 1 sync window?

### 9.2 Investor framing
- “Even in worst-case environments, a user can generate enough power to transact.”

---

## 10. Power-Saving Strategies (Design Requirements)

These are strategies Seed should implement in firmware/software.

### 10.1 Device-level strategies
- Deep sleep by default
- Wake on button press or scheduled interval
- Adaptive screen refresh (avoid full refresh unless needed)

### 10.2 Radio strategies
- Duty-cycled listening windows (e.g., 5 seconds every minute, or scheduled sync slots)
- Adaptive transmit power (use minimum needed)
- Compress payloads and limit retries

### 10.3 Ledger strategies
- Batch writes
- Checkpointing schedule
- Avoid expensive validations unless needed (but never compromise safety)

### 10.4 Low-battery behavior
- Reduce sync frequency
- Reduce radio transmit power
- Disable non-essential features first (AI coaching, extended browsing)
- Always preserve “core transaction capability” as long as possible

---

## 11. Constraints and Environmental Factors

Seed’s power plan must account for:

- Heat (battery + charging)
- Dust/water ingress (enclosure)
- Intermittent charging access
- Long periods offline
- High-traffic days (market day spikes)

---

## 12. What “Success” Looks Like (Outputs You’ll Publish)

When hardware arrives and you run tests, the results that matter:

- Table of measured current by mode (sleep, UI, TX, RX, sync)
- Battery runtime estimates under 3–4 usage profiles
- Solar test summary (panel wattage, hours, net daily gain)
- Hand crank test summary (minutes to X transactions)
- A clear conclusion:
  - “Seed can support daily commerce in low-power conditions.”

---

## 13. Next Actions (When Hardware Arrives)

1. Measure sleep current
2. Measure screen refresh current/time
3. Measure LoRa TX current at multiple power levels
4. Measure RX/listen strategy current
5. Build a “daily profile calculator” spreadsheet
6. Run solar + hand crank tests
7. Publish results into:
   - `specs/system_specs/power_budget.md`
   - `simulations/power_budget/battery_lifetime_estimates.md`
   - `hardware/power_system/power_budget.md`

---

## 14. Open Questions (Track as You Learn)

- What duty-cycle listening pattern gives acceptable sync latency?
- What is the smallest solar panel that keeps the device net-positive in Profile B?
- What battery chemistry is safest and most accessible for target regions?
- How much power overhead does signing/encryption add in practice?
- What’s the best UX for “low battery mode” without confusing users?

---
