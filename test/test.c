//
// Created by Gustavo Viegas on 2017/02
//

#include <stdio.h>
#include "CT_table_services.h"
#include "CT_security.h"

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

int main(int argc, char** argv) {
  uint8_t seq[] = {0xf5,0x2f,0x54,0x81};
  uint8_t key[] = {0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf,0xdf};
  memcpy(t.sequence, seq, sizeof seq);
  memcpy(t.s_omak, key, sizeof key);
  
  int i;
  printf("\nsubnet: %x", t.subnet);
  printf("\nnode: %x", t.node);
  printf("\nseq: ");
  for(i = 0; i < CT__LEN_SEQN; ++i) printf("%x ", t.sequence[i]);
  printf("\nkey: ");
  for(i = 0; i < CT__LEN_OMAK; ++i) printf("%x ", t.s_omak[i]);
  printf("\n");
  
  securityTest();
  
  return 0;
}