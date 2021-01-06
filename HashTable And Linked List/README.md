# Down the Rabbit Hole and Through the Looking Glass: Bloom Filters, Hashing, and the Red Queen’s Decrees

## Description

This is a program that uses hash tables and linked lists to detect words that you want banned. The banned words are in hatterspeak.txt and oldspeak.txt. The words from those two files are used to fill the hash table. Based on your input words, the program prompts a message whether your words were forbidden words and how severe your breach is. The command '-s' is provide statistics of the table and list, '-h' and '-f' allow you to change the size of hash table and bloom filter, and '-m' is whether you want to apply move to front rule. 

**To run the program, type 'make' in terminal followed by './hatterspeak' then type the words you want to see if include any forbidden words.**

*Note: typing command make infer might prompt memory leaks in regex_fill.c where the table gets filled. This error is to be ignored since the allocated data in functions of regex_fill.c are always reachable through hash table functions and get freed in the end when we delete the hash table. This can proven by the fact that valgrind does not give any memory leaks and prompts that all allocations were freed.*

## hatterspeak.c

This is the c file that produces the program executable. Deals with command inputs and calls functions in other files.

## regex_fill.c

This is the C file with functions used to fill the hash table with nodes of words from oldspeak.txt and hatterspeak.txt

## parser.c

Provided by Max Dunne.

## ll.c

Includes all the constructor as well as all the helper functions for a linked node and linked list. 

## hash.c

Includes the constructor and all the helper functions for the hash table. Constantly refers to functions in ll_c from its own from functions.

## speck.c

Given by the professor. Used to get the index to include a word in the hash table. 