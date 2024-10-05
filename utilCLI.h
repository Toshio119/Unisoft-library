#ifndef UTILCLI_H
#define UTILCLI_H

#include <stddef.h> // For size_t

// Define a structure for CLI options
typedef struct {
    const char *name;         // Option name (e.g., "--verbose")
    const char *short_name;   // Short option name (e.g., "-v")
    const char *description;  // Description for help message
    bool has_arg;             // True if the option requires an argument
    void *dest;               // Pointer to store the value of the option
} CLIOption;

// Function prototypes
void parse_arguments(int argc, char *argv[], const CLIOption *options, size_t num_options);
void print_help(const CLIOption *options, size_t num_options);
bool get_option(const CLIOption *options, size_t num_options, const char *name, void **dest);

#endif // UTILCLI_H
