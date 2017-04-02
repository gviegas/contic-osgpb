//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET01_H
#define CT_ET01_H

#include <stdbool.h>
#include "CT_date.h"

// Measure Data type
//
typedef struct {
  uint16_t value_high;
  uint16_t value_low;
  ctLTimeDate_t timestamp;
} ctMeasureData_t;

// ET01 - Simplified Measurement Data [Manufacturer Specific]
//
typedef struct {
  ctMeasureData_t measure_data[10+10+10+10]; // should be ET00.measure_info[i...n].number_entries
} ctET01_t;

#endif