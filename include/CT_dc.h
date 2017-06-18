//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_DC_H
#define CT_DC_H

#include "CT_definitions.h"
#include "CT_net.h"
#include "CT_apdu.h"

// DC Exec Info type
//
typedef struct {
  ctAddr_t* destinations;
  ctParam_t* messages;
  size_t count;
} ctDcExecInfo_t;

// Exec DC request flow
//
int ctDcExec(ctDcExecInfo_t* info);

// Start the DC
//
int ctDcStart(ctTarget_t* target, ctAddr_t* addr, char* in, char* out);

#endif // CT_DC_H
