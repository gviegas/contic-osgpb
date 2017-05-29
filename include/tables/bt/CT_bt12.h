//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT12_H
#define CT_BT12_H

#include <stdint.h>
#include <stdbool.h>

// BT12 - Unit of Measure Entry 
//
typedef struct {
  unsigned id_code : 8;
  unsigned time_base : 3;
  unsigned multiplier : 3;
  bool q1 : 1;
  bool q2 : 1;
  bool q3 : 1;
  bool q4 : 1;
  bool net_flow : 1;
  unsigned segmentation : 3;
  unsigned harmonic : 1;
  unsigned : 8;
  bool non_standard_defined : 1;
} ctBT12_t;

#endif // CT_BT12_H