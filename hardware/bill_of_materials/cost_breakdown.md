# Bill of Materials — Cost Breakdown

This document provides a detailed cost breakdown for the Seed prototype and projected mass-production costs. Values are estimates based on 2024–2025 component market pricing, global supply averages, and realistic volume-based discounts. Costs will vary by supplier, region, and minimum order quantity (MOQ). This breakdown is designed to support investor discussions, early manufacturing planning, and feasibility analysis.

---

## 1. Prototype-Level Cost Breakdown (Low Volume: 1–10 Units)

Prototype costs are higher due to non-bulk pricing, over-engineered flexibility, and supplier premiums. These estimates reflect the Seed development boards, sensors, secure elements, and batteries required to build functional early prototypes.

### Core Electronics
| Component | Estimated Unit Cost | Notes |
|----------|----------------------|-------|
| ESP32 or nRF52 MCU + LoRa (Dev Board) | $15–$28 | LILYGO, Heltec, RAK, or equivalent. |
| LoRa Radio Module (SX1262 or SX1276) | $5–$12 | Depending on power output and module packaging. |
| Secure Element (ATECC608 or similar) | $1.50–$3.00 | Hardware-based key storage. |
| Power Management ICs | $2–$4 | Buck/boost converters, MCP73831, charging ICs. |
| E-Ink Display (2.13" or similar) | $14–$23 | Depends on resolution and refresh drivers. |

### Sensors & Security Components
| Component | Estimated Unit Cost | Notes |
|----------|----------------------|-------|
| Capacitive Fingerprint Sensor | $8–$12 | Low-power embedded module. |
| Tamper Detection Switch / Mesh | $0.40–$1.00 | Basic mechanical or capacitive. |
| Battery Temperature Sensor | $0.20–$0.50 | NTC thermistor or digital variant. |

### Power System
| Component | Estimated Unit Cost | Notes |
|----------|----------------------|-------|
| LiFePO4 Battery (1000–1500 mAh) | $6–$10 | Safer high-temp performance. |
| Solar Panel (1–2 W mini panel) | $5–$8 | USB-compatible or exposed leads. |
| Hand-Crank Dynamo (Optional) | $8–$15 | For ultra-offline deployment. |
| Protection Circuit Modules | $0.50–$1.20 | Overcharge/discharge protection. |

### Enclosure & Mechanical
| Component | Estimated Unit Cost | Notes |
|----------|----------------------|-------|
| 3D Printed Case | $4–$8 | PLA/ABS rapid prototype. |
| Screws, spacers, fasteners | $0.50 | Basic bill for prototype assembly. |
| Silicone keypad or buttons | $1–$3 | Optional for tactile input. |

### Total Prototype Estimated Cost
**Per device: $75–$135**

This depends primarily on:
- which MCU/radio dev board is chosen,
- whether solar + crank power are included,
- enclosure quality,
- battery size.

Two devices (for mesh testing): **$150–$270**

---

## 2. Projected Mass-Production Costs (10,000+ Units)

At scale, components are significantly cheaper due to:
- bulk pricing,
- simplified integrated PCB designs,
- removal of dev-board overhead,
- optimized enclosure manufacturing (injection molding),
- integrated chip selections.

### Core Electronics (Mass Production)
| Component | Estimated Unit Cost | Notes |
|----------|---------------------|-------|
| Custom PCB (4–6 layer) | $1.20–$2.00 | High-volume SMT assembly. |
| MCU (ESP32-C3, nRF52, RISC-V variant) | $1.10–$2.40 | Depending on chosen chipset. |
| LoRa Radio IC (SX1262, SX1268) | $1.50–$3.00 | Significantly cheaper in volume. |
| Secure Element | $0.80–$1.20 | ATECC608A bulk pricing. |
| Display Driver + E-Ink Panel | $7–$12 | High volume discount. |

### Sensors & Security
| Component | Estimated Unit Cost | Notes |
|----------|---------------------|-------|
| Fingerprint Sensor | $4–$6 | Bulk OEM module. |
| Tamper Detection Mesh | $0.10–$0.40 | Very cheap at volume. |
| Temp Sensor | $0.05–$0.15 | Built into battery management module. |

### Power System
| Component | Estimated Unit Cost | Notes |
|----------|---------------------|-------|
| LiFePO4 Battery | $3–$5 | Custom OEM pack. |
| Solar Panel | $2–$4 | PET-laminated micro-panel. |
| Charging/PMIC ICs | $0.30–$0.80 | Highly integrated. |

### Enclosure & Assembly
| Component | Estimated Unit Cost | Notes |
|----------|---------------------|-------|
| Injection-Molded Plastic Shell | $0.70–$1.50 | After mold amortization. |
| Internal Frame + Buttons | $0.20–$0.50 | Stamped or cast parts. |
| Final Assembly Labor | $0.40–$0.80 | Depends on region. |

---

## 3. Anticipated Final Manufacturing Cost per Device
**Estimated total per device (mass production): $25–$40**

This price target is extremely competitive, and Seed becomes viable in:
- NGOs,
- microfinance organizations,
- distributed economic development programs,
- disaster response deployments,
- low-income markets.

---

## 4. Cost Drivers and Optimization Opportunities

### Major Cost Drivers
- E-Ink display
- Fingerprint sensor
- LoRa radio module
- Battery + power subsystem

### Biggest Areas for Future Reduction
- Move from dev-board architecture → fully integrated PCB.
- Lower-cost radio (SX1262 variants).
- Simplify the fingerprint module or replace with PIN-based unlock for certain markets.
- Highly optimized enclosure manufacturing.

### Long-Term Optimizations
- On-device ML acceleration replaced with much smaller inference models.
- Transition to a single PMIC that handles solar, crank, and battery input.
- Localization for specific regions (different LoRa bands).

---

## 5. Investor Summary

- **Prototype cost per device:** $75–$135  
- **Mass-production cost per device:** $25–$40  
- **Primary cost drivers:** display, radio, battery, biometric sensor  
- **Path to $20 unit cost:** integrated PCB + alternative ID verification + simplified enclosure  
- **Scaling advantage:** Seed avoids expensive components like LCDs, touchscreens, or cellular modems  
- **High-margin potential price:** $50–$100 depending on partner segment  
- **Target institutional buyers:** NGOs, development banks, governments, disaster response orgs, microfinance lenders  
