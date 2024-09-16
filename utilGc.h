/*
 * 
 * Usage of these utilities is intended to enhance memory management and debugging processes. The functions provided in this header file include:
 * - `track_malloc(size_t size)`: Allocates memory of the specified size and tracks the allocation.
 * - `track_calloc(size_t num, size_t size)`: Allocates memory for an array of elements, initializing them to zero, and tracks the allocation.
 * - `track_free(void *ptr)`: Frees previously allocated memory and removes the tracking information.
 * - `report_memory_leaks(void)`: Reports memory leaks detected at program exit.
 * - `report_memory_usage(void)`: Reports the total amount of memory currently allocated.
 , including total allocated memory, total number of allocations, and maximum memory usage. 
 * 
 * The use of `malloc`, `calloc`, and `free` macros redirects memory management calls to the tracking functions, allowing for automated monitoring and debugging. 
 * 
 * This tool is designed to assist in debugging and ensuring proper memory management. 
 * However, it is essential to perform additional checks and tests in production environments. 
 * Users should review the implementation of this code to ensure it meets the specific needs and security requirements of their application. 
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

static MemoryBlock *head = NULL;

__attribute__((always_inline)) inline static void *track_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr) {
        MemoryBlock *new_block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        if (new_block) {
            new_block->ptr = ptr;
            new_block->size = size;
            new_block->next = head;
            head = new_block;
        } else {
            free(ptr);
            ptr = NULL;
        }
    }
    return ptr;
}

__attribute__((always_inline)) inline static void *track_calloc(size_t num, size_t size) {
    void *ptr = calloc(num, size);
    if (ptr) {
        MemoryBlock *new_block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        if (new_block) {
            new_block->ptr = ptr;
            new_block->size = num * size;
            new_block->next = head;
            head = new_block;
        } else {
            free(ptr);
            ptr = NULL;
        }
    }
    return ptr;
}

__attribute__((always_inline)) inline static void track_free(void *ptr) {
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
    fprintf(stderr, "\033[1;31mWarning: Attempt to free untracked memory\033[00m\n");
}

__attribute__((always_inline)) inline static void report_memory_leaks(void) {
    MemoryBlock *current = head;
    while (current) {
        fprintf(stderr, "\033[1;31mWarning: Memory leak detected: %zu bytes at %p\033[00m\n", current->size, current->ptr);
        MemoryBlock *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    head = NULL;
}

__attribute__((always_inline)) inline static void report_memory_usage(void) {
    size_t total_size = 0;
    for (MemoryBlock *current = head; current; current = current->next) {
        total_size += current->size;
    }
    printf("Total memory allocated: %zu bytes\n", total_size);
}

__attribute__((constructor)) static void register_report_memory_leaks(void) {
    atexit(report_memory_leaks);
}

#define malloc(size) track_malloc(size)
#define calloc(num, size) track_calloc(num, size)
#define free(ptr) track_free(ptr)

#endif
