# Third-Party Licenses

This document catalogs all external open-source and proprietary components used in Seed’s firmware, software stack, mobile/desktop tools, documentation, and prototype utilities. It also outlines the corresponding license obligations, attribution requirements, and compliance procedures. Maintaining a clear third-party license inventory is essential for protecting Seed’s intellectual property, enabling safe commercialization, and ensuring regulatory and contractual compliance.

---

# 1. Purpose of This Document

- Provide a centralized list of all third-party dependencies (software, libraries, hardware drivers, tools).
- Record the licenses governing each dependency.
- Identify obligations required for Seed’s distribution model (e.g., source disclosure, attribution notices).
- Flag any licenses that may pose compatibility or commercialization concerns.
- Serve as the reference for legal audits, due diligence, and investor technical risk review.

---

# 2. Third-Party Software Dependencies (Prototype Phase)

The following libraries may be included in the MVP or early firmware prototypes. Final component selection will be narrowed during engineering validation.

## 2.1 Embedded / Firmware Dependencies (Potential)

| Component / Library | Purpose | License | Notes |
|---------------------|---------|---------|-------|
| **FreeRTOS** | Lightweight RTOS for microcontroller task scheduling | MIT | Commercial-friendly, no copyleft obligations. |
| **TinyJSON / Minimal JSON Parsers** | Small JSON parsing for constrained devices | Varies (MIT or BSD) | Ensure chosen version is MIT/BSD. |
| **LoRaMAC-Node (Semtech Reference)** | Official LoRaWAN MAC implementation | BSD-3-Clause | Compatible with commercial firmware. |
| **CryptoAuthLib (Microchip)** | Library for secure element chips (ATECC608A, etc.) | Apache-2.0 | Attribution required; no copyleft. |
| **LVGL (Lightweight Graphics Library)** | For rendering UI on displays | MIT | Safe for commercial firmware. |
| **Meshtastic Radio Code (If used for testing)** | Mesh networking reference implementation | GPL-3.0 | **Cannot be included in final shipping firmware** due to strong copyleft. Only allowed for experimentation. |

---

## 2.2 Desktop / Python Tools Used for Simulation

| Library | License | Notes |
|--------|---------|--------|
| **Python Standard Library** | PSF License | No restrictions. |
| **PyCryptodome** | BSD-2-Clause | Strongly recommended for cryptography. |
| **NetworkX** | BSD License | If used for mesh simulation. |
| **Matplotlib / NumPy** | BSD | Safe for commercial use. |

---

## 2.3 Prototyping UI Tools

| Tool / Framework | License | Notes |
|------------------|---------|-------|
| **Figma** | Proprietary | No license constraints on output artifacts. |
| **React / React Native (Optional future app)** | MIT | Safe for commercial products. |

---

# 3. Third-Party Hardware Dependencies

| Hardware Component | License / Restrictions | Notes |
|-------------------|-------------------------|-------|
| **Semtech SX1276 / SX1262 Radio Chips** | Proprietary hardware, no firmware license restrictions | Documentation covered by Semtech SLA. |
| **Microchip ATECC608A Secure Element** | Proprietary hardware, crypto library under Apache-2.0 | Commercial products allowed. |
| **LILYGO Development Boards** | Hardware is open; software examples vary (MIT/Apache/GPL) | Final product will not redistribute vendor code. |
| **E-Ink Panels (Good Display, Waveshare)** | Proprietary hardware; drivers often MIT/BSD | Verify specific driver license before bundling. |

---

# 4. License Classes and Their Impact on Seed

## 4.1 Permissive Licenses (MIT, BSD, Apache-2.0)
- Fully compatible with Seed.
- Allow commercial distribution.
- Do not require Seed to open-source proprietary firmware.
- Require only attribution and license text reproduction.

**Recommended for all production dependencies.**

## 4.2 Weak Copyleft (LGPL)
- Allows static/dynamic linking under conditions.
- Typically safe if Seed keeps modifications to libraries separate.

## 4.3 Strong Copyleft (GPLv3)
- **Not suitable for Seed’s final firmware or core software**, because:
  - Any derivative work must be open-sourced.
  - Would force Seed to disclose proprietary firmware.
  - Could restrict commercial licensing and patent strategy.

**GPL dependencies may ONLY be used for prototyping, research, or standalone tools that are never distributed with the device.**

---

# 5. Compliance Requirements for Seed

Seed must maintain:

## 5.1 Attribution Files
A `THIRD_PARTY_NOTICES.txt` must be included in:
- The GitHub repository
- Firmware release bundles
- Website downloads (if distributing tools)

## 5.2 SBOM (Software Bill of Materials)
As Seed moves toward manufacturing and security audits, a full SBOM will be required containing:
- All libraries used
- Version numbers
- License identifiers
- Vulnerability status (CVEs)

## 5.3 Source Code Separation
Proprietary firmware must be clearly separated from open-source components to avoid accidental license contamination.

## 5.4 Legal Review Before New Dependencies
Every new dependency must go through a minimal checklist:
1. What is the license?
2. Is it permissive or copyleft?
3. Does it require redistributing source code?
4. Does it affect patents?
5. Will it be shipped on the device or only used for development?

---

# 6. Risk Flags to Avoid

Seed **must avoid** including in the final firmware:
- GPL-licensed mesh networking libraries  
- GPL-licensed cryptography  
- GPL code embedded into device firmware or bootloader  
- Libraries with unclear licensing or mixed ownership

These would threaten Seed’s ability to:
- Maintain proprietary IP
- License hardware commercially
- Raise venture capital
- Build defensible patent claims

---

# 7. Licensing Strategy Going Forward

Seed’s recommended long-term strategy:

- Use MIT/BSD/Apache-licensed components exclusively in production.
- Open-source **non-sensitive**, **non-security-critical** parts of the system to build trust (e.g., UI libraries, simulation tools).
- Keep cryptography, ledger engine, trust score logic, and proprietary mesh protocol **closed-source** or dual-licensed.
- Prepare for a future **dual-license model**:
  - Community license (MIT/Apache for non-core tools)
  - Commercial license (full device firmware + secure components)

---

# 8. Summary

Seed’s third-party licensing strategy ensures:

- Full legal compliance  
- Maximum commercial flexibility  
- No forced open-sourcing of proprietary firmware  
- Clean IP ownership for investors and partners  
- Smooth pathway to manufacturing and regulated environments  

This document will evolve as Seed matures, and every dependency must be continuously monitored to maintain legal safety and investor readiness.
