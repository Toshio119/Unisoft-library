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


#ifndef UTILGC_H
#define UTILGC_H
#include <stddef.h>
typedef struct MemoryBlock {
    void *ptr;
    size_t size;
    struct MemoryBlock *next;
} MemoryBlock;
extern MemoryBlock *head;
extern void *track_malloc(size_t size);
extern void *track_calloc(size_t num, size_t size);
extern void track_free(void *ptr);
extern void report_memory_leaks(void);
extern void report_memory_usage(void);
extern void register_report_memory_leaks(void);

#endif
