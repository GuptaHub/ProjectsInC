//
//  main.c
//  Assignment4
//
//  Created by Sahil Gupta on 11/4/20.
//  Copyright © 2020 Sahil Gupta. All rights reserved.
//

#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define OPTIONS "spn:"
void check_prime_kind(BitVector *b);
void check_palindrome(BitVector *b);
char *itoa(int num, char *str, int base);
void print_palindrome(int base, int *base_array, int count);
int main(int argc, char *argv[]) {
  // insert code here...
  int c;
  int n = 1000;
  bool prime = false;      // becomes true if -p is one of the commands
  bool palindrome = false; // becomes true if -s is one of the commands
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'n':
      n = atoi(optarg); // convert to num
      break;
    case 's':
      prime = true;
      break;
    case 'p':
      palindrome = true;
      break;
    default:
      break;
    }
  }
  BitVector *b = bv_create(n);
  sieve(b);
  if (prime) {
    check_prime_kind(b);
  }
  if (palindrome) {
    check_palindrome(b);
  }
  // check_prime_kind(b);
  // check_palindrome(b);
  bv_delete(b);
  return 0;
}

void check_prime_kind(BitVector *b) {
  int mersene_counter =
      0; // used to keep track of where values in mersenne_num are
  int fiboanaci_num[2] = {0, 1}; // will keep track of last two fibonacci
                                 // numbers that have been added upto

  int stor = 0; // Storage for lucas and  maybe others
  int lucas_num[2] = {2, 1};

  int *mersenne_num =
      (int *)calloc(mersene_counter,
                    sizeof(int)); // to avoid using too much space, it has
                                  // right now allocated no space but adds
                                  // space on every time prime number is found
  if (mersenne_num == NULL) {     // if you can't allocate more space, just quit
    printf("Cannot allocate space for mersenne in memory");
    exit(0);
  }
  int mersenne_loading_counter =
      0; // used to keep track of mersenne numbers that haven't been printed yet
  for (int i = 0; i < (int)b->length; i++) {
    // Check only the prime numbers
    if (bv_get_bit(b, i)) {
      printf("\n%d: prime", i);
      // Checking for mersenne first
      if (mersenne_num != NULL) {
        mersenne_num = (int *)realloc(
            mersenne_num,
            (mersene_counter + 1) * sizeof(int)); // on every prime add space
      }
      if (mersenne_num == NULL) { // quit if can't add more space
        free(mersenne_num);
        printf("Value too big for memory to keep track of for  mersenne.");
        exit(0);
      }
      mersenne_num[mersene_counter] = pow(2, i) - 1;
      mersene_counter += 1;
      if (mersenne_num[mersenne_loading_counter] == i) {
        printf(", mersenne");
        mersenne_loading_counter +=
            1; // point to next mersenne number that hasn't been printed
      }

      // Checking lucas second
      while (lucas_num[1] <= i) { // until the second number in lucas is bigger
                                  // or equal to prime index keep adding the two
                                  // in array
        if (lucas_num[1] == i || i == 2) {
          printf(", lucas");
        }
        // add the current two and store it at index 1, and stor the previous
        // number that was at index 1 to be at index 0.
        stor = lucas_num[1];
        lucas_num[1] = lucas_num[0] + lucas_num[1];
        lucas_num[0] = stor;
      }
      // Checking fibonacci last
      while (fiboanaci_num[1] <=
             i) { // More or less applying same logic as lucas
        if (fiboanaci_num[1] == i) {
          printf(", fibonacci");
        }
        stor = fiboanaci_num[1];
        fiboanaci_num[1] = fiboanaci_num[0] + fiboanaci_num[1];
        fiboanaci_num[0] = stor;
      }
    }
  }
  printf("\n");
  free(mersenne_num);
}
// A personal helping function used to check if the number with its base is
// palindrome or not.
bool isPalindrome(int num, int base) {
  // reverse the number in that base and check if that number is equal to num
  int i = num;
  int reversed_num = 0;
  while (i != 0) {
    reversed_num = (reversed_num * base) + i % base;
    i /= base;
  }
  return reversed_num == num;
}

