//
// Created by Gustavo Viegas on 2017/03
//

#include "CT_security.h"

int ctAuthenticate(uint8_t* buffer, uint8_t* request, uint8_t* response, 
  uint8_t req_count, uint8_t res_count, ctTarget_t* target)
{
  uint8_t cur = 0, d[CT__LEN_MAXAPDU];
  d[cur++] = target->subnet;
  d[cur++] = target->node;
  memcpy(d+cur, request, req_count);
  cur += req_count;
  memcpy(d+cur, target->sequence, CT__LEN_SEQN);
  cur += CT__LEN_SEQN;
  if(response) {
    memcpy(d+cur, response, res_count);
    cur += res_count;
    d[cur++] = res_count;
  }
  
  // DOING
  
  // memcpy(buffer, d, cur); // test

  ctDigest(buffer, d, cur, target);
  
  return cur;
}

int ctValidate(uint8_t* digest, uint8_t* request, uint8_t* response, 
  uint8_t req_count, uint8_t res_count, ctTarget_t* target)
{
  // todo
  return 0;
}

void ctDigest(uint8_t* buffer, uint8_t* data, uint8_t data_count, 
  ctTarget_t* target)
{

  printf("\ndigesting... "); int q; for(q = 0; q < data_count; ++q) printf("%x ", data[q]); printf("\n"); // test

  int k, i = 0;
  uint8_t a = 0, b = 0, m = 0, n = 0;
  do {
    do {
      do {
        k = (7 - b + 1) % 8;
        if(data_count > 0) {
          m = data[i++];
          data_count--;
        } else {
          return;
          // if(end) m = 0;
          // else return;
        }
        n = ~(buffer[7 - b] + 7 - b);
        if(target->s_omak[a % 12] & (1 << b))
          buffer[7 - b] = buffer[k] + m + ((n << 1) + (n >> 7));
        else
          buffer[7 - b] = buffer[k] + m - ((n >> 1) + (n << 7));
        b++;
      } while(b < 8);
      b = 0;
      a++;
    } while(a < 18);
    a = 0;
  } while(data_count > 0);
}