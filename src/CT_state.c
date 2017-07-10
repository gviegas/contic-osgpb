//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_file.h"
#include "CT_custom_events.h"
#include "CT_event_manager.h"
#include "CT_state.h"

void ctStateHasChanged(uint16_t table_id) {
  ctBlockEntry_t entry;
  ctEvent_t event;
  int e;
  memset(&entry, 0, sizeof entry);
  memset(&event, 0, sizeof event);

  if(ctGetBlockEntry(table_id, &entry) != CT__SUCCESS)
    fprintf(stderr, "ERROR: Failed to read block entry for table %d\n",
      table_id);
  else if(entry.type == CT__TTYPE_EVENT) {
    if(ctCustomEvent(table_id, &event) != CT__SUCCESS)
      fprintf(stderr, "ERROR: Requested event for table %d not implemented\n",
        table_id);
    else {
      while((e = ctNewEvent(&event)) == CT__NOTREADY);
      if(e != CT__SUCCESS)
        fprintf(stderr, "ERROR: Failed to create event for table %d\n",
          table_id);
    }
  }
}
