//
// Created by Gustavo Viegas on 2017/04
//

#include <stdio.h>
#include <string.h>
#include "CT_tables.h"
#include "CT_file.h"
#include "CT_event_manager.h"
#include "CT_apdu.h"
#include "CT_unit.h"

int ctUnitDefaultCommission() {
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
  bt00.et00_used = 1;
  bt00.et01_used = 1;
  bt00.et00_write = 1;
  bt00.et01_write = 1;

  ctET00_t et00;
  memset(&et00, 0, sizeof et00);
  et00.measure_devices_used = 0b1000;
  ctTime_t minfo_time = {0, 0, 60};
  ctMeasureInfo_t minfo = {1, 0, minfo_time, 10};
  et00.measure_info[0] = minfo;

  ctET01_t et01;
  memset(&et01, 0, sizeof et01);

  ctWrite(CT__BT00, &bt00, sizeof bt00, 0);
  ctWrite(CT__ET00, &et00, sizeof et00, 0);
  ctWrite(CT__ET01, &et01, sizeof et01, 0);

  return CT__SUCCESS;
}

// to test
int ctUnitStart(ctTarget_t* target, ctAddr_t* addr) {
  ctApdu_t apdu, res_apdu;
  ctAddr_t src;
  int n;
  if(ctManagerStart() != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to start the event manager\n");
    return CT__FAILURE;
  }
  if(ctBind(addr) != CT__SUCCESS) {
    fprintf(stderr, "ERROR: Failed to bind\n");
    return CT__FAILURE;
  }
  while(1) {
    n = ctRecv(apdu.apdu, sizeof apdu.apdu, &src);
    if(n < 1) continue;

    // debug
    int i;
    printf("received:\n");
    for(i = 0; i < n; ++i) printf("%x ", apdu.apdu[i]);
    printf("from: node=%s service=%s\n", src.node, src.service);
    printf("end of message\n");
    //

    n = ctProcessRequest(&res_apdu, &apdu, target);
    if(n < 1) continue;
    if(ctSend(res_apdu.apdu, n, &src) != CT__SUCCESS) {
      fprintf(stderr, "ERROR: Failed to send response\n");
      return CT__FAILURE;
    }
  }
  return CT__SUCCESS;
}
