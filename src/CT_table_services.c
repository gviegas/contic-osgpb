//
// Created by Gustavo Viegas on 2017/02
//

#include <string.h>
#include "CT_table_services.h"

int ctFullReadRequest(uint8_t* buffer, uint16_t table_id) {
  buffer[0] = CT__MSG_FULLREAD;
  buffer[1] = table_id >> 8;
  buffer[2] = table_id & 0x00ff;
  return 3;
}
 
int ctFullWriteRequest(uint8_t* buffer, uint16_t table_id, uint16_t count, 
  uint8_t* data)
{
  buffer[0] = CT__MSG_FULLWRITE;
  buffer[1] = table_id >> 8;
  buffer[2] = table_id & 0x00ff;
  buffer[3] = count >> 8;
  buffer[4] = count & 0x00ff;
  memcpy(buffer+5, data, count);
  return 5 + count;
}

int ctPartialReadRequest(uint8_t* buffer, uint16_t table_id, uint8_t offset[3], 
  uint16_t count)
{
  buffer[0] = CT__MSG_PARTREAD;
  buffer[1] = table_id >> 8;
  buffer[2] = table_id & 0x00ff;
  memcpy(buffer+3, offset, 3);
  buffer[6] = count >> 8;
  buffer[7] = count & 0x00ff;
  return 8;
}

int ctPartialWriteRequest(uint8_t* buffer, uint16_t table_id, 
  uint8_t offset[3], uint16_t count, uint8_t* data) 
{
  buffer[0] = CT__MSG_PARTWRITE;
  buffer[1] = table_id >> 8;
  buffer[2] = table_id & 0x00ff;
  memcpy(buffer+3, offset, 3);
  buffer[6] = count >> 8;
  buffer[7] = count & 0x00ff;
  memcpy(buffer+8, data, count);
  return 8 + count;
}

int ctReadResponse(uint8_t* buffer, uint8_t response, uint16_t count, 
  uint8_t* data)
{
  buffer[0] = response;
  buffer[1] = count >> 8;
  buffer[2] = count & 0x00ff;
  memcpy(buffer+3, data, count);
  return 3 + count;
}

int ctWriteResponse(uint8_t* buffer, uint8_t response) {
  buffer[0] = response;
  return 1;
}