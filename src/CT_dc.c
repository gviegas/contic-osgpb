//
// Created by Gustavo Viegas on 2017/04
//

#include <stdio.h>
#include <string.h>
#include "CT_cmd.h"
#include "CT_dc.h"

int ctDcExec(ctTarget_t* target, ctAddr_t* addr, ctAddr_t* destinations,
  ctParam_t* messages, ctResponse_t* responses, size_t count)
{
  ctApdu_t apdu, res_apdu;
  ctAddr_t src;
  int n, i;
  for(i = 0; i < count; ++i) {
    n = ctCreateApdu(&apdu, &messages[i], target);
    if(n < 1) continue;
    if(ctSend(apdu.apdu, n, &destinations[i]) != CT__SUCCESS) {
      fprintf(stderr, "WARNING: Failed to send message %d\n", i);
      continue;
    }

    // test
    ctTimeSpec_t t;
    t.sec = 0;
    t.nsec = 9000000;
    //

    n = ctRecv(res_apdu.apdu, sizeof res_apdu.apdu, &src, &t /*NULL*/);
    if(n < 1) {
      fprintf(stderr, "WARNING: Received invalid response for message %d\n", i);
      memset(&responses[i], -1, sizeof responses[0]);
      continue;
    }
    if(ctProcessResponse(&responses[i], &res_apdu, &apdu, target)
      != CT__SUCCESS)
    {
      fprintf(stderr, "WARNING: Failed to process response %d\n", i);
      memset(&responses[i], -1, sizeof responses[0]);
      continue;
    }
  }
  return CT__SUCCESS;
}

int ctDcStart(ctTarget_t* target, ctAddr_t* addr) {
  if(ctBind(addr) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to bind\n");
    return CT__FAILURE;
  }
  ctCmdStart(target, addr);
  return CT__SUCCESS;
}
