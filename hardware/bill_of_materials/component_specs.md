# Component Specifications

This document details the electrical, mechanical, and performance specifications for all components included in the Seed MVP hardware. These specifications ensure consistency across prototypes and support early manufacturing and testing activities.

## 1. Microcontroller Unit (MCU)

- Type: Low-power ARM Cortex-M0/M3/M4 class MCU
- Flash storage: Minimum 512 KB
- RAM: Minimum 128 KB
- Operating voltage: 1.8V – 3.6V
- Clock speed: 32–80 MHz depending on power mode
- Peripheral support:
  - SPI for LoRa radio
  - I2C for sensors and secure element
  - UART for debugging
  - GPIO for buttons and interrupts
- Power modes:
  - Active mode < 10 mA
  - Sleep mode < 50 µA
  - Deep sleep < 5 µA
- Temperature tolerance: -20C to +70C

## 2. LoRa Radio Module

- Chipset: Semtech SX1262 or SX1276
- Frequency: Region-dependent (868 MHz, 915 MHz recommended)
- Power output: 14 dBm to 22 dBm
- Sensitivity: Down to -137 dBm
- Modulation: LoRa, FSK
- Bandwidth: 125 kHz – 500 kHz
- Typical current draw:
  - TX high power: 100–120 mA
  - RX: 4.5–12 mA
  - Standby: < 1.5 mA
- Interface: SPI

## 3. Antenna

- Type: PCB or external whip antenna
- Frequency match: Must match LoRa module band (868/915 MHz)
- VSWR: < 2.0 recommended
- Gain: 0–2 dBi for compact prototypes
- Connector: U.FL or solder pad

## 4. E-Ink Display

- Size: 2.13 inches
- Resolution: 212 x 104 pixels
- Technology: Bistable e-paper, black and white
- Interface: SPI
- Refresh time: 250–450 ms full update
- Power consumption:
  - Refresh: ~20 mA peak
  - Idle: near 0 mA (retains image without power)
- Operating temperature: 0C – 50C

## 5. Lithium Iron Phosphate (LiFePO4) Battery

- Capacity: 500 – 1200 mAh for MVP
- Nominal voltage: 3.2V
- Charge voltage: 3.6V max
- Cycle life: > 2000 cycles
- Safety characteristics:
  - Thermal stability
  - Non-flammable chemistry
- Discharge capability: 1C continuous recommended

## 6. Charging and Power Management System

- Solar input support: 5V small solar panel
- Hand-crank generator compatibility: 5–7V rectified input
- Charge controller:
  - LiFePO4 compatible
  - Input current limit 200–500 mA
- Voltage regulators:
  - 3.3V buck/boost regulator
  - Efficiency > 85% at 5–50 mA loads
- Protection:
  - Overcharge
  - Over-discharge
  - Short circuit

## 7. Secure Element Chip

- Crypto processor: ECC and RSA support
- Secure boot support
- Hardware key storage:
  - Device private key
  - Ledger signing keys
- Tamper detection:
  - Voltage glitch detection
  - Temperature anomaly detection
- Interface: I2C or SPI

## 8. Fingerprint Sensor (Capacitive)

- Type: Capacitive fingerprint reader
- Template storage: Internal secure memory
- Matching speed: < 300 ms
- False reject rate: < 2%
- False accept rate: < 0.0001%
- Power: < 15 mA active

## 9. Buttons and Input Controls

- Number: 2–3 physical buttons
- Type: Tactile switch, 3.3V logic
- Debounce required: Hardware or firmware
- Expected lifespan: > 100,000 presses

## 10. Storage (Flash or FRAM)

- Type: SPI flash or I2C FRAM
- Size: 4–16 MB depending on design
- Write endurance:
  - Flash: ~100,000 cycles
  - FRAM: virtually unlimited
- Data retention: Minimum 10 years
- Use cases:
  - Ledger storage
  - Checkpoints
  - Cached mesh messages

## 11. PCB Requirements

- Layers: 2-layer for MVP, 4-layer recommended for RF optimization
- Board thickness: 1.0–1.6 mm
- Controlled impedance for RF traces
- Grounding:
  - Large ground plane under radio
  - Separate analog and digital ground recommended
- ESD protection components near connectors

## 12. Mechanical Enclosure Components

- Material: ABS or polycarbonate plastic
- Thickness: 1.2–1.8 mm walls
- Environmental resistance:
  - Dust: IP4X minimum
  - Water splash: IPX2 minimum
- Mounting features:
  - Screw posts
  - Snap fits for prototyping
- Cutouts:
  - Buttons
  - Charging port
  - Optional venting for heat

## 13. Miscellaneous Components

- LEDs:
  - Power indicator LED (optional)
  - Status LED for debugging
- Connectors:
  - JST battery connector
  - USB-C charging connector
- Passive components:
  - Bypass capacitors
  - Pull-up resistors
  - Matching network components for antenna

## 14. Prototype Assembly Notes

- All components must be hand-solderable for MVP iterations
- Prefer breakouts for complex parts such as LoRa, secure element, and display
- Keep RF components away from noisy digital traces
- Isolate battery wiring from logic wiring where possible
