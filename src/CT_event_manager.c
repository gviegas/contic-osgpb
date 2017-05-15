//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include "CT_defs.h"
#include "CT_thread.h"
#include "CT_event_manager.h"

static ctQueue_t _ct_queue;
static ctThread_t _ct_thread;
static ctMutex_t _ct_mutex;
static ctCond_t _ct_cond;

// to do
static void* _ctManagerRun(void* args) {
  printf("Manager running\n"); // test
  return NULL;
}

int ctManagerStart() {
  if(ctQueueCreate(&_ct_queue) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Manager failed to create queue\n");
    return CT__FAILURE;
  }
  if(ctMutexCreate(&_ct_mutex) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Manager failed to create mutex\n");
    return CT__FAILURE;
  }
  if(ctCondCreate(&_ct_cond) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Manager failed to create cond\n");
    return CT__FAILURE;
  }
  if(ctThreadCreate(&_ct_thread, _ctManagerRun) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Manager failed to create thread\n");
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}

// to do
int ctNewEvent(ctEvent_t* event) {
  return CT__SUCCESS;
}
