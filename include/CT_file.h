//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_FILE_H
#define CT_FILE_H

#include "CT_defs.h"

#define CT__DATAFILE "d.block"

// Create Data file
//
// NOTE: Call this once - It will destroy any data block previously created
//
int ctCreate(/*uint16_t block_size, uint32_t count*/);

// File read
//
int ctRead(uint16_t table_id, void* buffer, size_t count, size_t offset);

// File write
//
int ctWrite(uint16_t table_id, void* buffer, size_t count, size_t offset);

#endif // CT_FILE_H