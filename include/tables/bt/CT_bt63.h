//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT63_H
#define CT_BT63_H

#include <stdint.h>
#include <stdbool.h>

// BT63 - Load Profile Status
//
typedef struct {
  unsigned block_order : 1;
  bool overflow : 1;
  unsigned list_type : 1;
  bool block_inhibit_overflow : 1;
  unsigned interval_order : 1;
  bool active_mode : 1;
  unsigned test_mode : 1;
  bool : 1; // smh...
  uint16_t number_valid_blocks;
  uint16_t last_block;
  uint32_t last_block_sequence_number;
  uint16_t number_unread_blocks;
  uint16_t number_valid_intervals;
} ctBT63_t;

#endif // CT_BT63_H