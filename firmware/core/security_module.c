/**
 * firmware/core/security_module.c
 *
 * High-level security orchestration for Seed devices.
 *
 * Responsibilities:
 *  - Manage device identity keys (public/private)
 *  - Sign and verify messages (transactions, mesh packets)
 *  - Provide hooks for encryption/decryption of data at rest
 *  - React to tamper events and trigger emergency wipe
 *  - Expose a simple API to the rest of the firmware
 *
 * NOTE: This is a reference / architectural implementation.
 * Real production code must use a proven crypto library and
 * a certified secure element. No cryptography here is final.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "security_config.h"     // high-level security settings (key sizes, flags)
#include "power_config.h"        // for safe shutdown on wipe, if needed
#include "device_config.h"       // device_id, region info, etc.

/* These are implemented elsewhere in firmware or drivers */
extern bool secure_element_read_device_keys(uint8_t *pub_key_out,
                                            uint8_t *priv_key_placeholder_out);
extern bool secure_element_sign(const uint8_t *msg,
                                size_t msg_len,
                                uint8_t *sig_out,
                                size_t *sig_len_inout);
extern bool secure_element_random_bytes(uint8_t *buf, size_t len);

extern void storage_secure_wipe_ledger(void);
extern void storage_secure_wipe_user_data(void);
extern void storage_secure_wipe_keys_shadow(void);

/* -------------------------------------------------------------------------- */
/*  Types and global state                                                    */
/* -------------------------------------------------------------------------- */

#define SEED_PUBLIC_KEY_SIZE   32u    /* Example: Ed25519-sized public key */
#define SEED_PRIVATE_KEY_SIZE  64u    /* Stored only inside secure element */
#define SEED_SIGNATURE_MAX     64u    /* Max signature length for our scheme */

typedef enum {
    SECURITY_OK = 0,
    SECURITY_ERR_INIT = -1,
    SECURITY_ERR_KEY_LOAD = -2,
    SECURITY_ERR_SIGN = -3,
    SECURITY_ERR_VERIFY = -4,
    SECURITY_ERR_ENCRYPT = -5,
    SECURITY_ERR_DECRYPT = -6,
} security_status_t;

typedef enum {
    SECURITY_EVENT_TAMPER_PHYSICAL = 1,
    SECURITY_EVENT_TAMPER_FIRMWARE = 2,
    SECURITY_EVENT_FORCED_EMERGENCY_WIPE = 3,
} security_event_t;

typedef struct {
    char     device_id[DEVICE_ID_MAX_LEN];             /* from device_config.h */
    uint8_t  public_key[SEED_PUBLIC_KEY_SIZE];         /* used to identify device to mesh */
    uint8_t  private_key_shadow[SEED_PRIVATE_KEY_SIZE];/* placeholder; real keys stay in secure element */
    bool     keys_loaded;
    bool     tamper_detected;
    bool     last_boot_secure;
    uint32_t boot_counter;
} security_state_t;

static security_state_t g_sec_state;

/* -------------------------------------------------------------------------- */
/*  Internal helpers                                                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Zero sensitive buffers in a way compiler is less likely to optimize out.
 */
static void secure_memzero(volatile void *ptr, size_t len)
{
    volatile uint8_t *p = (volatile uint8_t *)ptr;
    while (len--) {
        *p++ = 0u;
    }
}

/**
 * @brief Stub for firmware integrity check (e.g., secure boot).
 *
 * In production, this would:
 *  - compute hash of firmware image
 *  - verify against signature stored in secure element or ROM
 */
static bool security_verify_firmware_integrity(void)
{
    /* TODO: integrate with secure boot chain.
     * For now we return true to indicate "boot looks OK".
     */
    return true;
}

/* -------------------------------------------------------------------------- */
/*  Public API                                                                */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize security module at boot.
 *
 *  - Loads device_id from config
 *  - Reads public/private keys from secure element
 *  - Verifies firmware integrity (secure boot)
 *  - Sets initial flags for tamper detection
 */
security_status_t security_init(void)
{
    memset(&g_sec_state, 0, sizeof(g_sec_state));

    /* Load device ID from static configuration */
    (void)device_config_get_id(g_sec_state.device_id, sizeof(g_sec_state.device_id));

    /* Load keys from secure element (public + private placeholder) */
    if (!secure_element_read_device_keys(g_sec_state.public_key,
                                         g_sec_state.private_key_shadow)) {
        g_sec_state.keys_loaded = false;
        return SECURITY_ERR_KEY_LOAD;
    }
    g_sec_state.keys_loaded = true;

    /* Verify firmware integrity (secure boot hook) */
    g_sec_state.last_boot_secure = security_verify_firmware_integrity();

    /* Increment boot counter (could be persisted in secure storage) */
    g_sec_state.boot_counter += 1;

    /* Clear tamper flag at boot; hardware tamper lines would set this later */
    g_sec_state.tamper_detected = false;

    /* Immediately zero out the private key shadow in RAM.
     * Real signing operations should use the secure element directly.
     */
    secure_memzero(g_sec_state.private_key_shadow, sizeof(g_sec_state.private_key_shadow));

    return SECURITY_OK;
}

/**
 * @brief Get pointer to device public key.
 *
 * @return pointer to internal buffer, valid as long as module is initialized.
 */
const uint8_t *security_get_public_key(void)
{
    return g_sec_state.public_key;
}

