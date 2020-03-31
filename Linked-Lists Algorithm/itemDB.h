/*
   itemDB.h: header file for database of items data structure 

   CS411 Lab 3
   Name: Kevin Sahr     
   Date: February 4, 2020
*/

#ifndef ITEM_DB_H
#define ITEM_DB_H

#include "item.h"

/*** this part is new for Lab 3 ***/

// forward typedef so that the Node
// definition can refer to itself
typedef struct node Node;

// single node for a doubly linked list
struct node {
   // the data element
   Item* theItem; 
   
   // pointers to next and previous Nodes
   Node* prev;
   Node* next;
};

typedef struct {

   // the linked list
   Node* head;

} ItemDB;

/*** end of Lab 3 changes ***/

/* API function prototypes */
int initializeItemDB(ItemDB* items, int maxItems);
void deleteItemDB(ItemDB* items);
void printItemDB(const ItemDB* items);
int insert(ItemDB* items, Item* theItem);
Item* find(const ItemDB* items, int id);
void delete(ItemDB* items, int id);

#endif
