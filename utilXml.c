#include "utilXml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t calculate_xml_buffer_size(const XmlElement *elements, size_t num_elements) {
    size_t size = 0;
    for (size_t i = 0; i < num_elements; ++i) {
        size += strlen(elements[i].tag) + strlen(elements[i].content) + 10; // Extra for tags and formatting
    }
    return size;
}

XmlElement *parse_xml(const char *xml_str, size_t *num_elements) {
    // Simplified parsing logic for demonstration
    // A real parser would handle nested tags and attributes

    *num_elements = 1; // Example count
    XmlElement *elements = malloc(sizeof(XmlElement) * (*num_elements));
    if (!elements) return NULL;

    elements[0].tag = strdup("tag");
    elements[0].content = strdup("content");

    return elements;
}

char *generate_xml(const XmlElement *elements, size_t num_elements) {
    size_t buffer_size = calculate_xml_buffer_size(elements, num_elements);
    char *xml_str = malloc(buffer_size);
    if (!xml_str) return NULL;

    size_t offset = 0;
    for (size_t i = 0; i < num_elements; ++i) {
        int written = snprintf(xml_str + offset, buffer_size - offset, "<%s>%s</%s>",
                               elements[i].tag, elements[i].content, elements[i].tag);
        if (written < 0 || (size_t)written >= buffer_size - offset) {
            free(xml_str);
            return NULL;
        }
        offset += written;
    }

    return xml_str;
}

void free_xml_elements(XmlElement *elements, size_t num_elements) {
    if (!elements) return;
    for (size_t i = 0; i < num_elements; ++i) {
        free(elements[i].tag);
        free(elements[i].content);
    }
    free(elements);
}
