//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET00_H
#define CT_ET00_H

#include <stdbool.h>
#include "CT_date.h"

// Measure Info type
//
// NOTE: this won't be of much use due to
// restrictions on dynamic memory allocation
//
typedef struct {
  uint8_t id;
  uint8_t type;
  ctTime_t polling_delay;
  uint8_t num_entries;
  uint8_t used;
} ctMeasureInfo_t;

// ET00 - Simplified Measurement Info [Manufacturer Specific]
//
typedef struct {
  ctMeasureInfo_t measure_info[4];
} ctET00_t;

#endif // CT_ET00_H
