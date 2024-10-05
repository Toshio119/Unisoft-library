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


/*
 * 
 * Usage of these utilities is intended to improve memory management and debugging processes. The functions provided in this header file:
 * - `track_malloc(size_t size)`: Allocates memory of the specified size and tracks the allocation.
 * - `track_free(void *ptr)`: Frees previously allocated memory and removes the tracking information.
 * - `collect_all(void)`: frees all memory at program exit.
 * - `report_memory_usage(void)`: Reports the total amount of memory currently allocated.
 * - `track_fopen(const char *filename, const char *mode)`: Opens a file and tracks the file pointer.
 * - `track_fclose(FILE *file)`: Closes a previously opened file and removes the tracking information.
 * - `close_allfiles(void)`: frees all files at program exit..
 * 
 * The use of `malloc`, `free`, `fopen`, and `fclose` macros redirects memory management calls to the tracking functions, allowing for automated monitoring.
 * 
 * While this tool is intended to assist in debugging and ensuring proper memory management, it is crucial to perform additional checks and tests
 * in production environments. The developers recommend reviewing the usage of this code and ensuring it meets the specific needs and security 
 * requirements of your application.
 * 
 * (c) 2024 Toshio Nayashima
 * All rights reserved.
 */

#ifndef UTILGC_H
#define UTILGC_H

#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct MemoryBlock {
    void *ptr;
    size_t size;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct FileBlock {
    FILE *file;
    const char *filename;
    struct FileBlock *next;
} FileBlock;

static MemoryBlock *head = NULL;
static FileBlock *fileHead = NULL;

__attribute__((hot)) extern void *track_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr) {
        MemoryBlock *new_block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        if (new_block) {
            new_block->ptr = ptr;
            new_block->size = size;
            new_block->next = head;
            head = new_block;
        } else {
            fputs("Unisoft Gc: Memory allocation failed.\n", stderr);
            free(ptr);
            ptr = NULL;
        }
    }
    return ptr;
}

__attribute__((hot)) extern void *track_calloc(size_t num, size_t size) {
    void *ptr = calloc(num, size);
    if (ptr) {
        MemoryBlock *new_block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        if (new_block) {
            new_block->ptr = ptr;
            new_block->size = num * size;
            new_block->next = head;
            head = new_block;
        } else {
            fputs("Unisoft Gc: Memory allocation failed.\n", stderr);
            free(ptr);
            ptr = NULL;
        }
    }
    return ptr;
}

__attribute__((hot)) extern void track_free(void *ptr) {
    MemoryBlock **current = &head;
    while (*current) {
        MemoryBlock *entry = *current;
        if (entry->ptr == ptr) {
            *current = entry->next;
            free(ptr);
            free(entry);
            return;
        }
        current = &entry->next;
    }
    fputs("\033[1;31mWarning: Attempt to free untracked memory\033[00m\n", stderr);
}

__attribute__((hot)) extern FILE *track_fopen(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file) {
        FileBlock *new_block = (FileBlock *)malloc(sizeof(FileBlock));
        if (new_block) {
            new_block->file = file;
            new_block->filename = filename;
            new_block->next = fileHead;
            fileHead = new_block;
        } else {
            fputs("Unisoft Gc: Unable to allocate memory for file block\n", stderr);
            fclose(file);
            file = NULL;
        }
    }
    return file;
}

__attribute__((hot)) extern void track_fclose(FILE *file) {
    FileBlock **current = &fileHead;
    while (*current) {
        FileBlock *entry = *current;
        if (entry->file == file) {
            *current = entry->next;
            fclose(file);
            free(entry);
            return;
        }
        current = &entry->next;
    }
    fputs("\033[1;31mWarning: Attempt to close untracked file pointer\033[00m\n", stderr);
}

__attribute__((hot)) extern void collect_all(void) {
    MemoryBlock *current = head;
    while (current) {
        MemoryBlock *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    head = NULL;
}

__attribute__((hot)) extern void close_allfiles(void) {
    FileBlock *current = fileHead;
    while (current) {
        FileBlock *next = current->next;
        fclose(current->file);
        free(current);
        current = next;
    }
    fileHead = NULL;
}

__attribute__((hot)) extern void report_memory_usage(void) {
    size_t total_size = 0;
    for (MemoryBlock *current = head; current; current = current->next) {
        total_size += current->size;
    }
    printf("Total memory allocated: %zu bytes\n", total_size);
}

__attribute__((constructor)) extern void register_report_memory_leaks(void) {
    atexit(collect_all);
    atexit(close_allfiles);
}

#define malloc(size) track_malloc(size)
#define calloc(num, size) track_calloc(num, size)
#define free(ptr) track_free(ptr)
#define fopen(filename, mode) track_fopen(filename, mode)
#define fclose(file) track_fclose(file)

#endif //UTILGC_H

