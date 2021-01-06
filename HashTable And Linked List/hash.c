//
//  hash.c
//  Assignment6
//
//  Created by Sahil Gupta on 11/19/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "hash.h"
#include <string.h>
//
// length : Length of the HashTable .
// salt : Salt for the HashTable .
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }

  return (HashTable *)NIL;
}
//
// First creates a new ListNode from HatterSpeak .
// The created ListNode is then inserted into a HashTable .
// This should call the ll_insert () function .
//
// ht: The HashTable .
// gs: The HatterSpeak to add to the HashTable .
//
void ht_insert(HashTable *ht, HatterSpeak *gs) {
  int index = hash(ht->salt, gs->oldspeak) % ht->length;
  ll_insert(&ht->heads[index], gs);
  // printf("%s\n", ht->heads[index]->gs->oldspeak);
}
void ht_delete(HashTable *ht) {
  // Free all the linked list, not just this. Needs more...
  for (uint32_t i = 0; i < ht->length; i++) {
    ll_delete(&ht->heads[i]);
  }
  free(ht->heads);
  ht->heads = NULL;
  free(ht);
}
// Returns number of entries in hash table
// avg link list len is sum of linked list nodes/ the size of the hash table

uint32_t ht_count(HashTable *h) {
  int count = 0;
  for (uint32_t i = 0; i < h->length; i++) {
    if (h->heads[i] != NULL) {
      ListNode *ln = h->heads[i];
      while (ln != NULL && ln->next != NULL) {
        count += 1;
        ln = ln->next;
      }
      count += 1;
    }
  }
  return count;
}
//
// Searches a HashTable for a key .
// Returns the ListNode if found and returns NULL otherwise .
// This should call the ll_lookup () function .
//
// ht: The HashTable .
// key: The key to search for .
//
ListNode *ht_lookup(HashTable *ht, char *key, bool move_to_front,
                    int *seeks_value, int *links_searched) {
  uint32_t linked_index = hash(ht->salt, key) % ht->length;
  //*seeks_value+=1;
  return ll_lookup(&ht->heads[linked_index], key, move_to_front, seeks_value,
                   links_searched);
  //    if(node!=NULL){
  //        return node;
  //    }
  //    return NULL;
  //    for(uint32_t x = 0; x < ht->length; x++){
  //        ListNode *node = ll_lookup(&ht->heads[x], key, move_to_front,
  //        seeks_value);//worked?
  //
  //        *seeks_value +=1;
  //
  //        if(node!=NULL){
  //            return node;
  //        }
  //    }
  //    return NULL;
}
