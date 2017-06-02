//
// Created by Gustavo Viegas on 2017/06
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CT_defs.h"
#include "CT_name_list.h"

int ctListCreate(ctList_t* list) {
  if(!list) return CT__FAILURE;
  list->head = list->tail = NULL;
  list->size = 0;
  return CT__SUCCESS;
}

int ctListSize(ctList_t* list) {
  if(!list) return -1; // failure...
  return list->size;
}

int ctListInsert(ctList_t* list, char* name, ctAddr_t* addr) {
  if(!list || !name || strlen(name) >= CT__LIST_NAMELEN) return CT__FAILURE;
  ctNode_t* node = malloc(sizeof(ctNode_t));
  if(!node) return CT__FAILURE;
  strcpy(node->name, name);
  memcpy(&node->addr, addr, sizeof(ctAddr_t));
  if(!list->head)
    list->head = list->tail = node;
  else {
    node->next = list->head;
    list->head = node;
  }
  ++list->size;
  return CT__SUCCESS;
}

int ctListRemove(ctList_t* list, char* name) {
  if(!list || !name || !list->size) return CT__FAILURE;
  ctNode_t *node, *prev;
  if(!strcmp(list->head->name, name)) {
    node = list->head;
    if(list->size == 1) list->head = list->tail = NULL;
    else list->head = list->head->next;
    free(node);
    --list->size;
  } else {
    prev = node = list->head;
    while(node->next) {
      node = node->next;
      if(!strcmp(node->name, name)) {
        prev->next = node->next;
        if(node == list->tail) list->tail = prev;
        free(node);
        --list->size;
        break;
      }
      prev = node;
    }
    if(prev == node) return CT__FAILURE;
  }
  return CT__SUCCESS;
}

ctNode_t* ctListFind(ctList_t* list, char* name) {
  if(!list || !name || !list->size) return NULL;
  ctNode_t* node = list->head;
  while(node) {
    if(!strcmp(node->name, name)) return node;
    node = node->next;
  }
  return NULL;
}

void ctListClear(ctList_t* list) {
  if(list && list->size) {
    ctNode_t *node, *prev;
    node = prev = list->head;
    while(node) {
      node = node->next;
      free(prev);
      prev = node;
    }
  }
}
