/*
   itemDB.c: functions for the DB of items

   CS411 Lab 4 
   Name: Alyssa Sharpe
   Date: 3.4.2020
*/ 
#include <stdio.h> 
#include <stdlib.h>
#include "itemDB.h"

//Initializing Item DB
int initializeItemDB(ItemDB* items, int maxItems) {
   items->root = NULL;
   return 0; 
}//end initializeItemDB

void deleteNode(Node **nodeHandle){
   deleteItem(&((*nodeHandle)->theItem));
   *nodeHandle = NULL;
}

//Post Order traversal
void deleteTree(ItemDB* items, Node* n){
   if(n){;
   //Traversing through tree and deleting/freeing nodes
      deleteTree(items, n->left);
      deleteTree(items, n->right);
      deleteNode(&n);
      free(n);
   }
}

// Deletes entire database
void deleteItemDB(ItemDB* items) { 
   Node *n = items->root;
   deleteTree(items,n);
   items->root = NULL;
}//end deleteItemDB

//INORDER-TREE-WALK - walks through the tree from the min values to the max values and prints them
void inOrderTreeWalk(Node *x){
   if(x){
      inOrderTreeWalk(x->left);
      printItem(x->theItem);
      inOrderTreeWalk(x->right);
   }
}// end inOrderTreeWalk

//Printing ItemDB
void printItemDB(const ItemDB* items) {
   Node *x = items->root;
   inOrderTreeWalk(x);
}//end printItemDB

Node* iterativeSearch(const ItemDB* items, int k){
   Node *x = items->root;
   while(x && k != x->theItem->id){
      if (k < x->theItem->id){
         x = x->left;
      }
      else{
         x = x->right;
      }
   }
   return x; 
}//end iterative search

//Find 
Item* find(const ItemDB* items, int id) {
   Node *x = iterativeSearch(items,id);
   if(x)
      return x->theItem;
   else
      return NULL;
}//end find

//BINARY TREE-INSERT - Inserts new node into binary tree
int insert(ItemDB* items, Item* theItem){
   Node *z = malloc(sizeof(Node));
   if(!z){  //Checking if node is null
      fprintf(stderr,"ERROR: Node was not correctly malloc'd... exiting.\n");
      return 1;
   }
   z->theItem = theItem;
   Node *y = NULL;
   Node *x = items->root; 
   while(x){
      y = x; //checking for dups
      if(theItem->id < x->theItem->id)
         x = x->left;   
      else if(theItem->id == x->theItem->id){
         fprintf(stderr, "ERROR: No duplicates are allowed.\n");
         return 1;
      }
      else
         x = x->right;
   }//end of while loop
      z->p = y;
      if(!y){
         items->root = z;
      }
      else if(z->theItem->id < y->theItem->id){
         y->left = z;
      }
      else
         y->right = z;
   return 0;
}//end insert

// TREE-MINUMUM - returns the left most node of a binary tree
Node *treeMin(Node *m){
   Node *min = m;
   while(min->left){
      min = min->left;
   }
   return min;
}//end treeMin

// TRANSPLANT - 
void transplant(ItemDB *items, Node *u, Node *v){
   if(!u->p)
      items->root = v;
   else if (u == u->p->left){
      u->p->left = v;
   }
   else
      u->p->right = v;
   if(v)
      v->p = u->p;
}//end transplant

//TREE-DELETE - deletes a node in a binary tree
void delete(ItemDB* items, int id) {
 Node *z = iterativeSearch(items,id);
 if(!z){
    fprintf(stderr, "Item you are trying to search is NULL.\n");
 }
 else{
   Node *y = z->p; 
   if(!z->left)
      transplant(items,z,z->right);
   else if (!z->right){
      transplant(items, y,y->right);
   }
   else{
      y = treeMin(z->right);
      if(y->p != z){
         transplant(items, y,y->right);
         y->right = z->right;
         y->right->p = y;
      }
      transplant(items,z,y);
      y->left = z->left;
      y->left->p = y;
   }
   deleteNode(&z);
   free(z);
 }
}//end delete 