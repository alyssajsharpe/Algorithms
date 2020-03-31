/*
   itemDB.c: functions for the DB of items

   CS411 Lab 1 
   Name: Alyssa Sharpe
   Date: 1.22.2020
*/ 
#include <stdio.h> 
#include <stdlib.h>
#include "itemDB.h"

// This function initializes a new ItemDB so that it can 
// hold up to maxItems Items. The function assumes that 
// the ItemDB has never been used, or that deleteItemDB
// has been called on it.
//
// The function allocates the database array and sets 
// all slots to NULL.
//
// Return 0 on success, and 1 on failure.
//
int initializeItemDB(ItemDB* items, int maxItems) {
   int i;
   items->maxItems = maxItems;
   items->numItems = 0;
   items->theItems = malloc(maxItems*sizeof(Item));
   for(i=0; i < maxItems; i++){
      items->theItems[i] = NULL; 
   }
      for(i=0; i < maxItems; i++){
         if(items->theItems[i] != NULL){
            fprintf(stderr, "ERROR: array was not completed allocated to NULL.\n"); 
            return 1;
         }   
      }
   return 0;
}//end initializeItemDB

// Deallocate all memory associated with the ItemDB,
//    including all memory associated with the Items 
//    contained within it.
void deleteItemDB(ItemDB* items) {  //deletes entire database
   int i;
   for(i=0; i<items->maxItems; i++){
      free(items->theItems[i]);
      items->theItems[i] = NULL;  
   }
}

// output all items in the DB to stdout, one-per-line
// each item should be output using the function printItem
void printItemDB(const ItemDB* items) {
   int i;
   for(i=0; i<items->numItems; i++){
      if(items->theItems[i]){
         printItem(items->theItems[i]);
      }
   }
}//end printItemDB

void helpMe (ItemDB *items, Item* theItem, int i, int tempID){
   int x; 
   for(x = items->numItems-1; x >= i && items->theItems[x]->id > tempID; x--){
       items->theItems[x+1] = items-> theItems[x];
   }
      items -> theItems[x+1] = theItem;
      items -> numItems++;
}

// Insert theItem into the ItemDB.
// Return 0 if successful, 1 if unsuccessful.
//
// Remember that the ItemDB should be ordered by Item ID
//   and that duplicates are not allowed.
//
int insert(ItemDB* items, Item* theItem) {
      int tempID = theItem -> id;
      int i = 0;
      //checking to make sure there is space
      if(items->numItems < items->maxItems){ 
         while(i < items->numItems){
            //checking for duplicates 
            if(items->theItems[i] -> id == tempID){ 
               fprintf(stderr, "ERROR: Duplicates are not allowed.\n");
               return 1; 
            }
            //checking if i is the first in the array
            if(i==0){  
               if(tempID < items->theItems[i] -> id){
                  helpMe(items, theItem, i, tempID);
                  return 0;
               }
            }
            //checking to if i+1 != null
            if(items->theItems[i+1] != NULL){ 
               if(items->theItems[i]->id < tempID && tempID < items->theItems[i+1]->id){
                  helpMe(items, theItem, i, tempID);
                  return 0;
               }
            }
         i++;           
         }//end while
      }
      items -> theItems[i] = theItem;
      items -> numItems++;
      return 0;
}//end insert

// Find and return the current array index of the Item with the 
//    specified id in items.
//
// Return -1 if not found.
int findIndex(const ItemDB* items, int id) {
   int lower, upper, mid, m;
   lower = 0;                  //first element
   upper = items->numItems-1;  //last element 

   while(lower <= upper){
   m = (lower + upper)/2;
   mid = items->theItems[m] -> id;
      if(mid == id){
         return m; 
      } 
      if(id > mid){ //id lies to the left of mid
         lower = m+1;  
      }
      else{         //id lies to the right of mid
          upper = m-1; 
      }
   }//end while loop
   return -1;
}//end findIndex

// Find and return the Item with the specified id in items.
// Return a pointer to the Item, or NULL if the Item is not found.
//
// Your function must use binary search to find the item. 

Item* find(const ItemDB* items, int id) {
   int temp;
   temp = findIndex(items, id); //creating a variable to hold the returned int from findIndex
   if(temp >= 0){
      return items-> theItems[temp];
   }
   else{             
      return NULL; 
   }
}//end find

// Remove the Item with the specified id from the ItemDB and 
//    deallocate the memory associated with the Item.
// If an Item with the specified id does not exist, do nothing.
void delete(ItemDB* items, int id) {
   int temp = findIndex(items, id);
   if(temp >= 0){
      deleteItem(&items->theItems[temp]);
      int count = temp; 
      if(count == items->numItems-1){
         items->theItems[count] = NULL; 
         items->numItems--;
      }
      else{
         while(items->theItems[count+1] != NULL){
           items->theItems[count] = items->theItems[count+1]; //count starts @ deleted item, replaces that element with the one above it(+1)
            count++;  
         } //end while
         items->theItems[count] = NULL; 
         items->numItems--;
      }  
   }
}//end delete 