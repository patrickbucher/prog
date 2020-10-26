#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void shuffle(char **src, char **dst, int n)
{
    int r, w;

    for (w = 0; n > 0; n--) {
        r = rand() % n;
        dst[w++] = src[r];
        src[r] = src[n-1];
    }
}

int main(int argc, char *argv[])
{
    int i, l, n;
    char **src, **dst;

    n = argc - 1;
    if (n < 1) {
        return 0;
    }

    srand(time(NULL));

    src = (char**)malloc(sizeof(char*) * n);
    dst = (char**)malloc(sizeof(char*) * n);

    for (i = 0; i < n; i++) {
        l = strlen(argv[i+1]);
        src[i] = (char*)malloc(sizeof(char) * (l + 1));
        strncpy(src[i], argv[i+1], l);
        src[i][l] = '\0';
    }

    shuffle((void*)src, (void*)dst, n);

    for (i = 0; i < n; i++) {
        printf("%s ", dst[i]);
        free(dst[i]);
    }
    putchar('\n');

    free(src);
    free(dst);

    return 0;
}
