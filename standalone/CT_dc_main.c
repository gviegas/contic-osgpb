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
  return CT__SUCCESS;
}
