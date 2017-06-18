//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_dc.h"

#define CT__DC_ARGC 7
#define CT__DC_ARGV_KEY "--key"
#define CT__DC_ARGV_NODE "--node"
#define CT__DC_ARGV_PORT "--port"
#define CT__DC_ARGV_IN "--in"
#define CT__DC_ARGV_OUT "--out"

int main(int argc, char** argv) {
  ctTarget_t target;
  ctAddr_t addr;
  char *in, *out, buf[3];
  int i, j;
  in = out = NULL;

  if(argc < CT__DC_ARGC) {
    printf("Usage: ");
    printf("%s <KEY> ", CT__DC_ARGV_KEY);
    printf("%s <NODE> ", CT__DC_ARGV_NODE);
    printf("%s <PORT> ", CT__DC_ARGV_PORT);
    printf("[%s <INPUT>] ", CT__DC_ARGV_IN);
    printf("[%s <OUTPUT>]\n", CT__DC_ARGV_OUT);
    return CT__FAILURE;
  }

  for(i = 1; i < argc; ++i) {
    if(!strcmp(argv[i], CT__DC_ARGV_KEY)) {
      if(strlen(argv[++i]) == (2 * sizeof target.key)) {
        for(j = 0; j < sizeof target.key; ++j) {
          strncpy(buf, argv[i] + j * 2, 2);
          target.key[j] = strtoul(buf, NULL, 16);
        }
      } else if(!strcmp(argv[i], "0"))
        memset(target.key, 0, sizeof target.key);
      else {
        fprintf(stderr,
          "ERROR: Key must be %lu bytes long in hexadecimal format\n",
          sizeof target.key);
        return CT__FAILURE;
      }
      target.node = target.subnet = 0;
      memset(target.sequence, 0, sizeof target.sequence);
    } else if(!strcmp(argv[i], CT__DC_ARGV_NODE)) {
      if(strlen(argv[++i]) >= sizeof addr.node) {
        fprintf(stderr, "ERROR: Node name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.node, argv[i]);
    } else if(!strcmp(argv[i], CT__DC_ARGV_PORT)) {
      if(strlen(argv[++i]) >= sizeof addr.port) {
        fprintf(stderr, "ERROR: Port name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.port, argv[i]);
    } else if(!strcmp(argv[i], CT__DC_ARGV_IN)) {
      if(++i == argc) {
        fprintf(stderr, "ERROR: Missing path for option %s\n", argv[i]);
        return CT__FAILURE;
      }
      in = argv[i];
    } else if(!strcmp(argv[i], CT__DC_ARGV_OUT)) {
      if(++i == argc) {
        fprintf(stderr, "ERROR: Missing path for option %s\n", argv[i]);
        return CT__FAILURE;
      }
      out = argv[i];
    } else {
      fprintf(stderr, "ERROR: Invalid argument %s\n", argv[i]);
      return CT__FAILURE;
    }
  }
  // Start the DC
  ctDcStart(&target, &addr, in, out);

  // // test
  // ctAddr_t dest[1];
  // ctParam_t param[1];
  // ctResponse_t responses[1];
  //
  // // ctUT01_t ut01 = {0xd, 0xe, 5, 10};
  // // ctFWRequest_t fwreq;
  // // fwreq.table_id = CT__UT01;
  // // fwreq.count = sizeof ut01;
  // // memcpy(fwreq.data, &ut01, sizeof ut01);
  // // param[0].service = REQUEST_FULL_WRITE;
  // // param[0].fw_request = &fwreq;
  //
  // ctPRRequest_t prreq;
  // ctUT02Data_t data;
  // // uint32_t szdata = sizeof data;
  // prreq.table_id = CT__UT02;
  // memset(prreq.offset, 0, sizeof prreq.offset);
  // // prreq.offset[0] = (szdata >> 16) & 0xff;
  // // prreq.offset[1] = (szdata >> 8) & 0xff;
  // // prreq.offset[2] = szdata & 0xff;
  // prreq.count = sizeof data;
  // param[0].service = REQUEST_PART_READ;
  // param[0].pr_request = &prreq;
  //
  // strcpy(dest[0].node, "localhost");
  // strcpy(dest[0].port, "50111");
  //
  // ctDcExec(&target, &addr, dest, param, responses,
  //   sizeof dest / sizeof dest[0]);
  //
  // for(i = 0; i < sizeof responses / sizeof responses[0]; ++i) {
  //   printf("response %d:\n", i + 1);
  //   printf("service=%d ", responses[i].port);
  //   printf("response=%d ", responses[i].response);
  //   printf("read_count=%d \n", responses[i].read_count);
  //   for(j = 0; j < responses[i].read_count; ++j)
  //     printf("%x ", responses[i].read_data[j]);
  //   printf("\n--------\n");
  // }
  //
  // memcpy(&data, responses[0].read_data, sizeof data);
  // printf("value: %f\n", data.value);
  // printf("timestamp: %d/%d/%d %d:%d:%d\n",
  //   data.timestamp.year, data.timestamp.month,
  //   data.timestamp.day, data.timestamp.hour,
  //   data.timestamp.minute, data.timestamp.second
  // );
  // //

  return CT__SUCCESS;
}
