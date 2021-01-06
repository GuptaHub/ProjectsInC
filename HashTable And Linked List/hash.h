//
//  hash.h
//  Assignment6
//
//  Created by Sahil Gupta on 11/19/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef hash_h
#define hash_h
# ifndef NIL
# define NIL ( void *) 0
# endif
# include "ll.h"
# include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"
//
// Struct definition for a HashTable .
//
// salt : The salt of the HashTable ( used for hashing ).
// length : The maximum number of entries in the HashTable .
// heads : An array of linked list heads .
//
typedef struct HashTable {
    uint64_t salt [2];
    uint32_t length ;
    ListNode ** heads ;
} HashTable ;

HashTable * ht_create ( uint32_t length ) ;

void ht_delete ( HashTable *ht) ;

uint32_t ht_count ( HashTable *h) ;

ListNode * ht_lookup ( HashTable *ht , char * key, bool move_to_front, int * seeks_value, int * links_searched);

void ht_insert ( HashTable *ht , HatterSpeak *gs) ;
#endif /* hash_h */
