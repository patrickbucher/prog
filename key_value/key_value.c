#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct key_value *parse(char *);

struct key_value {
    char *key;
    int value;
};

int
main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s key1=value1[, key2=value2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (i = 1; i < argc; i++) {
        struct key_value *kv = parse(argv[i]);
        printf("key: %s, value: %d\n", kv->key, kv->value);
    }

    return EXIT_SUCCESS;
}

struct key_value
*parse(char *str)
{
    struct key_value *kv;
    int i, len, sign;
    
    kv = (struct key_value *)malloc(sizeof(struct key_value));
    len = strlen(str);
    kv->key = (char *)malloc(sizeof(char) * len);

    for (i = 0; i < len && str[i] != '=' && str[i] != '\0'; i++) {
        kv->key[i] = str[i];
    }
    kv->key[i++] = '\0';

    kv->value = 0;
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else {
        sign = 1;
    }
    for (; str[i] != '\0' && str[i] >= '0' && str[i] <= '9'; i++) { 
        kv->value *= 10;
        kv->value += str[i] - '0';
    }
    kv->value *= sign;

    return kv;
}
