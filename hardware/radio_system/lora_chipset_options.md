# LoRa Chipset Options

This document summarizes candidate LoRa / sub-GHz radio chipsets for the Seed device, compares them against Seed’s requirements, and recommends a baseline choice for prototypes and early hardware revisions.

---

## 1. Seed Radio Requirements

Before choosing specific chipsets, Seed’s constraints and goals for the radio system:

- Operates fully offline in a device-to-device mesh
- Long-range communication in rural and peri-urban areas (hundreds of meters to several kilometers depending on terrain)
- Very low power consumption (battery + solar + hand-crank)
- Small message payloads (transactions, trust updates, group savings messages)
- License-free ISM bands (regional variants like 868 MHz, 915 MHz, etc.)
- Mature, well-documented, and widely supported ecosystem
- Availability of modules and dev boards for rapid prototyping
- Ability to scale to custom PCBs later without changing the core RF technology

These requirements shape which LoRa chipsets are realistic for Seed.

---

## 2. Selection Criteria

When comparing LoRa chipsets for Seed, we care about:

- Power consumption  
  - Sleep current  
  - TX/RX current at typical data rates and spreading factors

- RF performance  
  - Maximum output power  
  - Sensitivity  
  - Supported bands (e.g., 868 / 915 MHz)

- Integration level  
  - Standalone transceiver vs. MCU + radio in a single chip (SoC)  
  - Ease of connecting to Seed’s main MCU

- Ecosystem and tooling  
  - Availability of breakout boards and dev kits  
  - Open-source libraries and example code  
  - Community support and documentation

- Supply chain and longevity  
  - Multiple vendors shipping modules  
  - Roadmap and long-term availability

- Cost  
  - Per-unit module cost for small-batch and mass production  
  - Total system cost including matching components and antennas

---

## 3. Major LoRa Chipset Families Considered

This section lists common chipset families Seed could use, with pros, cons, and expected use cases.

### 3.1 Semtech SX127x Family (Classic LoRa)

Examples: SX1276, SX1278 (often inside RFM95/RFM96 modules)

- Pros  
  - Very widely deployed and battle-tested  
  - Lots of modules, boards, and example code available  
  - Good range and sensitivity for Seed’s small packets  
  - Supported by many hobbyist and professional platforms

- Cons  
  - Older generation compared to SX126x  
  - Typically higher power consumption than newer chips  
  - Transceiver only (needs a separate MCU)

- Fit for Seed  
  - Excellent for early experiments and educational prototypes  
  - Viable for v1 hardware if power budget allows  
  - Easy to source in many regions as modules (RFM95, Heltec, LILYGO boards, etc.)

### 3.2 Semtech SX126x Family (Newer LoRa)

Examples: SX1261, SX1262, SX1268

- Pros  
  - Lower power consumption than SX127x generation  
  - Good sensitivity and link budget  
  - Flexible configuration for different regions and bands  
  - Newer reference designs and power-optimized modes

- Cons  
  - Slightly more complex configuration than older chips  
  - Fewer “beginner” examples than SX127x, but still very workable  
  - Still requires separate MCU

- Fit for Seed  
  - Strong candidate for production hardware where power matters  
  - Good balance of range, power, and ecosystem maturity  
  - Works well for dense mesh networks sending small packets

### 3.3 STM32WL (MCU + LoRa in One Chip)

Examples: STM32WL55, STM32WLE5

- Pros  
  - Single chip with ARM MCU + LoRa radio integrated  
  - Can reduce board space and BOM complexity  
  - Supported by major vendors and dev tools (ST ecosystem)  
  - Good for professional, compact designs

- Cons  
  - Higher firmware complexity (RTOS, HAL, RF stack on same chip)  
  - Dev process more “embedded-pro-level” than hobby boards  
  - Fewer simple examples compared to ESP32 + LoRa combos

- Fit for Seed  
  - Strong candidate for later hardware revisions (v2/v3)  
  - Good when moving from dev boards to custom Seed PCBs  
  - Probably not the easiest starting point for a solo founder learning hardware

