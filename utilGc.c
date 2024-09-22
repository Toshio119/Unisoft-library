#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "utilGc.h"

extern MemoryBlock *head = NULL;
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

__attribute__((hot)) extern void report_memory_leaks(void) {
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

__attribute__((hot)) extern void report_memory_usage(void) {
    size_t total_size = 0;
    for (MemoryBlock *current = head; current; current = current->next) {
        total_size += current->size;
    }
    printf("Total memory allocated: %zu bytes\n", total_size);
}

__attribute__((constructor)) extern void register_report_memory_leaks(void) {
    atexit(report_memory_leaks);
}

#define malloc(size) track_malloc(size)
#define calloc(num, size) track_calloc(num, size)
#define free(ptr) track_free(ptr)
