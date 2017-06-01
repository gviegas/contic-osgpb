//
// Created by Gustavo Viegas on 2017/06
//

#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "CT_net.h"
#include "commands/CT_cmd_def.h"

#define _CT__NODE "node"
#define _CT__SERV "serv"

int ctCmdDef(char* name, ctAddr_t* addr) {
  char *b, *p;
  int v[3] = {0};
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    b = strchr(p, '=');
    if(b) {
      *b = '\0';
      ++b;
      if(!v[1] && !strcmp(p, _CT__NODE)) {
        strcpy(addr->node, b);
        v[1] = 1;
      } else if(!v[2] && !strcmp(p, _CT__SERV)) {
        strcpy(addr->service, b);
        v[2] = 1;
      }
      else {
        printf("Invalid parameter %s\n", p);
        return CT__FAILURE;
      }
    } else if(!v[0]) {
      strcpy(name, p);
      v[0] = 1;
    } else {
      printf("Invalid parameter %s\n", p);
      return CT__FAILURE;
    }
  }
  if(!v[0] || !v[1] || !v[2]) {
    printf("Missing parameters\n");
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}
