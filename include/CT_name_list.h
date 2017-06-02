//
// Created by Gustavo Viegas on 2017/06
//

#ifndef CT_NAME_LIST_H
#define CT_NAME_LIST_H

#include "CT_net.h"

// Node type
//
typedef struct _ctNode_t {
  char name[CT__NAMELEN];
  ctAddr_t addr;
  struct _ctNode_t* next;
} ctNode_t;

// List type (dynamic)
//
typedef struct {
  ctNode_t* head;
  ctNode_t* tail;
  int size;
} ctList_t;

// Create a new list
//
int ctListCreate(ctList_t* list);

// Get list size
//
int ctListSize(ctList_t* list);

// Insert a new node
//
int ctListInsert(ctList_t* list, char* name, ctAddr_t* addr);

// Remove a node
//
int ctListRemove(ctList_t* list, char* name);

// Find a node
//
ctNode_t* ctListFind(ctList_t* list, char* name);

// Clear the list
//
void ctListClear(ctList_t* list);

#endif // CT_NAME_LIST_H
