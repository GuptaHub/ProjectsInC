//
//  io.c
//  Assignment7
//
//  Created by Sahil Gupta on 12/6/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "io.h"
#include "code.h"
#include "word.h"
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Oran variables for the stats
uint64_t total_syms, total_bits = 0;

static uint8_t sym_buf[4096] = {0};
static uint16_t sym_count = 0;
static uint16_t sym_buf_end = UINT16_MAX;

static uint8_t bit_buf[4096] = {0};
static uint16_t bit_count = 0;

//
// Reads in a FileHeader from the input file.
//
// infile:  File descriptor of input file to read header from.
// header:  Pointer to memory where the bytes of the read header should go.
// returns: Void.
//
void read_header(int infile, FileHeader *header) {
  read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  total_bits += (8 * sizeof(FileHeader));
}
//
// Writes a FileHeader to the output file.
//
// outfile: File descriptor of output file to write header to.
// header:  Pointer to the header to write out.
// returns: Void.
//
void write_header(int outfile, FileHeader *header) {
  total_bits += (8 * sizeof(FileHeader));
  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
}
//
// Wrapper for the read() syscall.
// Loops to read the specified number of bytes, or until input is exhausted.
// Returns the number of bytes read.
//
// infile:  File descriptor of the input file to read from.
// buf:     Buffer to store read bytes into.
// to_read: Number of bytes to read.
// returns: Number of bytes read.
//
int read_bytes(int infile, uint8_t *buf, int to_read) {
  int bytes_to_read = to_read;
  int bytes_read = 0; // storing char # in each line
  int total_read = 0; // total # of char read overrall in the buffer
  // char buffer[to_read];
  do {
    // buf = buf + total_read;
    bytes_read = read(infile, buf + total_read, bytes_to_read);
    if (bytes_read == -1) {
      printf("Error in reading the word..from read\n");
      exit(1);
    }
    bytes_to_read -= bytes_read;
    total_read += bytes_read;

  } while (bytes_read && total_read != to_read);
  return total_read;
}
//
// Wrapper for the write() syscall.
// Loops to write the specified number of bytes, or until nothing is written.
// Returns the number of bytes written.
//
// outfile:   File descriptor of the output file to write to.
// buf:       Buffer that stores the bytes to write out.
// to_write:  Number of bytes to write.
// returns:   Number of bytes written.
//
int write_bytes(int outfile, uint8_t *buf, int to_write) {
  int bytes_to_write = to_write;
  int bytes_written = 0;
  int total_written = 0;
  // char buffer[to_write];
  do {

    buf = buf + total_written;
    bytes_written = write(outfile, buf, bytes_to_write);

    if (bytes_written == -1) {
      printf("Error in reading the word..from word\n");
      exit(0);
    }
    bytes_to_write -= bytes_written;
    total_written += bytes_written;
  } while (bytes_written && total_written != to_write);
  return total_written;
}
//
// "Reads" a symbol from the input file.
// The "read" symbol is placed into the pointer to sym (pass by reference).
// In reality, a block of symbols is read into a buffer.
// An index keeps track of the currently read symbol in the buffer.
// Once all symbols are processed, another block is read.
// If less than a block is read, the end of the buffer is updated.
// Returns true if there are symbols to be read, false otherwise.
//
// infile:  File descriptor of input file to read symbols from.
// sym:     Pointer to memory which stores the read symbol.
// returns: True if there are symbols to be read, false otherwise.
//

bool read_sym(int infile, uint8_t *sym) {
  if (!sym_count) {
    int bytes_read = read_bytes(infile, sym_buf, 4096);
    if (bytes_read != 4096) {
      sym_buf_end = bytes_read + 1;
    }
  }
  *sym = sym_buf[sym_count];
  sym_count = (sym_count + 1) % 4096;
  if (sym_count != sym_buf_end) {
    total_syms += 1;
  }
  return sym_count != sym_buf_end;
}

