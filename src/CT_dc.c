//
// Created by Gustavo Viegas on 2017/04
//

#include <stdio.h>
#include "CT_apdu.h"
#include "CT_dc.h"

// to do
int ctDcDefaultCommission() {
  return CT__SUCCESS;
}

// to test
int ctDcStart(ctTarget_t* target, ctAddr_t* addr, ctAddr_t* destinations,
  ctParam_t* messages, size_t count)
{
  ctApdu_t apdu, res_apdu;
  ctResponse_t response;
  ctAddr_t src;
  int n, i;
  if(ctBind(addr) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to bind\n");
    return CT__FAILURE;
  }
  for(i = 0; i < count; ++i) {
    n = ctCreateApdu(&apdu, &messages[i], target);
    if(n < 1) continue;
    if(ctSend(apdu.apdu, n, &destinations[i]) != CT__SUCCESS) {
      fprintf(stderr, "ERROR: Failed to send message %d\n", i);
      continue;
    }
    n = ctRecv(res_apdu.apdu, sizeof res_apdu.apdu, &src);
    if(n < 1) continue;

    // debug
    int j;
    printf("received:\n");
    for(j = 0; j < n; ++j) printf("%x ", res_apdu.apdu[j]);
    printf("\nend of message\n");
    //

    if(ctProcessResponse(&response, &res_apdu, &apdu, target) != CT__SUCCESS) {
      fprintf(stderr, "ERROR: Failed to process response %d\n", i);
      continue;
    }

    // debug
    printf("response:\n");
    printf("service=%d ", response.service);
    printf("response=%d ", response.response);
    printf("count=%d\n", response.read_count);
    for(j = 0; j < response.read_count; ++j)
      printf("%x ", response.read_data[j]);
    printf("\nend of response\n");
    //

  }
  return CT__SUCCESS;
}
