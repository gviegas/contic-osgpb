//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT13_H
#define CT_BT13_H

#include <stdint.h>

// BT13 - Demand Control 
//
typedef struct {
  uint8_t reset_exclusion;
  uint8_t power_fail_recognition_time;
  uint8_t power_fail_exclusion;
  uint8_t cold_load_pickup;
  uint16_t interval_value[256]; // to do: length macro
  uint8_t sub_interval;
  uint8_t interval_multiplier;
} ctBT13_t;

#endif // CT_BT13_H