CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o shell.o heap.o quick.o stats.o
	$(CC) -o sorting sorting.o insert.o shell.o heap.o quick.o stats.o $(LFLAGS)

mathlib-test.o: sorting.c sorting.h insert.c insert.h  shell.c shell.h heap.c heap.h quick.c quick.h stats.c stats.h set.h
	$(CC) $(CFLAGS) -c sorting.c insert.c shell.c heap.c quick.c stats.c

clean:
	rm -f sorting sorting.o insert.o shell.o heap.o quick.o stats.o

format:
	clang-format -i -style=file *.[ch]
