//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include "CT_defs.h"
#include "CT_date.h"
#include "CT_tables.h"
#include "CT_file.h"
#include "CT_custom.h"
#include "CT_custom_events.h"

// static void _ctCustomConsumption() {
//   printf("~Custom Consumption~\n");
// }

int ctCustomEvent(uint16_t table_id, ctEvent_t* event) {
  switch(table_id) {
    case CT__UT01: {
      ctUT01_t ut01;
      if(ctRead(CT__UT01, &ut01, 0, 0) != sizeof ut01) {
        fprintf(stderr, "ERROR: Failed to read from ut01\n");
        return CT__FAILURE;
      }
      event->timer = EVENT_INTERVAL;
      event->calendar = time(NULL);
      event->delay = ut01.delay_s;
      // event->exec = _ctCustomConsumption;
      event->exec = ctGetConsumption;
    }
    break;
    // case MY_CUSTOM_TABLE:
    // fill event structure with my custom event params...
    default:
      return CT__FAILURE;
  }
  return CT__SUCCESS;
}
