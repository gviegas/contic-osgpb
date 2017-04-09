//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_INTERNAL_H
#define CT_INTERNAL_H

#include "CT_tables.h"

#define CT__BEHAVIOR_E 1
#define CT__BEHAVIOR_H 2

// Real Time Consumption (sim)
//
int ctMeasureNow(ctMeasureData_t* buffer, ctMeasureInfo_t* info, int opt);

#endif // CT_INTERNAL_H