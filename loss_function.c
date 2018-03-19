#include <stdio.h>
#include "./loss_function.h"


int main(void)
{
	double t[10] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
	double y[10] = {0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0};
	double mse = mean_squared_error(10, y, t);
	double cee = cross_entropy_error(10, y, t);

	printf("mse: %f\n", mse);
	printf("cee: %f\n", cee);
	return 0;
}