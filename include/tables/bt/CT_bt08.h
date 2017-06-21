//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT08_H
#define CT_BT08_H

#include <stdint.h>
#include <stdbool.h>

// BT08 - Procedure Response
//
typedef struct {
  unsigned procedure_number : 12;
  unsigned : 4;
  uint8_t result_code;
} ctBT08_t;

#endif // CT_BT08_H