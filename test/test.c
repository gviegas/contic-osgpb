//
// Created by Gustavo Viegas on 2017/02
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "CT_table_services.h"
#include "CT_security.h"
#include "CT_apdu.h"
#include "CT_table_access.h"
#include "CT_tables.h"
#include "CT_file.h"
#include "CT_unit.h"
#include "CT_internal.h"
#include "CT_net.h"
#include "CT_event_queue.h"

ctTarget_t t = {0x02, 0x03};

void servicesTest() {
  uint8_t b[1024];
  int i, s = ctWriteResponse(b, CT__RES_ERR);
  for(i = 0; i < s; ++i) printf("%x\n", b[i]);
  printf("\nsize of msg: %zu\n", sizeof b);
}

void securityTest() {
  uint8_t b[100] = {0}, req[50] = {0}, res[50] = {0}, o[3] = {0},
    d[] = {0xd,0xc,0xb};

  int s1 = ctPartialReadRequest(req+1, 0x0034, o, 0x0006);
  s1++;
  int s2 = ctReadResponse(res+1, CT__RES_ERR, 3, d);
  // int i, s = ctAuthenticate(b, req, res, s1, s2, &t);
  int i, s = ctAuthenticate(b, req, NULL, s1, s2, &t);

  printf("\req: ");
  for(i = 0; i < s1; ++i) printf("%x ", req[i]);
  printf("\ndig: ");
  for(i = 0; i < s; ++i) printf("%x ", b[i]);
  printf("\n");
}

void apduTest() {
  // req
  ctParam_t param;

  // ctFRRequest_t frreq;
  // frreq.table_id = CT__ET12;
  // param.service = REQUEST_FULL_READ;
  // param.fr_request = &frreq;

  // ctPRRequest_t prreq;
  // prreq.table_id = CT__ET04;
  // prreq.offset[0] = 0;
  // prreq.offset[1] = 0;
  // prreq.offset[2] = 10;
  // prreq.count = 20;
  // param.service = REQUEST_PART_READ;
  // param.pr_request = &prreq;

  // ctFWRequest_t fwreq;
  // fwreq.table_id = CT__BP10;
  // uint8_t d[] = {1,2,3,4,5,6,7};
  // memcpy(fwreq.data, d, sizeof d);
  // fwreq.count = sizeof d;
  // param.service = REQUEST_FULL_WRITE;
  // param.fw_request = &fwreq;

  ctPWRequest_t pwreq;
  pwreq.table_id = CT__ET11;
  pwreq.offset[0] = 0;
  pwreq.offset[1] = 0;
  pwreq.offset[2] = 28;
  uint8_t d[] = {10,9,8,7,6,5,4,3,2,1};
  memcpy(pwreq.data, d, sizeof d);
  pwreq.count = sizeof d;
  param.service = REQUEST_PART_WRITE;
  param.pw_request = &pwreq;

  ctApdu_t apdu;
  int c = ctCreateApdu(&apdu, &param, &t);

  int i;
  printf("\napdu req: ");
  for(i = 0; i < c; ++i) printf("%x ", apdu.apdu[i]);
  printf("\n");

  //////////////////////////////
  // res
  // ctRResponse_t rres;
  // uint8_t d[] = {2,4,6,8,0x0a,0x0c,0x0e};
  // rres.response = 0;
  // rres.count = sizeof d;
  // memcpy(rres.data, d, rres.count);
  // rres.request = apdu.apdu;
  // rres.req_count = abs(c - CT__LEN_DIGEST);

  // ctParam_t param1;
  // param1.service = RESPONSE_FULL_READ;
  // param1.r_response = &rres;

  // ctApdu_t apdu1;

  // int c1 = ctCreateApdu(&apdu1, &param1, &t);

  // printf("\napdu res: ");
  // for(i = 0; i < c1; ++i) printf("%x ", apdu1.apdu[i]);
  // printf("\n");

  //////////////////////////////
  // validate req
  ctApdu_t apdu2;

  // apdu.apdu[3] = 0xdd;
  int c2 = ctProcessRequest(&apdu2, &apdu, &t);

  if(c2 != CT__FAILURE) {
    printf("\nprocess req: %d\n", c2);
    for(i = 0; i < c2; ++i) printf("%x ", apdu2.apdu[i]);
    printf("\n");
  } else printf("\nrequest failed\n");

  //////////////////////////////
  // validate res
  // ctResponse_t b;

  // int v = ctProcessResponse(&b, &apdu1, &apdu, &t);

  // // apdu1.apdu[6] = 0xff;
  // printf("\nprocess res: %d\n", v);
  // if(v == CT__SUCCESS) {
  //   printf("service: %x \n", b.service);
  //   printf("response: %x \n", b.response);
  //   printf("read_count: %x \n", b.read_count);
  //   printf("read_data: ");
  //   for(i = 0; i < b.read_count; ++i) printf("%x ", b.read_data[i]);
  // }
  // printf("\n");
}

