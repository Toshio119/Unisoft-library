#include "utilSync.h"
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

// Create and start a new thread
int create_thread(Thread *t, thread_func_t func, void *arg) {
    int ret = pthread_create(&t->thread, NULL, func, arg);
    if (ret != 0) {
        HANDLE_ERROR("pthread_create failed");
        return -1;
    }
    t->func = func;
    t->arg = arg;
    return 0;
}

// Join a thread
int join_thread(Thread *t) {
    int ret = pthread_join(t->thread, NULL);
    if (ret != 0) {
        HANDLE_ERROR("pthread_join failed");
        return -1;
    }
    return 0;
}

// Initialize a mutex
int init_mutex(Mutex *m) {
    int ret = pthread_mutex_init(&m->mutex, NULL);
    if (ret != 0) {
        HANDLE_ERROR("pthread_mutex_init failed");
        return -1;
    }
    return 0;
}

// Lock a mutex
int lock_mutex(Mutex *m) {
    int ret = pthread_mutex_lock(&m->mutex);
    if (ret != 0) {
        HANDLE_ERROR("pthread_mutex_lock failed");
        return -1;
    }
    return 0;
}

// Unlock a mutex
int unlock_mutex(Mutex *m) {
    int ret = pthread_mutex_unlock(&m->mutex);
    if (ret != 0) {
        HANDLE_ERROR("pthread_mutex_unlock failed");
        return -1;
    }
    return 0;
}

// Destroy a mutex
int destroy_mutex(Mutex *m) {
    int ret = pthread_mutex_destroy(&m->mutex);
    if (ret != 0) {
        HANDLE_ERROR("pthread_mutex_destroy failed");
        return -1;
    }
    return 0;
}
