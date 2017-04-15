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
#include "CT_dc.h"
#include "CT_file.h"
#include "CT_tables.h"

static const char* ct_g_host = "localhost";
static const char* ct_g_port = "45300";

void dgram_client(void* buffer, size_t length) {
  struct addrinfo hints, *result, *rp;
  int sfd, s, i;
  size_t n;
  ctApdu_t apdu;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // IPv4/6
  hints.ai_socktype = SOCK_DGRAM;

  s = getaddrinfo(ct_g_host, ct_g_port, &hints, &result);
  if(s) {
    fprintf(stderr, "\nERROR: getaddrinfo failed\n");
    return;
  }

  // for each address structure, try to connect()...
  for(rp = result; rp != NULL; rp = rp->ai_next) {
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(sfd == -1) continue;
    if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) break;
    close(sfd);
  }

  if(rp == NULL) {
    fprintf(stderr, "\nERROR: failed to connect\n");
    return;
  }

  freeaddrinfo(result);

  if(write(sfd, buffer, length) != length) {
    fprintf(stderr, "\nERROR: write failed\n");
    return;
  }

  n = read(sfd, apdu.apdu, CT__LEN_MAXAPDU);
  if(n == -1) {
    fprintf(stderr, "\nERROR: read failed\n");
    return;
  }

  for(i = 0; i < n; ++i) printf("%x ", apdu.apdu[i]);
  printf("\ndgram succesfull\n");
}

int main(int argc, char** argv) {
  ctApdu_t apdu; // message buffer

  ctFRRequest_t frreq; // full table read request
  frreq.table_id = CT__BT00; // basic table 00

  ctParam_t param; // apdu creation parameters
  param.service = REQUEST_FULL_READ;
  param.fr_request = &frreq;

  ctTarget_t target; // target unit info
  target.subnet = 0xff;
  target.node = 0x1f;
  memset(target.sequence, 1, sizeof target.sequence);
  memset(target.s_omak, 0xf0, sizeof target.s_omak);

  int n = ctCreateApdu(&apdu, &param, &target); // create full read req apdu

  // printf("len: %d\n", s);
  // int i;
  // for(i = 0; i < s; ++i) printf("%x ", apdu.apdu[i]);
  // printf("\n");

  dgram_client(apdu.apdu, n);

  printf("dc test done.\n");
  return EXIT_SUCCESS;
}