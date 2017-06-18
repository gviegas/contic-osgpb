//
// Created by Gustavo Viegas on 2017/04
//

#include <stdio.h>
#include <string.h>
#include "CT_thread.h"
#include "CT_pipe.h"
#include "CT_cmd.h"
#include "CT_dc.h"

static ctTarget_t _ct_target;
static ctAddr_t _ct_addr;

// TODO: call a print/format function from cmd (to correctly place TK
// on interactive mode) with processed response plus src info
// also, a mapping is needed to find a response matching request
static void* _ctDcRun(void* arg) {
  ctApdu_t apdu;
  ctAddr_t src;
  int n;
  while(1) {
    n = ctRecv(apdu.apdu, sizeof apdu.apdu, &src, NULL);
    if(n < 1)
      fprintf(stderr, "WARNING: Invalid response received\n");
    else // put response in a container to be processed...
      printf("\nOK: APDU received is %d bytes long\n", n); // test
    fflush(stdout); // testing
  }
  return NULL;
}

int ctDcExec(ctDcExecInfo_t* info) {
  ctApdu_t apdu;
  int n, i;
  for(i = 0; i < info->count; ++i) {
    n = ctCreateApdu(&apdu, &info->messages[i], &_ct_target);
    if(n < 1)
      fprintf(stderr, "WARNING: Failed to create apdu %d\n", i);
    else if(ctSend(apdu.apdu, n, &info->destinations[i]) != CT__SUCCESS)
      fprintf(stderr, "WARNING: Failed to send message %d\n", i);
  }
  return CT__SUCCESS;
}

int ctDcStart(ctTarget_t* target, ctAddr_t* addr, char* in, char* out) {
  ctThread_t thr;
  _ct_target = *target;
  _ct_addr = *addr;
  if(ctBind(addr) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to bind\n");
    return CT__FAILURE;
  }
  if(ctThreadCreate(&thr, _ctDcRun, NULL) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to create thread\n");
    return CT__FAILURE;
  }
  if(in && ctNpipeIn(in) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to open pipe for reading\n");
    return CT__FAILURE;
  }
  if(out && ctNpipeOut(out) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to open pipe for writing\n");
    return CT__FAILURE;
  }
  ctCmdStart(out == NULL);
  return CT__SUCCESS;
}
