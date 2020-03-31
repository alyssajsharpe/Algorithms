/*
   item.h: header file for Item's

   CS411 Lab 2 
   Name: Alyssa Sharpe
   Date: 2.5.2020

*/

#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM_ID     999999999
#define INVALID_ITEM_ID -1

#define MAX_ITEM_NAME_LEN 30

typedef struct {
   int id;
   char* name; // must be dynamically allocated
   float price;
} Item;

/* API function prototypes */
Item* createItem(int id, const char* name, float price);
void printItem(const Item* item);
void deleteItem(Item** item);

#endif 
