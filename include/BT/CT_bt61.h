//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT61_H
#define CT_BT61_H

#include <stdint.h>
#include <stdbool.h>

// BT61 - Actual Load Profile
//
typedef struct {
  uint32_t memory_length;
  bool set_1_inhibit_overflow : 1;
  bool set_2_inhibit_overflow : 1;
  bool set_3_inhibit_overflow : 1;
  bool set_4_inhibit_overflow : 1;
  bool end_reading_supported : 1;
  bool end_pulse_supported : 1;
  bool set_1_scalar_divisor_enabled : 1;
  bool set_2_scalar_divisor_enabled : 1;
  bool set_3_scalar_divisor_enabled : 1;
  bool set_4_scalar_divisor_enabled : 1;
  bool extended_interval_status : 1;
  bool simple_interval_status : 1;
  unsigned : 4;
  bool uint8_supported : 1;
  bool uint16_supported : 1;
  bool uint32_supported : 1;
  bool int8_supported : 1;
  bool int16_supported : 1;
  bool int32_supported : 1;
  bool nifmat1_supported : 1;
  bool nifmat2_supported : 1;
  uint16_t number_blocks_set_1;
  uint16_t number_intervals_set_1;
  uint8_t number_channels_set_1;
  uint8_t max_interval_time_set_1;
} ctBT61_t;

#endif // CT_BT61_H