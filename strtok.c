#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *line = (char *)malloc(sizeof(char) * 100);
    memset(line, 0, sizeof(char));
    strncpy(line, argv[1], sizeof(char) * 100);

    const char *delim = argv[2];
    char *str = NULL;
    for (str = strtok(line, delim); str != NULL; str = strtok(NULL, delim)) {
        printf("%s\n", str);
    }

    return 0;
}
