//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_EVENT_MANAGER_H
#define CT_EVENT_MANAGER_H

#include "CT_event_queue.h"

// Start the event manager
//
int ctManagerStart();

// Create a new event
//
int ctNewEvent(ctEvent_t* event);

#endif // CT_EVENT_MANAGER_H
