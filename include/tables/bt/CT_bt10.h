//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT10_H
#define CT_BT10_H

#include <stdint.h>
#include <stdbool.h>

// BT10 - Dimension Sources Limiting 
//
typedef struct {
  bool power_fail_exclusion : 1;
  bool reset_exclusion : 1;
  bool block_demand : 1;
  bool sliding_demand : 1;
  bool thermal_demand : 1;
  bool set_1_constants : 1;
  bool set_2_constants : 1;
  bool : 1;
  uint8_t number_uom_entries;
  uint8_t number_demand_control_entries;
  uint8_t data_control_length;
  uint8_t number_data_control_entries;
  uint8_t number_constants_entries;
  uint8_t constants_selector;
  uint8_t number_sources;
} ctBT10_t;

#endif // CT_BT10_H