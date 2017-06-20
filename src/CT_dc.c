//
// Created by Gustavo Viegas on 2017/04
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_thread.h"
#include "CT_pipe.h"
#include "CT_message_map.h"
#include "CT_cmd.h"
#include "CT_dc.h"

static ctTarget_t _ct_target;
static ctAddr_t _ct_addr;
static ctMap_t _ct_map;

// TODO: call a print/format function from cmd (to correctly place TK
// on interactive mode) with processed response plus src info
static void* _ctDcRun(void* arg) {
  ctApdu_t apdu;
  ctAddr_t src;
  ctResponse_t res;
  ctEntry_t* entry;
  int n, r, i;
  while(1) {
    n = ctRecv(apdu.apdu, sizeof apdu.apdu, &src, NULL);
    if(n < 1)
      fprintf(stderr, "WARNING: Invalid response received\n");
    else {
      entry = ctMapFind(&_ct_map, atoi(src.port));
      if(!entry) {
        fprintf(stderr, "WARNING: Source not mapped\n");
        continue;
      }
      r = ctProcessResponse(&res, &apdu, &entry->apdu, &_ct_target);
      if(r != CT__SUCCESS) {
        fprintf(stderr, "WARNING: Failed to process respose from %s %s\n",
          src.node, src.port);
        continue;
      }
      r = ctMapDelete(&_ct_map, entry->key);
      if(r != CT__SUCCESS)
        fprintf(stderr, "WARNING: Failed to delete entry %d\n", entry->key);

      // testing
      printf("\nFrom: %s %s\n", src.node, src.port);
      printf("Data:");
      for(i = 0; i < res.read_count; ++i) {
        if(!(i % 16)) printf("\n\t");
        printf(" %x", res.read_data[i]);
      }
      fflush(stdout);
      //

    }
  }
  return NULL;
}

int ctDcExec(ctDcExecInfo_t* info) {
  ctEntry_t* entry;
  int n, i;
  for(i = 0; i < info->count; ++i) {
    entry = ctMapAdd(&_ct_map, atoi(info->destinations[i].port));
    if(!entry) continue;
    entry->addr = info->destinations[i];
    n = ctCreateApdu(&entry->apdu, &info->messages[i], &_ct_target);
    if(n < 1)
      fprintf(stderr, "WARNING: Failed to create apdu %d\n", i);
    else if(ctSend(entry->apdu.apdu, n, &entry->addr) != CT__SUCCESS)
      fprintf(stderr, "WARNING: Failed to send message %d\n", i);
  }
  return CT__SUCCESS;
}

int ctDcStart(ctTarget_t* target, ctAddr_t* addr, char* in, char* out) {
  ctThread_t thr;
  _ct_target = *target;
  _ct_addr = *addr;
  if(ctMapCreate(&_ct_map) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to create message map\n");
    return CT__FAILURE;
  }
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
