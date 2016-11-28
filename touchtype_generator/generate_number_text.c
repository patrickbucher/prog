#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IP_LEN 18

int rand_int(int, int);
void rand_ip_addr(char *, int);
void fail(char *);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fail(argv[0]);
    }

    int lines = atoi(argv[1]);
    if (lines <= 0) {
        fail(argv[0]);
    }

    srand(time(NULL));
    char *ip = (char *)malloc(sizeof(char) * IP_LEN);

    for (int n = 0; n < lines; n++) {
        rand_ip_addr(ip, IP_LEN);
        printf("%s\n", ip);
    }

    return EXIT_SUCCESS;
}

void fail(char *prog)
{
    fprintf(stderr, "usage: %s [number of lines]\n", prog);
    exit(EXIT_FAILURE);
}

void rand_ip_addr(char *str, int size)
{
    if (size < IP_LEN) {
        return;
    }
    int w = 0;
    for (int n = 0; n < 4; n++) {
        char segment[4];
        snprintf(segment, 4, "%d", rand_int(0, 255));
        for (int r = 0; r < strlen(segment); r++) {
            str[w++] = segment[r];
        }
        if (n < 3) {
            str[w++] = '.';
        }
    }
    str[w] = '\0';
}

int rand_int(int min, int max)
{
   return rand() % (max - min + 1) + min; 
}
