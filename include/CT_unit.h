//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_UNIT_H
#define CT_UNIT_H

#include "CT_defs.h"
#include "CT_net.h"

// Unit default commission configuration
//
// NOTE: For Units only (no DCs)
//
int ctUnitDefaultCommission();

// Start the Unit
//
int ctUnitStart(ctTarget_t* target, ctAddr_t* addr);

#endif // CT_UNIT_H
