
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
CC = clang $(CFLAGS)
OBJECTS = hatterspeak.o speck.o bv.o bf.o ll.o hash.o parser.o regex_fill.o

EXECBIN = hatterspeak

all:$(EXECBIN)

$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)

speck.o: speck.c speck.h
	$(CC) $(CFLAGS) -c speck.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c

bf.o:bf.c bf.h
	$(CC) $(CFLAGS) -c bf.c

ll.o: ll.c ll.h
	$(CC) $(CFLAGS) -c ll.c

hash.o:hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c
regex_fill.o: regex_fill.c regex_fill.h
	$(CC) $(CFLAGS) -c regex_fill.c

clean: 
	rm -f hatterspeak hatterspeak.o hash.o bf.o bv.o ll.o speck.o parser.o regex_fill.o
infer:
	make clean; infer-capture -- make; infer-analyze -- make

