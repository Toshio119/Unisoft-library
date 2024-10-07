#include "utilGc.h"
#include <stdio.h>
#include <stdlib.h>

static MemoryBlock *head = NULL;
static FileBlock *fileHead = NULL;
__attribute__((hot)) extern void *Uialloc(size_t size) {
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

__attribute__((hot)) extern void *UiCalloc(size_t num, size_t size) {
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

__attribute__((hot)) extern void *Uiresize(void *ptr, size_t size) {
    MemoryBlock **current = &head;
    while (*current) {
        MemoryBlock *entry = *current;
        if (entry->ptr == ptr) {
            void *new_ptr = realloc(ptr, size);
            if (new_ptr) {
                entry->ptr = new_ptr;
                entry->size = size;  // Update the size in the tracking structure
            } else {
                fputs("Unisoft Gc: Memory reallocation failed.\n", stderr);
            }
            return new_ptr;
        }
        current = &entry->next;
    }
    fputs("\033[1;31mWarning: Attempt to realloc untracked memory\033[00m\n", stderr);
    return NULL;
}

__attribute__((hot)) extern void Uifree(void *ptr) {
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

__attribute__((hot)) extern FILE *Uifopen(const char *filename, const char *mode) {
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
            fclose(file);  // Ensure to close the file only if it was opened successfully
            file = NULL;
        }
    } else {
        fputs("Unisoft Gc: fopen failed for file.\n", stderr); // Additional error for fopen failure
    }
    return file;
}

__attribute__((hot)) extern void Uifclose(FILE *file) {
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

__attribute__((hot)) void collect_all(void) {
    MemoryBlock *current = head;
    while (current) {
        MemoryBlock *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    head = NULL;
}

__attribute__((hot)) void close_allfiles(void) {
    FileBlock *current = fileHead;
    while (current) {
        FileBlock *next = current->next;
        fclose(current->file);
        free(current);
        current = next;
    }
    fileHead = NULL;
}

__attribute__((hot)) void report_memory_usage(void) {
    size_t total_size = 0;
    for (MemoryBlock *current = head; current; current = current->next) {
        total_size += current->size;
    }
    printf("Total memory allocated: %zu bytes\n", total_size);
}

__attribute__((constructor)) void register_report_memory_leaks(void) {
    atexit(collect_all);
    atexit(close_allfiles);
}