void btTest() {
  ctBT00_t bt00;
  // bt00.data_order = 0;
  // bt00.char_format = 0b011;
  // printf("bt00: %d\n", bt00.data_order);
  // printf("bt00: %d\n", bt00.char_format);
  printf("bt00: %lu\n", sizeof bt00);
  ctBT05_t bt05;
  printf("bt05: %lu\n", sizeof bt05);
  ctBT06_t bt06;
  printf("bt06: %lu\n", sizeof bt06);
  ctBT07_t bt07;
  printf("bt07: %lu\n", sizeof bt07);
  ctBT08_t bt08;
  printf("bt08: %lu\n", sizeof bt08);
  ctBT10_t bt10;
  printf("bt10: %lu\n", sizeof bt10);
  ctBT12_t bt12;
  printf("bt12: %lu\n", sizeof bt12);
  ctBT13_t bt13;
  printf("bt13: %lu\n", sizeof bt13);
  ctBT15_t bt15;
  printf("bt15: %lu\n", sizeof bt15);
  ctBT16_t bt16;
  printf("bt16: %lu\n", sizeof bt16);
  ctBT20_t bt20;
  printf("bt20: %lu\n", sizeof bt20);
  ctBT21_t bt21;
  printf("bt21: %lu\n", sizeof bt21);
  ctBT22_t bt22;
  printf("bt22: %lu\n", sizeof bt22);
  ctBT23_t bt23;
  printf("bt23: %lu\n", sizeof bt23);
  ctBT26_t bt26;
  printf("bt26: %lu\n", sizeof bt26);
  ctBT50_t bt50;
  printf("bt50: %lu\n", sizeof bt50);
  ctBT52_t bt52;
  printf("bt52: %lu\n", sizeof bt52);
  ctBT54_t bt54;
  printf("bt54: %lu\n", sizeof bt54);
  ctBT55_t bt55;
  printf("bt55: %lu\n", sizeof bt55);
  ctBT60_t bt60;
  printf("bt60: %lu\n", sizeof bt60);
  ctBT61_t bt61;
  printf("bt61: %lu\n", sizeof bt61);
  ctBT62_t bt62;
  printf("bt62: %lu\n", sizeof bt62);
  ctBT63_t bt63;
  printf("bt63: %lu\n", sizeof bt63);
  ctBT64_t bt64;
  printf("bt64: %lu\n", sizeof bt64);
}

void etTest() {
  ctET00_t et00;
  printf("et00: %lu\n", sizeof et00);
  ctET01_t et01;
  printf("et01: %lu\n", sizeof et01);
  ctET04_t et04;
  printf("et04: %lu\n", sizeof et04);
  ctET11_t et11;
  printf("et11: %lu\n", sizeof et11);
  ctET12_t et12;
  printf("et12: %lu\n", sizeof et12);
  ctET21_t et21;
  printf("et21: %lu\n", sizeof et21);
  ctET42_t et42;
  printf("et42: %lu\n", sizeof et42);
}

void readTest() {
  uint8_t buf[3];
  memset(buf, 0, 3);
  printf("%d\n", ctRead(0, &buf, 3, 0));
  int i;
  for(i = 0; i < 3; i++) printf("%x ", buf[i]);
  printf("\n");
}

void writeTest() {
  uint8_t buf[] = {1,2,3,4,5,6,7,8,9,10};
  printf("%d\n", ctWrite(0, buf+9, 1, 0));
}

void createTest() {
  ctCreate();
}

void unitTest() {
  ctDefaultUnitCommission();
}

void dcTest() {};

void internalTest() {
  ctStartInternal();
}

void netrecvTest() {
  char buffer[20];
  ctAddr_t addr, src;
  int len;

  strcpy(addr.node, "localhost");
  strcpy(addr.service, "40100");
  memset(&src, 0, sizeof src);

  ctBind(&addr);
  len = ctRecv(buffer, (sizeof buffer) - 1, &src);
  buffer[len] = '\0';

  printf("\nnode=%s service=%s", src.node, src.service);
  printf("\nreceived: %s (%d)\n", buffer, len);
}

void netsendTest() {
  char* data = "Tinny Dog";
  ctAddr_t addr, dest;
  strcpy(addr.node, "localhost");
  strcpy(addr.service, "50100");
  strcpy(dest.node, "localhost");
  strcpy(dest.service, "40100");

  ctBind(&addr);
  ctSend(data, strlen(data), &dest);
}

