//
// Created by Gustavo Viegas on 2017/06
//

#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "commands/CT_cmd_undef.h"

int ctCmdUndef() {
  printf("On undef\n"); // debug
  char *b, *p;
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    printf("token: %s\n", p); // debug
  }
  return CT__SUCCESS;
}
