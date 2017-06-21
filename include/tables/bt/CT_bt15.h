//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT15_H
#define CT_BT15_H

#include <stdint.h>
#include <stdbool.h>

// BT15 - Constants 
//
typedef struct {
  uint32_t multiplier;
  uint32_t offset;
  bool applied : 1;
  unsigned : 7;
  uint32_t ratio_f;
  uint32_t ratio_p;
} ctBT15_t;

#endif // CT_BT15_H