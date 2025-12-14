# Adoption and Churn Scenarios

This document models how users adopt, engage with, and potentially disengage from the Seed ecosystem over time. Because Seed operates in low-connectivity, low-trust, and informal economic environments, adoption and churn dynamics differ significantly from traditional fintech products. These scenarios help evaluate network growth, resilience, and long-term sustainability.

---

## 1. Purpose of This Simulation

The adoption and churn simulation exists to:

- Understand how Seed spreads through communities without centralized onboarding.
- Identify risks that cause users to stop using the device.
- Test whether the network remains functional under partial abandonment.
- Inform trust-score decay, group savings stability, and hardware deployment strategies.
- Support investor evaluation of real-world adoption realism.

---

## 2. User Lifecycle Stages

Each Seed user progresses through the following lifecycle stages:

- **Unaware**: Has not encountered Seed.
- **Introduced**: Learns about Seed through another user, NGO, or pilot.
- **Activated**: Receives a Seed device and completes first transaction.
- **Engaged**: Uses Seed regularly for payments, savings, or groups.
- **Dormant**: Device remains owned but used infrequently.
- **Churned**: Device unused or abandoned.
- **Reactivated** (optional): Returns after dormancy via re-training or group incentives.

These stages are not linear and allow backward movement.

---

## 3. Adoption Scenarios

### Scenario A: Organic Peer-to-Peer Adoption

- Initial seed users distribute value directly to others.
- New users adopt Seed when:
  - They receive money via Seed.
  - They participate in group savings.
  - They transact with a vendor using Seed.

Key characteristics:
- Slow but stable growth.
- High trust alignment.
- Strong local network density.

Risk:
- Growth limited by physical proximity and device availability.

---

### Scenario B: NGO-Led Pilot Deployment

- Devices distributed through humanitarian or development programs.
- Users trained in small cohorts.
- Adoption driven by external facilitator.

Key characteristics:
- Fast early adoption.
- High initial engagement.
- Strong documentation and oversight.

Risk:
- Engagement drops if NGO support ends.
- Users may not fully internalize ownership.

---

### Scenario C: Vendor-Led Adoption

- Vendors act as local anchors.
- Customers adopt Seed to transact with trusted merchants.

Key characteristics:
- Rapid transactional growth.
- High daily usage.
- Strong incentive alignment.

Risk:
- Vendor churn can collapse local networks.
- Power imbalance if vendor dominates trust flow.

---

### Scenario D: Emergency or Disaster Adoption

- Seed used during network outages or displacement.
- Temporary but intense adoption.

Key characteristics:
- Extremely high short-term usage.
- Fast trust formation.
- Low onboarding friction.

Risk:
- High post-crisis churn.
- Devices may be resold or lost.

---

## 4. Churn Scenarios

### Scenario E: Hardware Failure or Loss

- Battery degradation.
- Screen damage.
- Device theft.

Impact:
- Sudden churn.
- Trust-score freeze.
- Potential group savings disruption.

Mitigation:
- Emergency wipe.
- Group-based recovery logic.
- Hardware replacement workflows.

---

### Scenario F: Trust Breakdown

- Perceived fraud.
- Group savings conflict.
- Misunderstood trust-score penalties.

Impact:
- Social churn (multiple users disengage).
- Network fragmentation.

Mitigation:
- Transparent ledger explanations.
- Local mediation protocols.
- Trust-score recovery paths.

---

### Scenario G: Economic Inactivity

- Seasonal income loss.
- Migration.
- Reduced financial need.

Impact:
- Dormancy rather than permanent churn.
- Low network activity but preserved state.

Mitigation:
- Trust-score decay instead of deletion.
- Reactivation via group invitations.

---

## 5. Quantitative Simulation Parameters

The following parameters are adjustable in simulation runs:

- Monthly adoption rate per active user.
- Average transactions per user per week.
- Probability of dormancy after inactivity.
- Churn probability per failure event.
- Reactivation probability per outreach.

These parameters allow modeling of both optimistic and conservative growth curves.

---

## 6. Network-Level Effects of Churn

The simulation evaluates:

- Minimum viable node density for ledger convergence.
- Impact of partial churn on mesh connectivity.
- Group savings survival thresholds.
- Trust-score inflation or decay under population loss.

Key insight:
Seed remains functional even when a large percentage of users churn, as long as local clusters persist.

---

## 7. Example Timeline Simulation

Month 1:
- 10 initial users
- 2 group savings pools
- High engagement

Month 3:
- 35 users
- 10% dormancy
- One vendor anchor

Month 6:
- 80 users
- 25% churn
- Ledger convergence maintained
- 90% group completion success

---

## 8. Failure Stress Tests

Simulated stress cases include:

- 50% user churn within 30 days.
- Vendor exit.
- NGO withdrawal.
- Device recall scenario.

Results show:
- Ledger integrity remains intact.
- Trust-score logic stabilizes behavior.
- Recovery possible without central authority.

---

## 9. Design Implications

Insights from adoption and churn simulations inform:

- Device pricing strategy.
- Replacement and recycling programs.
- Trust-score decay rules.
- Group savings design constraints.
- Training and onboarding materials.

---

## 10. Investor-Relevant Takeaways

- Seed adoption mirrors real-world social trust, not app virality.
- Churn does not collapse the system due to offline-first design.
- Growth is slower but more durable than centralized fintech.
- The system tolerates loss without requiring rescue infrastructure.

---

## 11. Summary

Seed is designed for environments where adoption is gradual, trust-driven, and resilient to churn. By modeling realistic user behavior — including failure, disengagement, and reactivation — this simulation demonstrates that Seed can grow sustainably without relying on continuous connectivity, centralized enforcement, or perfect user retention.
