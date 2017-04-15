//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_file.h"
#include "CT_tables.h"

// typedef struct {
//   uint16_t table_id;
//   long offset;
// } _ctTableOffset_t;
typedef struct {
  uint32_t bt00;
  uint32_t et00;
  uint32_t et01;
} _ctTableOffset_t;

static size_t _ctGetOffset(uint16_t table_id, FILE* f) {
  _ctTableOffset_t to;
  size_t n = sizeof to;
  fseek(f, 0, SEEK_SET);
  if(fread(&to, 1, n, f) != n)
    fprintf(stderr, "\nERROR: Could not read index block\n");
  else {
    switch(table_id) {
      case CT__BT00: return (sizeof to + 0);
      case CT__ET00: return (sizeof to + to.bt00);
      case CT__ET01: return (sizeof to + to.bt00 + to.et00);
      default:
        fprintf(stderr, "\nERROR: Invalid table id\n");
    }
  }
  return 0;
}

int ctCreate(/*uint16_t block_size, uint32_t count*/) {
  // Temporary (hastily done) solution
  // To do: design a better system to manage the tables in memory
  FILE* f = fopen(CT__DATAFILE, "wb");
  if(!f) {
    fprintf(stderr, "\nERROR: Could not create data file\n");
    return CT__FAILURE;
  }
  // Static size tables...
  _ctTableOffset_t to = {sizeof(ctBT00_t), sizeof(ctET00_t), sizeof(ctET01_t)};
  fwrite(&to, 1, sizeof to, f);
  fclose(f);
  return CT__SUCCESS;
}

int ctRead(uint16_t table_id, void* buffer, size_t count, size_t offset) {
  FILE* f = fopen(CT__DATAFILE, "rb");
  if(!f) {
    fprintf(stderr, "\nERROR: Could not open data file\n");
    return 0;
  }
  size_t to = _ctGetOffset(table_id, f) + offset;
  fseek(f, to, SEEK_SET);
  int c = fread(buffer, 1, count, f);
  fclose(f);
  return c;
}

int ctWrite(uint16_t table_id, void* buffer, size_t count, size_t offset) {
  FILE* f = fopen(CT__DATAFILE, "r+b");
  if(!f) {
    fprintf(stderr, "\nERROR: Could not open data file\n");
    return 0;
  }
  size_t to = _ctGetOffset(table_id, f) + offset;
  fseek(f, to, SEEK_SET);
  int c = fwrite(buffer, 1, count, f);
  fclose(f);
  return c;
}