//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT05_H
#define CT_BT05_H

#include <stdint.h>

// BT05 - Device Identification
//
typedef struct {
  // NOTE: Packed BCD encoding - each entry will hold TWO values
  uint8_t identification[10];
} ctBT05_t;

#endif // CT_BT05_H