//
// Buffers a pair. A pair is comprised of a symbol and an index.
// The bits of the symbol are buffered first, starting from the LSB.
// The bits of the index are buffered next, also starting from the LSB.
// bit_len bits of the index are buffered to provide a minimal representation.
// The buffer is written out whenever it is filled.
//
// outfile: File descriptor of the output file to write to.
// sym:     Symbol of the pair to buffer.
// index:   Index of the pair to buffer.
// bit_len: Number of bits of the index to buffer.
// returns: Void.
//
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bit_len) {
  total_bits += (bit_len + 8);
  for (uint8_t i = 0; i < bit_len; i++) {
    if ((code & (1 << (i % 16)))) { // check
      bit_buf[bit_count / 8] |= (1 << (bit_count % 8));

    } else {
      bit_buf[bit_count / 8] &= ~(1 << (bit_count % 8));
    }
    bit_count += 1;
    if ((bit_count / 8) == 4096) {
      write_bytes(outfile, bit_buf, 4096);
      bit_count = 0;
    }
  }

  for (uint8_t i = 0; i < 8; i++) {
    if (sym & (1 << (i % 8))) { // check
      bit_buf[bit_count / 8] |= (1 << (bit_count % 8));

    } else {
      bit_buf[bit_count / 8] &= ~(1 << (bit_count % 8));
    }
    bit_count += 1;
    if ((bit_count / 8) == 4096) {
      write_bytes(outfile, bit_buf, 4096);
      bit_count = 0;
    }
  }
}

//
// "Reads" a pair (symbol and index) from the input file.
// The "read" symbol is placed in the pointer to sym (pass by reference).
// The "read" index is placed in the pointer to index (pass by reference).
// In reality, a block of pairs is read into a buffer.
// An index keeps track of the current bit in the buffer.
// Once all bits have been processed, another block is read.
// The first 8 bits of the pair constitute the symbol, starting from the LSB.
// The next bit_len bits constitutes the index, starting from the the LSB.
// Returns true if there are pairs left to read in the buffer, else false.
// There are pairs left to read if the read index is not STOP_INDEX.
//
// infile:  File descriptor of the input file to read from.
// sym:     Pointer to memory which stores the read symbol.
// index:   Pointer to memory which stores the read index.
// bit_len: Length in bits of the index to read.
// returns: True if there are pairs left to read, false otherwise.
//

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bit_len) {
  total_bits += (8 + bit_len);
  *code = 0;
  *sym = 0;
  // almost identical to buffer_pair
  for (uint8_t i = 0; i < bit_len; i++) {
    if (!bit_count) { //! bit_count
      read_bytes(infile, bit_buf, 4096);
    }
    if (bit_buf[bit_count / 8] & (1 << (bit_count % 8))) {
      *code |= (1 << (i % 16));
    } else {
      *code &= ~(1 << (i % 16));
      // bit_count = (bit_count + 1) % (4096 * 8);
    }
    bit_count = (bit_count + 1) % (4096 * 8);
  }
  for (uint8_t i = 0; i < 8; i++) {
    if (bit_count == 0) { //! bit_count
      read_bytes(infile, bit_buf, 4096);
    }
    if (bit_buf[bit_count / 8] & (1 << (bit_count % 8))) {
      *sym |= (1 << (i % 8));
    } else {
      *sym &= ~(1 << (i % 8));
      // bit_count = (bit_count + 1) % (4096 * 8);
    }
    bit_count = (bit_count + 1) % (4096 * 8);
  }

  return *code != STOP_CODE;
}

//
// Buffers a Word, or more specifically, the symbols of a Word.
// Each symbol of the Word is placed into a buffer.
// The buffer is written out when it is filled.
//
// outfile: File descriptor of the output file to write to.
// w:       Word to buffer.
// returns: Void.
//
void buffer_word(int outfile, Word *w) {
  total_syms += w->len;
  for (uint32_t i = 0; i < w->len; i++) {
    sym_buf[sym_count] = w->syms[i];
    sym_count += 1;
    if (sym_count == 4096) {
      write_bytes(outfile, sym_buf, 4096);
      sym_count = 0;
    }
  }
}
//
// Writes out any remaining symbols in the buffer.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_words(int outfile) {
  if (sym_count > 0) {
    write_bytes(outfile, sym_buf, sym_count);
    sym_count = 0;
  }
  // might need to reset sym_count
}
//
// Writes out any remaining pairs of symbols and indexes to the output file.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_pairs(int outfile) { // need a function to determine # of bits needed
                                // to represent bit_count
  if (bit_count) {
    int bytes;
    if (bit_count % 8 == 0) {
      bytes = bit_count / 8;
    } else {
      bytes = (bit_count / 8) + 1;
    }
    write_bytes(outfile, bit_buf, bytes);
    bit_count = 0;
  }
}

uint8_t bit_len(int code) {
  int count = 0;
  while (code >= 1) {
    code /= 2;
    count++;
  }
  return count;
}
