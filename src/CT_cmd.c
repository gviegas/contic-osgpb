//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_commands.h"
#include "CT_cmd.h"

#define _CT__BUFLEN 0x100
#define _CT__TK "@"
#define _CT__LS "ls"
#define _CT__CALL "call"
#define _CT__DEF "def"
#define _CT__UNDEF "undef"

/*-------------------------------------------------------------------------------------------------
commands:

call fr|fw|fullread|fullwrite <TABLE> [param=p1,p2,...,pn] <DEVICE>

call pr|pw|partialread|partialwrite| <TABLE> [param=...,...] offset=<VALUE> <DEVICE>

def dev|device <NAME> node=<NODE> serv|service=<SERV>

undef <DEVICE>

ls dev|device|... [NAME]
-------------------------------------------------------------------------------------------------*/

// temp
static int _ctCall() {
  printf("On call\n"); // debug
  char *b, *p;
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    printf("token: %s\n", p); // debug
  }
  return CT__SUCCESS;
}
// temp
static int _ctDef() {
  printf("On def\n"); // debug
  char *b, *p;
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    printf("token: %s\n", p); // debug
  }
  return CT__SUCCESS;
}
// temp
static int _ctUndef() {
  printf("On undef\n"); // debug
  char *b, *p;
  while((p = strtok(NULL, CT__DELIM))) {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    printf("token: %s\n", p); // debug
  }
  return CT__SUCCESS;
}

static int _ctParse(char* buf) {
  char *b, *p = strtok(buf, CT__DELIM);
  int r;
  if(!p) return CT__FAILURE;
  do {
    b = strchr(p, '\n');
    if(b) p[strlen(p) - 1] = '\0';
    if(!strcmp(p, _CT__LS)) ctCmdLs();
    else if(!strcmp(p, _CT__CALL)) _ctCall();
    else if(!strcmp(p, _CT__DEF)) _ctDef();
    else if(!strcmp(p, _CT__UNDEF)) _ctUndef();
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

int ctCmdStart(ctTarget_t* target) {
  char buf[_CT__BUFLEN] = {0};
  printf("[DC Interactive shell started]\n");
  while(1) {
    printf("%s DC: ", _CT__TK);
    _ctInput(buf); // err check
    _ctParse(buf); // err check
  }
  return CT__SUCCESS;
}
