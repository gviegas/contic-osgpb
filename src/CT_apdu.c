//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_apdu.h"
#include "CT_table_services.h"
#include "CT_security.h"
#include "CT_table_access.h"

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
      return CT__FAILURE;
  }
  return c;
}

int ctProcessRequest(ctApdu_t* res_apdu, ctApdu_t* apdu, ctTarget_t* target) {
  int r;
  uint16_t c, a;
  ctParam_t p;
  switch(apdu->apdu[0]) {
    case CT__TYPE_CODE:
      switch(apdu->apdu[1]) {
        case CT__CMD_FULLREAD:
          c = 1 + 1 + 2 + CT__LEN_SEQN;
          p.service = RESPONSE_FULL_READ;
        break;
        case CT__CMD_PARTREAD:
          c = 1 + 1 + 2 + 3 + 2 + CT__LEN_SEQN;
          p.service = RESPONSE_PART_READ;
        break;
        case CT__CMD_FULLWRITE:
          a = ((uint16_t)apdu->apdu[4] << 8) | 
            ((uint16_t)apdu->apdu[5] & 0x00ff);
          c = 1 + 1 + 2 + 2 + a + CT__LEN_SEQN;
          p.service = RESPONSE_FULL_WRITE;
        break;
        case CT__CMD_PARTWRITE:
          a = ((uint16_t)apdu->apdu[7] << 8) | 
            ((uint16_t)apdu->apdu[8] & 0x00ff);
          c = 1 + 1 + 2 + 3 + 2 + a + CT__LEN_SEQN;
          p.service = RESPONSE_PART_WRITE;
        break;
        default:
          fprintf(stderr, "\nInvalid command %x\n", apdu->apdu[1]);
          return CT__FAILURE;
      }
    break;
    default:
      fprintf(stderr, "\nInvalid apdu type code %x\n", apdu->apdu[0]);
      return CT__FAILURE;
  }
  
  r = ctValidate(apdu->apdu+c, apdu->apdu, NULL, c, 0, target);
  if(r != CT__SUCCESS) {
    fprintf(stderr, "\nValidation failed\n");
    return r;
  }
  // needs testing
  switch(p.service) {
    case RESPONSE_FULL_READ:
    case RESPONSE_PART_READ:
      ctRResponse_t rres;
      rres.request = apdu->apdu;
      rres.req_count = c; // no digest
      p.r_response = &rres;
      r = ctTableOp(&p, target); // to do
      if(r == CT__FAILURE)
        fprintf(stderr, "\nTable operation failed\n");
      else
        r = ctCreateApdu(res_apdu, &p, target);
    break;
    case RESPONSE_FULL_WRITE:
    case RESPONSE_PART_WRITE:
      ctWResponse_t wres;
      wres.request = apdu->apdu;
      wres.req_count = c; // no digest
      p.w_response = &wres;
      r = ctTableOp(&p, target);
      if(r == CT__FAILURE)
        fprintf(stderr, "\nTable operation failed\n");
      else
        r = ctCreateApdu(res_apdu, &p, target);
    break;
  }
  return r;
}

int ctProcessResponse(ctResponse_t* buffer, ctApdu_t* apdu, ctApdu_t* req_apdu,
  ctTarget_t* target)
{
  int r;
  uint16_t req_c, res_c, a;
  switch(apdu->apdu[0]) {
    case CT__TYPE_CODE:
      switch(apdu->apdu[1]) {
        case CT__RES_OK:
        case CT__RES_ERR:
        case CT__RES_BSY:
        case CT__RES_DIG:
        case CT__RES_IAR:
        case CT__RES_ICA:
        case CT__RES_INC:
        case CT__RES_ISC:
        case CT__RES_ISS:
        case CT__RES_ONP:
        case CT__RES_SEQ:
        case CT__RES_SNS:
          switch(req_apdu->apdu[1]) {
            case CT__CMD_FULLREAD:
              req_c = 1 + 1 + 2 + CT__LEN_SEQN;
              a = ((uint16_t)apdu->apdu[2] << 8) | 
                ((uint16_t)apdu->apdu[3] & 0x00ff);
              res_c = 1 + 1 + 2 + a;
              buffer->service = RESPONSE_FULL_READ;
            break;
            case CT__CMD_PARTREAD:
              req_c = 1 + 1 + 2 + 3 + 2 + CT__LEN_SEQN;
              a = ((uint16_t)apdu->apdu[2] << 8) | 
                ((uint16_t)apdu->apdu[3] & 0x00ff);
              res_c = 1 + 1 + 2 + a;
              buffer->service = RESPONSE_PART_READ;
            break;
            case CT__CMD_FULLWRITE:
              a = ((uint16_t)req_apdu->apdu[4] << 8) | 
                ((uint16_t)req_apdu->apdu[5] & 0x00ff);
              req_c = 1 + 1 + 2 + 2 + a + CT__LEN_SEQN;
              res_c = 1 + 1;
              buffer->service = RESPONSE_FULL_WRITE;
            break;
            case CT__CMD_PARTWRITE:
              a = ((uint16_t)req_apdu->apdu[7] << 8) | 
                ((uint16_t)req_apdu->apdu[8] & 0x00ff);
              req_c = 1 + 1 + 2 + 3 + 2 + a + CT__LEN_SEQN;
              res_c = 1 + 1;
              buffer->service = RESPONSE_PART_WRITE;
            break;
            default:
              fprintf(stderr, "\nInvalid request\n");
              return CT__FAILURE;
          }
        break;
        default:
          fprintf(stderr, "\nInvalid response %x\n", apdu->apdu[1]);
          return CT__FAILURE;
      }
    break;
    default:
      fprintf(stderr, "\nInvalid apdu type code %x\n", apdu->apdu[0]);
      return CT__FAILURE;
  }

  r = ctValidate(apdu->apdu+res_c, req_apdu->apdu, apdu->apdu, req_c, res_c, 
    target);
  if(r == CT__FAILURE) {
    fprintf(stderr, "\nValidation failed\n");
    return r;
  }
  // needs testing
  buffer->response = apdu->apdu[1];
  switch(buffer->service) {
    case RESPONSE_FULL_READ:
    case RESPONSE_PART_READ:
      buffer->read_count = a;
      // LP: instead of returning raw bytes, create a function on CT_table_access 
      // to format it (will require a new structured type per table...)
      memcpy(buffer->read_data, apdu->apdu+4, a);
    break;
    case RESPONSE_FULL_WRITE:
    case RESPONSE_PART_WRITE:
      buffer->read_count = 0;
    break;
  }
  return CT__SUCCESS;
}