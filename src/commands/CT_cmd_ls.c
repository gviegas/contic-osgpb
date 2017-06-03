//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "commands/CT_cmd_ls.h"

int ctCmdLs(ctList_t* list) {
  char *b, *p;
  ctNode_t* node;
  if(!(p = strtok(NULL, CT__DELIM))) {
    node = ctListFirst(list);
    while(node) {
      printf("%s %s %s\n", node->name, node->addr.node, node->addr.service);
      node = ctListNext(list, node);
    }
  } else {
    do {
      b = strchr(p, '\n');
      if(b) p[strlen(p) - 1] = '\0';
      if((node = ctListFind(list, p)))
        printf("%s %s %s\n", node->name, node->addr.node, node->addr.service);
      else
        printf("\"%s\" not defined\n", p);
    } while((p = strtok(NULL, CT__DELIM)));
  }
  return CT__SUCCESS;
}
