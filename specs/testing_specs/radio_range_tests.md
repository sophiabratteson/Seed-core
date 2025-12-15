# Radio Range Testing Specification

This document defines how Seed devices are tested for reliable radio communication range under real-world conditions. Because Seed operates in offline, infrastructure-poor environments, radio performance is a mission-critical system requirement.

---

## 1. Purpose of Radio Range Testing

Radio range testing validates that Seed devices can:

- Reliably discover nearby nodes
- Transmit and receive transactions
- Maintain mesh connectivity over distance
- Operate under environmental interference
- Degrade gracefully rather than fail abruptly

These tests ensure Seed functions in rural, urban, disaster, and remote settings.

---

## 2. Test Objectives

Primary objectives:

- Measure maximum reliable communication distance
- Validate packet delivery rates at varying ranges
- Assess mesh hop reliability beyond direct line-of-sight
- Evaluate performance under interference and obstacles
- Confirm regulatory compliance for transmission power

---

## 3. Hardware Under Test

Devices:

- Seed prototype units with LoRa radio modules
- Identical antenna configurations
- Fully charged power systems

Radio components:

- LoRa chipset (SX127x / SX126x class)
- Regional frequency band (e.g., 915 MHz / 868 MHz)
- Configurable spreading factor and bandwidth

---

## 4. Test Environments

Testing is conducted across multiple environments:

### 4.1 Open Field
- Flat terrain
- Minimal interference
- Clear line-of-sight

### 4.2 Urban Environment
- Buildings and structures
- RF noise from WiFi, cellular, and electronics
- Non-line-of-sight conditions

### 4.3 Indoor Environment
- Multi-room and multi-floor testing
- Wall and material attenuation effects

### 4.4 Obstructed Terrain
- Trees, hills, and foliage
- Variable elevation
- Partial line-of-sight

---

## 5. Test Methodology

### 5.1 Direct Range Test

Procedure:

1. Place Node A at fixed position
2. Move Node B away in fixed distance increments
3. Transmit test packets at each interval
4. Record:
   - Packet success rate
   - Latency
   - RSSI and SNR values
5. Identify maximum reliable distance threshold

---

### 5.2 Mesh Hop Test

Procedure:

1. Deploy multiple nodes between endpoints
2. Disable direct communication beyond range
3. Measure:
   - Successful multi-hop message delivery
   - Latency increase per hop
   - Packet duplication or loss
4. Validate deterministic routing behavior

---

### 5.3 Interference Stress Test

Procedure:

- Introduce background RF interference
- Vary transmission power and spreading factor
- Observe degradation patterns
- Confirm graceful fallback behavior

---

## 6. Metrics Collected

Key metrics include:

- Maximum reliable range (meters)
- Packet delivery success rate (%)
- Average latency (milliseconds)
- Signal strength (RSSI)
- Signal-to-noise ratio (SNR)
- Energy cost per transmission

---

## 7. Pass / Fail Criteria

A test is considered successful if:

- Packet delivery rate ≥ 95% within target range
- Mesh routing succeeds when direct links fail
- No data corruption occurs
- Device remains within regulatory limits
- No unsafe power or thermal behavior is observed

---

## 8. Failure Handling

If failures occur:

- Logs are captured locally
- Failed packets are analyzed
- Radio parameters are adjusted
- Retesting is performed with documented changes

Failures do not halt deployment; they inform tuning and configuration updates.

---

## 9. Regulatory Compliance Verification

Testing confirms compliance with:

- Regional frequency regulations
- Transmission power limits
- Duty cycle constraints
- Antenna certification requirements

Compliance is documented per region.

---

## 10. Reporting and Documentation

Each test run produces:

- Environment description
- Device configuration
- Raw metrics
- Summary analysis
- Identified limitations
- Recommended configuration profiles

Reports are stored in the repository for audit and investor review.

---

## 11. Investor Relevance

Radio range testing demonstrates that Seed:

- Functions without infrastructure
- Scales across environments
- Is resilient under real-world conditions
- Is engineered for reliability, not theory

This testing validates Seed’s core promise: **financial systems that work anywhere, even when everything else fails**.

---

## 12. Future Enhancements

Planned extensions:

- Automated field testing rigs
- Drone-assisted relay tests
- Seasonal environmental testing
- Cross-region comparative benchmarks

---

## 13. Summary

Radio range testing ensures Seed’s mesh network is reliable, compliant, and field-ready. These tests confirm that Seed devices can communicate securely and consistently in the environments where traditional financial infrastructure does not exist.
