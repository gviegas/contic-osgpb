//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_THREAD_H
#define CT_THREAD_H

#include <pthread.h> // TODO: this should be included on src
#include "CT_date.h"

#define CT__TIMEDOUT -1

// Thread type
//
typedef unsigned long int ctThread_t;

// Mutex type
//
// TODO: remove dependency from header
//
typedef pthread_mutex_t ctMutex_t;

// Cond type
//
// TODO: remove dependency from header
//
typedef pthread_cond_t ctCond_t;

// Create a new thread
//
int ctThreadCreate(ctThread_t* thread, void* (*exec)(void*), void* arg);

// Create a new mutex
//
int ctMutexCreate(ctMutex_t* mutex);

// Lock mutex
//
int ctLock(ctMutex_t* mutex);

// Unlock mutex
//
int ctUnlock(ctMutex_t* mutex);

// Create a new condition
//
int ctCondCreate(ctCond_t* cond);

// Wait on condition or timeout
//
int ctWait(ctCond_t* cond, ctMutex_t* mutex, ctTimeSpec_t* time);

// Wake up the thread waiting on condition
//
int ctSignal(ctCond_t* cond);

// Put the calling thread to sleep
//
int ctSleep(unsigned int seconds);

#endif // CT_THREAD_H
