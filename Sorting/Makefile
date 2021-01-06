CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all:sorting

sorting: sorting.o bubble.o shell.o binary.o quick.o
	$(CC) -o sorting sorting.o shell.o binary.o quick.o bubble.o
sorting.o: sorting.c 
	$(CC) $(CFLAGS) -c sorting.c
bubble.o: bubble.c bubble.h
	$(CC) $(CFLAGS) -c bubble.c
shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c
binary.o: binary.c binary.h
	$(CC) $(CFLAGS) -c binary.c
quick.o: quick.c quick.h
	$(CC) $(CFLAGS) -c quick.c 
clean:
	rm -f sorting sorting.o bubble.o shell.o binary.o quick.o
infer:
	make clean; infer-capture -- make; infer-analyze -- make
format: .clang-format
	clang-format -i -style=file *.c *.h 

