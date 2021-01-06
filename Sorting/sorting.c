//
//  main.c
//  Assignment5
//
//  Created by Sahil Gupta on 11/12/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//
#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_number(int *numbers, int *messy_num, int print_count, int size);
int main(int argc, char *argv[]) {
  // insert code here...
  int c;
  // Bubble
  int size = 100;
  int print_count = 100;
  int s = 8222022;
  // int *numbers = (int *)calloc(size, sizeof(int));
  // int *messy_num = (int *)calloc(size, sizeof(int));

  bool bubble_called = false;
  bool shell_called = false;
  bool binary_called = false;
  bool quick_called = false;
  while ((c = getopt(argc, argv, "Absqip:r:n:")) != -1) {
    switch (c) {
    case 'b':
      bubble_called = true;
      break;
    case 's':
      shell_called = true;
      break;
    case 'q':
      quick_called = true;
      break;
    case 'i':
      binary_called = true;
      break;
    case 'p':
      print_count = atoi(optarg);
      break;
    case 'r':
      s = atoi(optarg);
      break;
    case 'n':
      size = atoi(optarg);
      break;
    case 'A':
      bubble_called = true;
      shell_called = true;
      binary_called = true;
      quick_called = true;
      break;
    default:
      break;
    }
  }
  if (print_count > size) {
    print_count = size;
  }
  int *numbers = (int *)calloc(size, sizeof(int));
  int *messy_num = (int *)calloc(size, sizeof(int));
  if (numbers == NULL || messy_num == NULL) {
    printf("Couldn't allocate memory for numbers");
    exit(0);
  }
  // initialize random numbers
  uint32_t mask = 1073741823;
  srand(s);
  for (int i = 0; i < size; i++) {
    numbers[i] = rand() & mask;
    messy_num[i] = numbers[i];
  }
  // Binary_insertion
  if (binary_called) {
    BinaryInsertion *binary_sort = bI_create(size);
    Binary_insertion(numbers, binary_sort);
    printf("Binary Insertion Sort\n");
    printf("%d elements, %d moves, %d compares\n", size, binary_sort->moves,
           binary_sort->comparisons);
    print_number(numbers, messy_num, print_count, size);
    free(binary_sort);
  }
  if (quick_called) {
    QuickSort *qs = qs_create(size);
    Quick_sort(numbers, size, size - 1, 0, qs);
    printf("Quick Sort\n");
    printf("%d elements, %d moves, %d compares\n", size, qs->moves,
           qs->comparisons);
    print_number(numbers, messy_num, print_count, size);
    free(qs);
  }
  if (shell_called) {
    ShellSort *shs = shell_create(size);
    shell_sort(numbers, shs);
    printf("Shell Sort\n");
    printf("%d elements, %d moves, %d compares\n", size, shs->moves,
           shs->comparisons);
    print_number(numbers, messy_num, print_count, size);
    free(shs);
  }
  if (bubble_called) {
    BubbleSort *bubble = bubble_create(size);
    bubble_sort(numbers, bubble);

    printf("Bubble Sort\n");
    printf("%d elements, %d moves, %d compares\n", size, bubble->moves,
           bubble->comparisons);
    print_number(numbers, messy_num, print_count, size);
    free(bubble);
  }

  //    ShellSort *shs = shell_create(size);
  //    shell_sort(numbers, shs);
  //    printf("%d\n\n", shs->moves);

  //    BinaryInsertion *binary_sort = bI_create(size);
  //    Binary_insertion(numbers, binary_sort);
  //    printf("%d\n\n", binary_sort->moves);

  //    QuickSort *qs = qs_create(size);
  //    Quick_sort(numbers, size, size-1, 0, qs);
  //    printf("%d\n\n", qs->comparisons);
  // print_count first 10 numbers for now

  free(numbers);
  free(messy_num);
  return 0;
}

void print_number(int *numbers, int *messy_num, int print_count, int size) {
  for (int x = 0; x < print_count; x++) {

    if (x % 7 == 0 && x != 0) {
      printf("\n");
    }
    printf("%13" PRIu32, numbers[x]);

    numbers[x] = messy_num[x];
  }
  // Setting the values back to what they used to be when they were intialized.
  for (int i = print_count; i < size; i++) {
    numbers[i] = messy_num[i];
  }
  printf("\n");
}
