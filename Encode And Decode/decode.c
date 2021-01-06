//
//  decode.c
//  Assignment7
//
//  Created by Sahil Gupta on 12/11/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "decode.h"
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
      // infile = open(optarg, O_RDONLY);
      //                if(infile == -1){
      //                    printf("file not found.\n");
      //                    exit(1);
      //                }
      break;
    case 'o':
      outfile_path = optarg;
      // outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
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
  FileHeader *fh = (FileHeader *)calloc(1, sizeof(FileHeader));
  if (!fh) {
    printf("Not enought space in memory.\n");
    exit(1);
  }
  read_header(infile, fh);
  if (fh->magic != MAGIC) {
    printf("Not allowed.\n");
    free(fh);
    exit(1);
  }
  free(fh);
  WordTable *table = wt_create();
  uint8_t current_sym = 0;
  uint16_t current_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &current_code, &current_sym, bit_len(next_code))) {
    // printf("%c indeed going into\n", (char)current_sym);
    table[next_code] = word_append_sym(table[current_code], current_sym);
    buffer_word(outfile, table[next_code]);
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
  wt_delete(table);
  close(outfile);
  close(infile);

  if (show_stats) {
    printf("Compressed file size: %lu bytes\n", total_bits / 8);
    printf("Uncompressed file size: %lu bytes\n", total_syms);
    double temp2 = (double)(total_bits / 8) / (double)total_syms;
    double ratio = 100 * (1 - temp2);
    printf("Compression ratio: %.2f%%\n", ratio);
  }
}
