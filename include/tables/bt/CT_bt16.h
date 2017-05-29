//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT16_H
#define CT_BT16_H

#include <stdint.h>
#include <stdbool.h>

// BT16 - Source Definition 
//
typedef struct {
  bool unit_measure : 1;
  bool demand_control : 1;
  bool data_control : 1;
  bool constants : 1;
  bool pulse : 1;
  bool applied : 1;
  unsigned : 2;
} ctBT16_t;

#endif // CT_BT16_H