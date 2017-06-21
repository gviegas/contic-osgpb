//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT20_H
#define CT_BT20_H

#include <stdint.h>
#include <stdbool.h>

// BT20 - Dimension Register
//
typedef struct {
  bool season_info_field : 1;
  bool date_time_field : 1;
  bool demand_reset_counter : 1;
  bool demand_reset_lockout : 1;
  bool cumulative_demand : 1;
  bool continuous_cumulative_demand : 1;
  bool time_remaining : 1;
  bool : 1;
  bool self_read_inhibit_overflow : 1;
  bool self_read_sequence_number: 1;
  bool daily_self_read : 1;
  bool weekly_self_read : 1;
  unsigned self_read_demand_reset : 2;
  unsigned : 2;
  uint8_t number_self_reads;
  uint8_t number_summations;
  uint8_t number_demands;
  uint8_t number_coincident_values;
  uint8_t number_occurrences;
  uint8_t number_tiers;
  uint8_t number_present_demands;
  uint8_t number_present_values;
} ctBT20_t;

#endif // CT_BT20_H