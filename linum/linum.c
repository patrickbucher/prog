// linum reads a text file and sends it to the standard output with
// right-aligned line numbers.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *numfmt(unsigned int);
unsigned int npos(unsigned int);

int main(int argc, char *argv[])
{
	int c, line;
	bool print_line;
	char *fmt;

	// TODO: read whole file in buffer, count lines, then process buffer
	fmt = numfmt(99);

	line = 1;
	print_line = true;
	while ((c = getchar()) != EOF) {
		if (print_line) {
			printf(fmt, line);
			print_line = false;
		}
		if (c == '\n') {
			print_line = true;
			line++;
		}
		putchar(c);
	}
	free(fmt);

	return 0;
}

// numfmt returns a format string to print the line numbers for nlines
// right-aligned with minimal width.
// Example: numfmt(4321) -> "%4d ", numfmt(21) -> "%2d "
char *numfmt(unsigned int nlines) {
	int cols = 0;
	int cols_bytes = 0;
	char *fmt = NULL;
	int nbytes = 4; // '%', 'd', ' ', '\0'

	cols = npos(nlines);
	cols_bytes = npos(cols); // "%10d " needs one byte more than "%5d "
	nbytes += cols_bytes;

	fmt = (char *)malloc(sizeof(char) * nbytes);
	if (fmt == NULL) {
		fprintf(stderr, "unable to allocate %d bytes\n", nbytes);
		exit(EXIT_FAILURE);
	}
	snprintf(fmt, nbytes, "%%%dd ", cols);

	return fmt;
}

// npos returns the number of positions needed to display the number n.
// Example: npos(1234) -> 4, npos(0) -> 1, npos(654321) -> 6
unsigned int npos(unsigned int n) {
	int pos = 0;

	do {
		n /= 10;
		pos++;
	} while (n > 0);

	return pos;
}
