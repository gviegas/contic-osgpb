//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_EVENT_MANAGER_H
#define CT_EVENT_MANAGER_H

#include "CT_event_queue.h"

#define CT__NOTREADY -3
#define CT__DSFULL -4

// Start the event manager
//
// NOTE: currently there is no way to remove events from the manager's event
// queue. This is a problem for INTERVAL events - they will stay forever in the
// system (unless you reboot it), and rewriting event tables will fire new
// instances of the same events (which probably isn't desired).
//
int ctManagerStart();

// Create a new event
//
int ctNewEvent(ctEvent_t* event);

#endif // CT_EVENT_MANAGER_H