void check_palindrome(BitVector *b) {
  // Allocating space for each base(2,9,10,18)
  int base_two_counter = 0;
  int *base_two = (int *)calloc(base_two_counter, sizeof(int));

  int base_nine_counter = 0;
  int *base_nine = (int *)calloc(base_nine_counter, sizeof(int));

  int base_ten_counter = 0;
  int *base_ten = (int *)calloc(base_ten_counter, sizeof(int));

  int base_seventeen_counter = 0;
  int *base_seventeen = (int *)calloc(base_seventeen_counter, sizeof(int));
  for (int i = 0; i < (int)b->length; i++) {
    if (bv_get_bit(b, i)) {
      // Checking Base 2. Reverse the number and check if they are equal.
      if (isPalindrome(i, 2)) {
        base_two =
            (int *)realloc(base_two, (base_two_counter + 1) * sizeof(int));
        if (base_two == NULL) {
          printf("ERROR: Memory allocation problem.");
          exit(0);
        }
        base_two[base_two_counter] = i;
        base_two_counter += 1;
      }
      // Checking Base 9.
      if (isPalindrome(i, 9)) {
        base_nine =
            (int *)realloc(base_nine, (base_nine_counter + 1) * sizeof(int));
        if (base_nine == NULL) {
          printf("Memory allocation problem. Quit");
          exit(0);
        }
        base_nine[base_nine_counter] = i;
        base_nine_counter += 1;
      }
      // Checking Base 10
      if (isPalindrome(i, 10)) {
        base_ten =
            (int *)realloc(base_ten, (base_ten_counter + 1) * sizeof(int));
        if (base_ten == NULL) {
          printf("Memory allocation problem. Quit");
          exit(0);
        }
        base_ten[base_ten_counter] = i;
        base_ten_counter += 1;
      }
      // Checking Base 17
      if (isPalindrome(i, 17)) {
        base_seventeen = (int *)realloc(
            base_seventeen, (base_seventeen_counter + 1) * sizeof(int));
        if (base_seventeen == NULL) {
          printf("Memory allocation problem. Quit");
          exit(0);
        }
        base_seventeen[base_seventeen_counter] = i;
        base_seventeen_counter += 1;
      }
    }
  }
  // Print the palindromes stored in their allocated space based on pdf format
  printf("Base %d\n", 2);
  printf("---- --\n");
  print_palindrome(2, base_two, base_two_counter);

  printf("\nBase %d\n", 9);
  printf("---- --\n");
  print_palindrome(9, base_nine, base_nine_counter);

  printf("\nBase %d\n", 10);
  printf("---- --\n");
  print_palindrome(10, base_ten, base_ten_counter);

  printf("\nBase %d\n", 17);
  printf("---- --\n");
  print_palindrome(17, base_seventeen, base_seventeen_counter);
  free(base_two);
  free(base_seventeen);
  free(base_nine);
  free(base_ten);
}
// printing the numbers in base array in their base representation
void print_palindrome(int base, int *base_array, int count) {
  char str[32] = ""; // This can be 32 because the int is 32 bits...
  for (int i = 0; i < count; i++) {
    printf("%d = %s\n", base_array[i], itoa(base_array[i], str, base));
    memset(str, 0, sizeof(str));
  }
}
// Convert the given num into a string of base representation of that num.
// Personal helper function
char *itoa(int num, char *str, int base) {
  char ans = 0;

  int str_index = 0;
  while (num > 0) {
    str[str_index] = num % base;
    str[str_index] =
        str[str_index] > 9 ? (str[str_index] - 10) + 'a' : str[str_index] + '0';
    str_index += 1;
    num /= base;
  }
  str_index -= 1;

  // reverse the string
  for (int i = 0; i <= str_index / 2; i++) {
    ans = str[str_index - i];
    str[str_index - i] = str[i];
    str[i] = ans;
  }
  return str;
}
