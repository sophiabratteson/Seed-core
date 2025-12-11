# Emergency Wipe Policy

This document defines the emergency wipe mechanism for Seed devices.  
Seed is designed for users in vulnerable environments, including conflict zones, unstable jurisdictions, refugee camps, and regions without reliable legal or digital protections. The emergency wipe system ensures that a user can immediately protect their financial data and identity if they face theft, coercion, or physical danger.

The policy covers the technical design, security guarantees, activation signals, user experience considerations, and post-wipe recovery workflows.

---

# 1. Purpose of Emergency Wipe

Seed devices may store sensitive information:
- Ledger entries reflecting income, savings, or loan history
- Trust-score evolution data
- Group savings participation logs
- Device identity keys
- Encryption keys for secure communication
- User profiles and optional AI coaching patterns

In hostile or high-risk environments, possession of such a device could endanger the user.  
Emergency wipe provides a fast, offline, irreversible way to secure the user’s data.

Goals:
- Prevent attackers or authorities from accessing private financial data
- Protect users during theft, extortion, or forced device inspection
- Retain user trust by ensuring complete autonomy over their information
- Preserve decentralized network integrity by invalidating compromised keys

---

# 2. Threat Model

Emergency wipe is intended to counter:
- Coercive inspection of device contents
- Physical seizure of the device
- Attempted extraction of private keys
- Attempts to force false transactions
- Adversaries with hardware access but limited time

Not in scope:
- Nation-state level lab extraction after disassembly
- Long-term forensic chip-level attacks (protected by secure element hardware)
- Remote wipe (Seed is offline-first and cannot rely on connectivity)

---

# 3. Activation Methods

Seed supports multiple wipe triggers so users can choose the safest option.

## 3.1 Fingerprint "duress print"
A fake fingerprint enrolled during setup that:
- Unlocks a decoy wallet
- Triggers silent wipe in background
- Shows plausible fake balances and dummy history

This protects the user if forced to unlock their device.

## 3.2 Button sequence
A hidden physical combination such as:
- Long-press power + double-tap side button
- Requires no UI interaction
- Works even if the screen is broken

## 3.3 Software-level gesture
From the UI:
- Triple-tap an invisible region of the screen
- Enter a duress PIN that looks like a normal PIN

## 3.4 Automatic wipe on tamper detection
Using hardware sensors:
- Secure element detects drilling, voltage glitching, or probing
- Device wipes immediately

---

# 4. What Gets Wiped

The emergency wipe procedure removes:
- Private keys (device identity keys, message signing keys)
- Ledger storage
- Trust score history
- AI personalization embeddings
- Cached group savings metadata
- Mesh neighbor tables
- Local configuration files
- User preferences
- Any unencrypted temporary memory

Data is destroyed using:
- Multiple overwrite cycles where possible
- Secure element key invalidation commands
- Rewriting flash with random noise

The wipe must finish within milliseconds to seconds.

---

# 5. What Does NOT Get Wiped

To protect network integrity:
- Public keys already distributed across the mesh remain known, but useless (identity becomes invalid)
- Network-level metadata stored on *other devices* remains untouched

No remote dependencies are required.

---

# 6. Post-Wipe Device State

After wiping:
- Device returns to factory-fresh mode
- Identity keys are gone
- Ledger is empty
- Trust score resets
- User must re-enroll fingerprint and identity
- Device receives new cryptographic identity on restart

This prevents impersonation of the wiped identity.

---

# 7. Decoy Mode (Optional)

Users may configure a second profile that:
- Stores fake ledger data
- Shows small amounts of “safe” money
- Behaves like a normal wallet
- Has no real communication with the mesh ledger

Purpose:
- Provide plausible deniability
- Reduce suspicion
- Avoid escalation in coercive situations

Decoy mode runs in isolation from real ledger storage.

---

# 8. Security Guarantees

Emergency wipe offers:
- Irreversibility: No attacker can undo the wipe once triggered.
- Offline functionality: No cloud or network access needed.
- Instant response: Designed to activate even under duress.
- Hardware-backed deletion: Secure element prevents forensic recovery.

Limitations:
- If device is wiped before syncing pending transactions, those transactions may be lost.
- Users must understand recovery requires re-identity onboarding.

---

# 9. Recovery Flow After Wipe

1. User restarts device.
2. Device begins first-time setup.
3. New device identity keys are generated.
4. A trusted group or partner organization may help reassign:
   - Previous trust score (optional)
   - Group savings role (optional)
   - Identity verification (community attestation approach)

Seed is intentionally decentralized, so recovery is based on community verification rather than central authorities.

---

# 10. Design Considerations

Emergency wipe must be:
- Extremely fast
- Impossible to trigger accidentally
- Impossible to cancel once started
- Safe to use in low-literacy and low-tech environments
- Clearly tested under physical stress conditions

UX principles:
- No visible indication that a wipe is in progress during duress mode
- Clear instructions during device onboarding
- Simple recovery flow

---

# 11. Testing Requirements

QA teams must perform:
- Forced duress print attempts
- Tamper sensor activation tests
- Power interruption during wipe tests
- Consistency checks to ensure no recoverable fragments remain
- Validation that decoy mode appears fully legitimate

Compliance:
- Align with privacy regulations (GDPR-like principles)
- Align with humanitarian data-protection standards

---

# 12. Summary

The emergency wipe protocol ensures Seed users remain safe even in high-risk environments.  
By combining tamper-resistant hardware, offline-first cryptography, and user-friendly duress triggers, Seed guarantees that no attacker can extract sensitive information from a seized device.

This feature is central to Seed’s mission: empowering vulnerable communities with financial autonomy, while protecting them from coercion and surveillance.
