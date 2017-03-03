//
// Created by Gustavo Viegas on 2017/02
//

#ifndef CT_DEFS_H
#define CT_DEFS_H

// EN14908-1 type code
#define CT__TYPE_CODE 0
// Request command codes
#define CT__CMD_FULLREAD  0x30
#define CT__CMD_PARTREAD  0x3F
#define CT__CMD_FULLWRITE 0x40
#define CT__CMD_PARTWRITE 0x4F
// Response codes
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
// Buffer size
#define CT__LEN_MAXAPDU   114
#define CT__LEN_PARTREAD  84
#define CT__LEN_PARTWRITE 75
#define CT__LEN_SEQN      4
#define CT__LEN_DIGEST    8
#define CT__LEN_OMAK      12

// OSGP target/device/slave info
typedef struct {
  uint8_t subnet;
  uint8_t node;
  uint8_t sequence[CT__LEN_SEQN];
  uint8_t s_omak[CT__LEN_OMAK];
} ctTarget_t;

#endif // CT_DEFS_H