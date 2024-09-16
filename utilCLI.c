#include "utilCLI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// Helper function to print an error message and exit
static void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

// Helper function to find an option by its name
static const CLIOption *find_option(const CLIOption *options, size_t num_options, const char *name) {
    for (size_t i = 0; i < num_options; ++i) {
        if (strcmp(name, options[i].name) == 0 || (options[i].short_name && strcmp(name, options[i].short_name) == 0)) {
            return &options[i];
        }
    }
    return NULL;
}

// Parse command-line arguments
void parse_arguments(int argc, char *argv[], const CLIOption *options, size_t num_options) {
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];
        const CLIOption *opt = find_option(options, num_options, arg);

        if (opt) {
            if (opt->has_arg) {
                if (i + 1 < argc) {
                    *(char **)opt->dest = argv[++i];
                } else {
                    print_error("Missing argument for option");
                }
            } else {
                *(bool *)opt->dest = true;
            }
        } else {
            print_error("Unknown option");
        }
    }
}

// Print help message
void print_help(const CLIOption *options, size_t num_options) {
    printf("Usage:\n");
    for (size_t i = 0; i < num_options; ++i) {
        printf("  %-15s", options[i].name);
        if (options[i].short_name) {
            printf(" (%s)", options[i].short_name);
        }
        printf(" - %s\n", options[i].description);
    }
}

// Get the value of an option
bool get_option(const CLIOption *options, size_t num_options, const char *name, void **dest) {
    const CLIOption *opt = find_option(options, num_options, name);
    if (opt) {
        *dest = opt->dest;
        return true;
    }
    return false;
}
