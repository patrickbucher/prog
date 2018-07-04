// Calculates the mean of the n provided values.
double mean(double *values, int n);

// Calculates the standard deviation of the n provided values.
double standard_deviation(double *values, int n);

// Parses the double values from the argument array and returns them as a
// array with argc-1 elements of doubles. The first argument is ignored. If
// less than two arguments are provided, NULL is returned.
double *get_values(int argc, char *argv[]);
