//
// Created by Gustavo Viegas on 2017/06
//

#include <stdio.h>
#include <string.h>
#include "CT_apdu.h"
#include "CT_dc.h"
#include "commands/CT_cmd_call.h"

#define _CT__FR "fr"
#define _CT__FW "fw"
#define _CT__PR "pr"
#define _CT__PW "pw"
#define _CT__UT01 "ut01"
#define _CT__UT02 "ut02"

int _ctGetDest(ctList_t* list, ctAddr_t* addr) {
  char *b, *p;
  ctNode_t* node;
  if(!(p = strtok(NULL, CT__DELIM))) {
    printf("Missing parameter <DEFINE>\n");
    return CT__FAILURE;
  }
  b = strchr(p, '\n');
  if(b) p[strlen(p) - 1] = '\0';
  if(!(node = ctListFind(list, p))) {
    printf("\"%s\" not defined\n", p);
    return CT__FAILURE;
  }
  memcpy(addr, &node->addr, sizeof(ctAddr_t));
  return CT__SUCCESS;
}

int _ctUT01() {
  return CT__SUCCESS;
}

int _ctFR(ctList_t* list, ctTarget_t* target) {
  char *b, *p;
  int i;
  ctParam_t param;
  ctFRRequest_t fr;
  ctResponse_t res;
  ctAddr_t addr, dest;
  param.service = REQUEST_FULL_READ;
  param.fr_request = &fr;

  strcpy(addr.node, "localhost"); // temp
  strcpy(addr.service, "40102"); // temp

  if(!(p = strtok(NULL, CT__DELIM))) {
    printf("Missing parameter <TABLE ID>\n");
    return CT__FAILURE;
  }
  b = strchr(p, '\n');
  if(b) p[strlen(p) - 1] = '\0';

  if(!strcmp(_CT__UT01, p)) {
    fr.table_id = CT__UT01;
    if(_ctGetDest(list, &dest) != CT__SUCCESS) return CT__FAILURE;
    ctDcStart(target, &addr, &dest, &param, &res, 1);
    // debug
    printf("service=%d ", res.service);
    printf("response=%d ", res.response);
    printf("read_count=%d \n", res.read_count);
    for(i = 0; i < res.read_count; ++i)
      printf("%x ", res.read_data[i]);
    printf("end\n");
    //
  } else if(!strcmp(_CT__UT02, p)) {
    fr.table_id = CT__UT02;
    // ...
  } else {
    printf("Invalid table \"%s\"\n", p);
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}

int ctCmdCall(ctList_t* list, ctTarget_t* target) {

  // temp
  memset(target->key, 0, sizeof target->key);
  target->node = 0;
  target->subnet = 0;
  //

  char *b, *p;
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';

    if(!strcmp(_CT__FR, p)) _ctFR(list, target);
    else if(!strcmp(_CT__FW, p));
    else if(!strcmp(_CT__PR, p));
    else if(!strcmp(_CT__PW, p));
    else {
      printf("Invalid call \"%s\"\n", p);
      return CT__FAILURE;
    }
  }
  return CT__SUCCESS;
}
