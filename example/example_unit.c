//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_apdu.h"
#include "CT_date.h"
#include "CT_file.h"
#include "CT_net.h"
#include "CT_tables.h"
#include "CT_internal.h"
#include "CT_unit.h"

static ctTarget_t ct_g_target; // target unit info

static int processReq(ctApdu_t* res_apdu, ctApdu_t* apdu) {
  return ctProcessRequest(res_apdu, apdu, &ct_g_target);
}

// NOTE: error checking avoided for clarity - don't do that!
int main(int argc, char** argv) {
  ct_g_target.subnet = 0xff;
  ct_g_target.node = 0x1f;
  memset(ct_g_target.sequence, 1, sizeof ct_g_target.sequence);
  memset(ct_g_target.s_omak, 0xf0, sizeof ct_g_target.s_omak);

  ctCreate(); // create data block
  ctUnitDefaultCommission(); // create unit with default configuration
  ctStartInternal(); // start internal operation (new thread)

  ctAddr_t addr;
  strcpy(addr.node, "localhost");
  strcpy(addr.service, "40100");
  ctBind(&addr); // bind to addr

  ctApdu_t apdu;

  for(;;) {
    int i, n;
    ctAddr_t src;

    n = ctRecv(apdu.apdu, sizeof apdu.apdu, &src); // receive message

    printf("\nreceived: ");
    for(i = 0; i < n; ++i) printf("%x ", apdu.apdu[i]);
    printf("\nfrom: node=%s service=%s", src.node, src.service);
    printf("\nend of message\n");

    ctApdu_t res;
    n = processReq(&res, &apdu);

    ctSend(res.apdu, n, &src); // send response apdu
  }

  printf("unit completed.\n");
  return EXIT_SUCCESS;
}
