//
// Created by Gustavo Viegas on 2017/06
//

#include <stdio.h>
#include "CT_definitions.h"
#include "CT_pipe.h"

int ctNpipeIn(char* path) {
  if(!(freopen(path, "r", stdin))) {
    fprintf(stderr, "ERROR: Failed to open pipe for reading on %s\n", path);
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}

int ctNpipeOut(char* path) {
  if(!(freopen(path, "w", stdout))) {
    fprintf(stderr, "ERROR: Failed to open pipe for writing on %s\n", path);
    return CT__FAILURE;
  }
  return CT__SUCCESS;
}
