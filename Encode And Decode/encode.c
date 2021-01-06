//
//  encode.c
//  Assignment7
//
//  Created by Sahil Gupta on 12/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "encode.h"
#define OPTIONS "vi:o:"
#include <getopt.h>
int main(int argc, char *argv[]) {
  int c = 0;
  int infile = STDIN_FILENO;
  int outfile = STDOUT_FILENO;
  bool show_stats = false;
  char *infile_path = NULL;
  char *outfile_path = NULL;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'v':
      show_stats = true;
      break;
    case 'i':
      infile_path = optarg;
      //                infile = open(optarg, O_RDONLY);
      //                if(infile == -1){
      //                    printf("file not found.\n");
      //                    exit(1);
      //                }
      break;
    case 'o':
      outfile_path = optarg;
      //                outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
      //                if(outfile == -1){
      //                    printf("file not found\n");
      //                    exit(1);
      //                }
      break;
    default:
      break;
    }
  }
  if (infile_path != NULL && outfile_path != NULL) {
    infile = open(infile_path, O_RDONLY);
    if (infile == -1) {
      printf("file not found.\n");
      exit(1);
    }
    outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC);
    if (outfile == -1) {
      printf("file not found\n");
      exit(1);
    }
  }
  struct stat statbuf;

  // File headers
  FileHeader *fh = (FileHeader *)calloc(1, sizeof(FileHeader));
  if (!fh) {
    printf("Not enought space in memory.\n");
    exit(1);
  }
  fh->magic = 0x8BADBEEF;
  fstat(infile, &statbuf);
  fh->protection = statbuf.st_mode;
  // fchmod(outfile, statbuf.st_mode);
  write_header(outfile, fh);
  free(fh);

  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  uint8_t current_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;
  while (read_sym(infile, &current_sym)) {
    // printf(".%c\n", (char)current_sym);
    TrieNode *next_node = trie_step(curr_node, current_sym);
    if (next_node != NULL) {
      // buffer_pair(outfile, next_code, current_sym, bit_len(next_code));
      prev_node = curr_node;
      curr_node = next_node;
      // next_code = next_code + 1;
    } else {
      buffer_pair(outfile, curr_node->code, current_sym, bit_len(next_code));
      curr_node->children[current_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
      // curr_node = curr_node->children[current_sym];
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = current_sym;
    // next_code = next_code + 1;
  }
  if (curr_node != root) {

    buffer_pair(outfile, prev_node->code, prev_sym, bit_len(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, bit_len(next_code));
  flush_pairs(outfile);
  trie_delete(root);

  if (show_stats) {
    printf("Compressed file size: %lu bytes\n", total_bits / 8);
    fstat(infile, &statbuf);
    printf("Uncompressed file size: %lu bytes\n", total_syms);
    double temp2 = (double)(total_bits / 8) / (double)total_syms;
    double ratio = 100 * (1 - temp2);
    printf("Compression ratio: %.2f%%\n", ratio);
  }
  close(infile);
  close(outfile);
}
