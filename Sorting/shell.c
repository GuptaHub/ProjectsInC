//
//  shell.c
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "shell.h"

ShellSort *shell_create(int size) {
  ShellSort *shs = (ShellSort *)calloc(size, sizeof(ShellSort));
  if (shs != NULL) {
    shs->arr_size = size;
    shs->comparisons = 0;
    shs->moves = 0;
    shs->gap_size = 0;
    shs->gap_sequence = (int *)calloc(shs->gap_size, sizeof(int));
  } else {
    exit(0);
  }
  return shs;
}

void gap_generate(ShellSort *shs) {
  int n = shs->arr_size;

  while (n > 1) {
    shs->gap_sequence =
        (int *)realloc(shs->gap_sequence, sizeof(int) * (shs->gap_size + 1));
    if (shs->gap_sequence == NULL) {
      printf("Memory error.");
      exit(0);
    }
    shs->gap_size += 1;
    if (n <= 2) {
      shs->gap_sequence[shs->gap_size - 1] = 1;
      n = 1;
    } else {
      shs->gap_sequence[shs->gap_size - 1] =
          ((5 * n) - ((5 * n) % 11)) / 11; // floor division, get rid of decimal
      n = shs->gap_sequence[shs->gap_size - 1];
    }
  }
}

void shell_sort(int *numbers, ShellSort *shs) {
  gap_generate(shs);
  for (int step = 0; step < shs->gap_size; step++) {
    // printf("%d\n", shs->gap_sequence[step]);
    for (int i = shs->gap_sequence[step]; i < shs->arr_size; i++) {
      for (int j = i; j > shs->gap_sequence[step] - 1;
           j -= shs->gap_sequence[step]) {
        shs->comparisons += 1;
        if (numbers[j] < numbers[j - shs->gap_sequence[step]]) {
          // swap
          int temp = numbers[j];
          numbers[j] = numbers[j - shs->gap_sequence[step]];
          numbers[j - shs->gap_sequence[step]] = temp;
          shs->moves += 3;
        }
      }
    }
  }
  shs->gap_size = 0;
  free(shs->gap_sequence);
}
