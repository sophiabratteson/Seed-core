# Tier 1 Troubleshooting Guide

This document defines Tier 1 support procedures for Seed devices. Tier 1 support is designed to resolve the most common user issues quickly, safely, and offline-first, without requiring advanced technical tools or central infrastructure.

Tier 1 troubleshooting prioritizes:
- User safety
- Data integrity
- Minimal device downtime
- Non-technical resolution paths

Escalation to Tier 2 occurs only when Tier 1 actions cannot resolve the issue.

---

## 1. Scope of Tier 1 Support

Tier 1 support handles:
- Device power issues
- Display or input problems
- Transaction visibility confusion
- Mesh connectivity questions
- User authentication issues
- Suspected device loss or theft
- Basic trust score and group savings questions

Tier 1 does NOT:
- Modify firmware
- Access encrypted private data
- Override security protections
- Perform hardware repairs

---

## 2. Required Tools and Access

Tier 1 support requires:
- Physical access to the Seed device
- User consent
- No internet connection
- No external computers

Optional:
- Printed troubleshooting guide
- Visual indicator reference sheet

---

## 3. Power and Startup Issues

### Issue: Device does not turn on

Steps:
1. Ask user to charge device using:
   - Hand crank (minimum 60 seconds)
   - Solar panel (direct sunlight, 10–15 minutes)
2. Confirm battery indicator appears
3. Ask user to hold power button for 5 seconds
4. If no response:
   - Ask user to wait 10 minutes
   - Retry power-on

If unresolved:
- Mark as Tier 2 escalation

---

### Issue: Device turns on then shuts off

Steps:
1. Check battery level indicator
2. Ask user to recharge fully
3. Restart device
4. Observe if shutdown repeats

If repeated shutdown occurs:
- Log as battery or power subsystem issue
- Escalate to Tier 2

---

## 4. Display and Input Issues

### Issue: Screen is blank but device appears powered

Steps:
1. Ask user to press any navigation button
2. Ask user to power cycle device
3. Move device into brighter ambient light
4. Confirm screen refresh occurs

Notes:
- E-ink displays only update on state change
- Blank screen does not always indicate failure

---

### Issue: Buttons or fingerprint scanner not responding

Steps:
1. Ask user to clean input surface
2. Retry input slowly
3. Restart device
4. Attempt alternate navigation method (buttons vs fingerprint)

If input remains unresponsive:
- Escalate to Tier 2

---

## 5. Transaction and Balance Issues

### Issue: User believes money is missing

Steps:
1. Ask user to open transaction history
2. Review:
   - Pending transactions
   - Group savings contributions
   - Recent outgoing transfers
3. Explain pending vs confirmed status
4. Confirm device last sync time

Important:
- No funds are lost due to delayed sync
- Pending transactions resolve automatically during next mesh contact

---

### Issue: Transaction sent but recipient did not receive

Steps:
1. Confirm transaction appears as pending
2. Explain offline-first delivery model
3. Ask recipient to sync via mesh proximity
4. Confirm no duplicate transaction attempts

If unresolved after multiple syncs:
- Escalate to Tier 2

---

## 6. Mesh Connectivity Issues

### Issue: Device not discovering nearby Seed devices

Steps:
1. Ask user to move closer (within ~100–300 meters)
2. Ensure device is awake and not in low-power sleep
3. Restart device
4. Wait up to 2 minutes for discovery cycle

Notes:
- Mesh discovery is periodic to save power
- Dense environments may slow discovery

---

## 7. Authentication Issues

### Issue: Fingerprint not recognized

Steps:
1. Ask user to clean finger and scanner
2. Retry slowly and consistently
3. Use backup authentication method if available
4. Restart device

If fingerprint consistently fails:
- Escalate to Tier 2 for re-enrollment

---

## 8. Lost or Stolen Device (User Report)

Steps:
1. Confirm device identity and owner verbally
2. Ask user if emergency wipe was triggered
3. If device is lost:
   - Explain emergency wipe process
   - Mark device as compromised
4. Reassure user:
   - Funds and ledger integrity remain protected
   - Device cannot be accessed without biometric match

Immediate escalation to Tier 2 required.

---

## 9. Trust Score and Group Savings Questions

### Issue: User confused about trust score changes

Steps:
1. Explain trust score reflects:
   - Repayment behavior
   - Participation consistency
   - Network contribution
2. Show recent score-affecting events
3. Emphasize:
   - Trust score is not permanent
   - Improves through consistent behavior

---

### Issue: Group savings payout confusion

Steps:
1. Confirm group cycle and payout order
2. Review contribution history
3. Explain automatic rotation logic
4. Confirm no missed contributions

---

## 10. Resolution Outcomes

Tier 1 support outcomes must be logged as:
- Resolved
- User education provided
- Pending sync resolution
- Escalated to Tier 2

No Tier 1 action modifies cryptographic data or ledger state.

---

## 11. Escalation Criteria

Escalate to Tier 2 if:
- Device fails to power on after recharge
- Authentication permanently fails
- Ledger corruption suspected
- Hardware damage is visible
- User safety is at risk

---

## 12. Guiding Principles

Tier 1 support operates under:
- Offline-first assumptions
- User dignity and trust
- Minimal intervention
- Security-first design

The goal is to empower users, not control devices.

---

## 13. Summary

Tier 1 troubleshooting resolves the majority of Seed user issues without internet access, specialized tools, or invasive procedures. It reinforces Seed’s core promise: resilient, user-owned financial access in any environment.
