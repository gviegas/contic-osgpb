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
static int _ct_wake;

// to do
static void* _ctManagerRun(void* args) {
  ctEvent_t event, *p_event;
  int w;
  while(1) {
    ctLock(&_ct_mutex);
    _ct_wake = w = 0;
    while(!_ct_wake && w != CT__TIMEDOUT)
      w = ctWait(&_ct_cond, &_ct_mutex, NULL); // should use time
    if(w == CT__TIMEDOUT) {
      if(ctQueueGet(&_ct_queue, &event) == CT__SUCCESS) {
        event.exec();
        if(event.timer == EVENT_INTERVAL) {
          // calc new time & put on queue & sort
        }
      }
    } else
      ctQueueSort(&_ct_queue);
    if(ctQueuePeek(&_ct_queue, &p_event) == CT__SUCCESS) {
      // set time to event.delay
    } else {
      // set time to ... now? 1s?
    }
    ctUnlock(&_ct_mutex);
  }
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

// to test
int ctNewEvent(ctEvent_t* event) {
  if(!event) {
    fprintf(stderr, "ERROR: Invalid new event\n");
    return CT__FAILURE;
  }
  ctLock(&_ct_mutex);
  if(ctQueuePut(&_ct_queue, event) == CT__FAILURE) {
    ctUnlock(&_ct_mutex);
    fprintf(stderr, "ERROR: Failed to insert the new event\n");
    return CT__FAILURE;
  }
  _ct_wake = 1;
  ctSignal(&_ct_cond);
  ctUnlock(&_ct_mutex);
  return CT__SUCCESS;
}
