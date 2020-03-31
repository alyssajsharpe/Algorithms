/*
   itemDB.h: header file for database of items data structure 

   CS411 Lab 1
   Name: Alyssa Sharpe
   Date: 1.22.2020

   THIS FILE SHOULD NOT CHANGE FOR LAB 1.
*/

#ifndef ITEM_DB_H
#define ITEM_DB_H

#include "item.h"

typedef struct
{
   int maxItems;   // the max number of items DB can hold 
   int numItems;   // the current number of items in the DB
   Item** theItems; 

} ItemDB;

/* API function prototypes */
int initializeItemDB(ItemDB* items, int maxItems);
void deleteItemDB(ItemDB* items);
void printItemDB(const ItemDB* items);
int insert(ItemDB* items, Item* theItem);
Item* find(const ItemDB* items, int id);
void delete(ItemDB* items, int id);

#endif
