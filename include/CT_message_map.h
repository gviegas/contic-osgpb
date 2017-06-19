//
// Created by Gustavo Viegas on 2017/06
//

#ifndef CT_MESSAGE_MAP_H
#define CT_MESSAGE_MAP_H

#include "CT_net.h"
#include "CT_apdu.h"

#define CT__MAP_HINTLEN 1000

// Entry type
//
typedef struct {
  int key;
  ctAddr_t addr;
  ctApdu_t apdu;
} ctEntry_t;

// Map type (dynamic)
//
typedef struct {
  ctEntry_t** entries;
  int size;
  int total;
} ctMap_t;

// Create a message map
//
int ctMapCreate(ctMap_t* map);

// Get the map size
//
int ctMapSize(ctMap_t* map);

// Allocate space for a new entry
//
ctEntry_t* ctMapAdd(ctMap_t* map, int key);

// Get and remove the entry of specified key
//
ctEntry_t* ctMapGet(ctMap_t* map, int key);

// Get and remove one of the entries
//
ctEntry_t* ctMapPop(ctMap_t* map);

// Clear the map
//
int ctMapClear(ctMap_t* map);

#endif // CT_MESSAGE_MAP_H
