//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT64_H
#define CT_BT64_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// Load Profile data
//
typedef struct {
  ctStimeDate_t end_time;
  uint32_t end_readings[256]; // to do: length macro
  bool simple_status[256/8]; // to do: length macro
  uint8_t intervals[256]; // to do: length macro
  // uint8_t extended_status[256/2];
  // uint32_t interval_channel_data[256];
  // int32_t interval_channel_value;
} ctLoadProfile_t;

// BT64 - Load Profile Data
//
typedef struct {
  ctLoadProfile_t block_data[256]; // to do: length macro
} ctBT64_t;

#endif // CT_BT64_H