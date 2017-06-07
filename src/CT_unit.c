//
// Created by Gustavo Viegas on 2017/04
//

#include <stdio.h>
#include <string.h>
#include "CT_tables.h"
#include "CT_file.h"
#include "CT_event_manager.h"
#include "CT_state.h"
#include "CT_apdu.h"
#include "CT_unit.h"

int ctUnitCommissioning() {
  // BT00
  ctBT00_t bt00;
  memset(&bt00, 0, sizeof bt00);
  bt00.char_format = 1;
  bt00.time_format = 2;
  bt00.data_access_method = 1;
  bt00.non_int_format_1 = 8;
  bt00.non_int_format_2 = 8;
  memcpy(bt00.manufacturer, "CT00", 4);
  bt00.nameplate_type = 2;
  bt00.procedure_param_length = 255;
  bt00.response_data_length = 12;
  bt00.standard_version = 1;
  bt00.dim_basic_tables_used = 10;
  bt00.dim_extended_tables_used = 13;
  bt00.dim_basic_procedures_used = 2;
  bt00.dim_extended_procedures_used = 12;
  bt00.manufacturer_status_length = 4;
  bt00.number_pending_tables = 2;
  bt00.bt00_used = 1;
  // UT01
  ctUT01_t ut01;
  memset(&ut01, 0, sizeof ut01);
  ut01.id = 1;
  ut01.type = 1;
  ut01.delay_s = 60;
  ut01.num_entries = CT__UT01_NENT;
  // UT02
  ctUT02_t ut02;
  memset(&ut02, 0, sizeof ut02);

  if(ctWrite(CT__BT00, &bt00, sizeof bt00, 0) < sizeof bt00) return CT__FAILURE;
  if(ctWrite(CT__UT01, &ut01, sizeof ut01, 0) < sizeof ut01) return CT__FAILURE;
  if(ctWrite(CT__UT02, &ut02, sizeof ut02, 0) < sizeof ut02) return CT__FAILURE;

  ctStateHasChanged(CT__BT00);
  ctStateHasChanged(CT__UT01);
  ctStateHasChanged(CT__UT02);

  return CT__SUCCESS;
}

// TODO: launch events when restarting without clear...
int ctUnitStart(ctTarget_t* target, ctAddr_t* addr, int clear) {
  ctApdu_t apdu, res_apdu;
  ctAddr_t src;
  int n;
  if(ctManagerStart() != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to start the event manager\n");
    return CT__FAILURE;
  }
  if(clear && ctUnitCommissioning() != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Unit commissioning failed\n");
    return CT__FAILURE;
  }
  if(ctBind(addr) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to bind\n");
    return CT__FAILURE;
  }
  while(1) {
    n = ctRecv(apdu.apdu, sizeof apdu.apdu, &src, NULL);
    if(n < 1) continue;
    n = ctProcessRequest(&res_apdu, &apdu, target);
    if(n < 1) continue;
    if(ctSend(res_apdu.apdu, n, &src) != CT__SUCCESS)
      fprintf(stderr, "WARNING: Failed to send response\n");
  }
  return CT__SUCCESS;
}
