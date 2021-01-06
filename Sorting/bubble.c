//
//  bubble.c
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "bubble.h"

BubbleSort *bubble_create(int size) {
  BubbleSort *b_sort = (BubbleSort *)calloc(1, sizeof(BubbleSort));
  if (b_sort != NULL) {
    b_sort->arr_size = size;
    b_sort->comparisons = 0;
    b_sort->moves = 0;
  } else {
    printf("Memory allocation problem.");
    exit(0);
  }
  return b_sort;
}

void bubble_sort(int *numbers, BubbleSort *bs) {
  for (int i = 0; i < bs->arr_size; i++) {
    for (int x = bs->arr_size - 1; x > i; x--) {
      bs->comparisons += 1;
      if (numbers[x] < numbers[x - 1]) {
        // swap
        bs->moves += 3;
        int temp = numbers[x];
        numbers[x] = numbers[x - 1];
        numbers[x - 1] = temp;
      }
    }
  }
}
