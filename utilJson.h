#ifndef UTIL_JSON_H
#define UTIL_JSON_H

#include <stdbool.h>

typedef struct {
    char *key;
    char *value;
} JsonObject;

typedef struct {
    JsonObject *objects;
    size_t num_objects;
} JsonArray;

JsonArray *parse_json(const char *json_str);
char *generate_json(const JsonArray *json_array);
void free_json_array(JsonArray *json_array);

#endif // UTIL_JSON_H
