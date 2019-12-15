CC=gcc
FLAGS=-Wpedantic -std=c99

.PHONY: clean

monty_hall: monty_hall.c
	$(CC) $(FLAGS) $^ -o $@

gprof_monty_hall: monty_hall.c
	$(CC) $(FLAGS) -pg $^ -o $@

profile: gprof_monty_hall
	./gprof_monty_hall 1000000
	gprof -l gprof_monty_hall gmon.out > profile
	rm -f gmon.out

clean:
	rm -f monty_hall gprof_monty_hall profile
