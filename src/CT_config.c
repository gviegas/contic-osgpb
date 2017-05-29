//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <time.h>
#include "CT_config.h"

int ct_opt_g = 0x80000001;

void ctConfig(void* opt) {
  if(!opt) return;
  ct_opt_g = *((int*) opt);
  srand(time(NULL) + ct_opt_g);
}
