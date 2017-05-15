//
// Created by Gustavo Viegas on 2017/05
//

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "CT_defs.h"
#include "CT_thread.h"

int ctThreadCreate(ctThread_t* thread, void* (*exec)(void*)) {
  int e = pthread_create((pthread_t*) thread, NULL, exec, NULL);
  if(e) {
    fprintf(stderr, "\nERROR: Failed to create a new thread");
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}

// to do
int ctSignal(ctThread_t* thread, int signum) {
  return CT__SUCCESS;
}

int ctSleep(unsigned int seconds) {
  return sleep(seconds);
}

int ctMutexCreate(ctMutex_t* mutex) {
  return pthread_mutex_init((pthread_mutex_t*) mutex, NULL);
}

int ctLock(ctMutex_t* mutex) {
  return pthread_mutex_lock((pthread_mutex_t*) mutex);
}

int ctUnlock(ctMutex_t* mutex) {
  return pthread_mutex_unlock((pthread_mutex_t*) mutex);
}
