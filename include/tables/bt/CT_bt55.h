//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT55_H
#define CT_BT55_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// BT55 - Clock State
//
typedef struct {
  ctLTimeDate_t clock_calendar;
  unsigned day_week : 3;
  bool daylight_saving_time : 1;
  bool greenwich_mean_time : 1;
  bool time_zone_applied : 1;
  bool dst_applied : 1;
  bool : 1;
  unsigned current_tier : 3;
  unsigned : 3;
  unsigned tier_drive : 2;
  unsigned special_schedule_active : 4;
  unsigned season : 4;
} ctBT55_t;

#endif // CT_BT55_H