### 3.4 Module-Level Options (RFM, RA-01, LILYGO, Heltec Boards)

These are not raw chips, but small modules or dev boards that integrate a Semtech chip plus supporting circuitry.

Common examples:

- HopeRF RFM95 / RFM96 modules (SX127x-based)
- Ai-Thinker RA-01, RA-02 modules
- LILYGO LoRa32, T3S3, etc. (ESP32 + LoRa combo)
- Heltec LoRa boards with OLED or E-Ink displays

- Pros  
  - Extremely fast for prototyping  
  - Come with antenna connectors, crystals, and power regulation  
  - Example firmware exists (Meshtastic, point-to-point demos, etc.)  
  - No need to design RF front-end from scratch for early prototypes

- Cons  
  - Not all modules are ideal for ultra-low-power final devices  
  - Board form factors may not match Seed’s final industrial design  
  - Some boards include extra features (Wi-Fi, OLED) that increase idle power

- Fit for Seed  
  - Ideal for pre-hardware and early v0/v1 prototypes  
  - Great for field-testing mesh behavior before custom PCB design  
  - Can inform which underlying chipset to standardize on

---

## 4. Regulatory Band Considerations

Seed needs to operate in unlicensed ISM bands, which vary by region:

- 868 MHz band in much of Europe and some other regions
- 915 MHz band in North America and parts of Latin America
- 433 MHz band in some countries (longer wavelength, larger antennas)

Implications:

- Seed should have region-specific SKUs or configurable band options
- For prototypes, choosing a single band (for example, 915 MHz) keeps things simple
- Final manufacturing will need:
  - Band-specific antenna tuning
  - Compliance testing against local radio regulations

---

## 5. Recommended Baseline for Seed

To balance learning, prototyping speed, power, and future scalability, Seed can use a staged approach.

Stage 1: Learning and early mesh experiments

- Underlying chipset  
  - SX127x or SX126x via module (for example: RFM95, RA-01, Heltec / LILYGO boards)

- Why  
  - Very easy to get running  
  - Rich ecosystem and community examples  
  - Lets you focus on ledger logic, sync behavior, and UX first

Stage 2: Refined low-power prototype

- Underlying chipset  
  - SX1262 (or similar SX126x) as the main production-oriented LoRa transceiver

- Why  
  - Better power consumption than older chips  
  - Enough support to be practical  
  - Good long-term candidate for Seed device v1

Stage 3: Custom PCB integration

- Underlying options  
  - Continue with SX1262 + external MCU  
  - Or migrate to STM32WL for a single-chip solution

- Why  
  - Reduces board space and BOM  
  - Positions Seed for more robust manufacturing and scaling

---

## 6. Comparison Summary

High-level scoring for Seed’s needs (subjective, for design guidance):

- SX127x  
  - Ecosystem: high  
  - Power efficiency: medium  
  - Ease of prototyping: high  
  - Long-term choice: acceptable, but not optimal

- SX126x  
  - Ecosystem: high  
  - Power efficiency: high  
  - Ease of prototyping: medium to high (with modules)  
  - Long-term choice: strong candidate

- STM32WL  
  - Ecosystem: medium  
  - Power efficiency: high  
  - Ease of prototyping: medium (more embedded complexity)  
  - Long-term choice: strong for integrated, high-volume devices

---

## 7. Next Steps

To move from this options document into concrete engineering work:

- Choose a primary prototype platform  
  - Example: ESP32 + SX127x or SX126x module (LILYGO / Heltec board)

- Run basic tests  
  - Range tests in real environments  
  - Battery life estimates under realistic duty cycles  
  - Packet reliability and throughput for Seed’s message sizes

- Document measured results  
  - Record RSSI, SNR, failure rates  
  - Compare different spreading factors and bandwidths

- Decide on a reference chipset  
  - Lock in SX1262 (or similar) as Seed’s reference transceiver for hardware design and regulatory planning

This document can be updated as you perform real-world experiments and refine the choice of exact LoRa chipset for Seed.
