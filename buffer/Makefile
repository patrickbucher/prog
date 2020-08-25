CC = gcc
FLAGS = -Wall -std=c99

.PHONY: all clean

all: demo

demo: demo.o buffer.o
	$(CC) $(CFLAGS) $^ -o $@

*.o: *.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o demo
