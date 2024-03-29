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
#define _CT__BT00 "bt00"

int _ctGetDest(ctList_t* list, ctAddr_t* addr) {
  char *p;
  ctNode_t* node;
  if(!(p = strtok(NULL, CT__DELIM))) {
    printf("Missing parameter <DEFINE>\n");
    return CT__FAILURE;
  }
  if(!(node = ctListFind(list, p))) {
    printf("\"%s\" not defined\n", p);
    return CT__FAILURE;
  }
  *addr = node->addr;
  return CT__SUCCESS;
}

int _ctFR(ctList_t* list) {
  char *p;
  ctParam_t param;
  ctFRRequest_t fr;
  ctAddr_t dest;
  ctDcExecInfo_t info;
  param.service = REQUEST_FULL_READ;
  param.fr_request = &fr;

  if(!(p = strtok(NULL, CT__DELIM))) {
    printf("Missing parameter <TABLE>\n");
    return CT__FAILURE;
  }

  if(!strcmp(_CT__UT01, p)) fr.table_id = CT__UT01;
  else if(!strcmp(_CT__UT02, p)) fr.table_id = CT__UT02;
  else if(!strcmp(_CT__BT00, p)) fr.table_id = CT__BT00;
  else {
    printf("Invalid table \"%s\"\n", p);
    return CT__FAILURE;
  }
  if(_ctGetDest(list, &dest) != CT__SUCCESS) return CT__FAILURE;
  info = (ctDcExecInfo_t) {&dest, &param, 1};
  ctDcExec(&info);

  return CT__SUCCESS;
}

// TODO
int _ctFW(ctList_t* list) {
  return CT__SUCCESS;
}

// TODO
int _ctPR(ctList_t* list) {
  return CT__SUCCESS;
}

// TODO
int _ctPW(ctList_t* list) {
  return CT__SUCCESS;
}

int ctCmdCall(ctList_t* list) {
  char *p;
  if((p = strtok(NULL, CT__DELIM))) {
    if(!strcmp(_CT__FR, p)) _ctFR(list);
    else if(!strcmp(_CT__FW, p)) _ctFW(list);
    else if(!strcmp(_CT__PR, p)) _ctPR(list);
    else if(!strcmp(_CT__PW, p)) _ctPW(list);
    else {
      printf("Invalid call \"%s\"\n", p);
      return CT__FAILURE;
    }
  } else {
    printf("Missing parameter <SERVICE>\n");
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}
