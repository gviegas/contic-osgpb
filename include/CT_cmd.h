//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_CMD_H
#define CT_CMD_H

#include "CT_apdu.h"
#include "CT_net.h"

// Start the command interpreter
//
int ctCmdStart(int interactive);

// Print response
//
void ctCmdPrint(ctAddr_t* addr, ctResponse_t* res);

// Print error
//
void ctCmdErr(ctAddr_t* addr, char* err);

#endif // CT_CMD_H
