
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//
//// Constructor for a new Stack .
////
//// capacity : The maximum number of items the Stack can hold .
//// name : The Stack ’s single - character identifier .
////
Stack *stack_create(int capacity, char name) {
  Stack *s = (Stack *)malloc(sizeof(Stack)); //
  if (s != NULL) {
    s->top = 0;
    s->capacity = capacity;
    s->items = (int *)calloc(capacity, sizeof(int));
    s->name = name;
  } else {
    printf("ERROR WITH STACK");
  }
  return s;
}
//
//// Pushes an item into a Stack if it isn ’t full .
////
//// s: The Stack to push an item into .
////
void stack_push(Stack *s, int item) {
  if (s->top + 1 ==
      s->capacity) { // Checks if adding one more will push it to max
    s->capacity += 2;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
  }

  s->items[s->top] = item;
  s->top += 1;
  return;
}
// Inspired by Eugene's function
// SS
// Destructor for a Stack .
//
// s: The Stack to free allocated memory for .
void stack_delete(Stack *s) {
  free(s->items);
  s->items = NULL;
  free(s);
  return;
}

// Returns true if a Stack is empty and false otherwise .
// //
// // s: The Stack to query about being empty .
// //
bool stack_empty(Stack *s) { return s->top == 0; }
int stack_pop(Stack *s) {
  if (stack_empty(s)) {
    return -1; // Means the stack is empty
  }
  s->top -= 1;
  return s->items[s->top];
}
int stack_peek(Stack *s) {
  if (stack_empty(s)) {
    return -1;
  }
  return s->items[s->top - 1];
}
