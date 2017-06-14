CC = musl-gcc
FLAGS = -Wpedantic -std=c99 -O3

all: sorting

sorting.o: sorting.c
	$(CC) $(FLAGS) -c sorting.c -o sorting.o

simple_sort.o: simple_sort.c
	$(CC) $(FLAGS) -c simple_sort.c -o simple_sort.o

sorting: sorting.o simple_sort.o
	$(CC) $(FLAGS) sorting.o simple_sort.o -o sorting

clean:
	rm -f sorting *.o
