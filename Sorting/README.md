# Sorting

## Description

This is a program that uses shell sort, bubble sort, quick sort, and binary insertion sort seperately on same data. The # of moves and comparisons each sorts makes are calculated and compared to see which is the most efficient. '-s' runs shell sort, '-b' bubble sort, '-q' for quick sort, '-i' for binary insertion sort.

*To run the program type make in terminal followeed by "./sorting", followed by a command argument to specify which sort to run*

*** Note: typing make infer might prompt an error calling there might be a memory leak. Ignore the error since using valgrind check, it's been confirmed there are no memory allocations that do not get freed. And unlike the claim in the error, the pointer is constantly reachable since it's realloced at the same place***

## Bubble.c

Contains code for bubble sort

## sorting.c

Contains code that deals with calling on sorts and printing them.

## quick.c

Contains code for quick sort.

## binary.c

Contains code for binary insertion sort.

## shell.c

Contains code for shell sort.

## Makefile

Contains commands to compile code in sorting.c