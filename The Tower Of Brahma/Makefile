CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: tower

tower: tower.o stack.o
	$(CC) -o tower tower.o stack.o


tower.o: tower.c
	$(CC) $(CFLAGS) -c tower.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f tower tower.o stack.o

infer: 
	make clean; infer-capture -- make; infer-analyze -- make

format: .clang-format
	clang-format -i -style=file *.c *.h

