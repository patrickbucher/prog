#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int random_number(int, int);
int *random_numbers(int, int, int);
bool is_sorted(int *, int);

#define SIZE 10
#define MIN 1
#define MAX 1000

int main()
{
    int *numbers, i;

    int sorted[] = {1, 2, 3, 4, 5}, sorted_size;
    sorted_size = (int)(sizeof(sorted) / sizeof(int));

    srand((unsigned int)time(NULL));

    printf("%s\n", is_sorted(sorted, sorted_size) ? "true" : "false");
    printf("%s\n", is_sorted(numbers, SIZE) ? "true" : "false");

    return 0;
}

bool is_sorted(int *numbers, int n) {
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

int *random_numbers(int n, int min_in, int max_ex)
{
    int *numbers, i;
    
    numbers = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        numbers[i] = random_number(min_in, max_ex);
    }

    return numbers;
}

int random_number(int min_in, int max_ex)
{
    return rand() % (max_ex - min_in) + min_in;
}
