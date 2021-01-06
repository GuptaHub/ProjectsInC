//
//  trie.c
//  Assignment7
//
//  Created by Sahil Gupta on 12/6/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "trie.h"
#include "code.h"
#include <stdlib.h>

//
// Constructor for a TrieNode.
//
// index:   Index of the constructed TrieNode.
// returns: Pointer to a TrieNode that has been allocated memory.
//
TrieNode *trie_node_create(uint16_t index) {
  TrieNode *tn = (TrieNode *)calloc(1, sizeof(TrieNode));
  if (!tn) {
    printf("Memory allocation. error\n");
    exit(1);
  }
  tn->code = index;
  return tn;
}

//
// Destructor for a TrieNode.
//
// n:       TrieNode to free allocated memory for.
// returns: Void.
//
void trie_node_delete(TrieNode *n) {
  if (n == NULL) {
    return;
  }
  //    for(int i = 0; i < ALPHABET; i++){
  //        trie_node_delete(n->children[i]);
  //    }
  free(n);
  n = NULL;
  // free(n->children);
}

//
// Initializes a Trie: a root TrieNode with the index EMPTY_CODE.
//
// returns: Pointer to the root of a Trie.
//
TrieNode *trie_create(void) {
  TrieNode *root_pointer = (TrieNode *)calloc(1, sizeof(TrieNode));
  if (!root_pointer) {
    printf("Not enough space to allocate.\n");
    exit(1);
  }
  root_pointer->code = EMPTY_CODE;
  return root_pointer;
}

//
// Resets a Trie to just the root TrieNode.
//
// root:    Root of the Trie to reset.
// returns: Void.
//
void trie_reset(TrieNode *root) {
  if (root == NULL) {
    return;
  }
  for (int i = 0; i < ALPHABET; i++) {
    trie_delete(root->children[i]);
    trie_node_delete(root->children[i]);
  }
}

//
// Deletes a sub-Trie starting from the sub-Trie's root.
//
// n:       Root of the sub-Trie to delete.
// returns: Void.
//
void trie_delete(TrieNode *n) {
  if (n == NULL) {
    return;
  }
  for (int i = 0; i < ALPHABET; i++) {
    trie_delete(n->children[i]);
    // trie_node_delete(n->children[i]);
  }
  trie_node_delete(n);
}

//
// Returns a pointer to the child TrieNode reprsenting the symbol sym.
// If the symbol doesn't exist, NULL is returned.
//
// n:       TrieNode to step from.
// sym:     Symbol to check for.
// returns: Pointer to the TrieNode representing the symbol.
//
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (n == NULL) {
    return NULL;
  }
  if (n->children[sym] != NULL) {
    return n->children[sym];
  } else {
    return NULL;
  }
  // return n->children[sym] != NULL ? n->children[sym] : NULL;
}
