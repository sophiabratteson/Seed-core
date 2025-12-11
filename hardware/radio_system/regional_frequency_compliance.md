# Regional Frequency Compliance

This document outlines the regulatory requirements, allowable frequency bands, transmission power limits, and certification pathways needed for Seed devices to legally operate across global regions. Because Seed relies on unlicensed ISM-band LoRa radios, compliance must be carefully engineered into both hardware and firmware to ensure global deployability.

---

# 1. Overview

Seed devices use sub-GHz LoRa radios (SX1262/SX1276 family). These radios operate in unlicensed ISM bands that vary by region. Each region sets specific limits on:

- Allowed frequency bands  
- Maximum transmission power (EIRP)  
- Duty cycle limitations  
- Channel spacing and bandwidth  
- Listen-Before-Talk (LBT) requirements  
- Certification standards (FCC, CE, etc.)

Compliance ensures Seed devices can be distributed internationally without violating spectrum regulations.

---

# 2. Primary Frequency Bands by Region

## 2.1 North America (USA, Canada, Mexico)

- **Band:** 902–928 MHz  
- **Regulation:** FCC Part 15.247 (USA), IC RSS-247 (Canada)  
- **Max Power:** Up to +30 dBm EIRP (varies based on modulation)  
- **Duty Cycle:** No strict duty cycle limit, but spectrum etiquette recommended  
- **Special Requirements:**  
  - Frequency-hopping or spread-spectrum modes allowed  
  - No Listen-Before-Talk requirement  

Seed Implications:  
- Excellent region for long-range communication  
- Easiest deployment environment  

---

## 2.2 Europe (EU, UK, EFTA)

- **Band:** 863–870 MHz  
- **Regulation:** ETSI EN 300 220 / EN 301 489  
- **Max Power:** +14 dBm EIRP typical  
- **Duty Cycle:**  
  - 0.1% duty cycle in many sub-bands  
  - Up to 1% in others  
- **Alternative:** LBT + Adaptive Frequency Agility may replace duty-cycle limits in some cases  

Seed Implications:  
- Firmware must enforce strict duty cycle limits  
- Hardware must be capable of CE certification  
- Mesh behavior must be adapted for low-duty cycle regions  

---

## 2.3 India

- **Band:** 865–867 MHz  
- **Max Power:** +30 dBm EIRP  
- **Regulation:** TEC / WPC guidelines  
- **Duty Cycle:** None specified  

Seed Implications:  
- Limited frequency width may reduce channel diversity  
- Power levels allow good range  

---

## 2.4 China

- **Band:** 779–787 MHz (sub-GHz), 470–510 MHz (alternative LoRa band)  
- **Regulation:** SRRC type approval  
- **Max Power:** Typically +12 to +20 dBm EIRP depending on band  
- **Restrictions:**  
  - LoRaWAN regional parameters differ significantly  
  - Only approved modules allowed  

Seed Implications:  
- Requires China-specific firmware build  
- Module-level certification mandatory  

---

## 2.5 Australia & New Zealand

- **Band:** 915–928 MHz  
- **Regulation:** AS/NZS 4268  
- **Max Power:** +30 dBm EIRP  
- **Duty Cycle:** None  

Seed Implications:  
- Aligned with North American frequency usage  
- Can reuse 915MHz hardware and firmware  

---

# 3. Required Hardware Adjustments Per Region

## 3.1 Tunable Radio Front End
Seed devices must support tunable frequency plans because:

- EU uses 863–870 MHz  
- US uses 902–928 MHz  
- India uses 865–867 MHz  

Two strategies:

### Strategy A: Single Global Hardware (Preferred)
- Use an SX1262 + universal RF front-end  
- Allow firmware to configure band limits  
- Antenna must support wide-band tuning (860–930 MHz)

### Strategy B: Region-Specific Hardware Variants
- Different antennas and SAW filters  
- Variant SKUs for each region  

---

# 4. Firmware Compliance Requirements

## 4.1 Enforced Duty Cycle (EU)
- Firmware must track transmission airtime  
- Automatic rate limiting  
- Mesh flooding controlled to avoid violations  

## 4.2 Adaptive Frequency Switching
Avoids overuse of a single sub-band.

## 4.3 Region-Based Build Profiles
Seed firmware must compile with region settings:
- Allowed frequencies  
- Channel lists  
- Max transmission power  
- Regulatory marking (FCC ID, CE mark)

Example:
- `REGION_US915`
- `REGION_EU868`
- `REGION_IN865`

---

# 5. Certification Requirements

## 5.1 FCC (USA)
- Part 15.247 unlicensed radio device  
- Requires intentional radiator testing  
- If using a pre-certified module:  
  - Much easier approval route  

## 5.2 CE (Europe)
- EMC testing  
- RF output, spurious emissions  
- Safety and battery compliance  
- Requires technical file and Declaration of Conformity  

## 5.3 Other Regions
- India: WPC ETA  
- Australia/NZ: RCM  
- Latin America: multiple small regulators  

Certification is one of the biggest cost and time drivers for hardware deployment.

---

# 6. Antenna Considerations

To remain compliant:
- Antenna must match the regional frequency band  
- High-gain antennas may violate EIRP limits  
- Detachable antennas may require additional testing  

Seed strategy:
- Use PCB or flexible antennas tuned to ISM bands  
- Ensure consistent RF behavior across units  

---

# 7. Compliance Risks & Mitigation

## Risk 1: Using wrong frequency in wrong region  
**Mitigation:** Region-locked firmware + internal regulatory table.

## Risk 2: Duty cycle violations  
**Mitigation:** Firmware-level airtime accounting.

## Risk 3: Antenna mismatch  
**Mitigation:** Pre-certified antenna included in Seed device.

## Risk 4: Certification delays  
**Mitigation:** Use of pre-certified LoRa modules.

## Risk 5: Multi-country deployment issues  
**Mitigation:** Maintain a “regional compliance database” inside firmware.  

---

# 8. Summary

Regional frequency compliance is essential for Seed to operate globally and legally. By designing a flexible radio architecture, enforcing region-specific firmware rules, and selecting components capable of passing certification requirements, Seed can achieve:

- Safe, lawful transmission worldwide  
- Scalable distribution into frontier markets  
- Long-term reliability in high-density mesh environments  

Seed’s compliance strategy ensures the device remains both powerful and globally deployable while respecting local spectrum regulations.
