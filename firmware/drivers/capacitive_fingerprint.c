/**
 * capacitive_fingerprint.c
 * -----------------------------------------
 * Seed Device – Capacitive Fingerprint Driver (High-Level Prototype)
 *
 * Purpose:
 *   - Interface with a low-power capacitive fingerprint sensor
 *   - Provide biometric enrollment, authentication, and secure matching
 *   - Integrate with Seed's secure element for anti-spoofing & replay protection
 *
 * Notes:
 *   - Hardware-agnostic prototype: works as a clean abstraction layer
 *   - Replace SENSOR_* functions with actual vendor SDK calls when hardware chosen
 */

#include "capacitive_fingerprint.h"
#include "security_module.h"
#include "safe_memory.h"
#include "device_config.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// -------------------------------------------
// Internal State
// -------------------------------------------

static bool sensor_initialized = false;
static uint8_t last_match_score = 0;

// -------------------------------------------
// Low-Level Hardware Stubs (to replace later)
// -------------------------------------------

static bool SENSOR_Init(void) {
    // TODO: Replace with real hardware init (I2C/SPI, IRQ pin, power-up timing)
    return true;
}

static bool SENSOR_CaptureImage(uint8_t *buffer, uint16_t *size_out) {
    // TODO: Replace with real capture function
    *size_out = 128; // placeholder image size
    memset(buffer, 0xAA, *size_out); 
    return true;
}

static bool SENSOR_ExtractTemplate(uint8_t *img, uint16_t img_size,
                                   uint8_t *templ, uint16_t *templ_size_out) {
    // TODO: Replace with real image → template algorithm
    *templ_size_out = 64;
    memset(templ, 0x55, *templ_size_out);
    return true;
}

static uint8_t SENSOR_CompareTemplates(uint8_t *templA, uint16_t a_size,
                                       uint8_t *templB, uint16_t b_size) {
    // TODO: Replace with real matching algorithm
    return 85; // "85/100" match score placeholder
}

// -------------------------------------------
// Public API
// -------------------------------------------

bool FP_Init(void) {
    if (sensor_initialized) return true;

    bool ok = SENSOR_Init();
    if (!ok) return false;

    sensor_initialized = true;
    return true;
}

bool FP_Enroll(uint8_t *out_encrypted_template,
               uint16_t *out_size) {

    if (!sensor_initialized) return false;

    uint8_t img_buf[256];
    uint16_t img_size = 0;

    if (!SENSOR_CaptureImage(img_buf, &img_size))
        return false;

    uint8_t templ_buf[128];
    uint16_t templ_size = 0;

    if (!SENSOR_ExtractTemplate(img_buf, img_size,
                                templ_buf, &templ_size))
        return false;

    // Encrypt template using secure element
    if (!SECURE_EncryptFingerprintTemplate(templ_buf, templ_size,
                                           out_encrypted_template, out_size))
        return false;

    // wipe sensitive memory
    SAFE_ZERO(templ_buf, sizeof(templ_buf));
    SAFE_ZERO(img_buf, sizeof(img_buf));

    return true;
}

bool FP_Authenticate(const uint8_t *reference_encrypted_template,
                     uint16_t ref_size) {

    if (!sensor_initialized) return false;

    uint8_t img_buf[256];
    uint16_t img_size = 0;

    if (!SENSOR_CaptureImage(img_buf, &img_size))
        return false;

    uint8_t live_templ[128];
    uint16_t live_size = 0;

    if (!SENSOR_ExtractTemplate(img_buf, img_size,
                                live_templ, &live_size))
        return false;

    // Decrypt reference template using secure element
    uint8_t ref_templ[128];
    uint16_t ref_decrypted_size = 0;

    if (!SECURE_DecryptFingerprintTemplate(reference_encrypted_template,
                                           ref_size,
                                           ref_templ,
                                           &ref_decrypted_size))
        return false;

    // Compare templates
    last_match_score = SENSOR_CompareTemplates(live_templ, live_size,
                                               ref_templ, ref_decrypted_size);

    // Cleanup memory
    SAFE_ZERO(live_templ, sizeof(live_templ));
    SAFE_ZERO(ref_templ, sizeof(ref_templ));
    SAFE_ZERO(img_buf, sizeof(img_buf));

    // Accept if score above threshold
    return last_match_score >= FP_MATCH_THRESHOLD;
}

uint8_t FP_GetLastMatchScore(void) {
    return last_match_score;
}
