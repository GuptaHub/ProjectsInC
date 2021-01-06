#include "stack.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void solve_stack(int n);
#define OPTIONS "srn:"
void solve_stack(int n);
// enum bool{True, False};
void toh(int n, char from, char using, char to, int *count);
int main(int argc, char *argv[]) {
  int x = 5;
  int c;
  bool recursive_call = false; // To check if these functions are called
  bool stack_call = false;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'n':
      x = atoi(optarg);
      if (sizeof(x) != 4) { // sizeof(int) is 4 and we want an int
        printf("Please give a number after command -n.\n");
        return 0;
      }
      break;

    case 'r':
      recursive_call = true;
      break;

    case 's':
      stack_call = true;
      break;
    }
    // toh(3, 'A', 'C', 'B');
  }
  // printing headers then calling the functions if their boolean values are
  // true
  if (stack_call == true) {
    printf("================================\n");
    printf("----------   STACKS   ----------\n");
    printf("================================\n");
    solve_stack(x); // The printing for moves is already done in the function
  }
  if (recursive_call == true) {
    int moves = 0;
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");
    toh(x, 'A', 'C', 'B', &moves);
    printf("\nNumber of moves: %d\n\n", moves);
  }
}

void solve_stack(int n) {
  int moves = 0; // calculates the moves

  Stack *peg_A = stack_create(n, 'A'); // Creating all stacks
  Stack *peg_B = stack_create(n, 'B');
  Stack *peg_C = stack_create(n, 'C');
  for (int i = n; i > 0; i--) {
    stack_push(peg_A, i); // Pushing all disks on peg A
  }
  if (n % 2 == 0) {          // The three move pattern is different for even and
                             // odd disks.
    while (peg_B->top < n) { // Loop until
      if (moves % 3 == 0) {  // if first in pattern 3 do the following
        // Checks if one of the pegs between C and A are empty or if one disk
        // is smaller than other.Well explained on DESIGN.pdf
        if (stack_peek(peg_C) == -1 ||
            (stack_peek(peg_A) != -1 &&
             stack_peek(peg_A) < stack_peek(peg_C))) {
          stack_push(peg_C, stack_pop(peg_A));
          printf("Move disk %d from peg A to peg C\n", stack_peek(peg_C));
        } else if (stack_peek(peg_A) == -1 ||
                   (stack_peek(peg_C) != -1 &&
                    stack_peek(peg_A) > stack_peek(peg_C))) {
          stack_push(peg_A, stack_pop(peg_C));
          printf("Move disk %d from peg C to peg A\n", stack_peek(peg_A));
        }
      }
      // Checks if one of the pegs between B and A are empty or if one disk
      //        //is smaller than other.Well explained on DESIGN.pdf
      if (moves % 3 == 1) {
        if (stack_peek(peg_B) == -1 ||
            (stack_peek(peg_A) != -1 &&
             stack_peek(peg_A) < stack_peek(peg_B))) {
          stack_push(peg_B, stack_pop(peg_A));
          printf("Move disk %d from peg A to peg B\n", stack_peek(peg_B));
        } else if (stack_peek(peg_A) == -1 ||
                   (stack_peek(peg_B) != -1 &&
                    stack_peek(peg_A) > stack_peek(peg_B))) {
          stack_push(peg_A, stack_pop(peg_B));
          printf("Move disk %d from peg B to peg A\n", stack_peek(peg_A));
        }
      }
      // Checks if one of the pegs between C and B are empty or if one disk
      //        //is smaller than other.Well explained on DESIGN.pdf
      if (moves % 3 == 2) {
        if (stack_peek(peg_B) == -1 ||
            (stack_peek(peg_B) != -1 && stack_peek(peg_C) != -1 &&
             stack_peek(peg_C) < stack_peek(peg_B))) { // Moving C to B
          stack_push(peg_B, stack_pop(peg_C));
          printf("Move disk %d from peg C to peg B\n", stack_peek(peg_B));
        } else if (stack_peek(peg_C) == -1 ||
                   (stack_peek(peg_C) > stack_peek(peg_B))) {
          stack_push(peg_C, stack_pop(peg_B));
          printf("Move disk %d from peg B to peg C\n", stack_peek(peg_C));
        }
      }
      moves += 1;
    }
  } else {
    while (peg_B->top < n) {
      // Checks if one of the pegs between B and A are empty or if one disk
      //        //is smaller than other.Well explained on DESIGN.pdf
      if (moves % 3 == 0) {
        if (stack_peek(peg_B) == -1 ||
            (stack_peek(peg_A) != -1 &&
             stack_peek(peg_A) < stack_peek(peg_B))) {
          stack_push(peg_B, stack_pop(peg_A));
          printf("Move disk %d from peg A to peg B\n", stack_peek(peg_B));
        } else if (stack_peek(peg_A) == -1 ||
                   (stack_peek(peg_B) != -1 &&
                    stack_peek(peg_A) > stack_peek(peg_B))) {
          stack_push(peg_A, stack_pop(peg_B));
          printf("Move disk %d from peg B to peg A\n", stack_peek(peg_A));
        }
      }
      // Checks if one of the pegs between C and A are empty or if one disk
      //        //is smaller than other.Well explained on DESIGN.pdf
      if (moves % 3 == 1) {
        if (stack_peek(peg_C) == -1 ||
            (stack_peek(peg_A) != -1 &&
             stack_peek(peg_A) < stack_peek(peg_C))) {
          stack_push(peg_C, stack_pop(peg_A));
          printf("Move disk %d from peg A to peg C\n", stack_peek(peg_C));
        } else if (stack_peek(peg_A) == -1 ||
                   (stack_peek(peg_C) != -1 &&
                    stack_peek(peg_A) > stack_peek(peg_C))) {
          stack_push(peg_A, stack_pop(peg_C));
          printf("Move disk %d from peg C to peg A\n", stack_peek(peg_A));
        }
      }
      // Checks if one of the pegs between C and B are empty or if one disk
      //        //is smaller than other.Well explained on DESIGN.pdf
      if (moves % 3 == 2) {
        if (stack_peek(peg_C) == -1 ||
            (stack_peek(peg_C) != -1 && stack_peek(peg_B) != -1 &&
             stack_peek(peg_B) < stack_peek(peg_C))) { // Moving C to B
          stack_push(peg_C, stack_pop(peg_B));
          printf("Move disk %d from peg B to peg C\n", stack_peek(peg_C));
        } else if (stack_peek(peg_B) == -1 ||
                   (stack_peek(peg_B) > stack_peek(peg_C))) {
          stack_push(peg_B, stack_pop(peg_C));
          printf("Move disk %d from peg C to peg B\n", stack_peek(peg_B));
        }
      }
      moves += 1; // Increment moves for every loop
    }
  }
  printf("\nNumber of moves: %d\n\n", moves);
  stack_delete(peg_C);
  stack_delete(peg_B);
  stack_delete(peg_A);
}
void toh(int n, char from, char using, char to, int *count) {
  if (n == 1) {
    *count += 1; // Increment the value where the move count is stored.
    printf("Move disk 1 from peg %c to peg %c\n", from, to);

  } else {
    toh(n - 1, from, to, using, count); // Move n-1 from peg A to C
    printf("Move disk %d from peg %c to peg %c\n", n, from, to); // Move to aux
    *count += 1;
    toh(n - 1, using, from, to, count); // Move n-1 from peg C to B
  }
}
