//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT07_H
#define CT_BT07_H

#include <stdint.h>
#include <stdbool.h>

// BT07 - Procedure Initiate
//
typedef struct {
  unsigned procedure_number : 12;
  unsigned response_handling : 4;
  uint8_t sequence_number;
} ctBT07_t;

#endif // CT_BT07_H