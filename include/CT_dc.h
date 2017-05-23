//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_DC_H
#define CT_DC_H

#include "CT_defs.h"
#include "CT_net.h"

// DC default commission configuration
//
// NOTE: For DCs only (no Units)
//
int ctDcDefaultCommission();

// Start the DC
//
int ctDcStart(ctTarget_t* target, ctAddr_t* addr, ctAddr_t* destinations,
  ctParam_t* messages, ctResponse_t* responses, size_t count);

#endif // CT_DC_H
