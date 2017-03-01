//
// Created by Gustavo Viegas on 2017/02
//

#include <stdint.h>
#include "defs.h"

// Application Protocol Data Unit (APDU)
// The apdu field represents a table service packet
// [NOTE: this avoids dynamic memory allocation]
typedef struct {
  uint8_t status;
  uint8_t apdu[CT__LEN_MAX];
} ctApdu_t;

// Creates the APDU for an OSGP Full Table Read Request 
//
// Format: <command><tableId>
//
ctApdu_t ctFullReadRequest(uint16_t table_id);

// Creates the APDU for an OSGP Full Table Write Request
//
// Format: <command><tableId><count><data>
// 
ctApdu_t ctFullWriteRequest(uint16_t table_id, uint16_t count, uint8_t* data);

// Creates the APDU for an OSGP Partial Table Read Request
//
// Format: <command><tableId><offset><count>
//
ctApdu_t ctPartialReadRequest(uint16_t table_id, uint8_t offset[3], 
  uint16_t count);

// Creates the APDU for an OSGP Partial Table Write Request
//
// Format: <command><tableId><offset><count><data>
//
ctApdu_t ctPartialWriteRequest(uint16_t table_id, uint8_t offset[3], 
  uint16_t count, uint8_t* data);

// Creates the APDU for an OSGP Full/Partial Table Read Response
//
// Format: <response><count><data>
//
ctApdu_t ctReadResponse(uint8_t response, uint16_t count, uint8_t* data);

// Creates the APDU for an OSGP Full/Partial Table Write Response
//
// Format: <response>
//
ctApdu_t ctWriteResponse(uint8_t response);