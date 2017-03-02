//
// Created by Gustavo Viegas on 2017/02
//

#include <stdio.h>
#include "table_services.h"

int main(int argc, char** argv) {
  uint8_t p[] = {1,2,4,6,8,10,15};
  ctApdu_t m = ctFullWriteRequest(0xabcd, sizeof p, p);
  int i;
  for(i = 0; i <= 5 + sizeof p; ++i)
    printf("%x ", m.apdu[i]);
  printf("\nsize of msg: %zu\n", sizeof m);
  return 0;
}