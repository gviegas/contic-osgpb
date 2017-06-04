//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_DC_H
#define CT_DC_H

#include "CT_defs.h"
#include "CT_net.h"
#include "CT_apdu.h"

// Exec DC request flow
//
// TODO: target and addr should be set once with DcStart - remove from here
//
int ctDcExec(ctTarget_t* target, ctAddr_t* addr, ctAddr_t* destinations,
  ctParam_t* messages, ctResponse_t* responses, size_t count);

// Start the DC
//
int ctDcStart(ctTarget_t* target, ctAddr_t* addr);

#endif // CT_DC_H
