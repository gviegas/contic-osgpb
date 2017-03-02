//
// Created by Gustavo Viegas on 2017/02
//

#include <string.h>
#include "table_services.h"

ctApdu_t ctFullReadRequest(uint16_t table_id) {
  ctApdu_t d;
  d.apdu[0] = CT__TYPE_CODE;
  d.apdu[1] = CT__CMD_FULLREAD;
  d.apdu[2] = table_id >> 8;
  d.apdu[3] = table_id & 0x00ff;
  // doing
  return d;
}
 
ctApdu_t ctFullWriteRequest(uint16_t table_id, uint16_t count, uint8_t* data) {
  ctApdu_t d;
  d.apdu[0] = CT__TYPE_CODE;
  d.apdu[1] = CT__CMD_FULLWRITE;
  d.apdu[2] = table_id >> 8;
  d.apdu[3] = table_id & 0x00ff;
  d.apdu[4] = count >> 8;
  d.apdu[5] = count & 0x00ff;
  memcpy(d.apdu+6, data, count);
  // doing
  return d;
}

ctApdu_t ctPartialReadRequest(uint16_t table_id, uint8_t offset[3], 
  uint16_t count)
{
  ctApdu_t d;
  // doing
  return d;
}

ctApdu_t ctPartialWriteRequest(uint16_t table_id, uint8_t offset[3], 
  uint16_t count, uint8_t* data) 
{
  ctApdu_t d;
  // doing
  return d;
}

ctApdu_t ctReadResponse(uint8_t response, uint16_t count, uint8_t* data) {
  ctApdu_t d;
  // doing
  return d;
}

ctApdu_t ctWriteResponse(uint8_t response) {
  ctApdu_t d;
  // doing
  return d;
}