void e1() { printf("\ne1!"); }
void e2() { printf("\ne2!"); }
void e3() { printf("\ne3!"); }
void e4() { printf("\ne4!"); }
void e5() { printf("\ne5!"); }
void e6() { printf("\ne6!"); }
void e7() { printf("\ne7!"); }
void e8() { printf("\ne8!"); }
void e9() { printf("\ne9!"); }
void eventTest() {
  ctEvent_t a = {EVENT_TIMEOUT, 10, e1};
  ctEvent_t b = {EVENT_TIMEOUT, 5, e2};
  ctEvent_t c = {EVENT_TIMEOUT, 20, e3};
  ctEvent_t d = {EVENT_TIMEOUT, 60, e4};
  ctEvent_t e = {EVENT_TIMEOUT, 30, e5};
  ctEvent_t f = {EVENT_TIMEOUT, 40, e6};
  ctEvent_t g = {EVENT_TIMEOUT, 90, e7};
  ctEvent_t h = {EVENT_TIMEOUT, 1, e8};
  ctEvent_t i = {EVENT_TIMEOUT, 3, e9};

  ctQueue_t q;
  ctEvent_t t, *u = NULL;

  ctQueueCreate(&q);
  ctQueuePut(&q, &a);
  ctQueuePut(&q, &b);
  ctQueuePut(&q, &c);
  ctQueuePut(&q, &d);

  ctQueueGet(&q, &t);
  ctQueueGet(&q, &t);
  ctQueueGet(&q, &t);

  ctQueuePut(&q, &e);
  ctQueuePut(&q, &f);
  ctQueuePut(&q, &g);
  ctQueuePut(&q, &h);
  ctQueuePut(&q, &i);

  ctQueueSort(&q);

  printf("head: %d tail: %d", q.head, q.tail);
  int idx;
  for(idx = q.head;; idx = (idx + 1) % CT__QUEUE_LEN) {
    printf("\n%ld", q.events[idx].delay);
    q.events[idx].exec();
    if(idx == q.tail) break;
  }
  ctQueuePeek(&q, &u);
  printf("\n0_0 %ld", u->delay);
  u->exec();
  printf("\n");
}

int main(int argc, char** argv) {
  srand(time(NULL));
  uint8_t seq[] = {0xf5,0x2f,0x54,0x81};
  uint8_t key[] = {0xdf,0x01,0x02,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf,0xaf};
  memcpy(t.sequence, seq, sizeof seq);
  memcpy(t.s_omak, key, sizeof key);

  // apduTest();
  // btTest();
  // etTest();
  // readTest();
  // writeTest();

  // createTest();
  // unitTest();
  // ctBT00_t bt00;
  // ctRead(CT__BT00, &bt00, sizeof bt00, 0);
  // printf("%x\n", bt00.char_format);
  // printf("%x\n", bt00.time_format);
  // printf("%x\n", bt00.data_access_method);
  // printf("%x\n", bt00.non_int_format_1);
  // printf("%x\n", bt00.non_int_format_2);
  // printf("%s\n", bt00.manufacturer);
  // printf("%x\n", bt00.nameplate_type);
  // printf("%x\n", bt00.procedure_param_length);
  // printf("%x\n", bt00.response_data_length);
  // printf("%x\n", bt00.standard_version);
  // printf("%x\n", bt00.dim_basic_tables_used);
  // printf("%x\n", bt00.dim_extended_tables_used);
  // printf("%x\n", bt00.dim_basic_procedures_used);
  // printf("%x\n", bt00.dim_extended_procedures_used);
  // printf("%x\n", bt00.manufacturer_status_length);
  // printf("%x\n", bt00.number_pending_tables);
  // printf("%x\n", bt00.bt00_used);
  // printf("%x\n", bt00.et00_used);
  // printf("%x\n", bt00.et01_used);
  // printf("%x\n", bt00.et00_write);
  // printf("%x\n", bt00.et01_write);
  // uint8_t buf[38];
  // ctRead(CT__ET00, &buf, sizeof buf, 0);
  // int i = 0;
  // for(; i< sizeof buf; i++) printf("%x ", buf[i]);
  // printf("\n");
  // ctET00_t et00;
  // ctRead(CT__ET00, &et00, sizeof et00, 0);
  // printf("%x\n", et00.measure_devices_used);

  // internalTest();
  // sleep(900);

  eventTest();

  // printf("\n|ET01|\n");
  // ctMeasureData_t entries[10];
  // ctRead(CT__ET01, entries, sizeof entries, 0);
  // int j;
  // for(j = 0; j < sizeof entries / sizeof entries[0]; ++j) {
  //   printf("value: %f\n", entries[j].value);
  //   printf("timestamp: %d/%d/%d %d:%d:%d\n",
  //     entries[j].timestamp.year, entries[j].timestamp.month,
  //     entries[j].timestamp.day, entries[j].timestamp.hour,
  //     entries[j].timestamp.minute, entries[j].timestamp.second
  //   );
  // }

  // dcTest();

  // netrecvTest();
  // netsendTest();

  return 0;
}
