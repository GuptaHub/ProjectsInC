//
//  regex_fill.h
//  Assignment6
//
//  Created by Sahil Gupta on 11/28/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#ifndef regex_fill_h
#define regex_fill_h
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "speck.h"
#include "bf.h"
#include "ll.h"
#include "hash.h"
#include "parser.h"
#include <string.h>

void fill_hash_filter(char *filename, HashTable * ht, BloomFilter * bf, regex_t regex, bool move_to_front, int * seeks, int * links_searched);
void fill_oldspeak_fscanf(char *filename, HashTable * ht, BloomFilter * bf, bool move_to_front, int * seeks, int * links_searched);
#endif /* regex_fill_h */
