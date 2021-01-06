//
//  ll.h
//  Assignment6
//
//  Created by Sahil Gupta on 11/19/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef ll_h
#define ll_h

#include <stdio.h>
#include <stdlib.h>

 # ifndef NIL
 # define NIL ( void *) 0
 # endif
 # include <stdbool.h>

 // If flag is set , ListNodes that are queried are moved to the front .
 //extern bool move_to_front;

 typedef struct ListNode ListNode;
 typedef struct HatterSpeak HatterSpeak;


struct HatterSpeak {
     char * oldspeak;
     char * hatterspeak;
 };

 //
 // Struct definition of a ListNode .
 //
 // gs: HatterSpeak struct containing oldspeak and its hatterspeak translation .
 //

 struct ListNode {
  HatterSpeak *gs;
  ListNode * next ;
};

HatterSpeak * create_hatterword(char *oldspeak, char *hs);

 //
 // Constructor for a ListNode .
 //
 // gs: HatterSpeak struct containing oldspeak and its hatterspeak translation .
 //
 ListNode * ll_node_create ( HatterSpeak *gs) ;

 //
 // Destructor for a ListNode .
 //
 // n: The ListNode to free .
 //
 void ll_node_delete (ListNode *n);

 //
 // Destructor for a linked list of ListNodes .
 //
 // head : The head of the linked list .
 //
void ll_delete (ListNode ** head);

 //
 // Creates and inserts a ListNode into a linked list .
 //
 // head : The head of the linked list to insert in.
 // gs: HatterSpeak struct .
 //
 ListNode * ll_insert (ListNode ** head , HatterSpeak *gs) ;

 //
 // Searches for a specific key in a linked list .
 // Returns the ListNode if found and NULL otherwise .
 //
 // head : The head of the linked list to search in.
 // key: The key to search for .
 ListNode * ll_lookup (ListNode ** head, char * key, bool which_move, int *seeks_value, int * links_searched);

void hatterWord_delete(HatterSpeak *gs);
#endif /* ll_h */
