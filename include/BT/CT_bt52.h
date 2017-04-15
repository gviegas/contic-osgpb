//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT52_H
#define CT_BT52_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// BT52 - Clock
//
typedef struct {
  ctLTimeDate_t clock_calendar;
  unsigned day_week : 3;
  bool daylight_saving_time : 1;
  bool greenwich_mean_time : 1;
  bool time_zone_applied : 1;
  bool dst_applied : 1;
  bool : 1;
} ctBT52_t;

#endif // CT_BT52_H