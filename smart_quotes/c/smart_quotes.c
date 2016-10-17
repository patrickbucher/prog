#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOOKAHEAD 3
int buf[LOOKAHEAD];
int buf_i;
bool buf_finished;

int buf_getchar();
void buf_discard(int);
char *buf_next(int);

int main()
{
    int c, last;

    memset(buf, 0, sizeof(buf));
    buf_i = 0;
    buf_finished = false;

    last = 0;
    while ((c = buf_getchar()) != EOF) {
        if (c == '.') {
            // ... -> …
            if (strncmp("..", buf_next(2), 2) == 0) {
                printf("…");
                buf_discard(2);
            } else {
                putchar(c);
            }
        } else if (c == '"') {
            // "…" -> «…»
            if (isspace(last) || last == 0) {
                printf("«");
            } else {
                printf("»");
            }
        } else if (c == '\'') {
            // '…' -> ‹…›
            if (isspace(last) || last == '"' || last == 0) {
                printf("‹");
            } else if (isalnum(last)) {
                // don't -> don’t
                printf("’");
            } else {
                printf("›");
            }
        } else if (c == '-') {
            // -- -> ‒
            if (strncmp("-", buf_next(1), 1) == 0) {
                printf("‒");
                buf_discard(1);
            } else {
                putchar(c);
            }
        } else {
            putchar(c);
        }
        last = c;
    }

    return 0;
}

char *buf_next(int n)
{
    int i;
    char *str = (char*)malloc(sizeof(char) * n);
    for (i = 0; i < n; i++) {
        str[i] = (i < buf_i) ? buf[i] : 0;
    }
    return str;
}

void buf_discard(int n)
{
    int i;

    while (n--) {
        for (i = 0; i < LOOKAHEAD - 1; i++) {
            buf[i] = buf[i + 1];
        }
        buf[i] = 0;
        buf_i--;
    }
}

int buf_getchar()
{
    int c;

    if (buf_finished && buf_i) {
        c = buf[0];
        buf_discard(1);
        return c;
    } else {
        do {
            c = getchar();
            buf[buf_i++] = c;
            buf_finished = (c == '\n' || c == EOF);
        } while (!buf_finished && buf_i < LOOKAHEAD);
    }
    c = buf[0];
    buf_discard(1);
    return c;
}
