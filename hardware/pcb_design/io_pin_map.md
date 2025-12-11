# IO pin map

This document defines the logical to physical IO pin map for the Seed reference device.  
It connects three layers:

- Logical signals used by firmware (for example LORA_MOSI, EINK_DC, BTN_OK)
- MCU pins (for example PA5, PB3, GPIO10)
- Board-level nets and connectors

The goal is to keep hardware and firmware aligned so that:

- Every peripheral has a clear, documented pin assignment
- Pins are grouped for signal integrity and layout simplicity
- Low-power design and future expandability are preserved

This is a reference map and may be updated as the exact MCU or module changes. The structure should remain the same even if pin numbers change.

---

## 1. MCU and naming conventions

MCU assumptions:

- Low-power 32-bit MCU (for example STM32-class or ESP32-class)
- At least:
  - 2 SPI buses (one for radio, one for e-ink and secure element if needed)
  - 2 I2C buses (sensors / secure element)
  - 1 UART debug port
  - Enough GPIOs for buttons, LEDs, and control lines
  - ADC inputs for battery sensing

Naming conventions:

- MCU pins are written as PA0, PB3, GPIO5, or similar
- Net names are written in uppercase with underscores, such as:
  - LORA_MOSI
  - EINK_DC
  - FP_IRQ
  - BTN_OK
- Signals are grouped by interface: SPI_RADIO, SPI_DISPLAY, etc

All firmware should refer to the logical net names. Board-specific mapping is isolated here and in the device_config.h header.

---

## 2. High-level pin group summary

This table summarizes the main functional groups and the number of pins they consume.

| Group                      | Function                            | Approx pin count |
|--------------------------- |--------------------------------------|------------------|
| SPI_RADIO                  | LoRa radio transceiver              | 4 data + 2 ctrl  |
| SPI_DISPLAY                | E-ink display                      | 4 data + 3 ctrl  |
| I2C_SECURE                 | Secure element / fingerprint (if I2C)| 2                |
| UART_DEBUG                 | Debug / logging                     | 2                |
| BUTTON_INPUTS              | User input buttons                  | 3 to 5           |
| LED_STATUS                 | Simple status LED                   | 1 to 2           |
| BATTERY_SENSE              | ADC input for battery voltage       | 1                |
| POWER_CONTROL              | Enable lines for subsystems         | 2 to 4           |
| FINGERPRINT_SENSOR         | Additional GPIO (IRQ, reset)        | 2 to 3           |
| MISC_EXPANSION             | Reserved for future features        | 2 to 4           |

---

## 3. Detailed pin map

### 3.1 SPI bus for LoRa radio (SPI_RADIO)

Used by the LoRa transceiver (for example SX1262 or SX1276).

| Net name     | Direction (MCU) | Purpose                            | MCU pin example |
|--------------|------------------|------------------------------------|-----------------|
| LORA_MOSI    | output           | SPI MOSI to radio                  | PA7             |
| LORA_MISO    | input            | SPI MISO from radio                | PA6             |
| LORA_SCK     | output           | SPI clock to radio                 | PA5             |
| LORA_NSS     | output           | Chip select (CS) for radio         | PB0             |
| LORA_BUSY    | input            | Radio busy status                  | PB1             |
| LORA_DIO0    | input            | Radio interrupt / event pin        | PB2             |
| LORA_RESET   | output           | Radio hardware reset               | PB10            |

Design notes:

- Keep LORA_MOSI, LORA_MISO, LORA_SCK short and tightly routed for signal integrity.
- Group these pins on the same side of the MCU when possible for easier routing.
- LORA_BUSY and LORA_DIO0 should connect to interrupt-capable GPIOs.

---

### 3.2 SPI bus for e-ink display (SPI_DISPLAY)

Dedicated SPI bus for the e-ink display to avoid contention with radio.

| Net name     | Direction (MCU) | Purpose                             | MCU pin example |
|--------------|------------------|-------------------------------------|-----------------|
| EINK_MOSI    | output           | SPI MOSI to display                 | PB5             |
| EINK_MISO    | input (optional) | SPI MISO from display (if used)     | PB4             |
| EINK_SCK     | output           | SPI clock to display                | PB3             |
| EINK_CS      | output           | Chip select for e-ink               | PA15            |
| EINK_DC      | output           | Data/command select                  | PC0             |
| EINK_RST     | output           | Hardware reset                       | PC1             |
| EINK_BUSY    | input            | Panel busy / not ready               | PC2             |

Design notes:

- EINK_MISO is optional; many panels are write-only.
- EINK_BUSY should go to an interrupt-capable pin to support low-power waits.
- Keep all display control lines near each other on the connector footprint.

---

### 3.3 I2C secure element and optional sensors (I2C_SECURE)

Used for secure element, and optionally a fingerprint controller or other sensors.

| Net name    | Direction (MCU) | Purpose                              | MCU pin example |
|-------------|------------------|--------------------------------------|-----------------|
| I2C_SCL     | bidirectional    | I2C clock                            | PB8             |
| I2C_SDA     | bidirectional    | I2C data                             | PB9             |
| SE_INT      | input            | Secure element interrupt (optional)  | PC3             |

Devices on this bus may include:

- Secure element chip (for example ATECC608 class)
- Configuration EEPROM (optional)
- Simple low-rate sensors

Design notes:

- Pull-up resistors required on I2C_SCL and I2C_SDA.
- Keep bus length short and avoid noisy traces.

---

### 3.4 Fingerprint sensor interface (if not purely I2C)

Some fingerprint modules use UART or SPI plus dedicated control pins.

