//
// Creted by Gustavo Viegas on 2017/05
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

static int ct_g_sfd = -1;

int ctBind(ctAddr_t* addr) {
  struct addrinfo hints, *result, *rp;
  int s;

  if(ct_g_sfd != -1) {
    fprintf(stderr, "\nERROR: already bound");
    return CT__FAILURE;
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // IPv4/6
  hints.ai_socktype = SOCK_DGRAM;

  s = getaddrinfo(addr->node, addr->service, &hints, &result);
  if(s) {
    fprintf(stderr, "\nERROR: ctBind - failed to resolve address (%s)\n",
      gai_strerror(s));
    return CT__FAILURE;
  }

  // for each address structure, try to bind()
  for(rp = result; rp != NULL; rp = rp->ai_next) {
    ct_g_sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(ct_g_sfd == -1) continue;
    if(bind(ct_g_sfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
    close(ct_g_sfd);
  }

  if(rp == NULL) {
    fprintf(stderr, "\nERROR: ctBind - failed to bind\n");
    return CT__FAILURE;
  }

  freeaddrinfo(result);
  return CT__SUCCESS;
}

int ctSend(void* data, size_t len, ctAddr_t* dest) {
    struct addrinfo hints, *result, *rp;
    int s;
    size_t n;

    if(ct_g_sfd == -1) {
      fprintf(stderr, "\nERROR: ctSend - unbound\n");
      return CT__FAILURE;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // IPv4/6
    hints.ai_socktype = SOCK_DGRAM;

    s = getaddrinfo(dest->node, dest->service, &hints, &result);
    if(s) {
      fprintf(stderr, "\nERROR: ctSend - failed to resolve address (%s)\n",
        gai_strerror(s));
      return CT__FAILURE;
    }

    // for each address structure, try sendto()
    for(rp = result; rp != NULL; rp = rp->ai_next) {
      n = sendto(ct_g_sfd, data, len, 0, rp->ai_addr, rp->ai_addrlen);
      if(n != -1) break;
    }

    freeaddrinfo(result);

    if(n != len) {
      fprintf(stderr, "\nERROR: ctSend - send failed\n");
      return CT__FAILURE;
    }

    return CT__SUCCESS;
}

int ctRecv(void* buffer, size_t len, ctAddr_t* src) {
  size_t n;
  struct sockaddr_storage peer_addr;
  socklen_t addr_len;
  int s;

  if(ct_g_sfd == -1) {
    fprintf(stderr, "\nERROR: ctRecv unbound\n");
    return -1;
  }

  n = recvfrom(ct_g_sfd, buffer, len, 0,
    (struct sockaddr*) &peer_addr, &addr_len);

  s = getnameinfo((struct sockaddr*) &peer_addr, addr_len, src->node,
    sizeof src->node, src->service, sizeof src->service, 0);

  if(s) {
    fprintf(stderr, "\nERROR: ctRecv - failed to resolve address (%s)\n",
      gai_strerror(s));
    return -1;
  }

  return n;
}

int ctUnbind() {
  if(close(ct_g_sfd)) {
    fprintf(stderr, "\nERROR: ctUnbind - failed to unbound");
    return CT__FAILURE;
  }
  ct_g_sfd = -1;
  return CT__SUCCESS;
}
