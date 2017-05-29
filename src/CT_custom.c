//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include "CT_date.h"
#include "CT_tables.h"
#include "CT_file.h"
#include "CT_custom.h"

static int _ct_opt = 1;

static float _ctBaseValue() {
  return ((rand() % 10000) + 1000) * 0.000001;
}

// NOTE: Need to call srand() somewhere
static void _ctCustomConsumption() {
  ctUT02Data_t data;
  float value = _ctBaseValue();
  time_t etime = time(NULL);
  struct tm* now = gmtime(&etime);
  switch(_ct_opt) {
    case 1: // temp
      if(now->tm_wday == 0) // Sunday
        value /= 3 + rand() % 5;
      else if(now->tm_hour > 8 && now->tm_hour < 18)
        value *= 2 + rand() % 5;
    break;
    case 2: // temp
      if(now->tm_wday == 0) // Sunday
        value *= 2 + rand() % 4;
      if(now->tm_hour > 18 && now->tm_hour < 23)
        value *= 2 + rand() % 5;
    break;
    default:
      fprintf(stderr, "Invalid option\n");
  }
  data.value = value;
  ctGetLTimeDate(&data.timestamp);
  ctWrite(CT__UT02, &data, sizeof data, 0);
}

void ctGetConsumption() { _ctCustomConsumption(); }
