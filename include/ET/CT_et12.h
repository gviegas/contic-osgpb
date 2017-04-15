//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET12_H
#define CT_ET12_H

#include <stdint.h>
#include <stdbool.h>

// Daily Consumption type
//
typedef struct {
  uint32_t active_forward;
  uint32_t active_reverse;
  uint32_t reactive_import;
  uint32_t reactive_export; 
} ctDailyConsumption_t;

// ET12 - Daily Consumption
//
typedef struct {
  ctDailyConsumption_t last_day_consumption[256]; // todo: len should be taken from et04.55 
  ctDailyConsumption_t today_consumption[256]; // todo: len should be taken from et04.55
} ctET12_t;

#endif // CT_ET12_H