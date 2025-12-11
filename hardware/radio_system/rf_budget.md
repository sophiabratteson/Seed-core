# RF Budget

This document estimates how far Seed devices can communicate over LoRa in typical environments by building an RF (radio frequency) link budget. It connects hardware choices (radio chip, antenna, power level) with real-world outcomes (range, reliability, power usage).

The goal is not to be perfectly precise, but to give realistic, conservative numbers investors, engineers, and field partners can work with.

---

## 1. Objectives

- Estimate realistic communication range for Seed devices in:
  - open rural environments
  - semi-urban villages
  - indoor / dense environments
- Show how transmit power, antenna gain, and modulation settings add up to a usable link
- Highlight tradeoffs between range, data rate, and power consumption
- Provide constraints that feed into:
  - hardware design (antenna, radio choice)
  - mesh-protocol design (hops, retries)
  - deployment planning (how many devices per area)

---

## 2. Assumptions and Parameters

These are baseline assumptions for the RF budget. They can be tuned later as field data comes in.

### 2.1 Frequency band

- Region: initial prototype in ISM band (example: 915 MHz for US, 868 MHz for many other regions)
- Frequency: 868–915 MHz LoRa band

### 2.2 Radio and modulation

- Modulation: LoRa
- Typical spreading factor (SF): 9–12 for long range
- Bandwidth: 125 kHz
- Coding rate: 4/5

Higher spreading factors give more range and robustness but lower data rate and higher airtime.

### 2.3 Transmit power and antenna

- Transmit power (radio output): up to +20 dBm (100 mW) for Seed-class device
- Regulatory limit (EIRP) depends on region; we target:
  - typical EIRP budget around +14 to +20 dBm before antenna losses
- Antenna type:
  - PCB or small whip antenna
- Antenna gains:
  - transmit antenna gain: +1 dBi (small whip)
  - receive antenna gain: +1 dBi

### 2.4 Receiver sensitivity

Approximate LoRa receiver sensitivity at 125 kHz bandwidth:

- SF7: around -123 dBm
- SF9: around -127 dBm
- SF12: around -137 dBm

For long-range, low-data-rate links, we assume sensitivity of about:

- receiver sensitivity: -135 dBm (SF11–SF12 class)

### 2.5 Target link margin

We want margin above minimum sensitivity to handle:

- fading
- obstructions
- imperfect antenna alignment
- manufacturing variation

Target link margin:

- 10–15 dB safety margin

---

## 3. Link Budget Basics

### 3.1 Link budget equation

Simplified link budget:

- received power (dBm) =
  - transmit power (dBm)
  - + transmit antenna gain (dBi)
  - + receive antenna gain (dBi)
  - – path loss (dB)
  - – miscellaneous losses (cable, mismatch) (dB)

We compare received power to receiver sensitivity:

- link margin (dB) = received power (dBm) – receiver sensitivity (dBm)

We want:

- link margin ≥ 10 dB (desired)
- link margin ≥ 0 dB (works but fragile)

### 3.2 Free-space path loss approximation

For frequency around 900 MHz:

- free-space path loss (FSPL) in dB ≈ 32.4 + 20·log10(distance_km) + 20·log10(frequency_MHz)

Example for 900 MHz:

- FSPL ≈ 32.4 + 20·log10(distance_km) + 59.1
- FSPL ≈ 91.5 + 20·log10(distance_km)

Real-world conditions are worse than free space, so we add additional loss for:

- buildings
- vegetation
- terrain
- device placement near the body or inside bags

---

## 4. Example Link Budgets

Below are three scenarios: open rural, semi-urban village, and indoor dense environment. All assume 915 MHz, +20 dBm transmit power, +1 dBi antennas on both ends, and -135 dBm receiver sensitivity.

### 4.1 Open rural environment

Assume:

- environment: line-of-sight, low clutter
- extra loss beyond free space: 5–10 dB

Parameters:

- transmit power: +20 dBm
- antenna gains: +1 dBi TX, +1 dBi RX (total +2 dB)
- miscellaneous losses: 3 dB
- receiver sensitivity: -135 dBm
- extra environment loss: 10 dB

Received power target (for 10 dB margin):

- required received power = -135 dBm + 10 dB = -125 dBm

Link budget:

- transmit power + antenna gains = 20 + 2 = 22 dBm
- total allowed path loss = transmit side – required received power – misc losses
  - 22 dBm – (-125 dBm) – 3 dB = 22 + 125 - 3 = 144 dB total path loss allowed
- subtract environment loss (10 dB)
  - free-space component ≈ 134 dB

Solve for distance where FSPL ≈ 134 dB:

- 134 ≈ 91.5 + 20·log10(distance_km)
- 134 - 91.5 = 42.5
- 20·log10(distance_km) ≈ 42.5
- log10(distance_km) ≈ 2.125
- distance_km ≈ 10^2.125 ≈ about 133 km (theoretical free space; real world will be much less)

This number is unrealistically large for handheld devices at low height. Practical constraints such as earth curvature, antenna height, and clutter reduce range.

Realistic planning assumption:

- conservative planning range in rural line-of-sight:
  - 5–15 km between devices at modest heights
- for Seed:
  - target design assumption: 2–5 km typical coverage between nodes in rural flat terrain

