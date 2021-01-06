# Bit Vectors And Primes

## Description

This is a program that uses bitvector with indexes upto 1000, or a given length by user, to imply whether their index is prime or not. If the index is prime, the bit at that index is 1 else it's zero. Using bitvectors to find prime, this program will either generate the list of prime numbers and whether they are also fibonacci prime, lucas prime, or mersenne prime, or they will generate numbers whose representation in base 2,9,10, and 18 is palindromic. To print a list of primes and prime types, give use command line argument '-s' and to print base 2,9,10, and 18 palindromic numbers use command line argument '-p'. To set a different amount of numbers to find prime or palindrome till, use '-n' and then type the new amount number.

**To run the program, type 'make' in terminal to compile the code followed by './sequence' and the command line arguments.**

*Note: typing 'make infer' might give an error. Ignore that error since it's a false positive. Infer cannot detect that all allocated memory was freed. Contrary to the error statement, the space that was allocated using malloc() is always reachable when printed. Plus, there are no memory leaks when running valgrind checkup and every memory allocation is followed by a condition that checks that the allocation was successful or not.*

## bv.c

Contains code for bitvector

## sequence.c

Contains code for the legit execution and printing.

## sieve.c

Contains code given from pdf

## Makefile

Contains commands to compile code in sequence, sieve, and bv.