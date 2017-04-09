//
// Cretaed by Gustavo Viegas on 2017/04
//

#include "CT_date.h"

void ctGetLTimeDate(ctLTimeDate_t* buffer) {
  time_t t = time(NULL);
  ctPosixToLTimeDate(buffer, &t);
}

void ctPosixToLTimeDate(ctLTimeDate_t* buffer, time_t* ptime) {
  struct tm* cal = gmtime(ptime);
  buffer->year = cal->tm_year % 100;
  buffer->month = cal->tm_mon + 1;
  buffer->day = cal->tm_mday;
  buffer->hour = cal->tm_hour;
  buffer->minute = cal->tm_min;
  buffer->second = cal->tm_sec;
}