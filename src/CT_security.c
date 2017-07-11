//
// Created by Gustavo Viegas on 2017/03
//

#include <string.h>
#include <stdio.h>
#include "CT_security.h"

int ctAuthenticate(uint8_t* buffer, uint8_t* request, uint8_t* response,
  uint8_t req_count, uint8_t res_count, ctTarget_t* target)
{
  uint8_t cur = 0, d[CT__LEN_APDU];
  d[cur++] = target->subnet;
  d[cur++] = target->node;
  memcpy(d+cur, request, req_count);
  cur += req_count;
  if(response) {
    memcpy(d+cur, response, res_count);
    cur += res_count;
    d[cur++] = res_count;
  }
  ctDigest(buffer, d, cur, target);
  return CT__LEN_DIGEST;
}

int ctValidate(uint8_t* digest, uint8_t* request, uint8_t* response,
  uint8_t req_count, uint8_t res_count, ctTarget_t* target)
{
  uint8_t cur = 0, d[CT__LEN_APDU], b[8];
  d[cur++] = target->subnet;
  d[cur++] = target->node;
  memcpy(d+cur, request, req_count);
  cur += req_count;
  if(response) {
    memcpy(d+cur, response, res_count);
    cur += res_count;
    d[cur++] = res_count;
  }
  ctDigest(b, d, cur, target);
  int i;
  for(i = 0; i < 8; ++i) {
    if(digest[i] != b[i]) return CT__FAILURE;
  }
  return CT__SUCCESS;
}

// TODO: hash function
// NOTE: for local testing only
void ctDigest(uint8_t* buffer, uint8_t* data, uint8_t data_count,
  ctTarget_t* target)
{
  buffer[0] = 0x98;
  buffer[1] = 0x17;
  buffer[2] = 0x44;
  buffer[3] = 0x0a;
  buffer[4] = 0x8c;
  buffer[5] = 0xf6;
  buffer[6] = 0xbd;
  buffer[7] = 0x12;
}
