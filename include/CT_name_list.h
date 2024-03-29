//
// Created by Gustavo Viegas on 2017/06
//

#ifndef CT_NAME_LIST_H
#define CT_NAME_LIST_H

#include "CT_net.h"

#define CT__LIST_NAMELEN 16

// Node type
//
typedef struct _ctNode_t {
  char name[CT__LIST_NAMELEN];
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

// Get the list size
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

// Get the first node
//
ctNode_t* ctListFirst(ctList_t* list);

// Get the next node
//
ctNode_t* ctListNext(ctList_t* list, ctNode_t* node);

// Clear the list
//
void ctListClear(ctList_t* list);

#endif // CT_NAME_LIST_H
