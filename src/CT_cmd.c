//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_apdu.h"
#include "CT_cmd.h"

#define _CT__BUFLEN 0x100
#define _CT__TK "@"
#define _CT__DELIM " "
#define _CT__CMD "cmd"
#define _CT__LS "ls"
#define _CT__DEV "dev"
#define _CT__RM "rm"


/*-------------------------------------------------------------------------------------------------
commands:

cmd|command fr|fw|fullread|fullwrite <TABLE> [param=p1,p2,...,pn] <DEVICE>

cmd|command pr|pw|partialread|partialwrite| <TABLE> [param=...,...] offset=<VALUE> <DEVICE>

dev|device <NAME> node=<NODE> serv|service=<SERV>

rm <DEVICE>

ls dev|device|... [NAME]
-------------------------------------------------------------------------------------------------*/


static int _ctParse(char* buf) {
  char* p = strtok(buf, _CT__DELIM);
  printf("token: %s\n", p);
  while((p = strtok(NULL, _CT__DELIM))) {
    printf("token: %s\n", p);
    // printf("len: %lu\n", strlen(p));
  }
  return CT__SUCCESS;
}

static int _ctInput(char* buf) {
  if(!fgets(buf, _CT__BUFLEN, stdin)) printf("invalid command\n");
  // else printf("%s", buf); // debug
  if(!strchr(buf, '\n')) while(getchar() != '\n');
  return CT__SUCCESS;
}

static int _ctOutput() {
  return CT__SUCCESS;
}

int ctCmdStart(ctTarget_t* target) {
  char buf[_CT__BUFLEN] = {0};
  printf("[DC Interactive shell started]\n");
  while(1) {
    printf("%s DC: ", _CT__TK);
    _ctInput(buf);
    _ctParse(buf);
    _ctOutput();
  }
  return CT__SUCCESS;
}
