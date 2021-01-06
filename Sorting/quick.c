//
//  quick.c
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "quick.h"
#include <stdbool.h>

QuickSort *qs_create(int size) {
  QuickSort *qs = (QuickSort *)calloc(1, sizeof(QuickSort));
  if (qs != NULL) {
    qs->arr_size = size;
    qs->comparisons = 0;
    qs->moves = 0;
  } else {
    printf("Memory problem with quicksort.\n");
    exit(0);
  }
  return qs;
}
int Partition(int right, int left, int *numbers, QuickSort *qs) {
  int pivot = numbers[left];
  int lo = left + 1;
  int hi = right;

  while (true) {
    while (lo <= hi) {
      if (numbers[hi] >= pivot) {
        qs->comparisons += 1;
        hi -= 1;
      } else {
        qs->comparisons += 1; // You still compared to get to else
        break;
      }
    }
    while (lo <= hi) {
      if (numbers[lo] <= pivot) {
        qs->comparisons += 1;
        lo += 1;
      } else {
        qs->comparisons += 1;
        break;
      }
    }
    if (lo <= hi) {
      int temp = numbers[lo];
      numbers[lo] = numbers[hi];
      numbers[hi] = temp;
      qs->moves += 3;
    } else {
      break;
    }
  }
  int temp = numbers[left];
  numbers[left] = numbers[hi];
  numbers[hi] = temp;
  qs->moves += 3;
  return hi;
}

void Quick_sort(int *numbers, int size, int right, int left, QuickSort *qs) {
  if (left < right) {
    int index = Partition(right, left, numbers, qs);
    Quick_sort(numbers, size, index - 1, left, qs);
    Quick_sort(numbers, size, right, index + 1, qs);
  }
}
