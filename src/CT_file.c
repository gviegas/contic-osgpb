//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_tables.h"
#include "CT_file.h"

static FILE* _ct_f = NULL;

int ctCreate() {
  if(!_ct_f) {
    if(!(_ct_f = fopen(CT__DATAFILE, "w+b"))) {
      fprintf(stderr, "ERROR: Could not create data file\n");
      return CT__FAILURE;
    }
  } else
    rewind(_ct_f);

  ctBlock_t block;
  memset(&block, 0, sizeof block);
  // BT00
  block.indexes[0] = (ctBlockIndex_t) {CT__BT00, 0, 1};
  block.entries[0] = (ctBlockEntry_t) {sizeof(ctBT00_t), 0, CT__TTYPE_RDONLY};
  // UT01
  block.indexes[1] = (ctBlockIndex_t) {CT__UT01, 1, 1};
  block.entries[1] = (ctBlockEntry_t) {sizeof(ctUT01_t),
    block.entries[0].size + block.entries[0].offset, CT__TTYPE_EVENT};
  // UT02
  block.indexes[2] = (ctBlockIndex_t) {CT__UT02, 2, 1};
  block.entries[2] = (ctBlockEntry_t) {sizeof(ctUT02_t),
    block.entries[1].size + block.entries[1].offset, CT__TTYPE_RDWR};

  fwrite(&block, 1, sizeof block, _ct_f);
  fflush(_ct_f);
  return CT__SUCCESS;
}

int ctGetBlockEntry(uint16_t table_id, ctBlockEntry_t* entry) {
  if(!_ct_f) {
    if(!(_ct_f = fopen(CT__DATAFILE, "r+b"))) {
      fprintf(stderr, "ERROR: Could not open data file\n");
      return CT__FAILURE;
    }
  } else
    rewind(_ct_f);
  int i, count;
  ctBlockIndex_t index[CT__BLOCK_LEN];
  memset(index, 0, sizeof index);
  count = fread(index, sizeof index[0], CT__BLOCK_LEN, _ct_f);
  if(count != CT__BLOCK_LEN)
    fprintf(stderr, "ERROR: Could not read index block\n");
  else {
    for(i = 0; i < count; ++i) {
      if(index[i].used && index[i].table_id == table_id) {
        fseek(_ct_f, sizeof index + sizeof *entry * index[i].index, SEEK_SET);
        count = fread(entry, sizeof *entry, 1, _ct_f);
        if(count != 1) {
          fprintf(stderr, "ERROR: Could not read block entry\n");
          break;
        }
        return CT__SUCCESS;
      }
    }
  }
  return CT__FAILURE;
}

int ctRead(uint16_t table_id, void* buffer, size_t count, size_t offset) {
  if(!_ct_f) {
    if(!(_ct_f = fopen(CT__DATAFILE, "r+b"))) {
      fprintf(stderr, "ERROR: Could not open data file\n");
      return 0;
    }
  }
  int c, sz;
  sz = ctSeek(table_id, offset, _ct_f);
  if(sz < 1)
    c = -1;
  else
    c = count ? fread(buffer, 1, count, _ct_f) : fread(buffer, 1, sz, _ct_f);
  return c;
}

int ctWrite(uint16_t table_id, void* buffer, size_t count, size_t offset) {
  if(!_ct_f) {
    if(!(_ct_f = fopen(CT__DATAFILE, "r+b"))) {
      fprintf(stderr, "ERROR: Could not open data file\n");
      return 0;
    }
  }
  int c, sz;
  sz = ctSeek(table_id, offset, _ct_f);
  if(sz < 1)
    c = -1;
  else {
    c = count ? fwrite(buffer, 1, count, _ct_f) : fwrite(buffer, 1, sz, _ct_f);
    fflush(_ct_f);
  }
  return c;
}

int ctSeek(uint16_t table_id, size_t offset, void* file) {
  if(!file) {
    fprintf(stderr, "ERROR: Invalid file\n");
    return 0;
  }
  int i, count;
  ctBlockEntry_t entry;
  ctBlockIndex_t index[CT__BLOCK_LEN];
  memset(index, 0, sizeof index);
  rewind(file);
  count = fread(index, sizeof index[0], CT__BLOCK_LEN, file);
  for(i = 0; i < count; ++i) {
    if(index[i].used && index[i].table_id == table_id) {
      fseek(file, sizeof index + sizeof entry * index[i].index, SEEK_SET);
      count = fread(&entry, sizeof entry, 1, file);
      if(count != 1) break;
      fseek(file, sizeof(ctBlock_t) + entry.offset + offset, SEEK_SET);
      return entry.size;
    }
  }
  fprintf(stderr, "ERROR: Failed to seek position for table %d\n", table_id);
  return -1;
}
