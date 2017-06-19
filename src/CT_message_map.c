//
// Created by Gustavo Viegas on 2017/06
//

#include <stdlib.h>
#include <stdio.h>
#include "CT_definitions.h"
#include "CT_message_map.h"

int ctMapCreate(ctMap_t* map) {
  if(!map) return CT__FAILURE;
  map->entries = (ctEntry_t**) calloc(CT__MAP_HINTLEN, sizeof(ctEntry_t*));
  if(!map->entries) return CT__FAILURE;
  map->size = 0;
  map->total = CT__MAP_HINTLEN;
  return CT__SUCCESS;
}

int ctMapSize(ctMap_t* map) {
  if(!map) return CT__FAILURE;
  return map->size;
}

ctEntry_t* ctMapAdd(ctMap_t* map, int key) {
  int i, n;
  size_t sz;
  ctEntry_t** aux;
  if(!map) return NULL;
  if(map->size == map->total) {
    n = 1 + map->total + (map->total / 10);
    sz = sizeof(ctEntry_t*) * n;
    aux = (ctEntry_t**) realloc(map->entries, sz);
    if(!aux) return NULL;
    map->entries = aux;
    map->total = n;
    i = map->size;
  } else {
    for(i = key, n = 0; n < map->total; i = (i+1) % map->total, ++n) {
      if(!map->entries[i]) break;
    }
  }
  map->entries[i] = (ctEntry_t*) malloc(sizeof(ctEntry_t));
  if(!map->entries[i]) return NULL;
  ++map->size;
  map->entries[i]->key = key;
  return map->entries[i];
}

ctEntry_t* ctMapGet(ctMap_t* map, int key) {
  if(!map) return NULL;
}

ctEntry_t* ctMapPop(ctMap_t* map) {
  if(!map) return NULL;
}

int ctMapClear(ctMap_t* map) {
  int i;
  if(map && map->size) {
    for(i = 0; map->size; ++i) {
      if(map->entries[i]) {
        free(map->entries[i]);
        --map->size;
      }
    }
  }
  free(map->entries);
  map->total = 0;
  return CT__SUCCESS;
}
