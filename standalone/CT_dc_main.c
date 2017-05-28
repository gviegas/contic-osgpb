//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "CT_dc.h"

#define CT__DC_ARGC 7
#define CT__DC_ARGV_KEY "--key"
#define CT__DC_ARGV_NODE "--node"
#define CT__DC_ARGV_SERV "--service"

// doing
int main(int argc, char** argv) {
  ctTarget_t target;
  ctAddr_t addr;
  char buf[3];
  int i, j;
  if(argc < CT__DC_ARGC) {
    printf("Usage: ");
    printf("%s <KEY> ", CT__DC_ARGV_KEY);
    printf("%s <NODE> ", CT__DC_ARGV_NODE);
    printf("%s <SERVICE>\n", CT__DC_ARGV_SERV);
    return CT__FAILURE;
  }
  for(i = 1; i < argc; ++i) {
    if(!strcmp(argv[i], CT__DC_ARGV_KEY)) {
      if(strlen(argv[++i]) != (2 * sizeof target.key)) {
        fprintf(stderr,
          "ERROR: Key must be %lu bytes long in hexadecimal format\n",
          sizeof target.key);
        return CT__FAILURE;
      }
      for(j = 0; j < sizeof target.key; ++j) {
        strncpy(buf, argv[i] + j * 2, 2);
        target.key[j] = strtoul(buf, NULL, 16);
      }
      target.node = target.subnet = 0;
      memset(target.sequence, 0, sizeof target.sequence);
    } else if(!strcmp(argv[i], CT__DC_ARGV_NODE)) {
      if(strlen(argv[++i]) >= sizeof addr.node) {
        fprintf(stderr, "ERROR: Node name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.node, argv[i]);
    } else if(!strcmp(argv[i], CT__DC_ARGV_SERV)) {
      if(strlen(argv[++i]) >= sizeof addr.service) {
        fprintf(stderr, "ERROR: Service name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.service, argv[i]);
    } else {
      fprintf(stderr, "ERROR: Invalid argument %s\n", argv[i]);
      return CT__FAILURE;
    }
  }

  // test
  ctAddr_t dest[1];
  ctParam_t param[1];
  ctResponse_t responses[1];

  ctFWRequest_t fwreq;
  fwreq.table_id = CT__UT01;
  memset(fwreq.data, 0xaf, 10);
  fwreq.count = 10;
  param[0].service = REQUEST_FULL_WRITE;
  param[0].fw_request = &fwreq;

  // ctFRRequest_t frreq1; // full table read request
  // frreq1.table_id = CT__BT00; // basic table 00
  // param[0].service = REQUEST_FULL_READ;
  // param[0].fr_request = &frreq1;

  strcpy(dest[0].node, "localhost");
  strcpy(dest[0].service, "50111");

  // ctDcDefaultCommission();
  ctDcStart(&target, &addr, dest, param, responses,
    sizeof dest / sizeof dest[0]);

  for(i = 0; i < sizeof responses / sizeof responses[0]; ++i) {
    printf("response %d:\n", i + 1);
    printf("service=%d ", responses[i].service);
    printf("response=%d ", responses[i].response);
    printf("read_count=%d \n", responses[i].read_count);
    for(j = 0; j < responses[i].read_count; ++j)
      printf("%x ", responses[i].read_data[j]);
    printf("\n--------\n");
  }
  //

  return CT__SUCCESS;
}
