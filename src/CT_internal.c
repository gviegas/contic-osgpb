//
// Created by Gustavo Viegas on 2017/04
//

#include <stdio.h>
#include "CT_internal.h"
#include "CT_defs.h"

int ctMeasureNow(ctMeasureData_t* buffer, ctMeasureInfo_t* info, int opt) {
  // Current implementation for simulation only - when fully implemented,
  // it should poll real values from available ports (M-Bus, MEP, etc).
  
  uint32_t value = 0;
  time_t etime = time(NULL);
  struct tm* now = gmtime(&etime);

  switch(opt) {
    case CT__BEHAVIOR_E:
      if(now->tm_wday == 0) { // Sunday
        // ...
      }
      if(now->tm_hour > 8 && now->tm_hour < 18) {
        // ...
      }
    break;
    case CT__BEHAVIOR_H:
      if(now->tm_wday == 0) { // Sunday
        // ...
      }
      if(now->tm_hour > 18 && now->tm_hour < 23) {
        // ...
      }
    break;
    default:
      fprintf(stderr, "\nInvalid measure option\n");
      return CT__FAILURE;
  }

  buffer->value_high = value >> 16;
  buffer->value_low = value & 0x0000ffff;
  ctGetLTimeDate(&buffer->timestamp);
  
  return CT__SUCCESS;
}