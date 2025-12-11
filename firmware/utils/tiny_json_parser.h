/**
 * tiny_json_parser.h
 * Minimal JSON parser used in Seed firmware.
 *
 * Supports:
 *  - Extracting string values
 *  - Extracting integer values
 *
 * Does NOT support:
 *  - Arrays
 *  - Nested objects
 *  - Boolean / null parsing
 */

#ifndef TINY_JSON_PARSER_H
#define TINY_JSON_PARSER_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Extract a string field from simple JSON.
 */
bool json_get_string(const char* json,
                     const char* key,
                     char* out,
                     size_t out_len);

/**
 * Extract an integer field from simple JSON.
 */
bool json_get_int(const char* json,
                  const char* key,
                  int* out);

#endif
