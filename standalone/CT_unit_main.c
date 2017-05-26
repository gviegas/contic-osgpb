//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "CT_unit.h"

#define CT__UNIT_ARGC 7
#define CT__UNIT_ARGV_KEY "--key"
#define CT__UNIT_ARGV_NODE "--node"
#define CT__UNIT_ARGV_SERV "--service"

// doing
int main(int argc, char** argv) {
  ctTarget_t target;
  ctAddr_t addr;
  char buf[3];
  int i, j;
  if(argc < CT__UNIT_ARGC) {
    printf("Usage: ");
    printf("--key <KEY> ");
    printf("--node <NODE> ");
    printf("--service <SERVICE>\n");
    return CT__FAILURE;
  }
  for(i = 1; i < argc; ++i) {
    if(!strcmp(argv[i], CT__UNIT_ARGV_KEY)) {
      if(strlen(argv[++i]) != (2 * sizeof target.s_omak)) {
        fprintf(stderr,
          "ERROR: Key must be %lu bytes long in hexadecimal format\n",
          sizeof target.s_omak);
        return CT__FAILURE;
      }
      for(j = 0; j < sizeof target.s_omak; ++j) {
        strncpy(buf, argv[i] + j * 2, 2);
        target.s_omak[j] = strtoul(buf, NULL, 16);
      }
    } else if(!strcmp(argv[i], CT__UNIT_ARGV_NODE)) {
      if(strlen(argv[++i]) >= sizeof addr.node) {
        fprintf(stderr, "ERROR: Node name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.node, argv[i]);
    } else if(!strcmp(argv[i], CT__UNIT_ARGV_SERV)) {
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

  // debug
  for(i = 0; i < sizeof target.s_omak; ++i)
    printf("%x ", target.s_omak[i]);
  printf("\n%s %s\n", addr.node, addr.service);
  //

  // ctUnitStart(&target, &addr);
  return CT__SUCCESS;
}
