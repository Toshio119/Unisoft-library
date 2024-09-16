#ifndef UTILSYNC_H
#define UTILSYNC_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Define a type for thread functions
typedef void *(*thread_func_t)(void *);

// Macro to handle errors
#define HANDLE_ERROR(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

// Structure for thread wrapper
typedef struct {
    pthread_t thread;
    thread_func_t func;
    void *arg;
} Thread;

// Structure for mutex wrapper
typedef struct {
    pthread_mutex_t mutex;
} Mutex;

// Function prototypes

// Thread functions
int create_thread(Thread *t, thread_func_t func, void *arg);
int join_thread(Thread *t);

// Mutex functions
int init_mutex(Mutex *m);
int lock_mutex(Mutex *m);
int unlock_mutex(Mutex *m);
int destroy_mutex(Mutex *m);

#endif // UTILSYNC_H
