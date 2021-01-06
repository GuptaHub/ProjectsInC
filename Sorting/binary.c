//
//  binary.c
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "binary.h"

BinaryInsertion *bI_create(int size) {
  BinaryInsertion *bi = (BinaryInsertion *)calloc(1, sizeof(BinaryInsertion));
  if (bi != NULL) {
    bi->arr_size = size;
    bi->comparisons = 0;
    bi->moves = 0;
  } else {
    printf("Memory problem for binary.\n");
    exit(0);
  }
  return bi;
}

void Binary_insertion(int *numbers, BinaryInsertion *bI) {
  for (int i = 1; i < bI->arr_size; i++) {
    int value = numbers[i];
    int left = 0;
    int right = i;

    while (left < right) {
      int mid = left + ((right - left) - ((right - left) % 2)) / 2; // floor
      bI->comparisons += 1;
      if (value >= numbers[mid]) {
        left = mid + 1;

      } else {
        right = mid;
      }
    }
    for (int j = i; j > left; j -= 1) {
      // swap
      int temp = numbers[j - 1];
      numbers[j - 1] = numbers[j];
      numbers[j] = temp;
      bI->moves += 3;
    }
  }
}
