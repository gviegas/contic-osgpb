//
// Created by Gustavo Viegas on 2017/05
//

#include <string.h>
#include "CT_definitions.h"
#include "CT_event_queue.h"

int ctQueueCreate(ctQueue_t* queue) {
  if(!queue) return CT__FAILURE;
  queue->head = 0;
  queue->tail = -1;
  queue->size = 0;
  memset(queue->events, 0, sizeof queue->events);
  return CT__SUCCESS;
}

int ctQueueSize(ctQueue_t* queue) {
  if(!queue) return -1;
  return queue->size;
}

int ctQueuePut(ctQueue_t* queue, ctEvent_t* event) {
  if(queue && (queue->size < CT__QUEUE_LEN)) {
    queue->tail = (queue->tail + 1) % CT__QUEUE_LEN;
    memcpy(&(queue->events[queue->tail]), event, sizeof(ctEvent_t));
    ++queue->size;
    return CT__SUCCESS;
  }
  return CT__FAILURE;
}

int ctQueueGet(ctQueue_t* queue, ctEvent_t* event) {
  if(queue && (queue->size > 0)) {
    memcpy(event, &(queue->events[queue->head]), sizeof(ctEvent_t));
    queue->head = (queue->head + 1) % CT__QUEUE_LEN;
    --queue->size;
    return CT__SUCCESS;
  }
  return CT__FAILURE;
}

int ctQueuePeek(ctQueue_t* queue, ctEvent_t** event) {
  if(queue && (queue->size > 0)) {
    *event = &(queue->events[queue->head]);
    return CT__SUCCESS;
  }
  return CT__FAILURE;
}

// NOTE: good enough for ~20 entries
int ctQueueSort(ctQueue_t* queue) {
  if(!queue) return CT__FAILURE;
  int i, j;
  ctEvent_t e;
  for(i = queue->head; i != queue->tail; i = (i + 1) % CT__QUEUE_LEN) {
    j = i;
    do {
      j = (j + 1) % CT__QUEUE_LEN;
      if(queue->events[j].calendar < queue->events[i].calendar) {
        e = queue->events[i];
        queue->events[i] = queue->events[j];
        queue->events[j] = e;
      }
    } while(j != queue->tail);
  }
  return CT__SUCCESS;
}

int ctQueueClear(ctQueue_t* queue) {
  return ctQueueCreate(queue);
}
