//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_FILE_H
#define CT_FILE_H

#include "CT_defs.h"

// File read
//
int ctRead(uint16_t table_id, void* buffer, size_t count, size_t offset);

// File write
//
int ctWrite(uint16_t table_id, void* buffer, size_t count, size_t offset);

#endif // CT_FILE_H