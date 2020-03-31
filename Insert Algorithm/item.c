/*
   item.c: Item function implementations

   CS411 Lab 1
   Name: Alyssa Sharpe
   Date: 1/22/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strlen
#include "item.h"

// This function allocates and returns an Item with the 
// indicated field values.
//
// Return NULL if unsuccessful.
//
// The Item name field must be dynamically allocated to hold
//   a name of up to MAX_ITEM_NAME_LEN characters, and 
//   the passed-in name argument should be copied into it.
//
// The Item ID should be less than or equal to MAX_ITEM_ID.
//
Item* createItem(int id, const char* name, float price) {
   Item* temp = malloc(sizeof(Item));
   if(temp == NULL){
      fprintf(stderr, "ERROR: input for Item is NULL.\n");
      return NULL;
   }
   else{
      //checking id input
      if(id <= MAX_ITEM_ID){
         temp->id = id; 
      }
      else{
         fprintf(stderr, "ERROR: ID:%d for Item is too large.\n", id);
         return NULL;
      }
      //checkin name input
      if(strlen(name) < MAX_ITEM_NAME_LEN && strlen(name) > 0){
         temp->name = malloc(strlen(name)*sizeof(char));
         strcpy(temp->name, name);
      }
      else{
         fprintf(stderr, "ERROR: Name:%s for Item is too large.\n", name);
         return NULL;
      }
   }//end if-else
   temp->price = price;
   return temp;
} //end createItem

// output the item to stdout on a single line
// THIS FUNCTION SHOULD NOT BE CHANGED
void printItem(const Item* item) {
   printf("ID: %d NAME: %s PRICE: $%.2f\n", 
   item->id, item->name, item->price);
}

// This function deallocates all dynamically allocated 
//    memory associated with the Item indicated by the 
//    handle argument and sets the Item pointer to NULL.
void deleteItem(Item** item) {
   free(*item);  //freeing item
   item = NULL; //setting item to NULL 
}