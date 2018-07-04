CC=gcc
CFLAGS=-Wpedantic --std=c99

all: sd mean

mean: mean.o stat.o
	$(CC) $(CFLAGS) -lm mean.o stat.o -o mean

sd: sd.o stat.o
	$(CC) $(CFLAGS) -lm sd.o stat.o -o sd

mean.o: mean.c
	$(CC) $(CFLAGS) -c mean.c -o mean.o

sd.o: sd.c
	$(CC) $(CFLAGS) -c sd.c -o sd.o

stat.o: stat.h stat.c
	$(CC) $(CFLAGS) -c stat.c -o stat.o

clean:
	rm -f sd mean
