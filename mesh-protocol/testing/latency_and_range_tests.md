# Latency and Range Tests

This document defines how Seed’s mesh protocol is evaluated for communication latency and effective range under real-world conditions. Because Seed operates without centralized infrastructure and often without internet access, understanding performance limits is critical for reliability, usability, and investor confidence.

---

## 1. Purpose of Latency and Range Testing

The goals of latency and range testing are to:

- Measure how long it takes for messages to propagate through the mesh.
- Determine maximum reliable communication distance between Seed devices.
- Understand performance degradation as distance, interference, and node count increase.
- Validate assumptions used in protocol design and power budgeting.
- Identify safe operating envelopes for real-world deployments.

These tests inform hardware choices, firmware tuning, and deployment guidance.

---

## 2. Definitions

- **Latency**: Time between when a message is sent by one device and when it is successfully received and processed by another.
- **One-hop latency**: Communication time between two directly connected devices.
- **Multi-hop latency**: Total time for a message to traverse multiple intermediate nodes.
- **Effective range**: Maximum distance at which messages are reliably delivered within acceptable error rates.
- **Packet loss**: Percentage of messages that fail to arrive or fail integrity checks.

---

## 3. Test Environment Categories

Latency and range tests are conducted across multiple environments to reflect real usage:

### 3.1 Controlled Indoor Environment
- Short-range testing (1–50 meters)
- Minimal RF interference
- Line-of-sight and non-line-of-sight scenarios

### 3.2 Urban Outdoor Environment
- Buildings, vehicles, and interference sources
- Moderate node density
- Realistic deployment for street vendors and markets

### 3.3 Rural / Open Field Environment
- Long-range testing (hundreds of meters to several kilometers)
- Minimal interference
- Used to validate theoretical LoRa range limits

### 3.4 High-Interference Environment
- Near Wi-Fi routers, cellular towers, or electrical equipment
- Stress testing resilience and retry logic

---

## 4. Latency Test Methodology

### 4.1 One-Hop Latency Tests

Procedure:
1. Device A sends a timestamped message to Device B.
2. Device B responds with an acknowledgment.
3. Round-trip time is recorded.
4. One-way latency is calculated as half the round-trip time.

Metrics collected:
- Minimum latency
- Average latency
- Maximum latency
- Variance (jitter)

---

### 4.2 Multi-Hop Latency Tests

Procedure:
1. Deploy 3–10 devices in a mesh topology.
2. Send messages from one edge of the mesh to another.
3. Measure end-to-end delivery time.
4. Record hop count and retransmissions.

Metrics collected:
- Latency per hop
- Total end-to-end latency
- Impact of routing decisions
- Effect of congestion and retries

---

## 5. Range Test Methodology

### 5.1 Incremental Distance Testing

Procedure:
1. Place two devices at increasing distances.
2. Send fixed-size packets at each distance.
3. Record success rate and signal quality.
4. Stop when packet loss exceeds acceptable threshold.

Thresholds:
- Reliable range: >95% delivery success
- Marginal range: 50–95% success
- Unreliable range: <50% success

---

### 5.2 Mesh-Assisted Range Extension

Procedure:
1. Insert relay nodes between distant endpoints.
2. Measure how mesh routing extends effective communication.
3. Compare direct vs multi-hop delivery success.

This validates Seed’s ability to operate beyond single-hop limitations.

---

## 6. Metrics Collected

Each test records the following:

- Distance between nodes
- Transmission power level
- Spreading factor and bandwidth
- Packet size
- Packet success rate
- Average latency
- Retry count
- Battery impact during test

All metrics are logged locally and exported for analysis.

---

## 7. Acceptable Performance Targets

Seed aims to meet the following baseline targets:

- One-hop latency: <2 seconds typical
- Multi-hop latency: <10 seconds across small meshes
- Reliable range (urban): 300–800 meters
- Reliable range (rural): 2–10 kilometers
- Packet loss under normal conditions: <5%

These targets are adjustable based on regulatory and hardware constraints.

---

## 8. Failure and Degradation Analysis

During testing, the following failure modes are analyzed:

- Increased latency due to congestion
- Packet loss due to interference
- Routing instability at long distances
- Battery drain caused by excessive retries

Results feed directly into protocol tuning and power-saving strategies.

---

## 9. Reporting and Documentation

Each test run produces:

- A structured test report
- Raw metric logs
- Summary tables and charts
- Observations and anomalies

Results are stored in the simulations and testing directories for traceability.

---

## 10. Implications for Deployment

Latency and range findings are used to:

- Define recommended node spacing
- Inform user training and expectations
- Guide placement of kiosks or relay devices
- Adjust firmware defaults for different regions

These insights ensure Seed deployments remain reliable even in challenging environments.

---

## 11. Summary

Latency and range testing validate Seed’s ability to function as a resilient, offline-first financial mesh. By rigorously measuring performance across environments and topologies, Seed ensures predictable behavior, scalable deployments, and investor-grade technical credibility without reliance on traditional infrastructure.
