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
 * - `Uimalloc(size_t size)`: Allocates memory of the specified size and tracks the allocation.
 * - `Uifree(void *ptr)`: Frees previously allocated memory and removes the tracking information.
 * - `collect_all(void)`: frees all memory at program exit.
 * - `Uiresize(void *ptr, size_t newSize)`: Resizes the memory block pointed to by `ptr`
 * - `UiCalloc(size_t nmemb, size_t size)`: Allocates memory for an array of `nmemb`
 * - `report_memory_usage(void)`: Reports the total amount of memory currently allocated.
 * - `Uifopen(const char *filename, const char *mode)`: Opens a file and tracks the file pointer.
 * - `Uifclose(FILE *file)`: Closes a previously opened file and removes the tracking information.
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

#include <stdio.h>


typedef struct __attribute__((aligned(16))) MemoryBlock {
    void *ptr;
    size_t size;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct __attribute__((aligned(16))) FileBlock {
    FILE *file;
    const char *filename;
    struct FileBlock *next;
} FileBlock;

// Function prototypes
extern void *Uialloc(size_t size);
extern void *UiCalloc(size_t num, size_t size);
extern void *Uiresize(void *ptr, size_t size);
extern void Uifree(void *ptr);
extern FILE *Uifopen(const char *filename, const char *mode);
extern void Uifclose(FILE *file);
extern void collect_all(void);
extern void close_allfiles(void);
extern void report_memory_usage(void);
extern void register_report_memory_leaks(void);


#endif //UTILGC_H
