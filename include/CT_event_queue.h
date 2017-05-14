//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_EVENT_QUEUE_H
#define CT_EVENT_QUEUE_H

#include "CT_timed_event.h"

#define CT__QUEUE_LEN 20

// Queue type (static)
//
typedef struct {
  int head;
  int tail;
  int size;
  ctEvent_t events[CT__QUEUE_LEN];
} ctQueue_t;

// Create a new queue
//
int ctQueueCreate(ctQueue_t* queue);

// Get queue size
//
int ctQueueSize(ctQueue_t* queue);

// Put a new event in the queue
//
int ctQueuePut(ctQueue_t* queue, ctEvent_t* event);

// Get and remove the queue head
//
int ctQueueGet(ctQueue_t* queue, ctEvent_t* event);

// Get and does not remove the queue head
//
int ctQueuePeek(ctQueue_t* queue, ctEvent_t** event);

// Sort contents
//
int ctQueueSort(ctQueue_t* queue);

// Clear the queue
//
int ctQueueClear(ctQueue_t* queue);

#endif // CT_EVENT_QUEUE_H
