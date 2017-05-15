//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_THREAD_H
#define CT_THREAD_H

// Thread type
//
typedef void* ctThread_t;

// Mutex type
//
typedef void* ctMutex_t;

// Create a new thread
//
int ctThreadCreate(ctThread_t* thread, void* (*exec)(void*));

// Send a signal to a thread
//
int ctSignal(ctThread_t* thread, int signum);

// Put the calling thread to sleep
//
int ctSleep(unsigned int seconds);

// Create a new mutex
//
int ctMutexCreate(ctMutex_t* mutex);

// Lock mutex
//
int ctLock(ctMutex_t* mutex);

// Unlock mutex
//
int ctUnlock(ctMutex_t* mutex);

#endif // CT_THREAD_H
