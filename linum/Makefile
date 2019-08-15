diet: linum.c
	diet gcc -static -Wpedantic -std=c99 $^ -o linum

linum: linum.c
	gcc -static -Wpedantic -std=c99 $^ -o $@

debug: linum.c
	gcc -g -Wpedantic -std=c99 $^ -o linum

clean:
	rm -r linum
