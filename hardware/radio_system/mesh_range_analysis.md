# Mesh Range Analysis

This document provides a detailed assessment of expected communication range for the Seed device’s LoRa-based mesh network under real-world conditions. The purpose of this analysis is to quantify how far devices can reliably exchange packets, how environmental factors affect propagation, and how the mesh can maintain connectivity even when individual links degrade.

---

# 1. Overview

Seed relies on long-range, low-power LoRa radios to enable offline-first communication. LoRa allows Seed devices to form ad-hoc mesh networks that do not require infrastructure, cell towers, or Wi-Fi. Understanding range is critical for:

- Hardware design (antenna choice, output power, shielding)
- Protocol tuning (spreading factor, bandwidth)
- Mesh routing strategies
- Deployment planning in rural, urban, and remote settings
- Expected user experience during real-world field use

---

# 2. Key Factors Affecting Range

Range is not fixed. It depends on radio parameters, environment, and physical device design. Major influences include:

## 2.1 Frequency Band
- 915 MHz (Americas): balanced penetration and range.
- 868 MHz (EU): similar characteristics.
- 433 MHz: longest range, but larger antenna and regulatory complications.

Higher frequency = lower wall penetration but shorter antenna.  
Lower frequency = longer range but larger antenna.

## 2.2 Spreading Factor (SF)
- SF7: short range, high data rate.
- SF12: long range, low data rate.
- Seed devices dynamically adjust SF based on link quality.

## 2.3 Transmit Power (TX Power)
- Typical: +14 dBm to +22 dBm (LoRa legal max per region)
- Higher power increases range but reduces battery life.

## 2.4 Antenna Quality
- PCB antenna: shortest range.
- Helical antenna: medium range.
- External SMA whip: longest reliable range.

## 2.5 Environmental Conditions
- Line-of-sight: extremely long range.
- Dense urban areas: reflections, obstructions.
- Forests: signal absorption from vegetation.
- Indoors: walls degrade RF but still allow communication.

---

# 3. Expected Range Estimates

Below are realistic field-tested expectations for LoRa under different conditions. Values assume standard +20 dBm transmission power.

## 3.1 Line-of-Sight (Open Field)
- SF7: 1–3 km
- SF9: 5–10 km
- SF12: 10–15+ km (best case: 20 km)

Use case relevance:
- Rural villages
- Desert, plains, farmland
- Mountainous ridge-to-ridge communication

## 3.2 Light Urban (small buildings, open streets)
- SF7: 500–800 m
- SF9: 1–2 km
- SF12: 2–5 km

Use case relevance:
- Low-density towns
- Informal settlements
- Markets and small business clusters

## 3.3 Dense Urban (high-rise, heavy obstruction)
- SF7: 100–300 m
- SF9: 300–700 m
- SF12: 800–1500 m

Use case relevance:
- Slum networks
- High-density neighborhoods
- Mixed indoor/outdoor environments

## 3.4 Indoor-to-Indoor Through Walls
- Typical: 50–200 m depending on wall materials
- Concrete significantly reduces range
- Wood and drywall have minimal effect

---

# 4. Mesh Network Implications

Range is rarely the bottleneck because:

- Seed is a **mesh**, not a point-to-point system.
- Even short-range links contribute to multi-hop connectivity.
- More nodes = exponentially better coverage.

## 4.1 Mesh Density Benefits
- In dense areas, even 100 m range can support full mesh.
- In rural areas, 1–5 km range is enough for village-wide coverage.
- In nomadic or moving populations, hops dynamically reorganize.

## 4.2 Multi-hop Extension
If each device can reach:
- 1 km → 5 hops = 5 km coverage radius
- 5 km → 5 hops = 25 km coverage radius

This allows entire towns to synchronize.

---

# 5. Antenna Considerations

## 5.1 Recommended Antenna for Prototype
- External 915 MHz SMA whip or IPEX whip antenna
- Provides consistent 1–5 km range without tuning

## 5.2 Final Product Antenna
- Internal helical antenna for compact size
- Tuned on final PCB for optimal impedance matching

## 5.3 Optional High-Gain Antennas
- Directional Yagi antennas can extend range to 20+ km
- Useful for base stations, kiosks, or long-distance rural bridging

---

# 6. Environmental Reliability

## 6.1 Rain and Humidity
- Minimal impact on 868–915 MHz frequencies
- Very heavy storms may reduce 5–10 percent of range

## 6.2 Heat and Temperature
- Radio performance stable from -20°C to +60°C
- Batteries degrade faster in extreme heat but radio range is not heavily affected

## 6.3 Obstacles
- Metal walls cause the strongest signal loss
- Tree density (especially wet foliage) reduces range

---

# 7. Implications for Seed Deployment

## 7.1 Rural Deployment
- Few obstructions → excellent range
- Seed can connect entire communities with small node counts

## 7.2 Urban Deployment
- Mesh routing is key
- Many short links create large, resilient networks
- Devices operate well indoors and outdoors

## 7.3 Disaster and Humanitarian Context
- Mesh works even when infrastructure is down
- Long-range peer-to-peer communication is ideal for:
  - refugee camps
  - earthquake zones
  - areas with collapsed telecom systems

---

# 8. Field Testing Plan

Seed’s first real-world range tests will measure:

- RSSI and SNR at varying distances (every 50 m to 5 km)
- Transmission reliability under:
  - indoors
  - outdoors
  - around corners
  - dense trees
  - inside vehicles
- Performance at different spreading factors
- Impact of battery level and temperature
- Human-body absorption (device held in hand or pocket)

Data will inform final antenna selection and radio tuning.

---

# 9. Conclusion

LoRa provides exceptional long-range, low-power communication suitable for offline financial mesh networks. Based on environmental and hardware conditions, Seed devices can reliably achieve:

- 1–15 km outdoors  
- 100–1500 m urban  
- 50–200 m indoors  

When combined with multi-hop mesh routing, this enables community-wide coverage without towers, servers, or internet. The radio system is foundational for Seed’s mission of enabling global financial connectivity in low-infrastructure environments.
