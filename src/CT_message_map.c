//
// Created by Gustavo Viegas on 2017/06
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_definitions.h"
#include "CT_date.h"
#include "CT_message_map.h"

int ctMapCreate(ctMap_t* map) {
  if(!map) return CT__FAILURE;
  map->entries = (ctEntry_t**) calloc(CT__MAP_HINTLEN, sizeof(ctEntry_t*));
  if(!map->entries) return CT__FAILURE;
  map->size = map->iter = map->seen = 0;
  map->total = CT__MAP_HINTLEN;
  return CT__SUCCESS;
}

int ctMapSize(ctMap_t* map) {
  if(!map) return -1;
  return map->size;
}

ctEntry_t* ctMapAdd(ctMap_t* map, int key) {
  int i, n;
  size_t sz;
  ctEntry_t** aux;
  ctTimeSpec_t ts;
  if(ctMapFind(map, key)) return NULL; // NOTE: no duplicate key
  if(map->size == map->total) {
    n = 1 + map->total + map->total / 10;
    sz = sizeof(ctEntry_t*) * n;
    aux = (ctEntry_t**) realloc(map->entries, sz);
    if(!aux) return NULL;
    sz = sizeof(ctEntry_t*) * (1 + map->total / 10);
    memset(aux+(map->total * sizeof(ctEntry_t*)), 0, sz);
    map->entries = aux;
    map->total = n;
    i = map->size;
  } else {
    i = key % map->total;
    for(n = 0; n < map->total; i = (i+1) % map->total, ++n) {
      if(!map->entries[i]) break;
    }
  }
  map->entries[i] = (ctEntry_t*) malloc(sizeof(ctEntry_t));
  if(!map->entries[i]) return NULL;
  ++map->size;
  map->entries[i]->key = key;
  ctGetTimeSpec(&ts);
  map->entries[i]->timestamp = ts.sec;
  map->seen = 0; // reset iter
  return map->entries[i];
}

int ctMapDelete(ctMap_t* map, int key) {
  int n, c, i;
  if(!map) return CT__FAILURE;
  n = c = 0;
  i = key % map->total;
  for(; n < map->total && c < map->size; i = (i+1) % map->total, ++n) {
    if(map->entries[i]) {
      if(map->entries[i]->key == key) {
        free(map->entries[i]);
        map->entries[i] = NULL;
        --map->size;
        map->seen = 0; // reset iter
        return CT__SUCCESS;
      }
      ++c;
    }
  }
  return CT__FAILURE;
}

ctEntry_t* ctMapFind(ctMap_t* map, int key) {
  int n, c, i;
  if(!map) return NULL;
  n = c = 0;
  i = key % map->total;
  for(; n < map->total && c < map->size; i = (i+1) % map->total, ++n) {
    if(map->entries[i]) {
      if(map->entries[i]->key == key) return map->entries[i];
      ++c;
    }
  }
  return NULL;
}

ctEntry_t* ctMapAny(ctMap_t* map) {
  int i;
  if(!map || !map->size) return NULL;
  for(i = 0; i < map->total; ++i) {
    if(map->entries[i]) break;
  }
  return map->entries[i];
}

ctEntry_t* ctMapNext(ctMap_t* map) {
  int i;
  if(!map || !map->size) return NULL;
  if(map->seen == map->size) {
    map->seen = 0;
    return NULL;
  }
  i = map->iter;
  do {
    i = (i+1) % map->total;
    if(map->entries[i]) {
      map->iter = i;
      ++map->seen;
      break;
    }
  } while(map->seen != map->size);
  return map->entries[map->iter];
}

int ctMapOut(ctMap_t* map) {
  if(!map || !map->seen || !map->entries[map->iter])
    return CT__FAILURE;
  free(map->entries[map->iter]);
  map->entries[map->iter] = NULL;
  --map->size;
  return CT__SUCCESS;
}

void ctMapClear(ctMap_t* map) {
  int i;
  if(!map) return;
  for(i = 0; map->size; ++i) {
    if(map->entries[i]) {
      free(map->entries[i]);
      map->entries[i] = NULL;
      --map->size;
    }
  }
  map->seen = 0;
}

void ctMapDestroy(ctMap_t* map) {
  if(map) {
    ctMapClear(map);
    free(map->entries);
    map->entries = NULL;
    map->iter = map->total = 0;
  }
}
