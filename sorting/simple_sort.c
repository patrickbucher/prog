#include <stdio.h>
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

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (numbers[j] < numbers[i]) {
                swap(numbers, i, j);
            }
        }
    }
}

void insertion_sort(int *numbers, int n)
{
    // TODO implement properly
    bubble_sort(numbers, n);
}

void selection_sort(int *numbers, int n)
{
    // TODO implement properly
    bubble_sort(numbers, n);
}
