#include <math.h>
#include <stdlib.h>

#include "stat.h"

double mean(double *values, int n)
{
    int i;
    double sum;

    sum = 0.0;
    for (i = 0; i < n; i++) {
        sum += values[i];
    }

    return sum / n;
}

double standard_deviation(double *values, int n)
{
    double m, numerator;
    int i;

    m = mean(values, n);

    numerator = 0.0;
    for (i = 0; i < n; i++) {
        numerator += pow(values[i] - m, 2.0);
    }

    // FIXME is this correct?
    return sqrt(numerator / n);
}

double *get_values(int argc, char *argv[])
{
    double *values;
    int n_inputs, i;

    if (argc < 2) {
        return NULL;
    }

    n_inputs = argc - 1;
    values = (double*)malloc(sizeof(double) * n_inputs);
    for (i = 0; i < n_inputs; i++) {
        values[i] = atof(argv[i+1]);
    }

    return values;
}
