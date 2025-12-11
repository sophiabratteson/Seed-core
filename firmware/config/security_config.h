#ifndef SECURITY_CONFIG_H
#define SECURITY_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Seed Security Configuration
 * ---------------------------
 * This header defines the core security configuration for a Seed device.
 * It does NOT contain secret keys itself; instead it describes:
 *
 *  - Which crypto algorithms are used
 *  - What protections are enabled (secure boot, flash encryption, etc.)
 *  - How device identity and mesh message signing are handled
 *  - Policy knobs for lockouts, key rotation, and emergency wipe
 *
 * The actual secret material (private keys, HSM/secure-element blobs, etc.)
 * is stored in protected flash or in a dedicated secure chip.
 *
 * This file is designed to be:
 *  - Easy to read for auditors, investors, and hardware partners
 *  - Stable across firmware releases
 *  - Flexible enough to support different markets and regulations
 */


// -----------------------------------------------------------------------------
// Limits & constants
// -----------------------------------------------------------------------------

// Human-readable device identifier, e.g. "seed-node-00123"
#define SEED_DEVICE_ID_MAX_LEN        32

// Network / community identifier (e.g. village, coop, pilot ID)
#define SEED_NETWORK_ID_MAX_LEN       16

// Maximum length for region / jurisdiction code (e.g. "KE", "IN", "BR")
#define SEED_REGION_CODE_MAX_LEN      8

// Default lockout thresholds
#define SEED_DEFAULT_MAX_FAILED_AUTH_ATTEMPTS   5
#define SEED_DEFAULT_LOCKOUT_WINDOW_SECONDS     300   // 5 minutes

// Default key rotation interval (can be overridden per deployment)
#define SEED_DEFAULT_KEY_ROTATION_HOURS         24U * 90U   // ~90 days


// -----------------------------------------------------------------------------
// Crypto suite selection
// -----------------------------------------------------------------------------

typedef enum
{
    SEED_CRYPTO_SUITE_NONE = 0,

    // Curve25519 / Ed25519 ↔ good for low-power secure devices
    SEED_CRYPTO_SUITE_X25519_CHACHA20_POLY1305 = 1,

    // NIST P-256 variant (if required by regulators / partners)
    SEED_CRYPTO_SUITE_P256_AES_GCM = 2

} seed_crypto_suite_t;


// -----------------------------------------------------------------------------
// Key & identity configuration
// -----------------------------------------------------------------------------

/*
 * A Seed device always has:
 *  - A unique device_id (human readable)
 *  - A unique device keypair for signing/auth
 *  - Optionally, a secure element that protects those keys
 *
 * Public keys are stored here; corresponding private keys are
 * stored in protected memory or a secure element.
 */

typedef struct
{
    // Human-readable identity: stable across the life of the device.
    // Example: "seed-kenya-pilot-node-0001"
    char     device_id[SEED_DEVICE_ID_MAX_LEN];

    // Logical network / deployment / pilot identifier.
    // Example: "KE_PILOT1", "REFUGEE_CAMP_A"
    char     network_id[SEED_NETWORK_ID_MAX_LEN];

    // Country/region code for regulatory/profile selection.
    // Example: "KE", "IN", "US"
    char     region_code[SEED_REGION_CODE_MAX_LEN];

    // Which cryptographic algorithms to use for signatures + encryption.
    seed_crypto_suite_t crypto_suite;

    // Device long-term public identity key (for signatures / auth).
    // For X25519/Ed25519 this is 32 bytes.
    uint8_t device_public_key[32];

    // Optional network-level public key, if messages are signed
    // by a “network authority” for special use-cases.
    uint8_t network_public_key[32];

    // Indicates whether this device uses a discrete secure element chip
    // (e.g., ATECC608A) for private key storage and crypto ops.
    bool    has_secure_element;

} seed_identity_config_t;


// -----------------------------------------------------------------------------
// Security policy flags
// -----------------------------------------------------------------------------

