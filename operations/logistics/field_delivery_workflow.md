# Field Delivery Workflow

This document defines how Seed devices are delivered, activated, and supported in real-world field deployments, especially in low-connectivity, rural, humanitarian, and post-disaster environments. The workflow prioritizes reliability, accountability, and minimal infrastructure dependency.

---

## 1. Objectives

- Deliver Seed devices safely to end users in remote or unstable regions
- Ensure devices are functional upon receipt
- Enable activation without internet or centralized systems
- Maintain chain-of-custody and accountability
- Support NGO, community, and partner-led distribution models

---

## 2. Deployment Contexts

Seed field delivery supports multiple deployment environments:

- Rural villages with no banking access
- Refugee camps or displacement zones
- Disaster response regions
- Informal urban economies
- NGO-led microfinance pilots
- Community savings group rollouts

Each context may require different logistics partners but follows the same core workflow.

---

## 3. Pre-Delivery Preparation

Before devices enter the field:

- Devices are provisioned with:
  - Unique device ID
  - Cryptographic identity keys
  - Region-specific radio configuration
  - Default language packs
- Firmware version is verified and logged
- Battery is charged to safe transport level
- Tamper seals are applied if required
- Packaging includes:
  - Device
  - Quick-start guide (icon-based)
  - Solar or hand-crank accessory (if applicable)

A delivery manifest is generated listing all device IDs.

---

## 4. Distribution Models

Seed supports multiple delivery paths:

### NGO or Partner Distribution
- Devices shipped in bulk to partner organizations
- Partners distribute devices during onboarding sessions
- Partner logs device handoff locally or on paper

### Community Agent Distribution
- Trusted local agents receive batches of devices
- Agents distribute devices to individuals or groups
- Incentives may be tied to successful activation

### Direct Field Deployment
- Seed team or contractors deliver devices directly
- Used in pilot programs or research deployments

---

## 5. Handoff Process

At the point of delivery:

- Recipient receives device and accessories
- Agent explains:
  - Powering the device
  - Basic navigation
  - Security principles (do not share fingerprint)
- Device ID is recorded alongside:
  - Recipient name or alias
  - Group or village identifier
- No internet connection is required

Paper-based fallback logs are supported where digital tools are unavailable.

---

## 6. Device Activation in the Field

Activation is designed to be offline-first:

- User powers on device
- User enrolls fingerprint or PIN
- Initial wallet state is created locally
- Device joins local mesh when other devices are nearby
- Optional:
  - Group savings enrollment
  - Trust score initialization via group endorsement

Activation does not require external servers.

---

## 7. Verification and Confirmation

Field verification methods include:

- Visual confirmation by agent
- Test transaction between two devices
- Mesh handshake confirmation
- Optional signed activation receipt stored locally

If no other devices are present, activation is deferred until first mesh contact.

---

## 8. Post-Delivery Support

Support mechanisms include:

- Local support agents trained on:
  - Battery care
  - Reset procedures
  - Lost or stolen device protocol
- Printed or pictorial guides
- Periodic in-person check-ins
- Mesh-based update propagation when connectivity allows

No call centers or internet-based support is assumed.

---

## 9. Failure and Exception Handling

Common issues and responses:

- Device does not power on:
  - Replace unit from spare stock
- Device lost or stolen:
  - Trigger emergency wipe on next mesh contact
- User unable to authenticate:
  - Community re-verification process
- Delivery delays:
  - Staggered rollout with local storage of devices

All failures are logged when possible for audit and improvement.

---

## 10. Data and Accountability

Delivery data collected may include:

- Device ID
- Deployment region
- Distribution partner
- Activation date (approximate)
- Failure reports (non-personal)

Personal data collection is minimized to protect user privacy.

---

## 11. Scalability Considerations

The field delivery workflow is designed to scale by:

- Using decentralized agents
- Avoiding centralized activation servers
- Supporting offline-first record keeping
- Allowing gradual network formation

This enables Seed to grow from pilot programs to national-scale deployments.

---

## 12. Summary

Seed’s field delivery workflow enables secure, accountable distribution of financial devices in environments where traditional logistics and banking systems fail. By emphasizing offline activation, local trust networks, and simple processes, Seed ensures real-world usability from the first day of deployment.
