//
// Created by Gustavo Viegas on 2017/05
//

#ifndef CT_NET_H
#define CT_NET_H

#define CT__NET_MAXNODE 20
#define CT__NET_MAXSERV 12

// CtAddr type
//
typedef struct {
  char node[CT__NET_MAXNODE];
  char service[CT__NET_MAXSERV];
} ctAddr_t;

// Bind to addr communication endpoint
//
int ctBind(ctAddr_t* addr);

// Send message to dest
//
int ctSend(void* data, size_t len, ctAddr_t* dest);

// Receive message
//
int ctRecv(void* buffer, size_t len, ctAddr_t* src);

// Unbind from current address
//
int ctUnbind();

#endif // CT_NET_H
