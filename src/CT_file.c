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
// } ctTableOffset_t;

int ctRead(uint16_t table_id, void* buffer, size_t count, size_t offset) {
  // test
  // printf("\ntid: %d\n", table_id);
  // printf("count: %d\n", count);
  // printf("offset: %d\n", offset);
  // end test
  FILE* f = fopen(CT__DBLOCK, "rb");
  if(!f) {
    fprintf(stderr, "\nERROR: Could not open data block\n");
    return 0;
  }
  int c = fread(buffer, 1, count, f);
  fclose(f);
  return c;
}

int ctWrite(uint16_t table_id, void* buffer, size_t count, size_t offset) {
  // test
  // printf("\ntid: %d\n", table_id);
  // printf("count: %d\n", count);
  // printf("offset: %d\n", offset);
  // int i = 0;
  // for(; i < count; ++i) printf("%x ", ((uint8_t*)buffer)[i]);
  // printf("\n");
  // end test
  FILE* f = fopen(CT__DBLOCK, "ab");
  if(!f) {
    fprintf(stderr, "\nERROR: Could not open data block\n");
    return 0;
  }
  int c = fwrite(buffer, 1, count, f);
  fclose(f);
  return c;
}