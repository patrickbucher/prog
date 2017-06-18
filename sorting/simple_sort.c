#include <stdbool.h>

#include "simple_sort.h"

void swap(int *numbers, int a, int b)
{
    int tmp;

    tmp = numbers[a];
    numbers[a] = numbers[b];
    numbers[b] = tmp;
}

void bubble_sort(int *numbers, int n)
{
    int i, j;
    bool sorted = false;

    for (i = 0; !sorted && i < n; i++) {
        sorted = true;
        for (j = 0; j < n; j++) {
            if (numbers[i] < numbers[j]) {
                swap(numbers, i, j);
                sorted = false;
            }
        }
    }
}

void insertion_sort(int *numbers, int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j > 0 && numbers[j] < numbers[j - 1]; j--) {
            swap(numbers, j, j - 1);
        }
    }
}

void selection_sort(int *numbers, int n)
{
    int i, j, min_i;

    for (i = 0; i < n; i++) {
        min_i = i;
        for (j = i + 1; j < n; j++) {
            if (numbers[j] < numbers[min_i]) {
                min_i = j;
            }
        }
        if (i != min_i) {
            swap(numbers, i, min_i);
        }
    }
}
