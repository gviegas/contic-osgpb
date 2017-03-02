//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_SECURITY_H
#define CT_SECURITY_H

#include <stdint.h>
#include "CT_defs.h"

// OSGP authentication for request/response
//
int ctAuthenticate(uint8_t* buffer, uint8_t* request, uint8_t* response, 
  size_t req_count, size_t res_count, ctTarget_t* target);

// OSGP authentication for request
//
int ctAuthenticate_req(uint8_t* buffer, uint8_t* request, size_t req_count,
  ctTarget_t* target);

#endif // CT_SECURITY_H