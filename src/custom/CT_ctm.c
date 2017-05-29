//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include "CT_date.h"
#include "CT_tables.h"
#include "CT_file.h"
#include "custom/CT_ctm.h"

extern int ct_opt_g;

static float _ctCustomBaseValue() {
  return ((rand() % 10000) + 1000) * 0.000001;
}

static void _ctCustomConsumption() {
  ctUT02Data_t data;
  float value = _ctCustomBaseValue();
  time_t etime = time(NULL);
  struct tm* now = gmtime(&etime);
  switch(abs(ct_opt_g) % 2) {
    case 0: // Company behavior
      if(now->tm_wday == 0) // Sunday
        value /= 3 + rand() % 5;
      else if(now->tm_hour > 8 && now->tm_hour < 18)
        value *= 2 + rand() % 5;
    break;
    case 1: // Home behavior
      if(now->tm_wday == 0) // Sunday
        value *= 2 + rand() % 4;
      if(now->tm_hour > 18 && now->tm_hour < 23)
        value *= 2 + rand() % 5;
    break;
    default: // NOTE: won't reach this point
      fprintf(stderr, "ERROR: Invalid option %d\n", ct_opt_g);
      return;
  }
  data.value = value;
  ctGetLTimeDate(&data.timestamp);
  ctWrite(CT__UT02, &data, sizeof data, 0);
}

void ctGetConsumption() { _ctCustomConsumption(); }
