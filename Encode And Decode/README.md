# Lempel-Ziv Compression

There are two programs in this assignment, encode and decode. The main functions for each program are in their respective .c files. The encode program encodes performs LZ78 compression on any text or binary files and decode program performs decompression. To run the program type 'make' in terminal followed by either './encode' or './decode' whichever program you wish to run. Both programs have command '-i' to get in a file you want either encode or decoded and '-o' to specify in which file you want the output to be in.

## word.c

Builds a word table and words for the decode program. The word table is used to store symbols and their codes. Also contains helper functions for the word table and word object.

## io.c

Deals with the input of files being read and outputs the encoded or decoded file depending on the program you run.

## encode.c

encodes the text or binary input it gets

## decode.c

decodes the text or binary input it gets

## trie.c

Builds a trie object which is used in encode program. Reads file and stores its symbol and code in trie connected with to its previous symbol trie node. Contains helper function for the trie as well.