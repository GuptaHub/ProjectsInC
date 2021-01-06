CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
CC = clang $(CFLAGS)
OBJECTS = encode.o io.o word.o trie.o code.o decode.o

all:encode decode

encode: encode.o io.o word.o trie.o code.o
	$(CC) -o encode encode.o io.o word.o trie.o code.o

decode: decode.o io.o word.o trie.o code.o
	$(CC) -o decode decode.o io.o word.o trie.o code.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

word.o: word.c word.h
	$(CC) $(CFLAGS) -c word.c

trie.o:trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

code.o: code.c code.h
	$(CC) $(CFLAGS) -c code.c


clean: 
	rm -f encode encode.o io.o word.o trie.o code.o decode decode.o
infer:
	make clean; infer-capture -- make; infer-analyze -- make
