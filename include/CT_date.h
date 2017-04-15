//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_DATE_C
#define CT_DATE_C

#include <stdint.h>
#include <time.h>

// Date type
//
typedef struct {} ctDate_t; // to do

// Time type
//
typedef struct {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} ctTime_t;

// LTime_Date type
//
typedef struct {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;  
} ctLTimeDate_t;

// STime_Date type
//
typedef struct {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
} ctSTimeDate_t;

// RTime_Date type
//
typedef struct {} ctRDate_t; // to do

// Get Current LTimeDate
//
void ctGetLTimeDate(ctLTimeDate_t* buffer);

// POSIX time to ctLTimeDate
//
void ctPosixToLTimeDate(ctLTimeDate_t* buffer, time_t* ptime);

#endif // CT_DATE_C