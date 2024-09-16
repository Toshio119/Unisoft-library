#ifndef UTILXML_H
#define UTILXML_H

#include <stddef.h> // For size_t
#include <stdbool.h> // For bool

// Define a structure for XML elements
typedef struct {
    // You can define fields as needed
    char *tag;
    char *content;
} XmlElement;

// Function prototypes
XmlElement *parse_xml(const char *xml_str, size_t *num_elements);
char *generate_xml(const XmlElement *elements, size_t num_elements);
void free_xml_elements(XmlElement *elements, size_t num_elements);

#endif // UTILXML_H
