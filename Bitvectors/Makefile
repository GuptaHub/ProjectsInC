
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sequence

sequence: sequence.o sieve.o bv.o
	$(CC) -o sequence sequence.o sieve.o bv.o -lm


sequence.o: sequence.c
	$(CC) $(CFLAGS) -c sequence.c

sieve.o: sieve.c sieve.h
	$(CC) $(CFLAGS) -c sieve.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c
clean:
	rm -f sequence sequence.o sieve.o bv.o

infer: 
	make clean; infer-capture -- make; infer-analyze -- make

format: .clang-format
	clang-format -i -style=file *.c *.h

