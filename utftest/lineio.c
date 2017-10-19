#include <stdlib.h>
#include <stdio.h>

#define NALLOC 5

int main()
{
    int *line, i, c, f, eof;

    eof = 0;
    do {
        line = (int *)calloc(NALLOC + 1, sizeof(int));
        f = NALLOC;
        i = 0;
        c = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (f == 0) {
                line = realloc(line, (i + NALLOC + 1) * sizeof(int));
                f = NALLOC;
            }
            line[i++] = c;
            f--;
        } 
        line[i] = 0;
        for (i = 0; line[i] != 0; i++) {
            putchar(line[i]);
        }
        free(line);
        if (c == EOF) {
            break;
        } else {
            putchar('\n');
        }
    } while (1);
    return 0;
}
