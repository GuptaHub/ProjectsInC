//
//  word.c
//  Assignment7
//
//  Created by Sahil Gupta on 12/6/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "word.h"
//
// Constructor for a word.
//
// syms:    Array of symbols a Word represents.
// len:     Length of the array of symbols.
// returns: Pointer to a Word that has been allocated memory.
//
Word *word_create(uint8_t *syms,
                  uint64_t len) { // this was uint64_t changed to 32
  Word *w = (Word *)malloc(sizeof(Word));
  if (!w) {
    printf("Not enough space to allocat.\n");
    exit(1);
  }
  w->len = (uint32_t)len;
  w->syms = calloc(len, sizeof(uint8_t *));
  if (!w->syms) {
    printf("Not enough space to allocat.\n");
    exit(1);
  }
  for (uint64_t i = 0; i < len; i++) {
    w->syms[i] = syms[i];
  }
  return w;
}

//
// Constructs a new Word from the specified Word appended with a symbol.
// The Word specified to append to may be empty.
// If the above is the case, the new Word should contain only the symbol.
//
// w:       Word to append to.
// sym:     Symbol to append.
// returns: New Word which represents the result of appending.
//
Word *word_append_sym(Word *w, uint8_t sym) {
  // uint8_t *x = (uint8_t*)"";
  if (w && w->len == 0) {
    Word *w1 = word_create(&sym, 1);
    return w1;
  }
  Word *w2 = word_create(w->syms, w->len + 1);
  w2->syms[w->len] = sym;
  return w2;
}

//
// Destructor for a Word.
//
// w:       Word to free memory for.
// returns: Void.
//
void word_delete(Word *w) {
  free(w->syms);
  free(w);
  w = NULL;
}

//
// Creates a new WordTable, which is an array of Words.
// A WordTable has a pre-defined size of MAX_CODE (UINT16_MAX - 1).
// This is because codes are 16-bit integers.
// A WordTable is initialized with a single Word at index EMPTY_CODE.
// This Word represents the empty word, a string of length of zero.
//
// returns: Initialized WordTable.
//
WordTable *wt_create(void) {
  WordTable *wt = calloc(MAX_CODE, sizeof(Word));
  if (!wt) {
    printf("Not enough space to allocate.\n");
    exit(1);
  }
  wt[EMPTY_CODE] = word_create((uint8_t *)"", 0);
  return wt;
}

//
// Resets a WordTable to having just the empty Word.
//
// wt:      WordTable to reset.
// returns: Void.
//
void wt_reset(WordTable *wt) {
  for (int i = START_CODE; i < MAX_CODE; i++) {
    if (wt[i] != NULL) {
      word_delete(wt[i]);
    }
  }
}
//
// Deletes an entire WordTable.
// All Words in the WordTable must be deleted as well.
//
// wt:      WordTable to free memory for.
// returns: Void.
//
void wt_delete(WordTable *wt) {
  for (int i = START_CODE; i < MAX_CODE; i++) {
    if (wt[i] != NULL) {
      word_delete(wt[i]);
    }
  }
  word_delete(wt[EMPTY_CODE]);
  free(wt);
  wt = NULL;
}
