//
// Created by Gustavo Viegas on 2017/04
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_date.h"
#include "CT_thread.h"
#include "CT_pipe.h"
#include "CT_message_map.h"
#include "CT_cmd.h"
#include "CT_dc.h"

#define _CT__ANALYZER_TO 5

static ctTarget_t _ct_target;
static ctAddr_t _ct_addr;
static ctMap_t _ct_map;
static ctMutex_t _ct_mutex;

static void* _ctDcAnalyzer(void* arg) {
  ctTimeSpec_t ts;
  ctEntry_t* entry;
  long diff;
  while(1) {
    ctLock(&_ct_mutex);
    ctGetTimeSpec(&ts);
    while((entry = ctMapNext(&_ct_map))) {
      diff = ts.sec - entry->timestamp;
      if(diff < _CT__ANALYZER_TO) continue;
      ctCmdErr(&entry->addr, "No response");
      if(ctMapOut(&_ct_map) != CT__SUCCESS)
        fprintf(stderr, "WARNING: Failed to remove pending response\n");
    }
    ctUnlock(&_ct_mutex);
    diff = ts.sec;
    ctGetTimeSpec(&ts);
    diff = ts.sec - diff;
    ctSleep(_CT__ANALYZER_TO - diff);
  }
  return NULL;
}

static void* _ctDcReceiver(void* arg) {
  ctApdu_t apdu;
  ctAddr_t src;
  ctResponse_t res;
  ctEntry_t* entry;
  int n, r;
  while(1) {
    n = ctRecv(apdu.apdu, sizeof apdu.apdu, &src, NULL);
    if(n < 1)
      fprintf(stderr, "WARNING: Invalid response received\n");
    else {
      ctLock(&_ct_mutex);
      entry = ctMapFind(&_ct_map, atoi(src.port));
      if(!entry) {
        ctUnlock(&_ct_mutex);
        fprintf(stderr, "WARNING: Source not mapped (%s)\n", src.port);
        continue;
      }
      r = ctProcessResponse(&res, &apdu, &entry->apdu, &_ct_target);
      if(r != CT__SUCCESS) {
        ctUnlock(&_ct_mutex);
        fprintf(stderr, "WARNING: Failed to process respose from %s %s\n",
          src.node, src.port);
        continue;
      }
      r = ctMapDelete(&_ct_map, entry->key);
      ctUnlock(&_ct_mutex);
      // NOTE: this if clause should never happen with locks...
      if(r != CT__SUCCESS)
        fprintf(stderr, "WARNING: Failed to delete entry %d\n", entry->key);
      ctCmdPrint(&src, &res);
    }
  }
  return NULL;
}

int ctDcExec(ctDcExecInfo_t* info) {
  ctEntry_t* entry;
  int n, i;
  // NOTE: other threads could starve
  // consider moving this lock inside the loop
  ctLock(&_ct_mutex);
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
  ctUnlock(&_ct_mutex);
  return CT__SUCCESS;
}

int ctDcStart(ctTarget_t* target, ctAddr_t* addr, char* in, char* out) {
  ctThread_t thr1, thr2;
  _ct_target = *target;
  _ct_addr = *addr;
  if(ctMapCreate(&_ct_map) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to create message map\n");
    return CT__FAILURE;
  }
  if(ctBind(addr) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to bind\n");
    return CT__FAILURE;
  }
  if(ctMutexCreate(&_ct_mutex) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to create mutex\n");
    return CT__FAILURE;
  }
  if(ctThreadCreate(&thr1, _ctDcReceiver, NULL) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to create receiver thread\n");
    return CT__FAILURE;
  }
  if(ctThreadCreate(&thr2, _ctDcAnalyzer, NULL) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: DC failed to create analyzer thread\n");
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
