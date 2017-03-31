//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT50_H
#define CT_BT50_H

#include <stdint.h>
#include <stdbool.h>

// BT50 - Dimension Time and TOU
//
typedef struct {
  bool tou_self_read : 1;
  bool season_self_read : 1;
  bool season_demand_rest : 1;
  bool season_change_armed : 1;
  bool sort_dates : 1;
  bool anchor_date : 1;
  unsigned : 2;
  bool daylight_saving_time_auto : 1;
  bool separate_weekdays : 1;
  bool separate_summation_demands : 1;
  bool sort_tier_switches : 1;
  bool capable_time_zone_offset : 1;
  unsigned : 3;
  unsigned number_seasons : 4;
  unsigned number_special_schedules : 4;
  uint8_t number_non_recurring_dates;
  uint8_t number_recurring_dates;
  uint16_t number_tier_switches;
  uint16_t calendar_table_size;
} ctBT50_t;

#endif // CT_BT50_H