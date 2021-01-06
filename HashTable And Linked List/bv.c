//
//  bv.c
//  Assignment4
//
//  Created by Sahil Gupta on 11/4/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "bv.h"

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
BitVector *bv_create(uint32_t bit_len) {
  BitVector *b = (BitVector *)malloc(sizeof(BitVector));
  if (b != NULL) {
    b->length = bit_len;
    b->vector = (uint8_t *)calloc((bit_len / 8) + 1, sizeof(uint8_t));
  }
  return b;
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector *v) {
  free(v->vector);
  v->vector = NULL;
  free(v);
}
//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) { return v->length; }
//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  for (int i = 0; i < (int)(v->length / 8) + 1; i++) {
    for (int x = 0; x < 8; x++) {
      bv_set_bit(v, x + (8 * i));
    }
    // v->vector[i] = 0b11111111;
  }
}
//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  int row = i / 8;
  int index = i % 8;
  uint8_t mask;
  switch (index) {
  case 0:
    mask = 1;
    break;
  case 1:
    mask = 2;
    break;
  case 2:
    mask = 4;
    break;
  case 3:
    mask = 8;
    break;
  case 4:
    mask = 16;
    break;
  case 5:
    mask = 32;
    break;
  case 6:
    mask = 64;
    break;
  case 7:
    mask = 128;
    break;
  default:
    mask = 0; // Did this to remove a warning
    break;
  }
  v->vector[row] = v->vector[row] | mask;
}

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  int row = i / 8;
  int index = i % 8;
  uint8_t mask = 255;
  switch (index) {
  case 0:
    mask = mask - 1;
    break;
  case 1:
    mask = mask - 2;
    break;
  case 2:
    mask = mask - 4;
    break;
  case 3:
    mask = mask - 8;
    break;
  case 4:
    mask = mask - 16;
    break;
  case 5:
    mask = mask - 32;
    break;
  case 6:
    mask = mask - 64;
    break;
  case 7:
    mask = mask - 128;
    break;
  default:
    mask = 0; // Did this to remove a warning
    break;
  }
  v->vector[row] = v->vector[row] & mask;
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  int row = i / 8;
  int index = i % 8;
  uint8_t mask;
  switch (index) {
  case 0:
    mask = 1;
    break;
  case 1:
    mask = 2;
    break;
  case 2:
    mask = 4;
    break;
  case 3:
    mask = 8;
    break;
  case 4:
    mask = 16;
    break;
  case 5:
    mask = 32;
    break;
  case 6:
    mask = 64;
    break;
  case 7:
    mask = 128;
    break;
  default:
    mask = 0; // Did this to remove a warning
    break;
  }
  // v->vector[row] = v->vector[row]|mask;
  if ((v->vector[row] & mask) > 0) {
    return 1;
  }
  return 0;
}
