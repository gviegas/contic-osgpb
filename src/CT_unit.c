//
// Created by Gustavo Viegas on 2017/04
//

#include <string.h>
#include "CT_unit.h"
#include "CT_defs.h"
#include "CT_tables.h"
#include "CT_file.h"

int ctDefaultUnitCommission() {
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