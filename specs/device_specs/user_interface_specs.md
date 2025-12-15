# User Interface Specifications

This document defines the user interface (UI) specifications for the Seed device. The UI is designed for extreme accessibility, low power consumption, and operation in environments with limited literacy, connectivity, and infrastructure. The interface must be intuitive, resilient, and usable by first-time users without formal technical training.

---

## 1. Design Principles

- **Offline-first:** All core functions must work without internet access.
- **Low power:** UI must minimize energy usage to preserve battery life.
- **Universal access:** Designed for users with limited literacy, vision challenges, or disabilities.
- **Trust & clarity:** Financial actions must be clearly communicated and hard to misuse.
- **Consistency:** Identical interactions across all Seed devices to reduce confusion.

---

## 2. Display Specifications

### Display Type
- E-Ink (electrophoretic display)
- Size: 2.13"–2.9" recommended for readability
- Resolution: Minimum 250 × 122 pixels
- Monochrome (black/white)
- Non-backlit (optional front-light in future versions)

### Display Behavior
- Static content consumes zero power
- Full refresh only when state changes
- Partial refresh supported for menus and counters
- Screen readable in direct sunlight

---

## 3. Input Methods

### Primary Inputs
- Physical buttons (minimum 3, maximum 5)
  - Up / Down
  - Select / Confirm
  - Back / Cancel
  - Optional: Emergency / Power

### Biometric Input
- Capacitive fingerprint scanner
- Used for:
  - Device unlock
  - Transaction confirmation
  - Identity verification

### Input Constraints
- All actions must be possible using buttons only
- No reliance on touchscreen gestures
- Long-press vs short-press behavior clearly defined

---

## 4. Interaction Model

### Navigation
- Linear, menu-based navigation
- No nested menus deeper than 3 levels
- Clear "Back" option at all times

### Confirmation Flow
- Every financial action requires:
  1. Review screen
  2. Explicit confirmation
  3. Biometric or button-based approval

### Error Handling
- Clear visual error messages
- No technical jargon
- Suggested corrective action displayed

---

## 5. Core UI Screens

### Home Screen
- Current balance
- Trust score indicator
- Network sync status
- Battery level

### Transaction Screens
- Send money
- Receive money
- Transaction history (last N actions)
- Pending transactions

### Group Savings Screens
- Group overview
- Contribution status
- Next payout indicator
- Member trust indicators

### Settings Screens
- Language selection
- Volume/audio cues
- Security preferences
- Device status

---

## 6. Accessibility Features

- Icon-first UI with minimal text
- Audio prompts for:
  - Transaction confirmation
  - Errors
  - Navigation guidance
- Multi-language support (stored locally)
- High-contrast display mode
- Optional haptic feedback (future)

---

## 7. Language & Localization

- UI strings stored locally
- Supports:
  - Multiple scripts
  - Right-to-left languages
- Language selectable during initial setup
- No internet required for translation

---

## 8. Security & Privacy UX

- Sensitive data never displayed in full
- Partial masking for balances and IDs
- Emergency decoy mode:
  - Alternate fingerprint shows fake data
- Clear indication when device is locked/unlocked
- No visible private keys or identifiers

---

## 9. Power-Aware UI Behavior

- UI sleeps automatically after inactivity
- Reduced refresh rate on low battery
- Power warnings before shutdown
- UI available during charging and hand-crank input

---

## 10. Failure & Recovery States

- Graceful degradation if:
  - Fingerprint sensor fails
  - Display refresh fails
  - Power is critically low
- Recovery instructions shown on screen
- No data loss due to UI failure

---

## 11. Future UI Extensions (Non-MVP)

- QR-like visual codes for assisted syncing
- Companion phone app (optional)
- Larger displays for kiosks
- Voice-first interface mode

---

## 12. Summary

The Seed UI is intentionally minimal, robust, and inclusive. It prioritizes trust, clarity, and usability over visual complexity, enabling financial participation in environments where traditional digital interfaces fail. The UI is a core trust surface and must remain simple, deterministic, and energy-efficient.

This specification defines the baseline for all Seed device interfaces and ensures consistency across hardware revisions and deployment regions.
