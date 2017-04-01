//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET21_H
#define CT_ET21_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// ET021 - Load Profile Internal Configuration
//
typedef struct {
  uint32_t current_block_addr;
  uint32_t current_interval_addr;
  uint32_t block_size;
  uint16_t block_header_size;
  uint16_t number_valid_blocks;
  uint16_t number_valid_intervals;
  uint16_t last_block_index;
  uint16_t last_interval_number;
  uint8_t simple_status_offset_block;
  uint8_t simple_status_size;
  uint8_t interval_0_offset_block;
  uint8_t interval_size;
  uint8_t channel_0_offset_interval;
  uint8_t extended_status_common;
  uint8_t number_channels;
  uint8_t interval_time;
  uint8_t sources[8];
  int32_t placeholders[8];
  uint8_t sources_expansion[8];
  uint32_t lp_config_id;
  uint8_t mep_billing_start_channel;
  ctLtimeDate_t block_start_time;
  uint8_t block_start_hour;
  uint8_t block_start_minute;
  uint16_t interval_progress;
  uint8_t lp_options;
  ctLtimeDate_t interval_end_time_utc;
  ctLtimeDate_t interval_end_time_local;
} ctET21_t;

#endif // CT_ET21_H