//
// Created by Gustavo Viegas on 2017/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_apdu.h"
#include "CT_date.h"
#include "CT_dc.h"
#include "CT_file.h"
#include "CT_net.h"
#include "CT_tables.h"

static ctTarget_t ct_g_target; // target unit info

// NOTE: error checking avoided for clarity - don't do that!
int main(int argc, char** argv) {
  ct_g_target.subnet = 0xff;
  ct_g_target.node = 0x1f;
  memset(ct_g_target.sequence, 1, sizeof ct_g_target.sequence);
  memset(ct_g_target.key, 0xf0, sizeof ct_g_target.key);

  ctAddr_t addr;
  strcpy(addr.node, "localhost");
  strcpy(addr.service, "50100");

  ctBind(&addr); // bind to addr

  ctApdu_t apdu, res; // message buffer

  ctFRRequest_t frreq; // full table read request
  frreq.table_id = CT__BT00; // basic table 00

  ctParam_t param; // apdu creation parameters
  param.service = REQUEST_FULL_READ;
  param.fr_request = &frreq;

  int n = ctCreateApdu(&apdu, &param, &ct_g_target); // create full read req apdu

  ctAddr_t src, dest;
  strcpy(dest.node, "localhost");
  strcpy(dest.service, "40100");

  ctSend(apdu.apdu, n, &dest); // send full read req apdu

  n = ctRecv(res.apdu, sizeof res.apdu, &src); // wait for response

  int i;
  printf("\nreceived: ");
  for(i = 0; i < n; ++i) printf("%x ", res.apdu[i]);
  printf("\nfrom: node=%s service=%s", src.node, src.service);
  printf("\nend of message\n");

  ctPRRequest_t prreq; // partial table read request
  prreq.table_id = CT__ET01; // extended table 01
  memset(prreq.offset, 0, sizeof prreq.offset);
  prreq.offset[2] = 0x0c;
  prreq.count = 0x0c;

  param.service = REQUEST_PART_READ;
  param.pr_request = &prreq;

  memset(&apdu, 0, sizeof apdu);
  n = ctCreateApdu(&apdu, &param, &ct_g_target); // create partial read req apdu

  ctSend(apdu.apdu, n, &dest); // send partial read req apdu

  n = ctRecv(res.apdu, sizeof res.apdu, &src); // wait for response

  printf("\nreceived: ");
  for(i = 0; i < n; ++i) printf("%x ", res.apdu[i]);
  printf("\nfrom: node=%s service=%s", src.node, src.service);
  ctMeasureData_t entry;
  memcpy(&entry, res.apdu+4, sizeof entry);
  printf("\ndata...");
  printf("\nvalue: %f", entry.value);
  printf("\ntimestamp: %d/%d/%d %d:%d:%d",
    entry.timestamp.year, entry.timestamp.month,
    entry.timestamp.day, entry.timestamp.hour,
    entry.timestamp.minute, entry.timestamp.second
  );
  printf("\nend of message\n");

  printf("dc completed.\n");
  return EXIT_SUCCESS;
}
