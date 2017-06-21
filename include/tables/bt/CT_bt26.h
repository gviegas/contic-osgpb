//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT26_H
#define CT_BT26_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// Self Read Data record
//
typedef struct {
  uint16_t bidn;
  ctSTimeDate_t time_date;
  uint8_t season;
} ctSelfRead_t;

// BT26 - Self Read Data
//
typedef struct {
  bool order : 1;
  bool overflow : 1;
  bool list_type : 1;
  bool inhibit_overflow : 1;
  unsigned : 4;
  uint8_t number_valid_entries;
  uint8_t last_entry_element;
  uint16_t last_entry_sequence_number;
  uint8_t number_unread_entries;
  ctSelfRead_t self_read_data_records[256]; // todo: length macro
} ctBT26_t;

#endif // CT_BT26_H