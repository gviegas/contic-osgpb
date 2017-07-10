//
// Created by Gustavo Viegas on 2017/02
//

#ifndef CT_DEFINITIONS_H
#define CT_DEFINITIONS_H

#include <stdint.h>

// General definitions
//
#define CT__SUCCESS 0
#define CT__FAILURE 1

// Str definitions
#define CT__DELIM " \n\t" // \v\r\f...
#define CT__ENDL "\n"

// Message type code
//
#define CT__TYPE_CODE 0

// Request messages codes
//
#define CT__MSG_FULLREAD  0x30
#define CT__MSG_PARTREAD  0x3F
#define CT__MSG_FULLWRITE 0x40
#define CT__MSG_PARTWRITE 0x4F

// Response codes
//
#define CT__RES_OK  0
#define CT__RES_ERR 0x01

// Protocol buffer sizes
//
#define CT__LEN_APDU      114
#define CT__LEN_PARTREAD  84
#define CT__LEN_PARTWRITE 75
#define CT__LEN_SEQN      4
#define CT__LEN_DIGEST    8
#define CT__LEN_KEY       12

// Basic table IDs
//
#define CT__BT00 0
#define CT__BT05 5
#define CT__BT06 6
#define CT__BT52 52
#define CT__BT55 55

// Unified table IDs
//
#define CT__UTOFFSET 16384
#define CT__UT00 CT__UTOFFSET
#define CT__UT01 CT__UTOFFSET + 1
#define CT__UT02 CT__UTOFFSET + 2

// Table types
//
#define CT__TTYPE_RDONLY 0
#define CT__TTYPE_WRONLY 1
#define CT__TTYPE_RDWR   2
#define CT__TTYPE_EVENT  3

// Target/Device/Slave info
//
typedef struct {
  uint8_t subnet;
  uint8_t node;
  uint8_t sequence[CT__LEN_SEQN];
  uint8_t key[CT__LEN_KEY];
} ctTarget_t;

#endif // CT_DEFINITIONS_H
