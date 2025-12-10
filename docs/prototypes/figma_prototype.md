# Figma Prototype Plan

The Figma prototype represents the first visual and interactive demonstration of Seed’s offline-first financial ecosystem. It provides a realistic preview of the user experience (UX), interaction flow, and core system behaviors. This prototype is not intended to represent final hardware constraints, but instead to validate usability, communication clarity, and feature prioritization.

---

## 1. Goals of the Figma Prototype

- Demonstrate the Seed device interface in a clean, intuitive, culturally neutral way.
- Validate user flows for sending money, receiving money, joining a group savings pod, and viewing trust scores.
- Provide a visual reference for hardware engineers designing the physical interface.
- Provide an early investor-ready demo showing what the Seed experience will feel like in real life.
- Create a shared visual language to align the software, hardware, and UX teams.

---

## 2. Included Screens

### 2.1 Home Dashboard
- Balance display
- Trust Score indicator
- Quick actions (Send / Receive / Group Savings / History)
- Battery and signal indicator (LoRa mesh strength)

### 2.2 Send Money Flow
- Select recipient (ID number or nearby mesh contact)
- Enter amount
- Confirmation screen showing:
  - sender ID
  - receiver ID
  - amount
  - projected trust score effect
- Success animation + transaction ID

### 2.3 Receive Money Flow
- Device displays a ready-to-receive signal
- Sender confirmation handshake
- Success confirmation with transaction details

### 2.4 Transaction History
- Chronological list of all validated transactions
- Pending transactions (awaiting sync)
- Failed/conflicted transactions with explanations

### 2.5 Group Savings Pod
- Create or join group
- View pot balance
- Weekly contribution schedule
- Rotation order for payouts
- Trust-weighted voting for withdrawals

### 2.6 Trust Score Page
- Overview of user’s trust score
- Factors contributing to trust changes
- Visual timeline of improvements/drops
- Score components:
  - repayment reliability
  - contribution frequency
  - helpful relaying of mesh messages
  - network participation

### 2.7 Device Settings
- Language options
- Security settings (Fingerprint on/off, emergency wipe)
- Battery and power settings (solar, crank input indicators)

---

## 3. Interaction Requirements

- All screens must work on a **2.13-inch E-Ink display** aspect ratio.
- Typography must be readable at low DPI.
- Animations should simulate slow refresh rates of E-Ink.
- Buttons must be large enough for glove/finger use.
- Prototype interactions should introduce slight delays to mimic offline syncing behavior.
- All flows must be usable without reliance on color.

---

## 4. Figma Structure

### 4.1 Pages
- Wireframes
- High-Fidelity UI
- User Flows
- Prototype Interactions
- Developer Handoff (measurements, CSS-like specs)

### 4.2 Components
- Seed UI Kit:
  - headers
  - buttons
  - list items
  - input fields
  - modal windows
  - icons (mesh signal, battery, fingerprint, lock, group pot)
- Templates:
  - single-column layout
  - confirmation frame
  - error/state message frame

### 4.3 Styles
- Black/white/gray palette optimized for e-ink
- Monospace font options for clarity
- No gradients or shadows

---

## 5. User Flow Mapping

### Required map diagrams:
1. Home → Send → Confirm → Success  
2. Home → Receive → Success  
3. Home → Group Savings → Contribute → Confirm  
4. Home → Trust Score → Score Breakdown  
5. Home → Settings → Security/Emergency Wipe  

Each flow should include:
- decision points
- validation states
- offline pending states
- error messaging

---

## 6. Prototype Scenarios for Demonstration

### Scenario A: Two people exchanging money offline
- Show the “pending sync” indicator
- Show ledger updating after simulated mesh sync

### Scenario B: Group savings payout rotation
- Create group
- Show contributions accumulating
- Show payout animation

### Scenario C: Trust score adjustment after repayment
- Repay microloan
- Updated trust score animation

### Scenario D: Device locked and unlocked via fingerprint
- Authentication flow
- Emergency wipe flow preview

---

## 7. Accessibility Considerations

- High contrast UI for bright sunlight
- Large tap targets
- Minimal text per screen
- Icons that work without language
- Support for right-to-left languages in future versions

---

## 8. Deliverables Checklist

- Completed high-fidelity screens for all core flows
- Interactive Figma prototype (clickable)
- Exported frame set as PNG/SVG for hardware team
- UX notes for engineers (explanations of transitions)
- Scripted narrative for investor demo walkthrough

---

## 9. Next Steps After Prototype Completion

- Conduct early usability testing with 3–5 target users
- Iterate based on comprehension and ease-of-use feedback
- Sync with hardware engineers to align physical button layout
- Sync with firmware team to ensure UI is implementable on e-ink
- Prepare video demo for pitch deck

---

## 10. Summary

The Figma prototype is a foundational asset for Seed’s product development and storytelling. It bridges the gap between concept and reality by showing how an offline-first financial device will feel in the hands of real users. It allows investors, engineers, and partners to visualize Seed’s mission: empowering people everywhere with simple, resilient, and decentralized financial tools.
