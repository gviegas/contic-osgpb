//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_NET_H
#define CT_NET_H

#define CT__NET_MAXNODE 20
#define CT__NET_MAXPORT 12
#define CT__WOULDBLOCK -2

#include "CT_date.h"

// CtAddr type
//
typedef struct {
  char node[CT__NET_MAXNODE];
  char port[CT__NET_MAXPORT];
} ctAddr_t;

// Bind to addr communication endpoint
//
int ctBind(ctAddr_t* addr);

// Send message to dest
//
int ctSend(void* data, size_t len, ctAddr_t* dest);

// Receive message
//
int ctRecv(void* buffer, size_t len, ctAddr_t* src, ctTimeSpec_t* timeout);

// Unbind from current address
//
int ctUnbind();

#endif // CT_NET_H
