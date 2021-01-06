//
//  bf.c
//  Assignment6
//
//  Created by Sahil Gupta on 11/19/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "bf.h"
#include "speck.h"
#include <stdlib.h>

//
// Constructor for a BloomFilter .
//
// size : The number of entries in the BloomFilter .
//
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    bf->size = size;
    bf->bloom_filter_set_bits = 0;
    return bf;
  }
  return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter);
  bf->filter = NULL;
  free(bf);
  return;
}

void bf_insert(BloomFilter *bf, char *key) {
  // Each hash gets its own bloom filter?
  int index1 = hash(bf->primary, key) % bf->size;
  int index2 = hash(bf->secondary, key) % bf->size;
  int index3 = hash(bf->tertiary, key) % bf->size;

  if (!bv_get_bit(bf->filter, index1)) {
    bf->bloom_filter_set_bits += 1;
  }
  bv_set_bit(bf->filter, index1);

  if (!bv_get_bit(bf->filter, index2)) {
    bf->bloom_filter_set_bits += 1;
  }
  bv_set_bit(bf->filter, index2);
  if (!bv_get_bit(bf->filter, index3)) {
    bf->bloom_filter_set_bits += 1;
  }
  bv_set_bit(bf->filter, index3);
}

//
// Probes a BloomFilter to check if a key has been inserted .
//
// bf: The BloomFilter .
// key: The key in which to check membership .
//
bool bf_probe(BloomFilter *bf, char *key) {
  int index1 = hash(bf->primary, key) % bf->size;
  int index2 = hash(bf->secondary, key) % bf->size;
  int index3 = hash(bf->tertiary, key) % bf->size;
  return bv_get_bit(bf->filter, index1) && bv_get_bit(bf->filter, index2) &&
         bv_get_bit(bf->filter, index3);
}
