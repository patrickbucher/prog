#include <stdbool.h>
#include <stdlib.h>

#include "sort_utils.h"

bool is_sorted(int *numbers, int n)
{
    int i, last, current;

    last = *numbers;
    for (i = 1; i < n; i++) {
        numbers++;
        current = *numbers;
        if (last > current) {
            return false;
        }
        last = current;
    }

    return true;
}

/*@null@*/
int *random_numbers(int n, int min_in, int max_ex)
{
    int *numbers, i;
    
    numbers = (int*)malloc(sizeof(int) * n);
    if (numbers == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        numbers[i] = random_number(min_in, max_ex);
    }

    return numbers;
}

int random_number(int min_in, int max_ex)
{
    return rand() % (max_ex - min_in) + min_in;
}
