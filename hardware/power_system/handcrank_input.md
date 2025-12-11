# Hand-Crank Input System

This document describes the design, performance requirements, engineering constraints, and operational logic for Seed’s hand-crank power subsystem. The hand-crank generator is a critical backup energy source allowing Seed devices to function in environments without electricity, solar availability, or stable infrastructure. This subsystem ensures true off-grid resilience and guarantees that users can always access their financial tools, even during disasters or at night.

---

## 1. Purpose of the Hand-Crank System

The hand-crank system provides:

- An emergency, always-available method of powering the device.
- Energy harvesting in low-sunlight or indoor environments.
- A guaranteed minimum runtime for ledger access, payments, group-savings rotations, and sync operations.
- A psychologically reassuring "self-sufficiency" feature for users with unstable electricity access.

The system must be robust, low-maintenance, and intuitive for users with varying levels of technical literacy.

---

## 2. System Components

### 2.1 Micro-Generator
- A compact AC generator producing ~3–10W depending on crank speed.
- Output: typically 3–30V AC, converted to DC via a rectifier.
- Designed for durability (≥10,000 crank cycles).

### 2.2 Rectifier + Smoothing Stage
- Full-bridge rectifier converts AC output to DC.
- Capacitor smoothing reduces voltage ripple before entering the charge controller.

### 2.3 Charge Controller (DC-DC Power Conditioning)
- Steps the variable crank voltage into a stable 5V or 3.3V line.
- Includes:
  - Over-voltage protection  
  - Over-current protection  
  - Reverse-current protection  
  - Battery charging logic (LiPo/LiFePO4)  
- Typical controller: buck-boost converter with MPPT-like behavior for hand generators.

### 2.4 Energy Storage (Battery Integration)
- Charges the primary LiPo/LiFePO4 battery.
- Able to charge from extremely inconsistent human-generated power.

### 2.5 Power Management MCU Signals
- The firmware receives:
  - Crank detected  
  - Input voltage level  
  - Estimated human-generated watts  
  - Battery charge level  
- Seed uses this information to show UI feedback on the e-ink display (charging progress).

---

## 3. User Experience Requirements

- **1 minute of cranking** should yield at least **3–5 minutes of operational time**, depending on load.
- Cranking should feel:
  - Smooth  
  - Low resistance  
  - Noise-reduced  
- Display messages:
  - “Charging…”  
  - Battery percentage  
  - Estimated runtime gained  

- Must support cold and hot climate operation (-10°C to 45°C).

---

## 4. Electrical Requirements

- Input voltage range: **3V – 25V** (unregulated crank output).
- DC-DC conversion efficiency target: **≥85%**.
- Maximum safe charging current: **≤1C** of the battery.
- Ripple tolerance: device power rails must maintain ≤100mV ripple after smoothing.

- Generator current output:
  - Slow crank: 100–200mA  
  - Normal crank: 300–800mA  
  - Fast crank (short bursts): up to 1A (should be clamped by charge controller)

---

## 5. Mechanical Requirements

- Foldable or retractable crank arm.
- Non-slip grip and ergonomic rotation angle.
- Must survive:
  - Accidental drops  
  - Moisture and dust exposure (IP5X recommended)  
- Expected lifetime:
  - ≥10,000 rotations  
  - ≥3 years under moderate use  

---

## 6. Safety Features

- Over-voltage clamp to protect internal electronics if a user cranks excessively fast.
- Mechanical slip/clutch system to prevent gearbox damage.
- Electrical isolation to prevent reverse current into the generator.
- Thermal monitoring in case of prolonged fast cranking.

---

## 7. Firmware Integration

### 7.1 Power Manager Responsibilities
- Detects crank activity.
- Monitors incoming power and battery charge rate.
- Enables/disables charging subsystem.
- Displays energy contribution to user.

### 7.2 E-Ink UI Feedback
- Progress bar indicating charge gained.
- Crank speed indicator (slow/optimal/fast).
- Warnings:
  - “Crank Too Fast”  
  - “Charging Paused: Overheat Protection”  

### 7.3 Logging (Optional for MVP)
- Records hand-crank sessions:
  - Duration  
  - Energy generated  
  - Battery level before/after  

---

## 8. Charging Performance Targets

### MVP Minimum Targets
- 60 seconds of cranking = **1–2 minutes** of device operation.
- Allow full battery recharge via ~30–40 minutes of continuous cranking.

### Future Targets (Gen 2 Seed)
- Integrate ultra-low-power modes so that 60 seconds of cranking = **10+ minutes** of ledger-only usage.

---

## 9. Failure Modes and Recovery

### Possible Failures
- Generator produces voltage outside safe range.
- Crank gear becomes jammed.
- Charge controller overheats.
- User cranks too fast causing voltage spikes.

### Firmware Response
- Disable charging pathway.
- Notify user via e-ink.
- Log the fault for diagnostics.

### Hardware Response
- Voltage clamp engages automatically.
- Overcurrent shutoff protects lithium battery.
- Gearbox clutch prevents mechanical strain.

---

## 10. Rationale for Including Hand-Crank Power

- Many low-income or rural regions experience **intermittent power**, sometimes only a few hours/day.
- Disaster zones may have **zero infrastructure**.
- Solar can fail:
  - Cloudy weather  
  - Indoor use  
  - Nighttime  
- Hand-crank ensures Seed remains:
  - Self-reliable  
  - User-controlled  
  - Disaster-resilient  
  - Fully functional under the harshest conditions  

This aligns directly with Seed’s mission: **a financial system that works anywhere, anytime, for anyone.**

---

## 11. Future Improvements

- Supercapacitors for instant-charge short bursts.
- Magnetic-induction crank with higher efficiency.
- Detachable crank option for compact models.
- Bi-directional energy sharing with other Seed devices.

---

## 12. Summary

The hand-crank subsystem is one of the most mission-critical hardware components in Seed. It ensures offline financial access even in the absence of electricity, sunlight, or infrastructure. The system must be durable, safe, efficient, and integrated tightly with Seed’s power management firmware and user interface. A reliable hand-crank generator dramatically increases Seed’s appeal, usability, and survivability in real-world low-resource environments.
