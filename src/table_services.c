//
// Created by Gustavo Viegas on 2017/02
//

#include "table_services.h"

// TODO

ctApdu_t ctFullReadRequest(uint16_t table_id) {

}
 
ctApdu_t ctFullWriteRequest(uint16_t table_id, uint16_t count, uint8_t* data) {

}

ctApdu_t ctPartialReadRequest(uint16_t table_id, uint8_t offset[3], 
  uint16_t count)
{

}

ctApdu_t ctPartialWriteRequest(uint16_t table_id, uint8_t offset[3], 
  uint16_t count, uint8_t* data) 
{

}

ctApdu_t ctReadResponse(uint8_t response, uint16_t count, uint8_t* data) {

}

ctApdu_t ctWriteResponse(uint8_t response) {

}