//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_file.h"
#include "CT_custom_events.h"
#include "CT_event_manager.h"
#include "CT_state.h"

// to test
void ctStateHasChanged(uint16_t table_id/*, size_t count, size_t offset*/) {
  ctBlockEntry_t entry;
  ctEvent_t event;
  memset(&entry, 0, sizeof entry);
  memset(&event, 0, sizeof event);

  if(ctGetBlockEntry(table_id, &entry) != CT__SUCCESS)
    fprintf(stderr, "ERROR: Failed to read block entry for table %d\n",
      table_id);
  else if(entry.type == CT__TTYPE_EVENT) {
    if(ctCustomEvent(table_id, &event) != CT__SUCCESS)
      fprintf(stderr, "WARNING: Requested event for table %d not implemented\n",
        table_id);
    else {
      if(ctNewEvent(&event) != CT__SUCCESS)
        fprintf(stderr, "WARNING: Failed to create event for table %d\n",
          table_id);
    }
  }
  // test
  else
    printf("Not an event table (table=%d, type=%d)\n", table_id, entry.type);
}
