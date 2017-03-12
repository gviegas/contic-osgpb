//
// Created by Gustavo Viegas on 2017/03
//

#include "CT_table_access.h"
#include <string.h>

int ctTableOp(ctParam_t* param, ctTarget_t* target) {
  // to do
  // test
  if(param->service == RESPONSE_FULL_READ) {
    uint8_t d[] = {0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06};
    param->r_response->response = 0;
    param->r_response->count = sizeof d;
    memcpy(param->r_response->data, d, sizeof d);
  }
  // end test
  return 0;
}