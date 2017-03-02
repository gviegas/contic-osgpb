//
// Created by Gustavo Viegas on 2017/02
//

#include <stdio.h>
#include "CT_table_services.h"

int main(int argc, char** argv) {
  uint8_t b[1024], d[] = {0xd1,0xd3,0xd6}, o[] = {0,1,1};
  int i, s = ctWriteResponse(b, CT__RES_ERR);
  for(i = 0; i < s; ++i) printf("%x\n", b[i]);
  printf("\nsize of msg: %zu\n", sizeof b);
  return 0;
}