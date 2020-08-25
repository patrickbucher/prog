#include <ctype.h>
#include <stdio.h>

#include "buffer.h"

int main()
{
    buffer *buf = new_buffer(stdin, 5, 2);
    for (int c = next(buf); c != EOF; c = next(buf)) {
        switch (c) {
            case '"':
                if (isalnum(get(buf, +1))) {
                    printf("«");
                } else {
                    printf("»");
                }
                break;
            case '\'':
                if (isalnum(get(buf, +1)) && isalnum(get(buf, -1))) {
                    printf("’");
                } else if (isalnum(get(buf, +1))) {
                    printf("‹");
                } else if (isalnum(get(buf, -1)) || ispunct(get(buf, -1))) {
                    printf("›");
                } else {
                    putchar('\'');
                }
                break;
            case '.':
                if (get(buf, +1) == '.' && get(buf, +2) == '.') {
                    printf("…");
                    next(buf);
                    next(buf);
                }
                break;
            default:
                fputc(c, stdout);
        }
        fflush(stdout);
    }
    free_buffer(buf);
    return 0;
}
