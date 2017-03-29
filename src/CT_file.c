//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_file.h"

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
  return 0;
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
  return 0;
}