Example UART-driven fingerprint sensor:

| Net name   | Direction (MCU) | Purpose                      | MCU pin example |
|------------|------------------|------------------------------|-----------------|
| FP_TX      | output           | MCU TX to fingerprint RX     | PA2             |
| FP_RX      | input            | MCU RX from fingerprint TX   | PA3             |
| FP_RST     | output           | Reset line to sensor         | PC4             |
| FP_IRQ     | input            | Finger detected / interrupt  | PC5             |

Design notes:

- FP_IRQ should support interrupt mode.
- Place sensor close to board edge or enclosure surface for user access.
- Route FP traces away from high-speed SPI lines where possible.

---

### 3.5 User input buttons (BUTTON_INPUTS)

Used for simple UI navigation on the Seed device.

| Net name   | Direction (MCU) | Purpose              | MCU pin example |
|------------|------------------|----------------------|-----------------|
| BTN_OK     | input            | Confirm / select     | PA0             |
| BTN_BACK   | input            | Back / cancel        | PA1             |
| BTN_UP     | input            | Navigate up          | PC6             |
| BTN_DOWN   | input            | Navigate down        | PC7             |
| BTN_MENU   | input (optional) | Open menu / options  | PC8             |

Design notes:

- Buttons should have pull-up or pull-down resistors as appropriate.
- Consider using interrupt-capable pins for BTN_OK and BTN_BACK for wake-from-sleep.

---

### 3.6 Status LED (LED_STATUS)

Simple LED for device status.

| Net name   | Direction (MCU) | Purpose           | MCU pin example |
|------------|------------------|-------------------|-----------------|
| LED_STATUS | output           | Status indicator  | PC9             |

Design notes:

- Current-limiting resistor is required.
- Optional second LED could indicate radio or battery status.

---

### 3.7 Battery sensing (BATTERY_SENSE)

Battery voltage measurement via ADC.

| Net name       | Direction (MCU) | Purpose                             | MCU pin example |
|----------------|------------------|-------------------------------------|-----------------|
| BAT_SENSE_AIN  | input (ADC)      | Battery voltage after divider       | PA4             |

Design notes:

- Use a resistive divider to scale battery voltage into safe ADC range.
- Consider switching the divider with a FET to reduce idle current.

---

### 3.8 Power control signals (POWER_CONTROL)

Power-enable lines for subsystems, used by the power manager.

| Net name         | Direction (MCU) | Purpose                                  | MCU pin example |
|------------------|------------------|------------------------------------------|-----------------|
| PWR_RADIO_EN     | output           | Enable power to LoRa radio              | PB12            |
| PWR_DISPLAY_EN   | output           | Enable power to e-ink logic             | PB13            |
| PWR_SENSOR_EN    | output           | Enable power to sensors / fingerprint   | PB14            |
| PWR_SECURE_EN    | output           | Enable power to secure element          | PB15            |

Design notes:

- These lines drive load switches or regulator enable pins.
- Default state should be off at reset to minimize startup power.

---

### 3.9 Debug and programming interface (UART_DEBUG and SWD / JTAG)

Used by engineers, not exposed to end users.

UART debug:

| Net name    | Direction (MCU) | Purpose             | MCU pin example |
|-------------|------------------|---------------------|-----------------|
| UART_TX_DBG | output           | Debug log output    | PA9             |
| UART_RX_DBG | input            | Debug input (rare)  | PA10            |

SWD / JTAG:

| Net name | Direction (MCU) | Purpose             | MCU pin example |
|----------|------------------|---------------------|-----------------|
| SWDIO    | bidirectional    | Debug data          | PA13            |
| SWCLK    | input            | Debug clock         | PA14            |
| NRST     | input            | Hardware reset      | NRST pin        |

Design notes:

- Place programming header near PCB edge.
- These pins should remain accessible during all prototype stages.

---

## 4. Reserved and expansion pins

To support future features (extra sensors, new peripherals), reserve a few GPIOs.

Example reserved pins:

| Net name       | Direction (MCU) | Notes                             | MCU pin example |
|----------------|------------------|-----------------------------------|-----------------|
| EXP_GPIO1      | input/output     | General expansion                 | PC10            |
| EXP_GPIO2      | input/output     | General expansion                 | PC11            |
| EXP_INT1       | input            | Dedicated interrupt line          | PC12            |
| EXP_ADC1       | input (ADC)      | Extra analog input                | PA11            |

These pins should be exposed on a test pad or small internal connector.

---

## 5. Mapping summary for firmware

In firmware, all references to pins should use logical names defined in device_config.h, for example:

- DEVICE_ID
- PIN_LORA_MOSI
- PIN_LORA_SCK
- PIN_EINK_DC
- PIN_BTN_OK
- PIN_BAT_SENSE_AIN
- PIN_PWR_RADIO_EN

The compiler-specific mapping to MCU pins (for example PB3, PA0) is configured here in the IO pin map and mirrored in the config header. When the board spins change, only this document and the config header need to be updated.

---

## 6. Design and layout recommendations

- Group SPI_RADIO and SPI_DISPLAY pins on opposite sides of the MCU if possible to reduce crosstalk.
- Keep high-current paths (battery, charging, LoRa PA) away from sensitive analog pins (BAT_SENSE_AIN).
- Keep I2C lines short and routed as a pair.
- Reserve keep-out zones around the radio and antenna for RF performance.
- Clearly label all test points and programming pins in the silkscreen.

This IO pin map is the living reference for both hardware and firmware teams and should be kept up to date with each board revision.
