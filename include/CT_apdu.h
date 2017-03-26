//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_APDU_H
#define CT_APDU_H

#include "CT_defs.h"

// Available services
//
enum ctService_e {
  REQUEST_FULL_READ,
  REQUEST_PART_READ,
  REQUEST_FULL_WRITE,
  REQUEST_PART_WRITE,
  RESPONSE_FULL_READ,
  RESPONSE_PART_READ,
  RESPONSE_FULL_WRITE,
  RESPONSE_PART_WRITE
};

// Full Table Read Request parameters
//
typedef struct {
  uint16_t table_id;
} ctFRRequest_t;

// Partial Table Read Request parameters
//
typedef struct {
  uint16_t table_id;
  uint8_t offset[3];
  uint16_t count;
} ctPRRequest_t;

// Full Table Write Request parameters
//
typedef struct {
  uint16_t table_id;
  uint16_t count;
  uint8_t data[CT__LEN_MAXAPDU];
} ctFWRequest_t;

// Partial Table Write Request parameters
//
typedef struct {
  uint16_t table_id;
  uint8_t offset[3];
  uint16_t count;
  uint8_t data[CT__LEN_MAXAPDU];
} ctPWRequest_t;

// Table Read Response parameters
//
typedef struct {
  uint8_t response;
  uint16_t count;
  uint8_t data[CT__LEN_MAXAPDU];
  uint8_t* request;
  uint8_t req_count;
} ctRResponse_t;

// Table Write Response parameters
//
typedef struct {
  uint8_t response;
  uint8_t* request;
  uint8_t req_count;
} ctWResponse_t;

// Creation parameters
//
typedef struct {
  int service;
  union {
    ctFRRequest_t* fr_request;
    ctPRRequest_t* pr_request;
    ctFWRequest_t* fw_request;
    ctPWRequest_t* pw_request;
    ctRResponse_t* r_response;
    ctWResponse_t* w_response;
  };
} ctParam_t;

// Application Protocol Data Unit
//
typedef struct {
  uint8_t apdu[CT__LEN_MAXAPDU];
} ctApdu_t;

// Processed Response
//
typedef struct {
  int service;
  uint8_t response;
  uint16_t read_count;
  uint8_t read_data[CT__LEN_MAXAPDU - CT__LEN_DIGEST - 4];
} ctResponse_t;

// Creates a new APDU
//
int ctCreateApdu(ctApdu_t* apdu, ctParam_t* param, ctTarget_t* target);

// Process an APDU Request
//
int ctProcessRequest(ctApdu_t* res_apdu, ctApdu_t* apdu, ctTarget_t* target);

// Process an APDU Response
//
int ctProcessResponse(ctResponse_t* buffer, ctApdu_t* apdu, ctApdu_t* req_apdu,
  ctTarget_t* target);

#endif // CT_APDU_H