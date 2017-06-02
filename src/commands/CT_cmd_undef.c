//
// Created by Gustavo Viegas on 2017/06
//

#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "commands/CT_cmd_undef.h"

int ctCmdUndef(ctList_t* list) {
  char *b, *p;
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    if(ctListRemove(list, p) != CT__SUCCESS)
      printf("Name \"%s\" not defined\n", p);
  }
  return CT__SUCCESS; // always returns success...
}
