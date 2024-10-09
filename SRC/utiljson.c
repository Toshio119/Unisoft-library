#include "utilJson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
===================================================
       U!nisoft Libarary's 
       Utility at it's peak
---------------------------------------------------
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##             ##   #
  ##    ##  ##   ##        ##   ##   #
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##        ##   ##   #
  ##    ##       ##        ##   ##   #
    ####    ##   ########  ##   #####
---------------------------------------------------
© 2024 Unisoft .All rights reserved.
For support, contact: toshiojp119@gmail.com
===================================================
*/

// Helper function to find the length of a JSON string up to the next delimiter
static size_t json_strlen(const char *str) {
    size_t len = 0;
    while (str[len] && str[len] != ',' && str[len] != '}') {
        ++len;
    }
    return len;
}

// Helper function to trim quotes from a JSON string
static char *trim_quotes(const char *str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        char *trimmed = malloc(len - 1);
        if (trimmed) {
            strncpy(trimmed, str + 1, len - 2);
            trimmed[len - 2] = '\0';
        }
        return trimmed;
    }
    return strdup(str);
}

// Parse JSON string into a JsonArray
JsonArray *parse_json(const char *json_str) {
    if (!json_str || json_str[0] != '{' || json_str[strlen(json_str) - 1] != '}') {
        return NULL; // Invalid JSON format
    }

    JsonArray *json_array = malloc(sizeof(JsonArray));
    if (!json_array) return NULL;

    json_array->num_objects = 0;
    json_array->objects = NULL;

    const char *ptr = json_str + 1; // Skip the opening '{'
    while (*ptr && *ptr != '}') {
        // Skip whitespace
        while (*ptr == ' ' || *ptr == '\t') ++ptr;

        // Extract key
        size_t key_len = json_strlen(ptr);
        char *key = trim_quotes(ptr);
        if (!key) {
            free(json_array);
            return NULL;
        }
        ptr += key_len + 1; // Skip past the key and the ':'

        // Extract value
        while (*ptr == ' ' || *ptr == '\t') ++ptr;
        size_t value_len = json_strlen(ptr);
        char *value = trim_quotes(ptr);
        if (!value) {
            free(key);
            free(json_array);
            return NULL;
        }
        ptr += value_len;

        // Allocate and store the JsonObject
        JsonObject *temp_objects = realloc(json_array->objects, sizeof(JsonObject) * (json_array->num_objects + 1));
        if (!temp_objects) {
            free(key);
            free(value);
            free(json_array->objects);
            free(json_array);
            return NULL;
        }
        json_array->objects = temp_objects;

        json_array->objects[json_array->num_objects].key = key;
        json_array->objects[json_array->num_objects].value = value;
        ++json_array->num_objects;

        // Skip comma and whitespace
        while (*ptr == ',' || *ptr == ' ' || *ptr == '\t') ++ptr;
    }

    return json_array;
}

// Generate JSON string from JsonArray
char *generate_json(const JsonArray *json_array) {
    if (!json_array || json_array->num_objects == 0) return strdup("{}");

    size_t buffer_size = 256;
    char *json_str = malloc(buffer_size);
    if (!json_str) return NULL;

    size_t offset = 0;
    offset += snprintf(json_str + offset, buffer_size - offset, "{");

    for (size_t i = 0; i < json_array->num_objects; ++i) {
        if (offset + strlen(json_array->objects[i].key) + strlen(json_array->objects[i].value) + 10 > buffer_size) {
            buffer_size *= 2;
            char *new_str = realloc(json_str, buffer_size);
            if (!new_str) {
                free(json_str);
                return NULL;
            }
            json_str = new_str;
        }
        offset += snprintf(json_str + offset, buffer_size - offset, "\"%s\": \"%s\"%s",
                           json_array->objects[i].key, json_array->objects[i].value,
                           (i < json_array->num_objects - 1) ? ", " : "");
    }

    snprintf(json_str + offset, buffer_size - offset, "}");
    return json_str;
}

// Free memory allocated for JsonArray
void free_json_array(JsonArray *json_array) {
    if (!json_array) return;
    for (size_t i = 0; i < json_array->num_objects; ++i) {
        free(json_array->objects[i].key);
        free(json_array->objects[i].value);
    }
    free(json_array->objects);
    free(json_array);
}
