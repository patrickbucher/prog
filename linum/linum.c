// linum reads a text file and sends it to the standard output with
// right-aligned line numbers.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *numfmt(unsigned int);
unsigned int npos(unsigned int);
void alloc_fail(int);

int main(int argc, char *argv[])
{
	const int bufalloc = 1024;

	int *buf, bufp, c, nlines, line, bufsize, allocbytes, i;
	bool print_line;
	char *fmt;

	nlines = 0;
	allocbytes = sizeof(int) * bufalloc;
	buf = (int *)malloc(allocbytes);
	if (buf == NULL) {
		alloc_fail(allocbytes);
	}
	bufsize = bufalloc;
	for (bufp = 0; (c = getchar()) != EOF; bufp++) {
		if (bufp + 1 >= bufsize) {
			allocbytes = sizeof(int) * (bufsize + bufalloc);
			buf = realloc(buf, allocbytes);
			if (buf == NULL) {
				alloc_fail(allocbytes);
			}
			bufsize += bufalloc;
		}
		if (c == '\n') {
			nlines++;
		}
		buf[bufp] = c;
	}
	buf[bufp] = '\0';

	fmt = numfmt(nlines);
	line = 1;
	print_line = true;
	for (i = 0; i < bufp; i++) {
		if (print_line) {
			printf(fmt, line);
			print_line = false;
		}
		if (buf[i] == '\n') {
			print_line = true;
			line++;
		}
		putchar(buf[i]);
	}

	free(buf);
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
		alloc_fail(nbytes);
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

// alloc_fail prints an error message for nbytes that could not be allocated
// and exits the program.
void alloc_fail(int nbytes) {
	fprintf(stderr, "unable to allocate %d bytes\n", nbytes);
	exit(EXIT_FAILURE);
}
