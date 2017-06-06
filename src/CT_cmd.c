//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_definitions.h"
#include "CT_name_list.h"
#include "CT_commands.h"
#include "CT_cmd.h"

#define _CT__BUFLEN 0x100
#define _CT__TK "@"
#define _CT__LS "ls"
#define _CT__CALL "call"
#define _CT__DEF "def"
#define _CT__UNDEF "undef"

static int _ctParse(char* buf, ctList_t* list) {
  char *p = strtok(buf, CT__DELIM);
  if(!p) return CT__FAILURE;
  do {
    if(!strcmp(p, _CT__DEF)) ctCmdDef(list);
    else if(!strcmp(p, _CT__UNDEF)) ctCmdUndef(list);
    else if(!strcmp(p, _CT__LS)) ctCmdLs(list);
    else if(!strcmp(p, _CT__CALL)) ctCmdCall(list);
    // else {
    //   printf("Invalid option\n");
    //   break;
    // }
  } while((p = strtok(NULL, CT__DELIM)));
  return CT__SUCCESS;
}

static int _ctInput(char* buf) {
  char c;
  if(!fgets(buf, _CT__BUFLEN, stdin)) {
    fprintf(stderr, "ERROR: EOF - no input\n");
    return CT__FAILURE;
  }
  if(!strchr(buf, '\n')) {
    do {
      c = getchar();
      if(c == '\n') break;
      if(c == EOF) return CT__FAILURE;
    } while(1);
  }
  return CT__SUCCESS;
}

int ctCmdStart() {
  char buf[_CT__BUFLEN] = {0};
  ctList_t list;
  if(ctListCreate(&list) != CT__SUCCESS) {
    fprintf(stderr, "Failed to create the name list\n");
    return CT__FAILURE;
  }
  printf("[DC Interactive shell started]\n");
  while(1) {
    printf("%s DC: ", _CT__TK);
    _ctInput(buf); // err check
    _ctParse(buf, &list); // err check
  }
  return CT__SUCCESS;
}
