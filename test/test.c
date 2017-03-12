//
// Created by Gustavo Viegas on 2017/02
//

#include <stdio.h>
#include "CT_table_services.h"
#include "CT_security.h"
#include "CT_apdu.h"
#include <string.h>
#include <stdlib.h>

ctTarget_t t = {0x02, 0x03};

void servicesTest() {
  uint8_t b[1024], d[] = {0xd1,0xd3,0xd6}, o[] = {0,1,1};
  int i, s = ctWriteResponse(b, CT__RES_ERR);
  for(i = 0; i < s; ++i) printf("%x\n", b[i]);
  printf("\nsize of msg: %zu\n", sizeof b);
}

void securityTest() {
  uint8_t b[100] = {0}, req[50] = {0}, res[50] = {0}, o[3] = {0}, d[] = {0xd,0xc,0xb};
  
  int s1 = ctPartialReadRequest(req+1, 0x0034, o, 0x0006);
  s1++;
  int s2 = ctReadResponse(res+1, CT__RES_ERR, 3, d);
  // int i, s = ctAuthenticate(b, req, res, s1, s2, &t);
  int i, s = ctAuthenticate(b, req, NULL, s1, s2, &t);
  
  printf("\req: ");
  for(i = 0; i < s1; ++i) printf("%x ", req[i]);
  printf("\ndig: ");
  for(i = 0; i < s; ++i) printf("%x ", b[i]);
  printf("\n");
}

void apduTest() {
  // req
  ctFRRequest_t frreq;
  frreq.table_id = 0xffff;

  ctParam_t param;
  param.service = REQUEST_FULL_READ;
  param.fr_request = &frreq;

  ctApdu_t apdu;

  int c = ctCreateApdu(&apdu, &param, &t);

  int i;
  printf("\napdu req: ");
  for(i = 0; i < c; ++i) printf("%x ", apdu.apdu[i]);
  printf("\n");
  
  //////////////////////////////
  // res
  ctRResponse_t rres;
  uint8_t d[] = {2,4,6,8,0x0a,0x0c,0x0e};
  rres.response = 0;
  rres.count = sizeof d;
  memcpy(rres.data, d, rres.count);
  rres.request = apdu.apdu;
  rres.req_count = abs(c - CT__LEN_DIGEST);

  ctParam_t param1;
  param1.service = RESPONSE_FULL_READ;
  param1.r_response = &rres;

  ctApdu_t apdu1;

  int c1 = ctCreateApdu(&apdu1, &param1, &t);

  printf("\napdu res: ");
  for(i = 0; i < c1; ++i) printf("%x ", apdu1.apdu[i]);
  printf("\n");

  //////////////////////////////
  // validate req
  ctApdu_t apdu2;

  // apdu.apdu[3] = 0xdd;
  int c2 = ctProcessRequest(&apdu2, &apdu, &t);

  if(c2 != CT__FAILURE) {
    printf("\nprocess req: %d\n", c2);
    for(i = 0; i < c2; ++i) printf("%x ", apdu2.apdu[i]);
    printf("\n");
  } else printf("\nrequest failed\n");

  //////////////////////////////
  // validate req
  ctResponse_t b;

  int v = ctProcessResponse(&b, &apdu1, &apdu, &t);

  // apdu1.apdu[6] = 0xff;
  printf("\nprocess res: %d\n", v);
  if(v == CT__SUCCESS) {
    printf("service: %x \n", b.service);
    printf("response: %x \n", b.response);
    printf("read_count: %x \n", b.read_count);
    printf("read_data: ");
    for(i = 0; i < b.read_count; ++i) printf("%x ", b.read_data[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  uint8_t seq[] = {0xf5,0x2f,0x54,0x81};
  uint8_t key[] = {0xdf,0x01,0x02,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf};
  memcpy(t.sequence, seq, sizeof seq);
  memcpy(t.s_omak, key, sizeof key);
  
  // int i;
  // printf("\nsubnet: %x", t.subnet);
  // printf("\nnode: %x", t.node);
  // printf("\nseq: ");
  // for(i = 0; i < CT__LEN_SEQN; ++i) printf("%x ", t.sequence[i]);
  // printf("\nkey: ");
  // for(i = 0; i < CT__LEN_OMAK; ++i) printf("%x ", t.s_omak[i]);
  // printf("\n");
  
  apduTest();
  
  return 0;
}