### 4.2 Semi-urban village

Assume:

- environment: small buildings, trees, some non line-of-sight paths
- extra loss beyond free space: 20–30 dB

We reuse the same link budget but subtract more environment loss.

Total allowed loss (from earlier): ~144 dB  
Subtract 25 dB environment loss:

- free-space budget ≈ 119 dB

Solve:

- 119 ≈ 91.5 + 20·log10(distance_km)
- 119 - 91.5 = 27.5
- 20·log10(distance_km) ≈ 27.5
- log10(distance_km) ≈ 1.375
- distance_km ≈ 10^1.375 ≈ about 23.7 km (theoretical free space)

Again, practical planning must be much lower.

Realistic planning assumption:

- semi-urban, non line-of-sight, handheld:
  - 1–3 km reliable range
- for Seed:
  - design assumption: 0.5–2 km typical reliable hops in villages

### 4.3 Indoor / dense environment

Assume:

- environment: buildings, walls, people, devices near bodies
- extra loss beyond free space: 30–40 dB

Total allowed loss: ~144 dB  
Subtract 35 dB:

- free-space budget ≈ 109 dB

Solve:

- 109 ≈ 91.5 + 20·log10(distance_km)
- 109 - 91.5 = 17.5
- 20·log10(distance_km) ≈ 17.5
- log10(distance_km) ≈ 0.875
- distance_km ≈ 10^0.875 ≈ about 7.5 km (theoretical free space)

Realistic planning assumption:

- inside buildings, through walls:
  - 100–600 meters is a more conservative range
- for Seed:
  - design assumption: 0.1–0.5 km (100–500 m) indoors before needing another node

---

## 5. Mesh Design Implications

Seed does not rely on a single long link. Instead, it uses a mesh of nodes. The RF budget drives mesh design:

- typical hop range:
  - rural: 2–5 km
  - villages: 0.5–2 km
  - indoors: 0.1–0.5 km
- devices can forward messages:
  - if user A cannot directly reach user D
  - messages can go A → B → C → D

Mesh tradeoffs:

- more hops:
  - increases reliability coverage
  - uses more airtime and power
- fewer hops:
  - requires longer links and better placement

Seed’s mesh protocol will tune:

- maximum hop count
- retry limits
- duty cycle
- which nodes act as “anchor” nodes in key locations (markets, clinics, kiosks)

---

## 6. Power, Duty Cycle, and Range

Longer range links require:

- lower data rate (higher spreading factor)
- longer airtime per packet
- resulting in:
  - higher power usage per message
  - fewer messages allowed if there are duty-cycle regulations

Seed’s strategy:

- use lower spreading factors and shorter airtime for short-range hops when possible
- use higher spreading factors only when needed to cross gaps
- keep message size compact (just a small transaction record and metadata)
- batch sync:
  - send several transactions in one packet when possible
- sleep aggressively:
  - radio off most of the time
  - wake on schedule or user action to exchange messages

---

## 7. Antenna Placement and Device Design

The RF budget depends heavily on antenna performance in the actual enclosure.

Design considerations:

- keep antenna away from:
  - batteries
  - metal shielding
  - user’s hand blocking the radiation pattern
- try to place antenna:
  - near top of device
  - with clear area in plastic enclosure
- tune antenna length and matching network to target band:
  - for 868/915 MHz quarter-wave whips:
    - around 8–9 cm length for a straight wire
- test in field:
  - measure packet success vs distance
  - adjust design if measured range is much lower than budget estimates

---

## 8. Regional Regulatory Constraints

Different regions have:

- different allowed maximum transmit power (EIRP)
- duty cycle limits
- channelization and band plans

Examples (to be refined with regulatory research):

- US (915 MHz):
  - higher power allowed under certain rules, but must respect frequency hopping or LBT (listen before talk) requirements
- EU (868 MHz):
  - usually lower EIRP and strict duty cycle limits (e.g. 1% per channel)

Impact on Seed:

- where allowed, Seed can:
  - use up to +20 dBm with careful protocol design
- where stricter:
  - use lower power, more hops, or more anchor devices

Seed’s firmware and radio configuration must be region-specific and may store regional profiles in configuration.

---

## 9. Example RF Budget Summary Table

Approximate planning numbers (not guarantees):

- rural, line-of-sight:
  - planning hop distance: 2–5 km
- semi-urban:
  - planning hop distance: 0.5–2 km
- indoor / dense:
  - planning hop distance: 0.1–0.5 km

With a link margin of 10–15 dB and:
- transmit power up to +20 dBm
- small antennas (around +1 dBi)
- LoRa sensitivity around -135 dBm

These figures are intentionally conservative. Real-world field tests may reveal better or worse performance; Seed’s design allows adjusting radio parameters and mesh density accordingly.

---

## 10. Next Steps

- build initial prototypes with:
  - chosen LoRa chip (e.g. SX1262 / SX1276)
  - target antenna type
- run outdoor and indoor range tests in:
  - rural field environment
  - village-style built environment
- log:
  - packet success rate vs distance
  - RSSI and SNR statistics
- update this RF budget:
  - refine link margins
  - adjust planned hop distances
  - feed results into:
    - hardware revisions
    - mesh-protocol tuning
    - deployment planning models
