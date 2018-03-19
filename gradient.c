#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double function_1(double x)
{
	return 0.01 * pow(x, 2) + 0.1 * x;
}


double function_2(double x[2])
{
	return pow(x[0], 2) + pow(x[1], 2);
}


void numerical_diff(double (*function)(double), int n, double x[n])
{
	double h = 1e-4;
	int i;
	for (i=0; i<n; i++) {
		x[i] = (function(x[i] + h) - function(x[i] - h)) / (h * 2.0);
	}
}


double *numeriacal_gradient(double (*function)(double *), int n, double x[n])
{
	double h = 1e-4;

	double *grad = malloc(sizeof(double) * n);
	if (grad == NULL) {
		fprintf(stderr, "failed to allocate memory\n");
		exit(1);
	}

	int i;
	for (i=0; i<n; i++) {
		
		double tmp_val = x[i];
		
		x[i] = tmp_val + h;
		double fxh1 = function(x);

		x[i] = tmp_val - h;
		double fxh2 = function(x);

		grad[i] = (fxh1 - fxh2) / (h * 2.0);
		x[i] = tmp_val;
	}

	return grad;
}


int main(void)
{
	// double x[] = {10};
	// numerical_diff(function_1, 1, x);
	// printf("%f\n", x[0]);
	
	double array[2] = {3.0, 4.0};
	double *p = numeriacal_gradient(function_2, 2, array);

	printf("array([%0.1f, %0.1f])\n", p[0], p[1]);

	free(p);

	return 0;
}