#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stat.h"

int main(int argc, char *argv[])
{
    double *inputs, result;

    if (argc < 2) {
        printf("usage: %s [numbers]\n", argv[0]);
        return EXIT_FAILURE;
    }

    inputs = get_values(argc, argv);
    if (inputs == NULL) {
        fprintf(stderr, "invalid inputs\n");
        return EXIT_FAILURE;
    }

    result = standard_deviation(inputs, argc - 1);
    printf("%.3f\n", result);

    return EXIT_SUCCESS;
}
