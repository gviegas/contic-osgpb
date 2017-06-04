//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "CT_defs.h"
#include "CT_net.h"

static int _ct_sfd = -1;

int ctBind(ctAddr_t* addr) {
  struct addrinfo hints, *result, *rp;
  int s;

  if(_ct_sfd != -1) {
    fprintf(stderr, "ERROR: already bound\n");
    return CT__FAILURE;
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // IPv4/6
  hints.ai_socktype = SOCK_DGRAM;

  s = getaddrinfo(addr->node, addr->service, &hints, &result);
  if(s) {
    fprintf(stderr, "ERROR: ctBind - failed to resolve address (%s)\n",
      gai_strerror(s));
    return CT__FAILURE;
  }

  // for each address structure, try to bind()
  for(rp = result; rp != NULL; rp = rp->ai_next) {
    _ct_sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(_ct_sfd == -1) continue;
    if(bind(_ct_sfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
    close(_ct_sfd);
  }

  if(rp == NULL) {
    fprintf(stderr, "ERROR: ctBind - failed to bind\n");
    return CT__FAILURE;
  }

  freeaddrinfo(result);
  return CT__SUCCESS;
}

int ctSend(void* data, size_t len, ctAddr_t* dest) {
    struct addrinfo hints, *result, *rp;
    int s;
    size_t n;

    if(_ct_sfd == -1) {
      fprintf(stderr, "ERROR: ctSend - unbound\n");
      return CT__FAILURE;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // IPv4/6
    hints.ai_socktype = SOCK_DGRAM;

    s = getaddrinfo(dest->node, dest->service, &hints, &result);
    if(s) {
      fprintf(stderr, "ERROR: ctSend - failed to resolve address (%s)\n",
        gai_strerror(s));
      return CT__FAILURE;
    }

    // for each address structure, try sendto()
    for(rp = result; rp != NULL; rp = rp->ai_next) {
      n = sendto(_ct_sfd, data, len, 0, rp->ai_addr, rp->ai_addrlen);
      if(n != -1) break;
    }

    freeaddrinfo(result);

    if(n != len) {
      fprintf(stderr, "ERROR: ctSend - send failed\n");
      return CT__FAILURE;
    }

    return CT__SUCCESS;
}

int ctRecv(void* buffer, size_t len, ctAddr_t* src, ctTimeSpec_t* timeout) {
  size_t n;
  struct sockaddr_storage peer_addr;
  socklen_t addr_len;
  struct timeval t;
  int s;

  if(_ct_sfd == -1) {
    fprintf(stderr, "ERROR: ctRecv unbound\n");
    return -1;
  }

  if(timeout) {
    t.tv_sec = timeout->sec;
    t.tv_usec = timeout->nsec / 1000;
    if(setsockopt(_ct_sfd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof t)) {
      fprintf(stderr, "ERROR: ctRecv failed to set timeout\n");
      return -1;
    }
  } else {
    t.tv_sec = 0;
    t.tv_usec = 0;
    if(setsockopt(_ct_sfd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof t)) {
      fprintf(stderr, "ERROR: ctRecv failed to set NO timeout\n");
      return -1;
    }
  }

  addr_len = sizeof peer_addr;
  n = recvfrom(_ct_sfd, buffer, len, 0,
    (struct sockaddr*) &peer_addr, &addr_len);

  s = getnameinfo((struct sockaddr*) &peer_addr, addr_len, src->node,
    sizeof src->node, src->service, sizeof src->service, 0);

  if(s) {
    fprintf(stderr, "ERROR: ctRecv - failed to resolve address (%s)\n",
      gai_strerror(s));
    return -1;
  }

  return n;
}

int ctUnbind() {
  if(close(_ct_sfd)) {
    fprintf(stderr, "ERROR: ctUnbind - failed to unbind\n");
    return CT__FAILURE;
  }
  _ct_sfd = -1;
  return CT__SUCCESS;
}
