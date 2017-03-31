//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT54_H
#define CT_BT54_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// Calendar Action bit field
//
typedef struct {
  unsigned action : 5;
  bool demand_reset : 1;
  bool self_read : 1;
  bool : 1;  
} ctCalendarAction_t;

// Non Recurring Date record
//
typedef struct {
  ctDate_t non_recurring_date;
  // this action shouldn't be here this specification is SO FUCKED UP
  ctCalendarAction_t action;
} ctNonRecurrDate_t;

// Recurring Date record
//
typedef struct {
  ctRdate_t recurring_date;
  // ... should be here
  // ctCalendarAction_t action;
} ctRecurrDate_t;

// Tier Switch record
//
typedef struct {
  unsigned tier : 2;
  unsigned : 3;
  unsigned hour : 5;
  unsigned minute : 6;
  uint8_t schedule;
} ctTierSwitch_t;

// Season Schedule record
typedef struct {
  uint8_t saturday;
  uint8_t sunday;
  uint8_t weekday;
  uint8_t special_schedule_0;
  uint8_t special_schedule_1;
} ctSeasonSchedule_t;

// BT54 - Calendar
//
typedef struct {
  ctNonRecurrDate_t non_recurring_dates[256]; // to do: length macro
  ctRecurrDate_t recurring_dates[256]; // to do: length macro
  ctTierSwitch_t tier_switches[256]; // to do: length macro
  ctSeasonSchedule_t season_schedules[256]; // to do: length macro
  uint32_t calendar_id;
} ctBT54_t;

#endif // CT_BT54_H