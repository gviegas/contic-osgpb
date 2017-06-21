//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_definitions.h"
#include "CT_config.h"
#include "CT_file.h"
#include "CT_unit.h"

#define CT__UNIT_ARGC 7
#define CT__UNIT_ARGV_KEY "--key"
#define CT__UNIT_ARGV_NODE "--node"
#define CT__UNIT_ARGV_PORT "--port"
#define CT__UNIT_ARGV_OPT "--option"
#define CT__UNIT_ARGV_CLEAR "--clear"

// TODO: "clear" logic needs a revision
int main(int argc, char** argv) {
  ctTarget_t target;
  ctAddr_t addr;
  char buf[3];
  int i, j, clear = 0;

  if(argc < CT__UNIT_ARGC) {
    printf("Usage: ");
    printf("%s <KEY> ", CT__UNIT_ARGV_KEY);
    printf("%s <NODE> ", CT__UNIT_ARGV_NODE);
    printf("%s <PORT> ", CT__UNIT_ARGV_PORT);
    printf("[%s <OPTION>] ", CT__UNIT_ARGV_OPT);
    printf("[%s]\n", CT__UNIT_ARGV_CLEAR);
    return CT__FAILURE;
  }

  for(i = 1; i < argc; ++i) {
    if(!strcmp(argv[i], CT__UNIT_ARGV_KEY)) {
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
    } else if(!strcmp(argv[i], CT__UNIT_ARGV_NODE)) {
      if(strlen(argv[++i]) >= sizeof addr.node) {
        fprintf(stderr, "ERROR: Node name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.node, argv[i]);
    } else if(!strcmp(argv[i], CT__UNIT_ARGV_PORT)) {
      if(strlen(argv[++i]) >= sizeof addr.port) {
        fprintf(stderr, "ERROR: Port name must be shorter\n");
        return CT__FAILURE;
      }
      strcpy(addr.port, argv[i]);
    } else if(!strcmp(argv[i], CT__UNIT_ARGV_OPT)) {
      char *end;
      long opt = strtol(argv[++i], &end, 0);
      if(end == argv[i]) {
        fprintf(stderr, "ERROR: Option must be an integer\n");
        return CT__FAILURE;
      }
      ctConfig(&opt);
    } else if(!strcmp(argv[i], CT__UNIT_ARGV_CLEAR)) {
      if(ctCreate() != CT__SUCCESS) {
        fprintf(stderr, "ERROR: Unable to create new data file\n");
        return CT__FAILURE;
      }
      clear = 1;
    } else {
      fprintf(stderr, "ERROR: Invalid argument %s\n", argv[i]);
      return CT__FAILURE;
    }
  }
  // Start the Unit
  ctUnitStart(&target, &addr, clear);
  return CT__SUCCESS;
}
