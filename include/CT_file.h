//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_FILE_H
#define CT_FILE_H

#include "CT_definitions.h"

#define CT__BLOCK_LEN 10
#define CT__DATAFILE "d.block"

// Block entry type
//
typedef struct {
  uint16_t size;
  uint32_t offset;
  uint8_t type;
} ctBlockEntry_t;

// Block index type
//
typedef struct {
  uint16_t table_id;
  uint16_t index;
  uint8_t used;
} ctBlockIndex_t;

// Block type
//
typedef struct {
  ctBlockIndex_t indexes[CT__BLOCK_LEN];
  ctBlockEntry_t entries[CT__BLOCK_LEN];
} ctBlock_t;

// Create Data file
//
int ctCreate();

// Get block entry
//
int ctGetBlockEntry(uint16_t table_id, ctBlockEntry_t* entry);

// File read
//
int ctRead(uint16_t table_id, void* buffer, size_t count, size_t offset);

// File write
//
int ctWrite(uint16_t table_id, void* buffer, size_t count, size_t offset);

// File seek
//
int ctSeek(uint16_t table_id, size_t offset, void* file);

#endif // CT_FILE_H
