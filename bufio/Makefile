main: main.o bufio.o
	cc main.o bufio.o -o main

main.o: main.c
	cc -c main.c -o main.o

bufio.o: bufio.h bufio.c
	cc -c bufio.c -o bufio.o

clean:
	rm -f *.o main
