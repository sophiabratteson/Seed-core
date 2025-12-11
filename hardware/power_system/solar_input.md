# Solar Input System

This document describes the design, requirements, and performance expectations of the Seed device’s solar input subsystem. The goal is to ensure reliable off-grid operation in regions with intermittent electricity, enabling users to power their device using only sunlight and occasional hand-crank backup.

---

## 1. Objectives of the Solar Input System

- Provide **renewable, self-sufficient power** for users with no access to stable electricity.
- Enable **daily charging cycles** sufficient for Seed’s ultra-low-power architecture.
- Integrate seamlessly with Seed’s **LiFePO₄ battery**, **power manager**, and **charging circuitry**.
- Maintain safety, durability, and performance in **high-heat, high-dust, and high-humidity** environments.
- Minimize component cost to support large-scale deployment in low-income regions.

---

## 2. System Overview

The solar input subsystem consists of:

- A **high-efficiency monocrystalline solar panel** (1.5 W – 3 W target)
- Integrated **MPPT (Maximum Power Point Tracking) or pseudo-MPPT charge controller**
- Input protection components (reverse-current protection, over-voltage protection)
- Direct interface to the **battery charging circuits**
- Power harvesting telemetry (optional for battery % reporting)

The system must reliably charge the battery under **varied sunlight levels**, enabling full offline operation.

---

## 3. Solar Panel Specifications

### 3.1 Panel Type
- **Monocrystalline silicon**
  - Highest efficiency per area
  - Best performance in low-light conditions
  - Long lifespan and temperature stability

### 3.2 Electrical Requirements
| Parameter | Target Specification |
|----------|-----------------------|
| Rated Power | 1.5–3.0 W |
| Open-Circuit Voltage (Voc) | 6.0–7.0 V |
| Max Power Voltage (Vmp) | 5.0–5.5 V |
| Max Power Current (Imp) | 250–550 mA |
| Efficiency | ≥ 18% (preferably 20–22%) |

### 3.3 Environmental Requirements
- Operating Temperature: **–10°C to 70°C**
- Humidity: **≤ 95%**, non-condensing
- Coating: **PET or ETFE** (ETFE preferred for durability)
- UV degradation tolerance: **High**

---

## 4. Solar Charging Controller

The Seed hardware uses a **dedicated charge controller** to regulate solar power input and safely charge the LiFePO₄ battery.

### 4.1 Key Functions
- Regulate PV voltage to match LiFePO₄ charging profile
- Prevent overcharging the battery
- Prevent backflow from battery to panel at night
- Optimize charging efficiency under changing sunlight

### 4.2 Recommended Architectures
Two valid architectures are considered:

#### **Option A — MPPT Controller (Preferred)**
- Tracks optimal operating point dynamically  
- Provides **20–40% efficiency improvement** in low or variable sunlight  
- More expensive but far better performance  

Suitable ICs include:
- CN3791 (LiFePO₄ MPPT)
- LTC4126 or LTC4015 (advanced MPPT charging controllers)

#### **Option B — Pseudo-MPPT Controller (Cost-optimized)**
- Uses a fixed set-point voltage (e.g., 80% of Voc)
- Lower cost, simpler design
- Slightly lower efficiency in cloud cover or heat

---

## 5. Solar Power Budget

Seed’s power system must operate in environments with:

- **4–6 peak-sun-hours/day** in equatorial and subtropical regions  
- **2–4 peak-sun-hours/day** in cloudier regions  

### 5.1 Daily Energy Harvest Estimate
For a 2 W panel:

- Peak sun hours: 4  
- Harvested energy ≈ **8 Wh/day**  
- After charge loss (~80% efficiency): **6.4 Wh/day usable**

### 5.2 Device Consumption
Seed’s estimated consumption:

| Mode | Power |
|------|--------|
| Standby | 0.05–0.2 mW |
| Active interaction | 20–80 mW |
| Radio burst (LoRa mesh) | 200–600 mW for <1 second |

Daily average consumption is expected to be **< 1 Wh**.

**Result:**  
The solar panel provides **6× more power than required**, ensuring reliable operation even with several cloudy days.

---

## 6. Electrical Integration

### 6.1 Block Diagram
