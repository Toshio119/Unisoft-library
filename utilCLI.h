#ifndef UTILCLI_H
#define UTILCLI_H

#include <stddef.h>  // for size_t
#include <stdbool.h> // for bool

// Structure to represent a command-line option
typedef struct {
    const char *name;          // Long option name
    const char *short_name;    // Short option name
    bool has_arg;              // Indicates if the option requires an argument
    void *dest;                // Pointer to store the option's value
    const char *description;    // Description of the option
} CLIOption;

// Function to parse command-line arguments
void parse_arguments(int argc, char *argv[], const CLIOption *options, size_t num_options);

// Function to print the help message
void print_help(const CLIOption *options, size_t num_options);

// Function to get the value of an option
bool get_option(const CLIOption *options, size_t num_options, const char *name, void **dest);

// Static helper function to find an option by its name (only for internal use)
static const CLIOption *find_option(const CLIOption *options, size_t num_options, const char *name);

#endif // UTILCLI_H
