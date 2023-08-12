#ifndef KITC_JSON_H
#define KITC_JSON_H

#include <stdbool.h>

typedef struct kitc_json_parse_result {
    bool is_ok;
} kitc_json_parse_result;

typedef enum kitc_json_type {
    KITC_JSON_TYPE_BOOL,
    KITC_JSON_TYPE_FLOAT,
    KITC_JSON_TYPE_INT,
    KITC_JSON_TYPE_STRING,
    KITC_JSON_TYPE_ARRAY,
    KITC_JSON_TYPE_OBJECT,
    KITC_JSON_TYPE_NULL
} kitc_json_type;

static const char *json_type_to_str[] = {
    "Bool", "Float"
};

/** @brief Entry function that takes JSON string and parses into */
kitc_json_parse_result kitc_json_parse(const char *raw_json);

#endif // KITC_JSON_H