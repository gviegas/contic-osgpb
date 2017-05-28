//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_TIMED_EVENT_H
#define CT_TIMED_EVENT_H

// Event timer enum
//
typedef enum { EVENT_IMMEDIATE, EVENT_INTERVAL, EVENT_TIMEOUT } ctEventTimer_e;

// Event type
//
typedef struct {
  ctEventTimer_e timer;
  long int calendar;
  long int delay;
  void (*exec)();
} ctEvent_t;

#endif // CT_TIMED_EVENT_H
