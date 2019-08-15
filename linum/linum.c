// linum reads a text file and sends it to the standard output with
// right-aligned line numbers.

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	int c, line;
	bool print_line;

	line = 1;
	print_line = true;
	while ((c = getchar()) != EOF) {
		if (print_line) {
			printf("%4d ", line);
			print_line = false;
		}
		if (c == '\n') {
			print_line = true;
			line++;
		}
		putchar(c);
	}

	return 0;
}
