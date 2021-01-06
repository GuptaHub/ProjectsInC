# The Tower Of Brahma

## Description

This is a program that solves the puzzle of tower of hanoi using two methods, using dynamically allocated memory for stacks and recursively printing the moves needed to solve the puzzle. Except, unlike in the original puzzle, this program gets all disks from peg A to peg B instead to peg C. The program can take three types of command line arguments, 'n' followed by a number to set the number of disks you want moves for, 'r' to run recursive solution, and 's' to run the stack solution. If there no 'n' command and only 'r' or 's' command are given, then it prints moves for 5 disks as default. 

**To run the program, type 'make' in terminal then './tower' followed by command line arguments**

*Note: typing 'make clean' will delete all the .o files created when running the C file. When you type 'make infer' there will be an error about Null deference in stack_push() method in stack.c, meaning we items of a stack could be null when trying to push an item to one. This error should be ignored because the items only equal NULL when they get deleted and once they get deleted they are never accessed to push or pop.*

## tower.c

This C file has the source code that deals with the command line arguments and actually solves the function by creating Stacks or printing using recursion.

## stack.c

This C file defines all the functions listed on stack.h. The stack object can use any of these function.

## stack.h 

This file was given by the lab. It has the declaration of structure Stack and its functions.

## Makefile

This is the file with commands that compile the code in tower.c. Type "make" in terminal to run these commands.

## DESIGN.pdf

This file contains the pseucode and the structure of the entire program. It also explains the patterns and arithimetic. Refer to this file if you want to know the logic behind the code.

## WRITEUP.pdf

This document compares the efficiency between the recursive and the stack solution used to solve the puzzle. 