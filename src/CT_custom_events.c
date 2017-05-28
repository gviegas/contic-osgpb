//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include "CT_defs.h"
#include "CT_date.h"
#include "CT_custom_events.h"

static void _ctCustomConsumption() {
  printf("~Custom Consumption~\n");
}

int ctCustomEvent(uint16_t table_id, ctEvent_t* event) {
  switch(table_id) {
    // test
    case CT__ET00:
      event->timer = EVENT_INTERVAL;
      event->calendar = time(NULL);
      event->delay = 60;
      event->exec = _ctCustomConsumption;
    break;
    //
    // case MY_CUSTOM_TABLE:
    // fill event structure with my custom event params...
    default:
      fprintf(stderr, "ERROR: No event for table %d\n", table_id);
      return CT__FAILURE;
  }
  return CT__SUCCESS;
}
