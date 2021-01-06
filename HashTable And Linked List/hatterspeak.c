//
//  main.c
//  Assignment6
//
//  Created by Sahil Gupta on 11/19/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "bf.h"
#include "hash.h"
#include "ll.h"
#include "parser.h"
#include "regex_fill.h"
#include "speck.h"
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define REGEX "[a-zA-Z0-9_]+"
#define OPTIONS "sh:f:mb"
bool bad_word_lookup(ListNode *bad_words, char *key, int bad_words_length);
// regex correct: "[A-Za-z0-9'-_]+"
int main(int argc, char *argv[]) {
  int seeks = 0;
  int links_tranversed = 0;
  bool move_to_front = false;
  uint32_t ht_size = 10000, bf_size = 1048576;
  bool print_stats = false;

  int c;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      print_stats = true;
      break;
    case 'h':
      ht_size = atoi(optarg);
      break;
    case 'f':
      bf_size = atoi(optarg);
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      if (!move_to_front) {
        move_to_front = false;
      }
      break;
    default:
      break;
    }
  }

  bool nontalk = true;
  // bool hybridtalk = true;
  bool hattertalk = true;

  regex_t regex;
  int reg_return = regcomp(&regex, "[A-Za-z0-9_]+(('|-)[a-zA-z0-9_]*)*",
                           REG_EXTENDED); // given on 11/24 lab
  if (reg_return != 0) {
    return -1;
  }
  // Populating the bloom filter and hash table
  BloomFilter *bf = bf_create(bf_size);
  HashTable *ht = ht_create(ht_size);
  char *oldspeak_file = "oldspeak.txt";
  char *hatterspeak_file = "hatterspeak.txt";

  fill_oldspeak_fscanf(oldspeak_file, ht, bf, move_to_front, &seeks,
                       &links_tranversed);
  fill_hash_filter(hatterspeak_file, ht, bf, regex, move_to_front, &seeks,
                   &links_tranversed);

  ListNode *bad_words =
      (ListNode *)calloc(1, sizeof(ListNode *)); // this will store the pointers
                                                 // to nodes that are considered
                                                 // bad
  if (!bad_words) {
    printf("Memory allocation error. Quitting.\n");
    exit(0);
  }
  ListNode *recently_addedNode;
  int bad_word_index = 0;
  // FILE *test_file = fopen("dungeon_text.txt", "r");

  while (1) {
    char *buffer = next_word(stdin, &regex);
    // char * buffer = "you";
    if (buffer != NULL) {
      // if in bloom filter, add it to the list of bad words
      // if it's not in bloom filter, then search for it, if it's a bad word,
      // add it to the list of bad words.
      if (bf_probe(bf, buffer)) {
        seeks += 1;
        recently_addedNode =
            ht_lookup(ht, buffer, move_to_front, &seeks, &links_tranversed);

        if (recently_addedNode != NULL) {
          if (!bad_word_lookup(bad_words, buffer, bad_word_index)) {
            bad_words[bad_word_index] =
                *recently_addedNode; // the recently added node will point to
                                     // whatever the head(bad_words) was earlier
                                     // pointing to.(NULL)
            bad_word_index += 1;
            bad_words =
                realloc(bad_words, sizeof(ListNode) * (bad_word_index + 1));
            if (!bad_words) {
              printf("Memory allocation problem. Quitting program\n");
              exit(0);
            }
            if (recently_addedNode->gs->hatterspeak != NULL) {
              nontalk =
                  false; // the moment you see a hatterword this is ruled out
            }
            if (recently_addedNode->gs->hatterspeak == NULL) {
              hattertalk = false; // if you see NULL and nontalk is ruled out,
                                  // it's def hybrid
            }
          }
        }
      }
      // free(buffer);
    } else {
      // free(buffer);
      break;
    }
  }
  printf("\n");
  // if you are printing the stats, you are surpressing the text
  if (!print_stats) {

    if (!nontalk && !hattertalk) {
      // print the hybrid message...
      printf("Dear Comrade,\n\nYou have chosen to use words that the queen has "
             "decreed oldspeak.\nDue to your infraction you will be sent to "
             "the dungeon where you will be taught hatterspeak.\n\nYour "
             "errors:\n\n");
      for (int i = 0; i < bad_word_index; i++) {
        if (bad_words[i].gs->hatterspeak == NULL) {
          printf("%s\n", bad_words[i].gs->oldspeak);
        }
      }
      printf("\n\nAppropriate hatterspeak translations.\n\n");
      for (int i = 0; i < bad_word_index; i++) {
        if (bad_words[i].gs->hatterspeak != NULL) {
          printf("%s -> %s\n", bad_words[i].gs->oldspeak,
                 bad_words[i].gs->hatterspeak);
        }
      }
    } else if (nontalk && !hattertalk) {
      // print the nontalk message
      printf("Dear Wonderlander,\n\nYou have chosen to use words that the "
             "queen has decreed oldspeak.\nDue to your infraction you will be "
             "sent to the dungeon where you will be taught "
             "hatterspeak.\n\nYour errors:\n\n");
      for (int x = 0; x < bad_word_index; x++) {
        printf("%s\n", bad_words[x].gs->oldspeak);
      }
    } else if (hattertalk && !nontalk) {
      // print the hatterspeak message
      printf("Dear Wonderlander,\n\nThe decree for hatterspeak finds your "
             "message lacking . Some of the words that you used are not "
             "hatterspeak.\nThe list shows how to turn the oldspeak words into "
             "hatterspeak.\n");
      printf("\n");
      for (int x = 0; x < bad_word_index; x++) {
        printf("%s -> %s\n", bad_words[x].gs->oldspeak,
               bad_words[x].gs->hatterspeak);
      }
    }
  } else {
    printf("Seeks: %d\n", seeks);
    float links_search = (float)links_tranversed / (float)seeks;
    printf("Average seek length: %f\n", links_search);
    int total_nodes = ht_count(ht);
    float average_ll_length = (float)total_nodes / (float)ht_size;
    printf("Average Linked List Length: %f\n", average_ll_length);

    // Hash table load
    int non_null_heads = 0;
    for (uint32_t i = 0; i < ht->length; i++) {
      if (ht->heads[i] != NULL) {
        non_null_heads += 1;
      }
    }
    float hash_table_load = ((float)non_null_heads / (float)ht_size) * 100;
    printf("Hash table load: %f%%\n", hash_table_load);

    float bloom_filter_load =
        (float)bf->bloom_filter_set_bits / (float)bf->size;
    bloom_filter_load *= 100;
    printf("Bloom filter load: %f%%\n", bloom_filter_load);
  }
  // delete_saved_words(words_to_free, &freeing_words);
  // ht_delete(ht);

  ht_delete(ht);
  bf_delete(bf);
  free(bad_words);
  regfree(&regex);
  return 0;
}
bool bad_word_lookup(ListNode *bad_words, char *key, int bad_words_length) {
  if (bad_words == NULL) {
    return NULL;
  }
  for (int i = 0; i < bad_words_length; i++) {
    if (strcmp(bad_words[i].gs->oldspeak, key) == 0) {
      return true;
    }
  }
  return false;
}
// elasah
