//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_TABLE_ACCESS_H
#define CT_TABLE_ACCESS_H

#include "CT_definitions.h"
#include "CT_apdu.h"

// Table Read Operation
//
int ctTableRead(ctParam_t* param, ctTarget_t* target);

// Table Write Operation
//
int ctTableWrite(ctParam_t* param, ctTarget_t* target);

#endif // CT_TABLE_ACCESS_H