//
//  ll.c
//  Assignment6
//
//  Created by Sahil Gupta on 11/19/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "ll.h"
#include <string.h>

//
// Constructor for a ListNode .
//
// gs: HatterSpeak struct containing oldspeak and its hatterspeak translation .
//
ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *ln = (ListNode *)calloc(1, sizeof(ListNode));
  if (ln == NULL) {
    printf("Error: Couldn't allocate memory for a node.\n");
    exit(0);
  }
  ln->gs = gs;

  return ln;
}

//
// Destructor for a ListNode .
//
// n: The ListNode to free .
//
void ll_node_delete(ListNode *n) {
  // update head
  free(n->gs->oldspeak);
  free(n->gs->hatterspeak);
  free(n->gs);
  n->gs = NULL;
  free(n);
}
//
// Destructor for a linked list of ListNodes .
//
// head : The head of the linked list .
//
void ll_delete(ListNode **head) {
  ListNode *node1 = *head;
  ListNode *node2 = *head;
  if (node1 == NULL) {
    return;
  }
  while (node2 != NULL) {
    node2 = node1->next;
    ll_node_delete(node1);
    node1 = node2;
  }
  // ll_node_delete(node1);//delete the very last one
}
HatterSpeak *create_hatterword(char *oldspeak, char *hs) {
  HatterSpeak *gs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  if (gs == NULL) {
    printf("Couldn't allocate space in memory for another hatter word\n");
    exit(0);
  }
  gs->oldspeak = oldspeak;
  gs->hatterspeak = hs;
  return gs;
}
//
// Creates and inserts a ListNode into a linked list .
//
// head : The head of the linked list to insert in.
// gs: HatterSpeak struct .
//
// Following stack format. Last in, first out
ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  ListNode *new_Node = ll_node_create(gs);
  if (new_Node == NULL) {
    printf("Memory allocation issue. Quitting from ListNode.");
    exit(0);
  }
  new_Node->next = *head;
  *head = new_Node;
  return new_Node;
}

//
// Searches for a specific key in a linked list .
// Returns the ListNode if found and NULL otherwise .
//
// head : The head of the linked list to search in.
// key: The key to search for .
ListNode *ll_lookup(ListNode **head, char *key, bool which_move,
                    int *seeks_value, int *links_searched) {
  *seeks_value += 1;
  ListNode *leading_node = NULL;
  ListNode *current_node = *head;
  if (current_node == NULL) {
    return NULL;
  }
  while (strcmp(current_node->gs->oldspeak, key) != 0) {
    *links_searched += 1;
    if ((current_node->gs->hatterspeak != NULL &&
         strcmp(current_node->gs->hatterspeak, key) == 0)) {
      break;
    }
    if (current_node->next != NULL) {
      leading_node = current_node;
      current_node = current_node->next;
    } else {
      return NULL;
    }
  }
  if (current_node != NULL &&
      (strcmp(current_node->gs->oldspeak, key) == 0 ||
       strcmp(current_node->gs->hatterspeak, key) == 0)) {
    // make the previous one equal to your next, set your next to the first
    // node(*head)
    if (which_move) {
      if (leading_node != NULL) {
        leading_node->next = current_node->next;
        current_node->next = *head;
      }
    }
    return current_node;
  }
  return NULL;
}

void hatterWord_delete(HatterSpeak *gs) {
  gs->hatterspeak = NULL;
  gs->oldspeak = NULL;
  free(gs);
}
