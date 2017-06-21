//
// Created by Gustavo Viegas on 2017/06
//

#include <stdio.h>
#include <string.h>
#include "CT_definitions.h"
#include "commands/CT_cmd_def.h"

#define _CT__NODE "node"
#define _CT__PORT "port"

int ctCmdDef(ctList_t* list) {
  char *b, *p, name[CT__LIST_NAMELEN];
  ctAddr_t addr;
  int v[3] = {0};
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '=');
    if(b) {
      *b = '\0';
      ++b;
      if(!v[1] && !strcmp(p, _CT__NODE)) {
        strcpy(addr.node, b);
        v[1] = 1;
      } else if(!v[2] && !strcmp(p, _CT__PORT)) {
        strcpy(addr.port, b);
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
  } else if(ctListFind(list, name)) {
    printf("Duplicate name \"%s\"\n", name);
    return CT__FAILURE;
  } else if(ctListInsert(list, name, &addr) != CT__SUCCESS) {
    printf("Could not define new entry\n");
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}
