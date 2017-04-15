//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT22_H
#define CT_BT22_H

#include <stdint.h>
#include <stdbool.h>

// BT22 - Data Selection
//
// DBL: read previous tables to know number of entries,
// do not use static size (?)
typedef struct {
  uint8_t summation_sources[256]; // to do: length macro
  uint8_t demand_select[256]; // to do: length macro
  bool min_max_flags[256/8]; // to do: length macro
  uint8_t coincident_select[256]; // to do: length macro
  uint8_t coincident_demand_assoc[256]; // to do: length macro
} ctBT22_t;

#endif // CT_BT22_H