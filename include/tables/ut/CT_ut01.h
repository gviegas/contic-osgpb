//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_UT01_H
#define CT_UT01_H

#include <stdint.h>
#include "CT_date.h"

#define CT__UT01_NENT 5

// Unified Table 01 - Consumption info
//
typedef struct {
  uint8_t id;
  uint8_t type;
  uint32_t delay_s;
  uint8_t num_entries;
} ctUT01_t;

#endif // CT_UT01_H
