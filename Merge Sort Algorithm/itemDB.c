/*
   itemDB.c: functions for the DB of items

   CS411 Lab 2 
   Name: Alyssa Sharpe
   Date: 2.5.2020
*/ 
#include <stdio.h> 
#include <stdlib.h>
#include "itemDB.h"

int initializeItemDB(ItemDB* items, int maxItems) {
   int i;
   items->maxItems = maxItems;
   items->numItems = 0;
   items->theItems = malloc(maxItems*sizeof(Item*)); 
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

void deleteItemDB(ItemDB* items) {  //deletes entire database
   int i;
   for(i=0; i<items->maxItems; i++){
      free(items->theItems[i]);
      items->theItems[i] = NULL;  
   }
   items->numItems = 0;
   items->maxItems = 0;
}

void merge(Item** arr, int p, int q, int r){  
   int i,j,k;
   int n1= (q-p)+1;   //# of elements in L
   int n2= r-q;     //# of elements in R 

   Item** L = malloc((n1+1)*sizeof(Item*));  //creating left sub array  
   Item** R = malloc((n2+1)*sizeof(Item*));  //creating right sub array     
   
   //Creating a for loop to iterate through the left side of array
   for(i=0; i<n1; i++){
      L[i] = arr[p+i];  
   }
   //Creating a for loop to iterate through the right side of array
   for(j=0; j<n2; j++){
      R[j] = arr[q+j+1];  
   }
   //creating a limit for L and R
   L[n1] = createItem(MAX_ITEM_ID, "Left limit", 0);  
   R[n2] = createItem(MAX_ITEM_ID, "Right limit", 0);
   i=0;                       
   j=0;
   //merging together L and R subarrays 
   for(k=p; k<=r; k++){  
      if(L[i]->id <= R[j]->id){ 
         arr[k] = L[i];
         i = i+1;
      }
      else{
         arr[k] = R[j];
         j=j+1;
      }
   }
   //freeing memory of subarrays 
   free(L);
   L=NULL;
   free(R);
   R=NULL;
}//end merge

void mergeSort(Item** arr, int p, int r){ 
   //q = mid, r = last index, p = first index   
   if(p<r){
      int q = ((p+r)/2);
      mergeSort(arr,p,q);
      mergeSort(arr,q+1,r);
      merge(arr, p,q,r);
   }
}//end mergeSort

void printItemDB(const ItemDB* items) {
   int i;
   //Creating array to hold a copy of ItemDB items
   Item** arr = malloc(items->numItems* sizeof(Item*));
   //Filling copy array with the items in the ItemDB
   for(i=0; i<items->numItems; i++){
      arr[i] = items->theItems[i];
   }
   //Calling merge sort to sort the unsorted array
   mergeSort(arr, 0, items->numItems-1);
   
   //Printing out the items in the copy array
   for(i=0; i<items->numItems; i++){
         printItem(arr[i]);
   }
   //Freeing dynamically allocated memory
   free (arr);
   arr=NULL; 
}//end printItemDB

int insert(ItemDB* items, Item* theItem) {
   //Checking if numItems is at capacity
      if(items->numItems == items->maxItems){
         fprintf(stderr, "ERROR: unable to insert new item since the list is full.");
         return 1; 
      }
   //Adding the new item to the end of the array
      items->theItems[items->numItems] = theItem; 
      items->numItems++;
      return 0;
}//end insert

int findIndex(const ItemDB* items, int id) {
   int i;
   //Implementing linear search to find index
   for(i = 0; i < items->numItems; i++){
      if(items->theItems[i] -> id == id){
         return i;
      }
   }
   return -1;
}//end findIndex

Item* find(const ItemDB* items, int id) {
   //creating a variable to hold the returned int from findIndex
   int temp = findIndex(items, id); 
   if(temp >= 0){
      return items-> theItems[temp];
   }
   else{             
      return NULL; 
   }
}//end find

void delete(ItemDB* items, int id) {
   int temp = findIndex(items, id);
   if(temp == -1){
      fprintf(stderr,"ERROR: Item does not exist\n");
   }
   else{
      int i;
      //Finding match in id to then delete specified item
         for(i = 0; i < items->numItems; i++){
            if(items->theItems[i] -> id == temp)
               deleteItem(&(items->theItems[temp]));
      }
      //shifting over the empty space
      for(i=temp; i<items->numItems-1; i++)
         items->theItems[i] = items->theItems[i+1];

      items->theItems[items->numItems-1] = NULL;
      items->numItems--;
   }
}//end delete 