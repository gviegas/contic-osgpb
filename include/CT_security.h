//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_SECURITY_H
#define CT_SECURITY_H

#include "CT_definitions.h"

// Protocol authentication
//
int ctAuthenticate(uint8_t* buffer, uint8_t* request, uint8_t* response,
  uint8_t req_count, uint8_t res_count, ctTarget_t* target);

// Protocol validation
//
int ctValidate(uint8_t* digest, uint8_t* request, uint8_t* response,
  uint8_t req_count, uint8_t res_count, ctTarget_t* target);

// TODO: Protocol encryption
//
// int ctEncrypt(uint8_t* buffer, ...);

// TODO: Protocol decryption
//
// int ctDecrypt(uint8_t* buffer, ...);

// Digest algorithm used for authentication
//
void ctDigest(uint8_t* buffer, uint8_t* data, uint8_t data_count,
  ctTarget_t* target);

#endif // CT_SECURITY_H
