# Hardware Sourcing Plan

This document outlines the sourcing strategy for all hardware components required for Seed’s MVP and early pilot devices. The objective is to ensure reliable procurement, cost-efficient supplier relationships, risk-managed alternatives, and scalable pathways toward mass manufacturing.

---

## 1. Sourcing Objectives

- Ensure consistent availability of all components needed for prototype and small-batch manufacturing.
- Maintain cost efficiency while guaranteeing device safety and regulatory compliance.
- Reduce supply-chain risk through multi-vendor redundancy.
- Establish a clear path from prototype sourcing (retail, development boards) to pre-production (wholesale, custom modules).

---

## 2. Component Categories

Seed hardware requires sourcing from several categories:

- **Compute Module / MCU**
- **LoRa Radio Module & Antenna**
- **E-Ink Display**
- **Power System (Battery, Solar, Hand-Crank, Charging Board)**
- **Sensors & Security Modules**
- **Mechanical Enclosure & Accessories**
- **Miscellaneous Electronics (switches, connectors, wiring, PCB materials)**

Each category lists recommended suppliers, risks, and alternative options.

---

## 3. Primary Suppliers

### 3.1 Development-Stage Suppliers
Used for prototype and early validation:

- **DigiKey**
- **Mouser**
- **SparkFun**
- **Adafruit**
- **RAK Wireless**
- **LILYGO**
- **Heltec Automation**

These suppliers are preferred for:
- Fast shipping
- Reliable stock
- Clear documentation
- Community support

### 3.2 Pre-Production Suppliers
Used for pilot batches (100–1,000 units):

- **JLCPCB / JLCPCB Assembly**
- **Seeed Studio Fusion**
- **PCBWay**
- **GigaDevice, Espressif wholesale channels**
- **AliExpress verified manufacturers (quality-checked)**

### 3.3 Mass-Production Suppliers (Future)
For scaling beyond 5,000+ devices:

- **Foxconn / Flex manufacturing partners**
- **Preferred ODM/EMS factories**
- **Custom silicon or module suppliers**

---

## 4. Component-Level Sourcing Plan

### 4.1 Compute Module (MCU)
**Recommended:** ESP32 or NRF52 series  
**Primary Suppliers:** Adafruit, Mouser, LILYGO  
**Alternatives:** Espressif Systems wholesale, GigaDevice equivalents  
**Notes:** Choose a long-lifecycle MCU with stable supply.

---

### 4.2 LoRa Radio Module (SX1262 / SX1276)
**Recommended:** Semtech SX1262 or SX1276 modules  
**Primary Suppliers:** RAK Wireless, Heltec, DigiKey  
**Alternatives:** HopeRF RFM95/96, Ai-Thinker RA-01  
**Notes:** Ensure correct band (e.g., 915 MHz for US).

---

### 4.3 E-Ink Display
**Recommended:** 2.13" or 2.9" low-power E-Ink  
**Primary Suppliers:** Waveshare, Heltec  
**Alternatives:** GoodDisplay  
**Notes:** Prioritize tri-color or monochrome for power efficiency.

---

### 4.4 Battery & Power System
**Battery Type:** LiFePO4 preferred; Li-Ion acceptable for MVP  
**Suppliers:** Adafruit, SparkFun, EEMB  
**Charging Board:** TP4056-type or dedicated LiFePO4 charger  
**Solar Panel:** Voltaic Systems 5–10W modules  
**Hand-Crank Generator:** Off-grid generator modules from Adafruit / Amazon industrial suppliers  
**Notes:** Components must support thermal safety.

---

### 4.5 Secure Element & Sensors
**Fingerprint Sensor:** Goodix or commonly available capacitive sensors  
**Secure Element:** Microchip ATECC608/608B  
**Suppliers:** Microchip Direct, DigiKey  

---

### 4.6 PCB, Connectors, Switches
**Suppliers:** JLCPCB, PCBWay, Seeed Studio  
**Notes:** Ensure millimeter-level consistency for enclosure compatibility.

---

### 4.7 Enclosure Materials
**Options:**
- Injection-molded ABS (future scale)
- 3D-printed PLA/ABS (prototype)
- Rubberized shock-resistant exterior

**Suppliers:**  
- ProtoLabs (rapid prototyping)  
- Xometry  
- Local additive manufacturing labs  

---

## 5. Redundancy and Risk Mitigation

- Every critical component (MCU, LoRa radio, battery chemistry) must have *at least two* validated alternative suppliers.
- Maintain a stock buffer of 10–20% during prototype phase.
- Pre-approve drop-in replacements for any component with a history of supply fluctuations.
- Use modular PCB design so components can be swapped without redoing the entire board.

---

## 6. Procurement Strategy by Phase

### Phase 1 — MVP Prototype (1–20 devices)
- Purchase from SparkFun, Adafruit, DigiKey.
- Use evaluation boards (Heltec, LILYGO).
- Hand-assemble or use JLCPCB for small PCBs.

### Phase 2 — Pilot Batch (50–300 devices)
- Move to wholesale ordering (Mouser, RAK Wireless).
- Create revision-1 Seed PCB.
- Begin sourcing batteries and enclosures in bulk.

### Phase 3 — Pre-Production (300–5,000 devices)
- Source directly from manufacturers to reduce per-unit cost.
- Lock long-term component contracts.
- Begin environmental and durability testing.

### Phase 4 — Scaling to Mass Manufacturing
- Establish ODM/EMS factory partners.
- Replace off-the-shelf modules with custom PCBs.
- Perform full supply-chain risk audits.
- Move toward custom silicon for security + radio.

---

## 7. Cost Targets

**Prototype Unit Cost:** $45–$65  
**Pilot Unit Cost:** $28–$40  
**Mass Production Target:** $10–$18 per device  

Cost optimization focuses on:
- Replacing dev boards with integrated PCBs  
- Reducing assembly complexity  
- Securing long-term supplier contracts  

---

## 8. Quality Assurance and Supplier Vetting

- Each supplier must have clear datasheets and RoHS-compliance.
- Prefer suppliers with:
  - Verified shipping history  
  - Long-term stock availability  
  - Stable fabrication partners  
- Maintain supplier scorecards (lead time, pricing, quality failures).

---

## 9. Summary

Seed’s sourcing plan ensures:
- Reliable, low-cost, safe acquisition of all hardware;
- Multiple sourcing pathways for global resilience;
- A smooth path from prototyping → pilot → mass production;
- Compliance with radio, power, and safety regulations.

This plan supports Seed’s mission to deliver a durable, scalable, offline-first financial device for underserved global communities.
