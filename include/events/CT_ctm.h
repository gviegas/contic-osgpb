//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_CTM_H
#define CT_CTM_H

#include <stdint.h>

// Store consumption on UT02 as specified on UT01
//
void ctGetConsumption();

// Set number of records to keep on UT02
//
void ctSetNumEntries(uint8_t n);

#endif // CT_CTM_H
