# Battery Specifications

This document defines the battery system requirements for the Seed device, including chemistry choice, capacity planning, discharge behavior, environmental constraints, safety considerations, and compatibility with Seed's hybrid power strategy that includes solar, hand-crank, and USB-based charging.

---

## 1. Battery Chemistry Selection

Seed uses Lithium Iron Phosphate (LiFePO4) cells due to their superior safety and long life cycle performance in harsh environments.

### Benefits of LiFePO4
- High thermal stability and reduced fire risk
- Extremely long cycle life (2000 to 5000+ charge cycles)
- Safe behavior under physical damage or over-temperature conditions
- Performs reliably in high-heat regions common in low-connectivity countries
- Stable voltage profile compatible with low-power electronics
- Reduced degradation compared to typical Lithium-Ion or Lithium-Polymer cells

### Supported Form Factors
- Cylindrical cells (14500 or 18650 LiFePO4)
- Flat pouch cells (preferred for thin device design)
- Configurations allowed: single-cell 3.2V nominal, boosted internally to device voltage

---

## 2. Electrical Characteristics

### Nominal Voltage
- 3.2 V nominal
- 3.6 V maximum charging voltage
- 2.5 V minimum safe discharge voltage

### Recommended Capacity Range
- 1200 mAh to 3000 mAh depending on region, climate, and expected daily usage

### Discharge Rates
- Continuous discharge recommended: 1C or less
- Peak discharge: up to 2C supported for short bursts (e.g., radio transmit spikes)

### Expected Runtime
With typical usage patterns:
- Standby: 0.2 to 1.0 mA
- E-ink redraw: 15 to 30 mA short burst
- LoRa mesh transmission: 80 to 150 mA burst
- Typical daily consumption estimate: 20 to 40 mAh

This results in:
- 1200 mAh battery: approximately 20 to 40 days per charge
- 3000 mAh battery: up to 60 to 80 days per charge

---

## 3. Environmental Requirements

Seed devices operate in regions with limited infrastructure, extreme weather, and variable humidity. Battery behavior must remain dependable in these environments.

### Temperature Tolerance
- Operating range: -20°C to 60°C
- Charging range: 0°C to 45°C
- Storage range: -20°C to 50°C

### Vibration and Shock Durability
- Must withstand handheld device impact and accidental drops
- Reinforced enclosure and shock-absorbing padding required

### Humidity Resistance
- Target operating humidity: 5 percent to 95 percent non-condensing
- Conformal coating or internal compartment sealing recommended

---

## 4. Safety and Protection Circuits

Seed requires multiple layers of hardware protection to ensure safe operation.

### Built-In Battery Protection (PCB)
- Overcharge protection
- Over-discharge protection
- Over-current protection
- Short-circuit protection
- Thermal cutoff

### Device-Level Safety Mechanisms
- Temperature sensor integrated with power manager
- Automatic shutdown during unsafe thermal conditions
- Secure enclosure preventing user tampering with the cell
- Automatic low-voltage lockout preventing deep discharge

---

## 5. Charging Specifications

Seed relies on hybrid charging due to limited electrical infrastructure.

### Supported Charging Sources
- Solar panel 1 W to 3 W
- Hand-crank generator with regulated output
- USB 5V input (for regions with electrical access)
- Energy harvesting modules (future extension)

### Charge Controller Requirements
- MPPT (Maximum Power Point Tracking) recommended for solar input
- Over-charge regulation to 3.6 V maximum
- Charge current limited to 0.5C or below for longevity
- Reverse polarity protection

---

## 6. Capacity Planning for Regional Use Cases

### High Connectivity Urban Areas
- Moderate solar usage
- 1200 to 2000 mAh sufficient

### Rural and Off-Grid Communities
- High reliance on solar and hand-crank
- 2000 to 3000 mAh recommended

### Disaster Zones and Refugee Camps
- Unpredictable charging opportunities
- 2500 to 3000 mAh recommended

---

## 7. Aging and Degradation Model

### Life Expectancy
- Typical LiFePO4 cycle life: 2000+ cycles
- Seed device target lifespan: 5 to 8 years

### Expected Capacity Loss
- Year 1: 3 percent to 5 percent
- Year 3: 10 percent to 15 percent
- Year 5: 20 percent to 25 percent

### Design Implications
- Battery should be replaceable by certified technicians
- Battery health tracked in firmware for optimized performance

---

## 8. Certification Requirements

To support global deployment, batteries must comply with:

### Transportation and Safety Standards
- UN38.3 certification for lithium battery transport
- IEC 62133 for portable device battery safety
- RoHS and REACH compliance

### Country-Specific Requirements
- African, Asian, and South American import battery rules
- Local recycling and disposal regulations

---

## 9. Summary

The Seed battery system is built for reliability, durability, and safety across the world’s most challenging environments. By using LiFePO4 chemistry, protective circuitry, a modular charging approach, and robust thermal safeguards, Seed ensures stable operation even without consistent access to electricity.

Battery performance is essential to Seed’s mission of empowering financial access in low-infrastructure regions, and these specifications define a durable foundation for long-term field use.
