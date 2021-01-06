//
//  sieve.c
//  Assignment4
//
//  Created by Sahil Gupta on 11/4/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "sieve.h"
#include <math.h>
//
// The Sieve of Eratosthenes .
// Set bits in a BitVector represent prime numbers .
// Composite numbers are sieved out by clearing bits .
//
// v: The BitVector to sieve .
//
// Note: This is the exact code given on assignment 4 pdf for CSE13S at UCSC
// Fall2020.
void sieve(BitVector *v) {
  bv_set_all_bits(v);
  bv_clr_bit(v, 0);
  bv_clr_bit(v, 1);
  bv_set_bit(v, 2);
  for (uint32_t i = 2; i < sqrtl(bv_get_len(v)); i += 1) {
    // Prime means bit is set
    if (bv_get_bit(v, i)) {
      for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k += 1) {
        bv_clr_bit(v, (k + i) * i);
      }
    }
  }
  return;
}
