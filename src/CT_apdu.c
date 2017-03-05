//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_apdu.h"
#include "CT_table_services.h"
#include "CT_security.h"

int ctCreateApdu(ctApdu_t* apdu, ctParam_t* param, ctTarget_t* target) {
  int c = 1;
  apdu->apdu[0] = CT__TYPE_CODE;
  switch(param->service) {
    case REQUEST_FULL_READ:
      c += ctFullReadRequest(apdu->apdu+c, param->fr_request->table_id);
      memcpy(apdu->apdu+c, target->sequence, CT__LEN_SEQN);
      c += CT__LEN_SEQN;
      c += ctAuthenticate(apdu->apdu+c, apdu->apdu, NULL, c, 0, target);
    break;
    case REQUEST_PART_READ:
      c += ctPartialReadRequest(apdu->apdu+c, param->pr_request->table_id, 
        param->pr_request->offset, param->pr_request->count);
      memcpy(apdu->apdu+c, target->sequence, CT__LEN_SEQN);
      c += CT__LEN_SEQN;
      c += ctAuthenticate(apdu->apdu+c, apdu->apdu, NULL, c, 0, target);
    break;
    case REQUEST_FULL_WRITE:
      c += ctFullWriteRequest(apdu->apdu+c, param->fw_request->table_id,
        param->fw_request->count, param->fw_request->data);
      memcpy(apdu->apdu+c, target->sequence, CT__LEN_SEQN);
      c += CT__LEN_SEQN;;
      c += ctAuthenticate(apdu->apdu+c, apdu->apdu, NULL, c, 0, target);
    break;
    case REQUEST_PART_WRITE:
      c += ctPartialWriteRequest(apdu->apdu+c, param->pw_request->table_id,
        param->pw_request->offset, param->pw_request->count, 
        param->pw_request->data);
      memcpy(apdu->apdu+c, target->sequence, CT__LEN_SEQN);
      c += CT__LEN_SEQN;
      c += ctAuthenticate(apdu->apdu+c, apdu->apdu, NULL, c, 0, target);
    break;
    case RESPONSE_FULL_READ:
    case RESPONSE_PART_READ:
      c += ctReadResponse(apdu->apdu+c, param->r_response->response,
        param->r_response->count, param->r_response->data);
      c += ctAuthenticate(apdu->apdu+c, param->r_response->request, apdu->apdu,
        param->r_response->req_count, c, target);
    break;
    case RESPONSE_FULL_WRITE:
    case RESPONSE_PART_WRITE:
      c += ctWriteResponse(apdu->apdu+c, param->w_response->response);
      c += ctAuthenticate(apdu->apdu+c, param->w_response->request, apdu->apdu,
        param->w_response->req_count, c, target);
    break;
    default:
      fprintf(stderr, "\nInvalid service %d\n", param->service);
  }
  return c;
}

int ctProcessApdu(ctApdu_t* apdu, ctTarget_t* target) {
  // to do
  return 0;
}