/*
   itemDB.c: functions for the DB of items

   CS411 Lab 3 
   Name: Alyssa Sharpe
   Date: 2.19.2020
*/ 
#include <stdio.h> 
#include <stdlib.h>
#include "itemDB.h"

//Initializing Item DB
int initializeItemDB(ItemDB* items, int maxItems) {
   items->head = NULL;
   return 0; 
}//end initializeItemDB

// Deletes entire database
void deleteNode(Node **nodeHandle){
   deleteItem(&((nodeHandle)->theItem));
   free(*nodeHandle);
   *nodeHandle = NULL;
}
void deleteItemDB(ItemDB* items) { 
 Node *n = items->head;
 Node *next = NULL;
 while(n){
    next = n->next;
    deleteNode(&n);
    n = next;
 }
 items->head = NULL;
 }
//Printing ItemDB
void printItemDB(const ItemDB* items) {
   const Node *x = items->head;
   while(x){
      printItem(x->theItem);
      x = x->next;
   }
}//end printItemDB

//Linked LIST-SEARCH - help function for find that searches for a specific node, returns node instead of item
Node *findNode(const ItemDB* items, int key){
   const Node *x = items->head;
   while(x &&(x->theItem->id < key))
      x = x->next;
   
   if(x && x->theItem->id == key){
      return (Node*) x;
   }
   else
      return NULL; 
} //end search

//Find 
Item* find(const ItemDB* items, int id) {
   const Node *x = findNode(items,id);
   if(x)
      return x->theItem;
   else
      return NULL;
}//end find

//LIST-INSERT
int insert(ItemDB* items, Item* theItem){
   Node *newNode = malloc(sizeof(Node*));
   if(!newNode){
      fprintf(stderr,"ERROR: unable to malloc memory for Node.\n");
      return 1;
   }

   newNode->theItem = theItem;
   newNode->prev = NULL;
   newNode->next = NULL;

   Node *x = items->head;
   Node *prev = NULL;
   while(x && (x->theItem->id < theItem->id)){
      prev = x;
      x = x->next;
   }

   if(x){
      if(x->theItem->id == theItem->id){
         fprintf(stderr,"ERROR: Item with this ID already exists.\n");
         free(newNode);
         newNode = NULL;
      }
      else{
         newNode->next = x;
         x->prev = newNode;
      }
   }
   if(!prev){
      items->head = newNode;
   }
   else{
      prev->next = newNode;
      newNode->prev = prev;
   }
   return 0;
}//end insert

//LIST-DELETE
void delete(ItemDB* items, int id) {
 Node *x = findNode(items,id);
 if(!x){
    fprintf(stderr,"ERROR: Item with ID does not exist.\n");
 }
 else{
   if(x->prev)
      x->prev->next = x->next;
   else
      items->head = x->next;

   if(x->next)
      x->next->prev = x->prev

   deleteNode(&x);
 }
}//end delete 