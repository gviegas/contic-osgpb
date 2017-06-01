//
// Created by Gustavo Viegas on 2017/02
//

#ifndef CT_DEFS_H
#define CT_DEFS_H

#include <stdint.h>

// General definitions
//
#define CT__SUCCESS 0
#define CT__FAILURE 1

// Str definitions
#define CT__DELIM " "
#define CT__ENDL "\n" // '\n'
#define CT__NAMELEN 16

// EN14908-1 type code
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
#define CT__RES_SNS 0x02
#define CT__RES_ISC 0x03
#define CT__RES_ONP 0x04
#define CT__RES_IAR 0x05
#define CT__RES_BSY 0x06
#define CT__RES_ISS 0x0A
#define CT__RES_DIG 0x0B
#define CT__RES_SEQ 0x0C
#define CT__RES_INC 0x1E
#define CT__RES_ICA 0x1F

// Protocol buffer sizes
//
#define CT__LEN_APDU   114
#define CT__LEN_PARTREAD  84
#define CT__LEN_PARTWRITE 75
#define CT__LEN_SEQN      4
#define CT__LEN_DIGEST    8
#define CT__LEN_OMAK      12

// Basic table IDs
//
#define CT__BT00 0
#define CT__BT05 5
#define CT__BT06 6
#define CT__BT07 7
#define CT__BT08 8
#define CT__BT10 10
#define CT__BT16 16
#define CT__BT21 21
#define CT__BT22 22
#define CT__BT23 23
#define CT__BT26 26
#define CT__BT50 50
#define CT__BT52 52
#define CT__BT54 54
#define CT__BT55 55
#define CT__BT60 60
#define CT__BT61 61
#define CT__BT62 62
#define CT__BT63 63
#define CT__BT64 64

// Extended table IDs
//
#define CT__ETOFFSET 2048
#define CT__ET04 CT__ETOFFSET + 4
#define CT__ET11 CT__ETOFFSET + 11
#define CT__ET12 CT__ETOFFSET + 12
#define CT__ET21 CT__ETOFFSET + 21
#define CT__ET42 CT__ETOFFSET + 42

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
  uint8_t key[CT__LEN_OMAK];
} ctTarget_t;

#endif // CT_DEFS_H
