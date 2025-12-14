# Battery Lifetime Estimates

This document estimates the expected battery lifetime of the Seed device under different usage scenarios. The goal is to ensure that Seed remains functional for extended periods in environments with limited or unreliable access to electricity, while supporting core financial, security, and mesh networking operations.

---

## 1. Purpose of Battery Lifetime Modeling

Battery lifetime estimation serves several critical purposes:

- Validate that Seed can operate in low-infrastructure environments.
- Inform hardware design choices (battery size, charging methods).
- Guide firmware power management strategies.
- Set realistic user expectations for charging frequency.
- Support investor and partner confidence in feasibility.

This document focuses on first-order estimates suitable for early-stage design and field pilots.

---

## 2. Battery Assumptions

Baseline battery assumptions for the Seed prototype:

- Battery type: Lithium Iron Phosphate (LiFePO4)
- Nominal voltage: 3.2 V
- Capacity (prototype target): 3000 mAh
- Total energy capacity: approximately 9.6 Wh
- Usable capacity (after safety margin): 85% (≈ 8.2 Wh)

LiFePO4 is selected due to:
- High thermal stability
- Long cycle life (2000+ cycles)
- Improved safety compared to Li-ion
- Better performance in high-temperature environments

---

## 3. Power Consumption Components

Estimated average current draw by subsystem:

- Microcontroller (idle, low-power): 5 mA
- Microcontroller (active processing): 40 mA
- LoRa radio (receive idle): 10 mA
- LoRa radio (transmit burst): 120 mA
- E-ink display (refresh event): 30 mA for ~2 seconds
- Secure element + fingerprint sensor (active): 20 mA
- Storage operations (flash write): 15 mA

Most components remain in low-power or sleep states for the majority of time.

---

## 4. Usage Profiles

### Profile A: Low Activity User
- Transactions per day: 3
- Mesh sync events per day: 2
- Screen refreshes per day: 5
- Radio active time: <5 minutes/day

Estimated average current draw:
- ~12 mA average

Estimated battery life:
- ≈ 250 hours
- ≈ 10–12 days without recharge

---

### Profile B: Moderate Activity User
- Transactions per day: 15
- Mesh sync events per day: 10
- Screen refreshes per day: 20
- Radio active time: ~20 minutes/day

Estimated average current draw:
- ~22 mA average

Estimated battery life:
- ≈ 135 hours
- ≈ 5–6 days without recharge

---

### Profile C: High Activity / Vendor Device
- Transactions per day: 60+
- Mesh sync events per day: continuous
- Screen refreshes per day: 50+
- Radio active time: ~1 hour/day

Estimated average current draw:
- ~45 mA average

Estimated battery life:
- ≈ 65 hours
- ≈ 2–3 days without recharge

---

## 5. Impact of Power Optimization

Firmware-level optimizations can significantly extend battery life:

- Aggressive sleep modes during idle periods
- Batch processing of transactions
- Reduced screen refresh frequency
- Adaptive radio duty cycling
- Opportunistic syncing only when peers detected

Estimated gains from optimization:
- 20–40% improvement in battery life across all profiles

---

## 6. Charging Augmentation Scenarios

### Solar Charging
- 5W panel in direct sunlight: ~1–1.5A @ 5V
- 1–2 hours of sun per day can sustain moderate usage
- Enables indefinite operation in sunny regions

### Hand-Crank Charging
- Manual generation: ~5–10 minutes for several hours of usage
- Acts as emergency or backup charging method
- Particularly useful during outages or travel

---

## 7. Battery Degradation Over Time

LiFePO4 degradation assumptions:
- Capacity loss: ~5% per year under normal use
- Device remains usable for 3–5 years without battery replacement
- Firmware compensates by adjusting power budgets dynamically

---

## 8. Safety Margins and Failure Scenarios

Design includes safeguards for:
- Low-voltage shutdown to protect battery
- Thermal throttling during extreme heat
- Brownout detection to prevent ledger corruption

Even under worst-case conditions, Seed prioritizes:
- Ledger integrity
- Secure storage
- Graceful recovery after power loss

---

## 9. Summary

Battery lifetime modeling confirms that Seed can function for multiple days to weeks without recharging, depending on usage patterns. Combined with solar and hand-crank charging, Seed is capable of continuous operation in off-grid environments.

These estimates validate the technical feasibility of Seed as a resilient, low-power financial device suitable for real-world deployment in underserved regions.
