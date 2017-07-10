//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_file.h"
#include "CT_state.h"
#include "CT_table_access.h"

int ctTableRead(ctParam_t* param, ctTarget_t* target) {
  int c;
  uint16_t table_id = ((uint16_t)param->r_response->request[2] << 8) |
    ((uint16_t)param->r_response->request[3] & 0x00ff);

  if(param->service == RESPONSE_FULL_READ)
    c = ctRead(table_id, param->r_response->data, 0, 0);
  else if(param->service == RESPONSE_PART_READ) {
    size_t count = ((uint16_t)param->r_response->request[7] << 8) |
      ((uint16_t)param->r_response->request[8] & 0x00ff);
    size_t offset =
      (((uint32_t)param->r_response->request[4] << 16) & 0x00ff0000) |
      (((uint32_t)param->r_response->request[5] << 8) & 0x0000ff00) |
      ((uint32_t)param->r_response->request[6] & 0x000000ff);
    c = ctRead(table_id, param->r_response->data, count, offset);
  } else {
    fprintf(stderr, "ERROR: Invalid table read operation\n");
    return CT__FAILURE;
  }

  param->r_response->count = c;
  // TODO: service error check
  param->r_response->response = c > 0 ? CT__RES_OK : CT__RES_ERR;

  return CT__SUCCESS;
}

int ctTableWrite(ctParam_t* param, ctTarget_t* target) {
  int c;
  uint16_t table_id = ((uint16_t)param->w_response->request[2] << 8) |
    ((uint16_t)param->w_response->request[3] & 0x00ff);

  if(param->service == RESPONSE_FULL_WRITE) {
    size_t count = ((uint16_t)param->w_response->request[4] << 8) |
      ((uint16_t)param->w_response->request[5] & 0x00ff);
    c = ctWrite(table_id, param->w_response->request+6, count, 0);
  } else if(param->service == RESPONSE_PART_WRITE) {
    size_t count = ((uint16_t)param->w_response->request[7] << 8) |
      ((uint16_t)param->w_response->request[8] & 0x00ff);
    size_t offset =
      (((uint32_t)param->w_response->request[4] << 16) & 0x00ff0000) |
      (((uint32_t)param->w_response->request[5] << 8) & 0x0000ff00) |
      ((uint32_t)param->w_response->request[6] & 0x000000ff);
    c = ctWrite(table_id, param->w_response->request+9, count, offset);
  } else {
    fprintf(stderr, "ERROR: Invalid table write operation\n");
    return CT__FAILURE;
  }

  // TODO: service error check
  param->w_response->response = c > 0 ? CT__RES_OK : CT__RES_ERR;

  // Notify state change
  ctStateHasChanged(table_id);

  return CT__SUCCESS;
}
