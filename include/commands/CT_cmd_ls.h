//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_CMD_LS_H
#define CT_CMD_LS_H

#include "CT_defs.h"
#include "CT_net.h"

// List command
//
int ctCmdLs(char names[][CT__NAMELEN], ctAddr_t* addresses, size_t len);

#endif // CT_CMD_LS_H
