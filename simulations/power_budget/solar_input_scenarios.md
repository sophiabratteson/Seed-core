# Solar Input Scenarios

This document models how Seed devices operate under varying solar energy conditions. Because Seed is designed for low-connectivity and off-grid environments, solar input is a primary power source alongside hand-crank charging and battery storage. These simulations ensure Seed remains functional, predictable, and resilient across real-world lighting conditions.

---

## 1. Purpose of Solar Input Simulation

The solar input simulation serves to:

- Validate that Seed devices can remain operational without grid power.
- Estimate battery recharge rates under different sunlight conditions.
- Determine safe operating modes during low or inconsistent solar availability.
- Support hardware design decisions (panel size, charger efficiency).
- Inform investor and deployment partners about reliability in field conditions.

---

## 2. Solar Hardware Assumptions

These simulations assume the following baseline hardware:

- Solar panel: 3–5W monocrystalline panel
- Nominal voltage: 5–6V
- Charging IC efficiency: 85–92%
- Battery type: LiFePO4 or Li-ion (2,000–3,000 mAh equivalent)
- Orientation: user-adjustable, not sun-tracked
- Exposure: intermittent due to movement or placement

These values represent realistic constraints in rural or mobile deployments.

---

## 3. Environmental Solar Scenarios

### Scenario A: Full Sun (Optimal Conditions)

**Description**
- Clear sky
- Panel oriented correctly
- 5–8 hours of effective sunlight per day

**Estimated Input**
- Power: 3–5W sustained
- Energy/day: 15–30 Wh

**Outcome**
- Battery fully recharged daily
- Device operates in full-feature mode
- Mesh sync frequency unrestricted
- E-ink updates, fingerprint auth, and AI prompts fully enabled

**Conclusion**
This scenario supports continuous daily operation with surplus energy for buffering.

---

### Scenario B: Partial Sun (Common Rural Conditions)

**Description**
- Cloud cover or indirect sun
- Panel orientation inconsistent
- 3–5 hours of usable sunlight

**Estimated Input**
- Power: 1.5–3W average
- Energy/day: 6–12 Wh

**Outcome**
- Battery partially replenished
- Device enters adaptive power mode
- Mesh sync reduced to periodic bursts
- AI features throttled
- Core financial functions unaffected

**Conclusion**
This is the most common expected operating scenario and fully supports Seed’s mission.

---

### Scenario C: Low Sun (Overcast / Seasonal)

**Description**
- Dense cloud cover
- Forest canopy or dense urban shading
- <3 hours effective sunlight

**Estimated Input**
- Power: <1W
- Energy/day: 2–4 Wh

**Outcome**
- Battery drain slowed but not reversed
- Device prioritizes:
  - Ledger integrity
  - Transaction signing
  - Emergency access
- Non-essential background processes paused

**Conclusion**
Seed remains functional for days to weeks depending on battery size and usage.

---

### Scenario D: No Solar (Night / Indoor / Disaster)

**Description**
- Zero solar input
- Device stored or used indoors
- Disaster or displacement scenario

**Estimated Input**
- Power: 0W

**Outcome**
- Device runs exclusively on battery
- Enters ultra-low-power survival mode
- Screen updates minimized
- Mesh only transmits when triggered
- Manual hand-crank charging recommended

**Conclusion**
Seed is designed to survive extended periods without solar input.

---

## 4. Daily Energy Balance Model

Typical daily consumption (adaptive mode):

- Idle + sleep cycles: ~0.5 Wh
- Ledger processing: ~0.3 Wh
- Radio transmission (burst): ~0.5–1.0 Wh
- E-ink updates: ~0.1 Wh
- Security operations: ~0.1 Wh

**Total Daily Usage:** ~1.5–2.5 Wh

Even low solar input scenarios can sustain basic operation.

---

## 5. Power Management Adaptation Logic

Seed dynamically adjusts behavior based on solar input:

- High input:
  - Increased sync frequency
  - Optional AI prompts
  - User training features enabled
- Medium input:
  - Normal operation
  - Scheduled sync windows
- Low input:
  - Transaction-only mode
  - Reduced radio activity
- Critical battery:
  - Read-only mode
  - Emergency access preserved

This logic ensures graceful degradation rather than failure.

---

## 6. Long-Term Battery Health Impact

Solar charging profiles are designed to:

- Avoid overcharging
- Reduce thermal stress
- Support 2–5 year battery lifespan
- Minimize deep discharge cycles

Solar input smooths energy demand, extending battery life versus manual charging alone.

---

## 7. Risk Factors and Mitigations

**Risks**
- User misplacement of panel
- Seasonal sunlight variation
- Panel degradation over time

**Mitigations**
- User guidance via device prompts
- Overprovisioned battery capacity
- Multi-source charging (solar + hand crank)
- Conservative power budgeting

---

## 8. Investor Relevance

These simulations demonstrate that:

- Seed does not require reliable infrastructure to function.
- Power independence is a core design advantage.
- Solar charging enables scalability in underserved regions.
- Operational costs remain low post-deployment.

This positions Seed as a financially and operationally sustainable platform.

---

## 9. Summary

Solar input scenarios confirm that Seed devices remain functional across a wide range of environmental conditions. By combining modest solar harvesting with intelligent power management, Seed delivers consistent financial access without reliance on grid electricity, aligning directly with its mission to serve the most connectivity-constrained populations.
