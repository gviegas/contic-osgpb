//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET42_H
#define CT_ET42_H

#include <stdint.h>
#include <stdbool.h>

// Log Info type
typedef struct {} ctLogInfo_t; // to do

// Sources type
typedef struct {} ctSource_t; // to do

// ET42 - Interface Definition
//
typedef struct {
  uint16_t table_length;
  uint8_t fixed_section_length;
  uint8_t log_list_size;
  uint16_t interface_compatibility_settings;
  uint16_t c1219_compliance;
  // Billing Interface info
  uint16_t bidn;
  uint8_t bi_flags;
  uint8_t number_self_reads;
  uint8_t number_summations;
  uint8_t number_demands;
  uint8_t number_coincident_values;
  uint8_t number_occurrences;
  uint8_t number_tiers;
  uint8_t number_present_demands;
  uint8_t number_present_values;
  uint8_t demand_subinterval;
  uint8_t demand_multiplier;
  uint16_t tier_size;
  // Load Profile info
  uint32_t block_size;
  uint16_t number_blocks;
  uint8_t number_channels;
  uint8_t interval_duration;
  uint8_t interval_size;
  uint8_t options;
  uint16_t intervals_per_block;
  uint8_t block_start_hour;
  uint8_t block_start_minute;
  // History Log info
  uint8_t hl_flags;
  uint16_t hl_count;
  uint8_t hl_entry_size;
  // to do: last fields (actually, figure out wtf the spec means)
} ctET42_t;

#endif // CT_ET42_H