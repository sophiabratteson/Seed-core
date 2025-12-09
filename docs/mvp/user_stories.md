# User Stories for MVP

This document defines the minimum-viable user behaviors Seed must support in its first functional prototype. User stories describe the product from the perspective of real people who would rely on Seed in low-connectivity, low-infrastructure environments. These stories guide hardware design, software development, ledger architecture, and UX flow.

---

# 1. Primary Users

- Individual worker or vendor
- Small shop owner
- Community savings group member
- Aid worker or NGO field coordinator
- Person without formal ID or bank access
- Person in a region with unstable electricity or internet

---

# 2. Core MVP User Stories

## 2.1 Create a Seed Identity
- As a new user, I want to power on the Seed device for the first time.
- I want to register myself with a simple onboarding flow.
- I want the device to generate a secure unique identity for me without requiring internet or a formal government ID.
- I want to unlock the device with a fingerprint or PIN so that only I can access my funds.

## 2.2 Add Initial Balance (Cash Onboarding)
- As a user holding physical cash, I want a trusted vendor or agent to deposit my cash into my Seed balance.
- I want both our Seed devices to reflect the updated balance through an offline mesh transfer.
- I want a confirmation message showing the updated balance even without internet access.

## 2.3 Send Money to Another Person
- As a user, I want to select a recipient nearby.
- I want to enter an amount and press send.
- I want the transaction to move directly from my device to theirs using the mesh radio.
- I want the ledger to update on both devices, even if no internet is available.
- I want a simple success message after the transfer completes.

## 2.4 Receive Money
- As a recipient, I want my Seed device to automatically detect an incoming payment.
- I want to confirm receipt and see my new balance.
- I want this confirmation even if the sender later goes offline.

## 2.5 View Transaction History
- As a user, I want to see a clear list of my past transactions.
- I want transactions to be readable and timestamped using local logical clocks, not internet time.
- I want the device to work even if I have been offline for weeks.

## 2.6 Participate in a Savings Group
- As a community member, I want to join a group savings pool.
- I want to contribute a fixed weekly amount using local offline transfers.
- I want the group pot to rotate fairly and predictably.
- I want transparency: I should be able to see contributions and payouts on my device.

## 2.7 Benefit From Trust Score
- As a user, I want my responsible activity to improve my trust score.
- I want the score to increase when I repay group loans, contribute consistently, or behave reliably in the mesh network.
- I want this score to be stored locally and synced offline.

## 2.8 Sync With Other Devices
- As a user, I want my device to automatically sync when near another Seed device.
- I want the device to reconcile transaction histories without requiring me to do anything.
- I want any pending offline activity to update once a new device is discovered.

## 2.9 Emergency Wipe
- As a user, I want to protect myself if someone steals my device.
- I want to activate a fake fingerprint or hidden gesture that displays dummy data.
- I want a deeper wipe option that protects my private keys.

## 2.10 Battery Survival Under Harsh Conditions
- As a user, I want my Seed device to operate with no electricity grid.
- I want to charge it using a hand crank or a small solar panel.
- I want the screen to stay readable even in bright sunlight and without using much power.

---

# 3. Expanded Secondary User Stories

## 3.1 Vendor Accepting Offline Payments
- As a street vendor, I want to accept payments quickly without waiting for internet.
- I want to view my earnings for the day.
- I want to cash out into physical currency when needed.

## 3.2 NGO Aid Distribution
- As an NGO worker, I want to distribute funds to households in remote areas.
- I want to ensure every recipient gets the correct amount.
- I want the device to track distribution even in disaster zones with zero connectivity.

## 3.3 Community Leader Facilitating Savings Groups
- As a community leader, I want to create savings circles.
- I want to track participation reliably.
- I want to ensure fairness even if a member’s device is offline for days.

---

# 4. Non-Functional User Expectations

These are expectations users will not explicitly ask for, but Seed must meet to succeed.

## Reliability
- The device should work even with low battery.
- Transactions should not disappear or get corrupted.

## Security
- Device identity should be secure and tamper resistant.
- Ledger entries must not be modifiable after creation.

## Ease of Use
- Buttons, menus, and screens must be simple and intuitive.
- Users with no digital literacy must still succeed.

## Offline First
- No user should ever feel blocked because of no internet or phone network.

---

# 5. MVP Success Criteria

Seed MVP is successful when:

- Two devices can reliably exchange funds offline.
- Ledger histories sync cleanly when devices meet.
- Group savings works for small real communities.
- Trust score updates correctly across devices.
- Devices function without electricity using solar or hand-crank charging.
- Users understand and trust the system.

---

# 6. Summary

These user stories define what the first Seed prototype must accomplish. The stories focus on real behavior in low-infrastructure environments and serve as the backbone for the device hardware, software, security model, and mesh protocol. Meeting these stories ensures Seed delivers immediate, meaningful value in its earliest form.