/**
 * @brief Sign a message using the device's private key (inside secure element).
 *
 * @param msg            pointer to message bytes
 * @param msg_len        length of message in bytes
 * @param sig_out        output buffer for signature
 * @param sig_len_inout  in: max buffer size, out: actual signature length
 *
 * @return SECURITY_OK on success or error code.
 */
security_status_t security_sign_message(const uint8_t *msg,
                                        size_t msg_len,
                                        uint8_t *sig_out,
                                        size_t *sig_len_inout)
{
    if (!g_sec_state.keys_loaded || msg == NULL || sig_out == NULL || sig_len_inout == NULL) {
        return SECURITY_ERR_SIGN;
    }

    if (!secure_element_sign(msg, msg_len, sig_out, sig_len_inout)) {
        return SECURITY_ERR_SIGN;
    }

    return SECURITY_OK;
}

/**
 * @brief Very simple placeholder "encryption" API.
 *
 * In production, this should be replaced by:
 *  - AES-GCM or ChaCha20-Poly1305 via secure element / crypto library
 *  - Proper key derivation and nonce handling
 */
security_status_t security_encrypt_blob(const uint8_t *plaintext,
                                        size_t plaintext_len,
                                        uint8_t *ciphertext_out,
                                        size_t *ciphertext_len_inout)
{
    if (plaintext == NULL || ciphertext_out == NULL || ciphertext_len_inout == NULL) {
        return SECURITY_ERR_ENCRYPT;
    }

    /* NOTE: This is NOT real encryption—this is a stub. */
    if (*ciphertext_len_inout < plaintext_len) {
        return SECURITY_ERR_ENCRYPT;
    }

    for (size_t i = 0; i < plaintext_len; i++) {
        ciphertext_out[i] = (uint8_t)(plaintext[i] ^ 0xA5U);  /* XOR with fixed mask (demo only) */
    }
    *ciphertext_len_inout = plaintext_len;

    return SECURITY_OK;
}

security_status_t security_decrypt_blob(const uint8_t *ciphertext,
                                        size_t ciphertext_len,
                                        uint8_t *plaintext_out,
                                        size_t *plaintext_len_inout)
{
    if (ciphertext == NULL || plaintext_out == NULL || plaintext_len_inout == NULL) {
        return SECURITY_ERR_DECRYPT;
    }

    if (*plaintext_len_inout < ciphertext_len) {
        return SECURITY_ERR_DECRYPT;
    }

    /* Symmetric XOR "decryption" to match encrypt_blob stub. */
    for (size_t i = 0; i < ciphertext_len; i++) {
        plaintext_out[i] = (uint8_t)(ciphertext[i] ^ 0xA5U);
    }
    *plaintext_len_inout = ciphertext_len;

    return SECURITY_OK;
}

/* -------------------------------------------------------------------------- */
/*  Tamper & emergency wipe                                                   */
/* -------------------------------------------------------------------------- */

/**
 * @brief Handle a security-critical event.
 *
 * For example:
 *  - physical case open/tamper switch
 *  - secure boot failure
 *  - user-initiated emergency wipe gesture + fake fingerprint
 */
void security_handle_event(security_event_t event)
{
    switch (event) {
    case SECURITY_EVENT_TAMPER_PHYSICAL:
        g_sec_state.tamper_detected = true;
        /* In a real device, we might:
         *  - lock UI
         *  - require re-authentication
         *  - limit features until safe reset
         */
        break;

    case SECURITY_EVENT_TAMPER_FIRMWARE:
        g_sec_state.tamper_detected = true;
        /* Could restrict all financial actions until device is re-flashed
         * from a trusted source or verified at a kiosk.
         */
        break;

    case SECURITY_EVENT_FORCED_EMERGENCY_WIPE:
        /* Immediately drop into wipe routine. */
        security_emergency_wipe();
        break;

    default:
        /* Unknown event, ignore for now. */
        break;
    }
}

/**
 * @brief Emergency wipe routine.
 *
 * Triggered when:
 *  - User performs a special "panic" gesture + fake fingerprint.
 *  - Device detects high-risk physical tampering or coercion.
 *
 * Behavior:
 *  - Wipes local ledger and user data.
 *  - Clears any key shadows in normal flash.
 *  - Leaves secure element keys intact or optionally wiped depending on policy.
 */
void security_emergency_wipe(void)
{
    /* Flag so future boots know an emergency wipe occurred. */
    g_sec_state.tamper_detected = true;

    /* Wipe application-level data first. */
    storage_secure_wipe_ledger();
    storage_secure_wipe_user_data();
    storage_secure_wipe_keys_shadow();

    /* Zero any in-RAM sensitive material. */
    secure_memzero(&g_sec_state, sizeof(g_sec_state));

    /* In a real device, we might:
     *  - force a reboot
     *  - display a "factory reset" or decoy screen
     *  - require full re-provisioning at a trusted kiosk
     */
}

/* -------------------------------------------------------------------------- */
/*  Status helpers                                                            */
/* -------------------------------------------------------------------------- */

bool security_is_tampered(void)
{
    return g_sec_state.tamper_detected;
}

bool security_boot_was_secure(void)
{
    return g_sec_state.last_boot_secure;
}

uint32_t security_get_boot_counter(void)
{
    return g_sec_state.boot_counter;
}
