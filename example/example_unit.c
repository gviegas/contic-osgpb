//
// Created by Gustavo Viegas on 2017/04
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "CT_apdu.h"
#include "CT_date.h"
#include "CT_file.h"
#include "CT_tables.h"
#include "CT_unit.h"

static const char* ct_g_port = "45300";

void dgram_server(/*void* buffer, size_t length*/) {
  struct addrinfo hints, *result, *rp;
  int sfd, s, i;
  size_t n;
  struct sockaddr_storage peer_addr;
  socklen_t peer_addr_len;
  ctApdu_t apdu;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // IPv4/6
  hints.ai_socktype = SOCK_DGRAM;

  s = getaddrinfo(NULL, ct_g_port, &hints, &result);
  if(s) {
    fprintf(stderr, "\nERROR: getaddrinfo failed\n");
    return;
  }

  // for each address structure, try to bind()...
  for(rp = result; rp != NULL; rp = rp->ai_next) {
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(sfd == -1) continue;
    if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
    close(sfd); 
  }

  if(rp == NULL) {
    fprintf(stderr, "\nERROR: failed to bind\n");
    return;
  }

  freeaddrinfo(result);

  for(;;) {
    n = recvfrom(sfd, apdu.apdu, CT__LEN_MAXAPDU, 0,
      (struct sockaddr*) &peer_addr, &peer_addr_len);
    
    if(n == -1) continue; // failed request - ignore...

    char host[NI_MAXHOST], service[NI_MAXSERV];
    s = getnameinfo((struct sockaddr*) &peer_addr, peer_addr_len,
      host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

    if(s == 0) {
      printf("\nmessage:\n");
      for(i = 0; i < n; ++i) printf("%x ", apdu.apdu[i]);
      printf("\nend of message\n");
    } else fprintf(stderr, "\nERROR: getnameinfo failed\n");

    if(sendto(sfd, "OK", 3, 0, (struct sockaddr*) &peer_addr,
      peer_addr_len) != 3)
      fprintf(stderr, "\nERROR: sendto failed\n");
  }
}

int main(int argc, char** argv) {
  dgram_server();

  printf("unit test done.\n");
  return EXIT_SUCCESS;
}