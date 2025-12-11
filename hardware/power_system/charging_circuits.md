# Charging Circuits

This document describes the charging subsystem for the Seed device, including supported power inputs, charging IC selection, battery protection strategy, and safety requirements. The charging circuit is a critical element of Seed’s offline-first design because users may rely on solar, hand-crank, or intermittent grid access to power their device in low-infrastructure environments.

---

## 1. Charging System Goals

- Support **multiple energy sources**: solar, hand-crank dynamo, USB when available.
- Provide **safe charging** for LiFePO₄ batteries, which are preferred for heat tolerance and long cycle life.
- Maintain **high efficiency** even under fluctuating or low-power input conditions.
- Prevent battery damage from over-voltage, under-voltage, over-current, and thermal excursions.
- Enable **predictable runtime**, **long lifespan**, and **reliability** in extreme environments.

---

## 2. Supported Power Inputs

### 2.1 Solar Panel Input
- Expected operating range: **3.5V–6.5V** depending on the selected panel.
- Must tolerate **rapid power fluctuation** due to shading or angle changes.
- Uses a **MPPT (Maximum Power Point Tracking)** or pseudo-MPPT algorithm depending on IC.

### 2.2 Hand-Crank Generator Input
- Typical raw output: **5–12V AC/DC** depending on crank speed.
- Must pass through:
  - **Full-bridge rectifier** (if AC)
  - **Input smoothing capacitor**
  - **Over-voltage clamp** (TVS diode)

### 2.3 USB Input (optional)
- 5V regulated.
- Simplifies lab testing and controlled charging environments.
- USB-C PD is **not required** for MVP.

---

## 3. Battery Type and Charging Requirements

### 3.1 Chosen Battery Chemistry
- **Lithium Iron Phosphate (LiFePO₄)**  
  Selected for:
  - Thermal stability
  - Non-flammability compared to Li-ion
  - Long lifespan (2,000–5,000 cycles)
  - Wide environmental suitability

### 3.2 Charging Requirements
- Charge voltage: **3.6V–3.65V**
- Max charge current (MVP target): **200–500 mA**
- Needs **constant-current / constant-voltage (CC/CV)** charging profile.

---

## 4. Charging IC Options

### 4.1 Recommended IC (MVP)
**CN3791 (LiFePO₄ MPPT Solar Charger IC)**  
- Supports solar directly.
- Built-in pseudo-MPPT algorithm.
- Simple BOM & low cost.
- Adjustable charge current via sense resistor.
- Widely used in low-infrastructure solar projects.

### 4.2 Alternative ICs
- **BQ24650 (TI)** — true MPPT solar charger, higher performance.
- **MCP73123** — simpler LiFePO₄ charger when solar variability is low.
- **TP5000** — inexpensive single-cell LiFePO₄ charger with USB/solar flexibility.

---

## 5. Charging Architecture (Block Diagram)

[SOLAR] ––> [Reverse Polarity Protection] ––> [MPPT Charger IC] ––> [LiFePO₄ Battery]
|                                    |
[Hand-Crank Rectifier]                [Battery Temp Sensor]
|                                    |
[Supercap]                         [Protection BMS]

A detailed version will later move into PCB schematic documentation.

---

## 6. Battery Management System (BMS)

Each Seed device must include a **single-cell BMS** with the following protections:

### Protections Required
- **Over-charge:** cutoff at ~3.6–3.7V  
- **Over-discharge:** cutoff at ~2.0–2.2V  
- **Over-current protection:** prevents device damage during faults  
- **Short-circuit protection**  
- **Thermal cutoff** via NTC thermistor feedback  

### Recommended BMS Modules
- DW01 + FS8205A dual MOSFET  
- Seiko S-8261 series  
- Smart BMS optional in future versions (with I²C monitoring)

---

## 7. Thermal Safety and Environmental Suitability

Seed devices may be used in:
- high-heat rural environments
- disaster zones
- direct sunlight

Therefore:
- Charging current is **automatically derated** based on battery temperature.
- Charging is suspended above **60°C** and below **0°C**.
- PCB layout must ensure:
  - Heat dissipation around the IC
  - Adequate copper pour for grounding
  - Separation between charging IC and radio circuitry

---

## 8. Input Protection Stages

### 8.1 Reverse Polarity Protection
- Schottky diode or ideal diode MOSFET prevents damage if inputs are reversed.

### 8.2 Over-Voltage Clamp
- TVS diode protects charger from surges (common with hand-crank inputs).

### 8.3 Filtering
- 10–100 µF capacitor at input to stabilize solar and crank variability.
- 0.1 µF ceramic capacitor near charger IC pins.

---

## 9. Charge Status and UI Integration

Seed devices display charge state on the e-ink screen and optionally via LED indicator.

### Status Signals:
- **Charging**
- **Charged**
- **Low battery**
- **Temperature fault**
- **Input power too low (solar)**

Status comes from:
- Charger IC STAT pins
- Battery voltage readings via ADC
- Internal temperature sensor

---

## 10. Power Path Management

To ensure the device can operate **while charging**:

- Some ICs support direct power-path management.
- If not, a **diode-OR** or **ideal MOSFET switch** prevents brown-outs.
- Supercapacitors can smooth hand-crank power spikes.

---

## 11. Hand-Crank Specific Challenges

Hand-crank input is variable and user-dependent.

To stabilize:
- Rectify AC with Schottky bridge.
- Add bulk capacitor (100 µF to 470 µF).
- Limit voltage spikes with TVS diode.
- Use MPPT charger if available; otherwise derate current.

---

## 12. Charge Algorithm Summary (Simplified)

### CC Phase
- Battery receives constant current until ~3.55V.

### CV Phase
- Voltage is held at ~3.60–3.65V.
- Current tapers to ~0.05C.

### Charge Complete
- Charging stops or trickle-maintains depending on IC.

### Safety Cutoffs
- Temperature cutoff (NTC)
- Over-voltage cutoff
- Timeout cutoff (optional)

---

## 13. Future Extensions

- Smart BMS with SoC estimation
- Wireless energy sharing between Seed devices
- Solar-panel angle optimization via firmware hints
- Fast-charge profile with advanced power path

---

## 14. Summary

Seed’s charging circuitry is designed to be:

- **Robust** against solar variability and manual power generation  
- **Safe** under extreme temperatures  
- **Efficient** to maximize runtime  
- **Modular** for future hardware upgrades  

This subsystem ensures that Seed devices remain operational in areas without reliable electricity, reinforcing the mission: *provide secure financial tools anywhere in the world, under any conditions*.
