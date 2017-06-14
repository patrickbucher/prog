#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "simple_sort.h"

bool is_sorted(int *, int);

int *random_numbers(int, int, int);
int random_number(int, int);

#define SIZE 30000
#define MIN 1
#define MAX 100000

int main()
{
    int *numbers, i;
    int *bubble, *insertion, *selection;
    size_t size;
    clock_t start, end;
    double bubble_diff, insertion_diff, selection_diff;;

    srand((unsigned int)time(NULL));

    // create a random array and three copies of it
    numbers = random_numbers(SIZE, MIN, MAX);
    size = sizeof(int) * SIZE;
    bubble = (int *)malloc(size);
    insertion = (int *)malloc(size);
    selection = (int *)malloc(size);
    for (i = 0; i < SIZE; i++) {
        bubble[i] = insertion[i] = selection[i] = numbers[i];
    }

    // bubble sort
    start = clock();
    bubble_sort(bubble, SIZE);
    end = clock();
    if (!is_sorted(bubble, SIZE)) {
        fprintf(stderr, "bubble sort failed\n");
        exit(EXIT_FAILURE);
    }
    bubble_diff = 1000 * (double)(end - start) / CLOCKS_PER_SEC;

    // insertion sort
    start = clock();
    insertion_sort(insertion, SIZE);
    end = clock();
    if (!is_sorted(insertion, SIZE)) {
        fprintf(stderr, "insertion sort failed\n");
        exit(EXIT_FAILURE);
    }
    insertion_diff = 1000 * (double)(end - start) / CLOCKS_PER_SEC;

    // selection sort
    start = clock();
    selection_sort(selection, SIZE);
    end = clock();
    if (!is_sorted(selection, SIZE)) {
        fprintf(stderr, "selection sort failed\n");
        exit(EXIT_FAILURE);
    }
    selection_diff = 1000 * (double)(end - start) / CLOCKS_PER_SEC;

    printf("Bubble  Insertion Selection\n");
    printf("%4.0fms %8.0fms   %5.0fms\n",
        bubble_diff, insertion_diff, selection_diff);

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
