//
// Created by Gustavo Viegas on 2017/02
//

#ifndef CT_TABLE_SERVICES_H
#define CT_TABLE_SERVICES_H

#include "CT_defs.h"

// Creates the APDU for an OSGP Full Table Read Request 
//
// Format: <command><tableId>
//
int ctFullReadRequest(uint8_t* buffer, uint16_t table_id);

// Creates the APDU for an OSGP Full Table Write Request
//
// Format: <command><tableId><count><data>
// 
int ctFullWriteRequest(uint8_t* buffer, 
  uint16_t table_id, uint16_t count, uint8_t* data);

// Creates the APDU for an OSGP Partial Table Read Request
//
// Format: <command><tableId><offset><count>
//
int ctPartialReadRequest(uint8_t* buffer, 
  uint16_t table_id, uint8_t offset[3], uint16_t count);

// Creates the APDU for an OSGP Partial Table Write Request
//
// Format: <command><tableId><offset><count><data>
//
int ctPartialWriteRequest(uint8_t* buffer, 
  uint16_t table_id, uint8_t offset[3], uint16_t count, uint8_t* data);

// Creates the APDU for an OSGP Full/Partial Table Read Response
//
// Format: <response><count><data>
//
int ctReadResponse(uint8_t* buffer, uint8_t response, uint16_t count, 
  uint8_t* data);

// Creates the APDU for an OSGP Full/Partial Table Write Response
//
// Format: <response>
//
int ctWriteResponse(uint8_t* buffer, uint8_t response);

#endif // CT_TABLE_SERVICES_H