# PCB Prototyping Notes

This document provides practical guidance, constraints, and lessons learned for prototyping the Seed device PCB. The goal is to ensure that early hardware iterations are reliable, manufacturable, and aligned with Seed's low-power, offline-first architecture.

---

## 1. Prototyping Objectives

- Validate electrical connections between MCU, LoRa radio, secure element, power system, and e-ink display.
- Confirm that the board boots consistently and remains stable under low-power conditions.
- Verify RF performance, antenna tuning, and real-world mesh reliability.
- Ensure that component placement supports manufacturability and enclosure integration.
- Identify early failure modes before moving to multi-layer production-grade boards.

---

## 2. Recommended PCB Prototyping Workflow

1. Begin with breakout modules and a breadboard to validate minimum functionality.
2. Move to a simple two-layer PCB for radio + MCU + power subsystem.
3. Add peripherals (e-ink, secure element, fingerprint sensor) only after stable power and RF.
4. Run benchtop tests for thermal behavior and power draw.
5. Iterate on antenna design after the enclosure form factor is determined.
6. Move to a more compact four-layer board once electrical behavior is well understood.

---

## 3. Breadboard and Module Testing Tips

- Use jumper wires under 10 cm to reduce noise in the radio lines.
- Power the LoRa module from a regulated 3.3 V supply; avoid 5 V inputs.
- Test SPI communication with the e-ink display separately before integration.
- Validate secure element communication (I2C) using a minimal test program.
- Use serial logging heavily to confirm startup timing and pin initialization.

---

## 4. Early PCB Revision Goals

- Establish stable boot sequence for power rails and MCU clock.
- Ensure LoRa radio SPI lines operate without clock skew.
- Integrate reverse-polarity and over-current protection.
- Verify that the hand-crank + solar input does not introduce voltage ripple into logic rails.
- Measure baseline quiescent current to confirm sleep-mode efficiency.

---

## 5. Layout Considerations for Prototyping

- Place the LoRa radio and antenna connector at the PCB edge for clear RF paths.
- Separate analog and digital grounds where possible and join at a single star point.
- Keep SPI traces (MCU to radio, MCU to display) short and routed as controlled-impedance pairs when possible.
- Isolate the secure element from noisy power domains.
- Allocate test pads for all critical signals, especially:
  - Radio SPI
  - Power rails (VIN, 3.3 V, battery)
  - Reset lines
  - Debug UART

---

## 6. Antenna Prototyping Notes

- Use an external SMA antenna for early prototypes to simplify debugging.
- Maintain a minimum ground clearance region around the antenna feed line.
- Ensure the antenna ground reference area is large enough to match datasheet recommendations.
- Perform VSWR and return-loss measurements once enclosure decisions are made.

---

## 7. Power Subsystem Prototyping Notes

- Use oversized trace widths for battery and boost converter paths.
- Add test points before and after the charger IC to measure solar and hand-crank input behavior.
- Ensure the battery connector is keyed or locked to avoid polarity mistakes.
- Prototype with LiFePO4-compatible charge IC first due to safety and thermal stability.

---

## 8. MCU and Secure Element Integration Tips

- Keep the secure element close to the MCU to minimize I2C capacitance.
- Add pull-up resistors (4.7k or per datasheet) to I2C lines.
- Include a hardware reset pin on the secure element for debugging.
- Confirm MCU bootloader access remains available even if other subsystems fail.

---

## 9. E-Ink Display Notes

- Ensure the display connector orientation is correct before ordering PCBs.
- Route high-voltage e-ink driving lines per manufacturer recommendations.
- Add level shifters if the e-ink controller requires a different I/O voltage.
- Provide mounting holes that prevent flex stress on the fragile display.

---

## 10. Common Failure Modes in Early Prototypes

- RF interference from switching regulators.
- MCU brownout during radio transmit bursts.
- Incorrect antenna impedance causing short communication range.
- Fingerprint sensor noise due to shared ground return paths.
- Secure element lockup from unstable I2C line levels.
- E-ink display ghosting caused by improper waveform driving or timing.

---

## 11. Assembly and Soldering Recommendations

- Reflow is preferred for LoRa and secure elements; hand-solder only for prototypes.
- Use leaded solder for initial prototypes to reduce cold-joint risk.
- Inspect QFN and BGA pads with a microscope for bridging.
- Clean flux thoroughly to prevent leakage currents in low-power circuitry.

---

## 12. Testing Checklist for Prototype Boards

- Power rails at expected voltages under load.
- MCU boots consistently and runs minimal firmware.
- Secure element responds to I2C queries.
- LoRa radio transmits and receives short packets.
- Antenna tuning verified with at least a basic SWR check.
- E-ink successfully updates at least one reference image.
- Fingerprint sensor produces stable readings.
- All test points accessible and labeled.

---

## 13. When to Move to the Next PCB Revision

- Power sequencing is stable and reproducible.
- Communication between MCU, radio, secure element, and display is reliable.
- The device maintains communication at expected mesh distances.
- Sleep-mode power levels meet or are close to budget.
- No blocking thermal or mechanical issues remain.

---

## 14. Documentation to Maintain During Prototyping

- Annotated schematics showing changes between revisions.
- Measured power consumption logs.
- RF test notes (range tests, antenna tuning).
- Known issues list with reproduction steps.
- Revision-to-revision diff notes.

---

## 15. Summary

This prototyping guidance ensures that early hardware revisions of Seed are:
- Electrically stable
- RF-optimized
- Safe for battery and off-grid charging
- Easy to debug
- Ready for iterative improvement toward mass production

Follow these notes during every prototype cycle to reduce risk and accelerate hardware maturity.