typedef struct
{
    // Boot & firmware integrity
    bool require_secure_boot;          // Enforce signed bootloader
    bool require_signed_firmware;      // Only run signed firmware images
    bool enable_rollback_protection;   // Prevent reverting to old, vulnerable firmware

    // Storage protections
    bool enable_flash_encryption;      // Encrypt ledger and sensitive data at rest
    bool enable_config_encryption;     // Encrypt config blobs stored in flash
    bool enable_secure_erase;          // Overwrite on deletion / wipe

    // Mesh message protections
    bool enable_mesh_message_signing;  // Sign all outbound mesh packets
    bool require_mesh_sig_verification;// Verify signatures on inbound mesh packets
    bool enable_replay_protection;     // Track nonces / counters to block replay attacks

    // Authentication / local access
    bool require_fingerprint_for_unlock;   // Require fingerprint to unlock device
    bool require_pin_for_critical_ops;     // Require PIN for sending funds / wiping device

    // Emergency / high-risk contexts
    bool enable_emergency_wipe_feature;    // Allow secret “panic” wipe gesture / code
    bool hide_sensitive_ui_in_high_risk_region; // Reduce on-screen sensitive info in certain regions

} seed_security_policy_t;


// -----------------------------------------------------------------------------
// Lockout & key-lifecycle policy
// -----------------------------------------------------------------------------

typedef struct
{
    // Authentication lockout
    uint8_t  max_failed_auth_attempts;     // Before temporary lockout
    uint32_t lockout_window_seconds;       // How long to lock out after threshold

    // Device-wide lock after repeated abuse (optional)
    uint8_t  max_lockout_cycles;           // Number of lockouts before long ban (0 = disable)

    // Key rotation
    uint32_t key_rotation_interval_hours;  // Suggested interval for rotating session keys
    bool     require_rotation_after_update;// Rotate keys after firmware update

    // Ledger / backup checkpoints
    uint32_t checkpoint_interval_txs;      // Create signed ledger checkpoint every N transactions
    uint32_t backup_interval_hours;        // Recommended sync/backup interval

} seed_lifecycle_policy_t;


// -----------------------------------------------------------------------------
// Top-level security configuration object
// -----------------------------------------------------------------------------

typedef struct
{
    seed_identity_config_t  identity;   // Who this device is
    seed_security_policy_t  policy;     // What protections are turned on
    seed_lifecycle_policy_t lifecycle;  // How keys & lockouts behave

    // Versioning to keep track of config schema changes
    uint16_t config_version;           // Increment when struct layout changes
    uint16_t reserved;                 // Padding / future use

} seed_security_config_t;


// -----------------------------------------------------------------------------
// Global config instance
// -----------------------------------------------------------------------------

/*
 * g_security_config
 *
 * - Lives in RAM; populated at boot from secure storage / factory settings.
 * - May be partially overridden by region-specific profiles.
 * - NEVER write private keys directly into this struct in production;
 *   this is for public keys and policy only.
 */
extern seed_security_config_t g_security_config;


// -----------------------------------------------------------------------------
// API functions
// -----------------------------------------------------------------------------

/*
 * Initialize g_security_config with safe defaults.
 * This should be called early in the boot process before
 * any crypto operations are performed.
 */
void security_config_load_defaults(void);

/*
 * Load security configuration from non-volatile storage.
 * Returns true on success, false if config is missing or invalid.
 */
bool security_config_load_from_flash(void);

/*
 * Persist the current g_security_config to flash (or secure element).
 * Returns true on success, false on error.
 */
bool security_config_save_to_flash(void);

/*
 * Validate a candidate configuration before applying it.
 * Checks for:
 *  - Non-empty device_id / network_id
 *  - Supported crypto_suite value
 *  - Reasonable bounds on lockout and rotation intervals
 */
bool security_config_is_valid(const seed_security_config_t *cfg);

/*
 * Apply region-specific overrides (e.g., different crypto suite or
 * lockout policy for certain regulatory environments).
 */
void security_config_apply_region_profile(const char *region_code);

#endif // SECURITY_CONFIG_H
