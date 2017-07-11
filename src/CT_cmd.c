//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include <string.h>
#include "CT_definitions.h"
#include "CT_thread.h"
#include "CT_name_list.h"
#include "CT_commands.h"
#include "CT_cmd.h"

#define _CT__BUFLEN 0x100
#define _CT__TK "@"
#define _CT__LS "ls"
#define _CT__CALL "call"
#define _CT__DEF "def"
#define _CT__UNDEF "undef"

static int _ct_tty;

static int _ctParse(char* buf, ctList_t* list) {
  char *p = strtok(buf, CT__DELIM);
  if(!p) return CT__FAILURE;
  do {
    if(!strcmp(p, _CT__DEF)) ctCmdDef(list);
    else if(!strcmp(p, _CT__UNDEF)) ctCmdUndef(list);
    else if(!strcmp(p, _CT__LS)) ctCmdLs(list);
    else if(!strcmp(p, _CT__CALL)) ctCmdCall(list);
    // else print "invalid command"
  } while((p = strtok(NULL, CT__DELIM)));
  return CT__SUCCESS;
}

static int _ctInput(char* buf) {
  char c;
  if(!fgets(buf, _CT__BUFLEN, stdin)) {
    fprintf(stderr, "ERROR: EOF - no input\n");
    ctSleep(3);
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

static void _ctPipe(char* buf, ctList_t* list) {
  while(1) {
    _ctInput(buf);
    _ctParse(buf, list);
    fflush(stdout);
  }
}

static void _ctTty(char* buf, ctList_t* list) {
  printf("[DC Interactive shell started]\n");
  while(1) {
    printf("%sDC: ", _CT__TK);
    _ctInput(buf);
    _ctParse(buf, list);
  }
}

int ctCmdStart(int interactive) {
  char buf[_CT__BUFLEN] = {0};
  ctList_t list;
  if(ctListCreate(&list) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to create the name list\n");
    return CT__FAILURE;
  }
  if((_ct_tty = interactive)) _ctTty(buf, &list);
  else _ctPipe(buf, &list);
  return CT__SUCCESS;
}

void ctCmdPrint(ctAddr_t* addr, ctResponse_t* res) {
  int i;
  if(_ct_tty) {
    printf("\n[OK]");
    printf("\nFrom: %s %s", addr->node, addr->port);
    printf("\nData:");
    for(i = 0; i < res->read_count; ++i) {
      if(!(i % 16)) printf("\n\t");
      printf(" %x", res->read_data[i]);
    }
    printf("\n");
    printf("%sDC: ", _CT__TK);
  } else {
    printf("\n[OK]");
    printf("\nFrom:%s %s", addr->node, addr->port);
    printf("\nData:");
    for(i = 0; i < res->read_count; ++i)
      printf("%x%s", res->read_data[i], i+1 == res->read_count ? "" : " ");
    printf("\n");
    printf("[EOF]");
  }
  fflush(stdout);
}

void ctCmdErr(ctAddr_t* addr, char* err) {
  if(_ct_tty) {
    printf("\n[ERR]");
    printf("\nOffender: %s %s", addr->node, addr->port);
    printf("\nError: %s", err);
    printf("\n");
    printf("%sDC: ", _CT__TK);
  } else {
    printf("\n[ERR]");
    printf("\nOffender:%s %s", addr->node, addr->port);
    printf("\nError:%s", err);
    printf("\n");
    printf("[EOF]");
  }
  fflush(stdout);
}
