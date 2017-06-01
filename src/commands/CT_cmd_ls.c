//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "commands/CT_cmd_ls.h"

int ctCmdLs(char* names, ctAddr_t* addresses, size_t len) {
  char *b, *p;
  int i, f = 0;
  if(!(p = strtok(NULL, CT__DELIM))) {
    for(i = 0; i < len; ++i) {
      printf("%s %s %s\n", names+i*CT__NAMELEN,
        &addresses[i].node, &addresses[i].service);
    }
  } else {
    do {
      b = strchr(p, '\n');
      if(b) p[strlen(p) - 1] = '\0';
      for(i = 0; i < len; ++i) {
        if(!strcmp(&names[i], p)) {
          printf("%s %s %s\n", names+i*CT__NAMELEN,
            &addresses[i].node, &addresses[i].service);
          f = 1;
          break;
        }
      }
      if(!f) printf("%s not defined\n", p);
    } while((p = strtok(NULL, CT__DELIM)));
  }
  return CT__SUCCESS;
}
