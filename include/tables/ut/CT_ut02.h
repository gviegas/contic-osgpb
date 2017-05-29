//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_UT02_H
#define CT_UT02_H

#include "CT_ut01.h"

// Consumption data type
//
typedef struct {
  float value;
  ctLTimeDate_t timestamp;
} ctUT02Data_t;

// Unified Table 02 - Consumption data
//
typedef struct {
  ctUT02Data_t data[CT__UT01_NENT];
} ctUT02_t;

#endif // CT_UT02_H
