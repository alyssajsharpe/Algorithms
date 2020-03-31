/*
   itemMenu.c: interactive test program for the database of items 
               data structure

   CS411 Lab 1 
   Name: Kevin Sahr
   Date: 4/19/18

   THIS FILE SHOULD NOT CHANGE FOR LAB 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "itemDB.h"

#define MAX_INPUT_STRING 256

// helper function to get an Item ID from the user
int getItemID (const char* prompt) {
   int id;
   printf("%s: ", prompt);
   while (!scanf("%d", &id))
   {
      fprintf(stderr, "ERROR: please enter an integer id: ");
      scanf("%*s");
   }

   return id;
}

int main (int argc, char* argv[]) {

   // validate the command-line argument
   if (argc != 2) {
      fprintf(stderr, "usage: %s maxItems\n", argv[0]);
      exit(1);
   }

   int maxItems = 0;
   if (!sscanf(argv[1], "%d", &maxItems)) {
      fprintf(stderr, "ERROR: %s is not a number\n", argv[1]);
      exit(1);
   }

   /*** declare and initialize the ItemDB here ***/
   ItemDB db;
   initializeItemDB(&db, maxItems);

   // do the menu
   int id; // variable to hold any user-input ID value
   int again = 1;
   do {

      printf("\n** ITEM INVENTORY MENU **\n");
      printf("1. Insert Item\n");
      printf("2. Delete Item\n");
      printf("3. Output Single Item\n");
      printf("4. Output Item DB\n");
      printf("5. Reset Item DB\n");
      printf("6. Quit\n");
      printf("* Enter your choice (1-6):  \n");

      int choice = -1;
      while (!scanf("%d", &choice)) {
         scanf("%*s");
         fprintf(stderr, "ERROR: please enter a number (1-6): \n");
      }

      switch (choice)
      {
         case 1: // insert item 
         {
            char name[MAX_INPUT_STRING + 1];
            float price;
            printf("Enter new item id, name, and price (without commas): ");
            if (scanf("%d %s %f", &id, name, &price) != 3) {
               fprintf(stderr, "ERROR: invalid Item values.\n");
               exit(1);
            }

            printf("* Inserting Item #%d\n", id);

            /*** create and insert a new Item with the user-input values ***/

            Item* newItem = createItem(id, name, price);
            if (newItem) {
               // if insert fails we need to deallocate the Item
               if (insert(&db, newItem))
                  deleteItem(&newItem);
            } else {
               fprintf(stderr, "ERROR: unable to create Item.\n");
               exit(2);
            }

            break;
         }   
         case 2: // delete item
            id = getItemID("Enter item ID to delete");
            printf("* Deleting Item #%d\n", id);

            delete(&db, id);
            break;

         case 3: // output single Item
         {
            id = getItemID("Enter item ID to display");
            printf("* Outputting Item #%d:\n", id);

            Item* item = find(&db, id);
            if (item)
               printItem(item);
            else
               printf("NOT FOUND.\n");

            break;
         }
         case 4: // output the entire DB contents
            printf("* The Item Database *\n");
            printItemDB(&db);

            break;

         case 5: // reset ItemDB
            printf("* Resetting the Item Database");
            deleteItemDB(&db);
            initializeItemDB(&db, maxItems);

            break;

         case 6: // quit
            printf("* You have chosen to QUIT\n");
            again = 0;
            break;

         default:
            fprintf(stderr, "ERROR: only choices 1-6 are valid.\n");
            break;
      }

   } while (again);

   // delete all dynamically allocated memory associated
   // with the ItemDB.
   deleteItemDB(&db);

   return 0;
}

