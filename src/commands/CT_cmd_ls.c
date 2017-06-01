//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "commands/CT_cmd_ls.h"

int ctCmdLs(char names[][CT__NAMELEN], ctAddr_t* addresses, size_t len) {
  char *b, *p;
  int i, f;
  if(!(p = strtok(NULL, CT__DELIM))) {
    for(i = 0; i < len; ++i) {
      printf("%s %s %s\n", names[i],
        addresses[i].node, addresses[i].service);
    }
  } else {
    do {
      b = strchr(p, '\n');
      if(b) p[strlen(p) - 1] = '\0';
      for(i = 0, f = 0; i < len && !f; ++i) {
        if(!strcmp(names[i], p)) {
          printf("%s %s %s\n", names[i],
            addresses[i].node, addresses[i].service);
          f = 1;
        }
      }
      if(!f) printf("%s not defined\n", p);
    } while((p = strtok(NULL, CT__DELIM)));
  }
  return CT__SUCCESS;
}
