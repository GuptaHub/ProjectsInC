//
//  regex_fill.c
//  Assignment6
//
//  Created by Sahil Gupta on 11/28/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "regex_fill.h"

void fill_hash_filter(char *filename, HashTable *ht, BloomFilter *bf,
                      regex_t regex, bool move_to_front, int *seeks,
                      int *links_searched) {
  FILE *text_file = fopen(filename, "r");
  while (1) {
    char *buffer = next_word(text_file, &regex);
    char *buffer2 = NULL;
    if (strcmp("hatterspeak.txt", filename) == 0) {
      buffer2 = next_word(text_file, &regex);
    }

    if (buffer != NULL) {
      if (ht_lookup(ht, buffer, move_to_front, seeks, links_searched) == NULL) {
        char *word = (char *)calloc(strlen(buffer) + 1, sizeof(char *));
        if (word == NULL) {
          printf("Error: Can't allocate enough memory to store.\n");
          exit(0);
        }
        if (buffer2 != NULL) {
          char *word2 = (char *)calloc(strlen(buffer2) + 1, sizeof(char *));
          if (word2 == NULL) {
            printf("Error: Can't allocate enough memory to store.\n");
            exit(0);
          }
          strcpy(word, buffer);
          strcpy(word2, buffer2);
          bf_insert(bf, word);
          // add in hashtable

          HatterSpeak *gs_hatter = create_hatterword(word, word2);
          // inserting in hash table is weird
          ht_insert(ht, gs_hatter);

        } else {
          strcpy(word, buffer);
          bf_insert(bf, word);
          // add in hashtable
          HatterSpeak *gs = create_hatterword(word, NULL);
          ht_insert(ht, gs); // insert in hashtable
        }
      }
      //            if(words_num > 14330){
      //                printf("pause\n");
      //            }
    } else {
      break;
    }
  }
  fclose(text_file);
}
void fill_oldspeak_fscanf(char *filename, HashTable *ht, BloomFilter *bf,
                          bool move_to_front, int *seeks, int *links_searched) {
  int count_old_words = 0;
  FILE *ptr = fopen(filename, "r");
  char buffer[4096] = "";
  while (fscanf(ptr, "%s", buffer) == 1) {
    if (ht_lookup(ht, buffer, move_to_front, seeks, links_searched) == NULL) {
      char *word = (char *)calloc(strlen(buffer) + 1, sizeof(char *));
      if (word == NULL) {
        printf("Error: Cannot allocate to store.\n");
        exit(0);
      }
      strcpy(word, buffer);
      bf_insert(bf, word);

      HatterSpeak *gs = create_hatterword(word, NULL);
      ht_insert(ht, gs); // insert in hashtable
      count_old_words += 1;
    }
  }
  fclose(ptr);
}

//    FILE *text_file = fopen("oldspeak.txt", "r");
//    while(1){
//        char * buffer = next_word(text_file, &regex);
//        if(buffer != NULL){
//            //print and populate in filter and hash table
//            char * word = (char *)calloc(strlen(buffer), sizeof(char));
//            strcpy(word, buffer);
//            bf_insert(bf, word);
//            //add in hashtable
//            gs = create_hatterword(word, NULL);
//            ht_insert(ht, gs); //insert in hashtable
//        }else{
//            break;
//        }
//    }
//    FILE *hatter_file = fopen("hatterspeak.txt", "r");
//    while(1){
//        char * buffer = next_word(hatter_file, &regex);
//        char * buffer2 = next_word(hatter_file, &regex);
//        if(buffer != NULL && buffer2 != NULL){
//            //print and populate the word of hatterspeak in filter and hash
//            table
//
//            char * word = (char *)calloc(strlen(buffer) + 1,sizeof(char));
//            char * word2 = (char *)calloc(strlen(buffer2) + 1,sizeof(char));
//
//            strcpy(word, buffer);
//            strcpy(word2, buffer2);
//            bf_insert(bf, word);
//            //add in hashtable
//            HatterSpeak * gs_hatter = create_hatterword(word, word2);
//            //inserting in hash table is weird
//            ht_insert(ht, gs_hatter);
//        }else{
//            break;
//        }
//    }
