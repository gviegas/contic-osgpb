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
static ctTarget_t ct_g_target; // target unit info

int processReq(ctApdu_t* res_apdu, ctApdu_t* apdu) {
  return ctProcessRequest(res_apdu, apdu, &ct_g_target);
}

void dgramServer(/*void* buffer, size_t length*/) {
  struct addrinfo hints, *result, *rp;
  int sfd, s, i;
  size_t n;
  struct sockaddr_storage peer_addr;
  socklen_t peer_addr_len;
  ctApdu_t apdu, res_apdu;

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
  peer_addr_len = sizeof peer_addr;

  for(;;) {
    n = recvfrom(sfd, apdu.apdu, CT__LEN_MAXAPDU, 0,
      (struct sockaddr*) &peer_addr, &peer_addr_len);

    if(n == -1) continue; // failed request - ignore...

    char host[NI_MAXHOST], service[NI_MAXSERV];
    s = getnameinfo((struct sockaddr*) &peer_addr, peer_addr_len,
      host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

    if(s == 0) {
      printf("\nrequest received (%d):\n", (int) n);
      for(i = 0; i < n; ++i) printf("%x ", apdu.apdu[i]);
      printf("\n----end of request----\n");

      n = processReq(&res_apdu, &apdu); // process request apdu

      // send response apdu
      if(sendto(sfd, &res_apdu, n, 0, (struct sockaddr*) &peer_addr,
        peer_addr_len) != n)
        fprintf(stderr, "\nERROR: sendto failed\n");

    } else
      fprintf(stderr, "\nERROR: getnameinfo failed\n");

    // if(sendto(sfd, "OK", 3, 0, (struct sockaddr*) &peer_addr,
    //   peer_addr_len) != 3)
    //   fprintf(stderr, "\nERROR: sendto failed\n");
  }
}

int main(int argc, char** argv) {
  ct_g_target.subnet = 0xff;
  ct_g_target.node = 0x1f;
  memset(ct_g_target.sequence, 1, sizeof ct_g_target.sequence);
  memset(ct_g_target.s_omak, 0xf0, sizeof ct_g_target.s_omak);

  dgramServer();

  printf("unit test done.\n");
  return EXIT_SUCCESS;
}
