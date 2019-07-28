#include <math.h>
#include <stdio.h>

double round_to(double x, double granularity)
{
	double factor = 1.0 / granularity;
	return round(x * factor) / factor; 
}

int main()
{
	printf("round %g by %g = %g\n", 13.94, 0.05, round_to(13.94, 0.05));
	printf("round %g by %g = %g\n", 13.94, 0.50, round_to(13.94, 0.50));
	printf("round %g by %g = %g\n", 13.74, 0.50, round_to(13.74, 0.50));
	printf("round %g by %g = %g\n", 13.74, 5.00, round_to(13.74, 5.00));

	return 0;
}
