#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "simple_sort.h"
#include "sort_utils.h"

#define SIZE 10000
#define MIN 1
#define MAX 100000

int main()
{
    int *numbers, i;
    int *bubble, *insertion, *selection;
    size_t size;
    clock_t start, end;
    double bubble_diff, insertion_diff, selection_diff;

    srand((unsigned int)time(NULL));

    // create a random array and three copies of it
    numbers = random_numbers(SIZE, MIN, MAX);
    if (numbers == NULL) {
        fprintf(stderr, "cannot allocated %d numbers\n", SIZE);
        exit(EXIT_FAILURE);
    }
    size = sizeof(int) * SIZE;
    bubble = (int *)malloc(size);
    insertion = (int *)malloc(size);
    selection = (int *)malloc(size);
    if (bubble == NULL || insertion == NULL || selection == NULL) {
        fprintf(stderr, "cannot allocated %d numbers\n", SIZE);
        exit(EXIT_FAILURE);
    }
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

    free(numbers);
    free(bubble);
    free(insertion);
    free(selection);

    return 0;
}
