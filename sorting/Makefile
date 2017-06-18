CC = gcc
FLAGS = -Wpedantic -std=c99 -g

all: sorting

sorting.o: sorting.c
	$(CC) $(FLAGS) -c sorting.c -o sorting.o

simple_sort.o: simple_sort.c
	$(CC) $(FLAGS) -c simple_sort.c -o simple_sort.o

sort_utils.o: sort_utils.c
	$(CC) $(FLAGS) -c sort_utils.c -o sort_utils.o

sorting: sorting.o simple_sort.o sort_utils.o
	$(CC) $(FLAGS) sorting.o simple_sort.o sort_utils.o -o sorting

clean:
	rm -f sorting *.o
