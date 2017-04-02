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
  uint8_t number_entries;
} ctMeasureInfo_t;

// ET00 - Simplified Measurement Info [Manufacturer Specific]
//
typedef struct {
  ctLTimeDate_t clock;
  
  // Clock synchronization
  ctLTimeDate_t sync;
  uint8_t sync_timer_sec;
  bool sync_programmed : 1;
  bool keep_records_on_sync : 1;

  // Resume measurements after a powerdown
  bool resume_on_powerdown : 1;
  
  // Clear memory of all devices
  bool purge_all_records : 1;
  
  // Measurement devices
  uint8_t measure_devices_used : 4;
  // uint8_t number_minfo_entries; // currently using static allocation
  ctMeasureInfo_t measure_info[4];
} ctET00_t;

#endif // CT_ET00_H