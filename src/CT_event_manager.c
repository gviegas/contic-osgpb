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

// to test more...
static void* _ctManagerRun(void* arg) {
  ctEvent_t event, *p_event = NULL;
  ctTimeSpec_t timeout, *p_timeout = NULL;
  int w;
  ctGetTimeSpec(&timeout); // subtle...
  while(1) {
    ctLock(&_ct_mutex);
    _ct_wake = w = 0;
    while(!_ct_wake && w != CT__TIMEDOUT)
      w = ctWait(&_ct_cond, &_ct_mutex, p_timeout);
    if(w == CT__TIMEDOUT) {
      if(ctQueueGet(&_ct_queue, &event) == CT__SUCCESS) {
        event.exec();
        if(event.timer == EVENT_INTERVAL) {
          ctGetTimeSpec(&timeout);
          event.calendar = timeout.sec + event.delay;
          ctQueuePut(&_ct_queue, &event); // NOTE: this cannot fail
          ctQueueSort(&_ct_queue);
        }
      }
    } // else signaled
    if(ctQueuePeek(&_ct_queue, &p_event) == CT__SUCCESS) {
      timeout.sec = p_event->calendar;
      p_timeout = &timeout;
    } else
      p_timeout = NULL;
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
  if(ctThreadCreate(&_ct_thread, _ctManagerRun, NULL) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Manager failed to create thread\n");
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}

int ctNewEvent(ctEvent_t* event) {
  if(!event) {
    fprintf(stderr, "ERROR: Invalid new event\n");
    return CT__FAILURE;
  }
  ctLock(&_ct_mutex);
  if(ctQueuePut(&_ct_queue, event) == CT__FAILURE) {
    ctUnlock(&_ct_mutex);
    fprintf(stderr, "ERROR: Failed to insert a new event\n");
    return CT__FAILURE;
  }
  ctQueueSort(&_ct_queue);
  _ct_wake = 1;
  ctSignal(&_ct_cond);
  ctUnlock(&_ct_mutex);
  return CT__SUCCESS;
}
