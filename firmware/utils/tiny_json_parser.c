/**
 * tiny_json_parser.c
 * Lightweight JSON parser for Seed firmware.
 *
 * Purpose:
 *  - Handle simple JSON messages inside Seed’s mesh and ledger engine.
 *  - Support key/value lookup, basic parsing, and small memory footprint.
 *
 * Limitations:
 *  - Only supports flat JSON objects: {"key":"value", "num":5}
 *  - No nested structures or arrays (keeps firmware lightweight)
 */

#include "tiny_json_parser.h"
#include <string.h>
#include <ctype.h>

/**
 * Skip whitespace characters.
 */
static const char* skip_ws(const char* s) {
    while (*s && isspace((unsigned char)*s)) s++;
    return s;
}

/**
 * Parse a quoted string into buffer.
 */
static const char* parse_string(const char* s, char* out, size_t out_len) {
    s = skip_ws(s);
    if (*s != '"') return NULL;
    s++;

    size_t i = 0;
    while (*s && *s != '"' && i < out_len - 1) {
        out[i++] = *s++;
    }
    if (*s != '"') return NULL;

    out[i] = '\0';
    return s + 1;
}

/**
 * Extract value for given key from simple JSON.
 */
bool json_get_string(const char* json, const char* key, char* out, size_t out_len) {
    char temp_key[64];
    const char* s = json;

    while ((s = strchr(s, '"')) != NULL) {
        s++;
        const char* end = strchr(s, '"');
        if (!end) return false;
        size_t len = end - s;
        if (len >= sizeof(temp_key)) return false;

        strncpy(temp_key, s, len);
        temp_key[len] = '\0';

        if (strcmp(temp_key, key) == 0) {
            const char* colon = strchr(end, ':');
            if (!colon) return false;

            return parse_string(colon + 1, out, out_len) != NULL;
        }

        s = end + 1;
    }

    return false;
}

/**
 * Parse integer value for given key.
 */
bool json_get_int(const char* json, const char* key, int* out) {
    char temp_key[64];
    const char* s = json;

    while ((s = strchr(s, '"')) != NULL) {
        s++;
        const char* end = strchr(s, '"');
        if (!end) return false;

        size_t len = end - s;
        strncpy(temp_key, s, len);
        temp_key[len] = '\0';

        if (strcmp(temp_key, key) == 0) {
            const char* colon = strchr(end, ':');
            if (!colon) return false;

            *out = atoi(colon + 1);
            return true;
        }

        s = end + 1;
    }

    return false;
}
