/*
   itemDB.h: header file for database of items data structure 

   CS411 Lab 4
   Name: Kevin Sahr     
   Date: February 17, 2020
*/

#ifndef ITEM_DB_H
#define ITEM_DB_H

#include "item.h"

// forward typedef so that the Node
// definition can refer to itself
typedef struct node Node;

// node for a BST
struct node {
   // the data element
   Item* theItem; 

   // child and parent pointers
   Node* left;
   Node* right;
   Node* p; //parent
};
typedef struct {

   // the BST
   Node* root;

} ItemDB;

/*** end of Lab 4 changes ***/

/* API function prototypes */
int initializeItemDB(ItemDB* items, int maxItems);
void deleteItemDB(ItemDB* items);
void printItemDB(const ItemDB* items);
int insert(ItemDB* items, Item* theItem);
Item* find(const ItemDB* items, int id);
void delete(ItemDB* items, int id);

#endif
