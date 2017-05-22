//
// Created by Gustavo Viegas on 2017/05
//

#include <unistd.h>
// #include <pthread.h>
#include <stdio.h>
#include <errno.h>
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

int ctMutexCreate(ctMutex_t* mutex) {
  return pthread_mutex_init((pthread_mutex_t*) mutex, NULL);
}

int ctLock(ctMutex_t* mutex) {
  return pthread_mutex_lock((pthread_mutex_t*) mutex);
}

int ctUnlock(ctMutex_t* mutex) {
  return pthread_mutex_unlock((pthread_mutex_t*) mutex);
}

int ctCondCreate(ctCond_t* cond) {
  return pthread_cond_init((pthread_cond_t*) cond, NULL);
}

int ctWait(ctCond_t* cond, ctMutex_t* mutex, ctTimeSpec_t* time) {
  int r;
  if(!time)
    r = pthread_cond_wait((pthread_cond_t*) cond, (pthread_mutex_t*) mutex);
  else
    r = pthread_cond_timedwait((pthread_cond_t*) cond,
      (pthread_mutex_t*) mutex, (struct timespec*) time);
  if(r == ETIMEDOUT) return CT__TIMEDOUT;
  return r;
}

int ctSignal(ctCond_t* cond) {
  // return pthread_cond_broadcast((pthread_cond_t*) cond);
  return pthread_cond_signal((pthread_cond_t*) cond);
}

int ctSleep(unsigned int seconds) {
  return sleep(seconds);
}
