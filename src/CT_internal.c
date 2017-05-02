//
// Created by Gustavo Viegas on 2017/04
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "CT_internal.h"
#include "CT_defs.h"
#include "CT_tables.h"
#include "CT_file.h"

// To do: base value for sim should come from program args and never change
static float _ctBaseValue() { return ((rand() % 10000) + 1000) * 0.000001; }

// To do: ^ same for behavior...
static int _ctMeasureNow(ctMeasureData_t* buffer, ctMeasureInfo_t* info, int opt) {
  // Current implementation for simulation only - when fully implemented,
  // it should poll real values from available ports (M-Bus, MEP, etc).

  float value = _ctBaseValue();
  time_t etime = time(NULL);
  struct tm* now = gmtime(&etime);

  // To do: generate more accurate values
  switch(opt) {
    case CT__BEHAVIOR_E:
      if(now->tm_wday == 0) // Sunday
        value /= 3 + rand() % 5;
      else if(now->tm_hour > 8 && now->tm_hour < 18)
        value *= 2 + rand() % 5;
    break;
    case CT__BEHAVIOR_H:
      if(now->tm_wday == 0) // Sunday
        value *= 2 + rand() % 4;
      if(now->tm_hour > 18 && now->tm_hour < 23)
        value *= 2 + rand() % 5;
    break;
    default:
      fprintf(stderr, "\nInvalid measure option\n");
      return CT__FAILURE;
  }

  buffer->value = value;
  ctGetLTimeDate(&buffer->timestamp);

  return CT__SUCCESS;
}

static void* _ctPerformInternalTask(void* args) {
  // To do: read this info from et00
  int i = 0; // start entry
  int n = 10; // size of circular mem block
  double delay = 60; // seconds
  //
  time_t st, et;
  double diff;
  ctMeasureInfo_t mi;
  ctMeasureData_t md;
  for(;;) {
    st = time(NULL);
    _ctMeasureNow(&md, &mi, CT__BEHAVIOR_E);
    ctWrite(CT__ET01, &md, sizeof md, sizeof md * i);
    i = (i + 1) % n;
    // debug
    printf("\nET01 (10 entries)\n");
    printf("next entry: %d\n", i);
    ctMeasureData_t entries[10];
    ctRead(CT__ET01, entries, sizeof entries, 0);
    int j;
    for(j = 0; j < sizeof entries / sizeof entries[0]; ++j) {
      printf("value: %f\n", entries[j].value);
      printf("timestamp: %d/%d/%d %d:%d:%d\n",
        entries[j].timestamp.year, entries[j].timestamp.month,
        entries[j].timestamp.day, entries[j].timestamp.hour,
        entries[j].timestamp.minute, entries[j].timestamp.second
      );
    }
    //
    et = time(NULL);
    diff = difftime(et, st);
    if(diff < delay)
      sleep(delay - diff);
  }
  return NULL;
}

static pthread_t tid;
static int targ = 0;
static void _ctCreateInternalTask() {
  // pthread_t tid; // no join no go...
  // int targ = 0; // ^^^
  int err = pthread_create(&tid, NULL, _ctPerformInternalTask, &targ);
  if(err) {
    fprintf(stderr, "\nCreate Internal Task failed\n");
    return;
  }
  // pthread_join(tid, NULL);
  // To do: should reach this point when ctStopInternal() is called
  // or some other kind or event (?)
  // dont forget to get current entry pos to resume measurements...
}

void ctStartInternal(/*int id*/) {
  _ctCreateInternalTask();
  // sleep(5); // test
}

// void ctStopInternal(/*int id*/) {} // To do
// void ctSetInternal(/*...*/) {} // To do
