#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void check_malloc(double *p) {
	if (p == NULL) {
		fprintf(stderr, "failed to allocate memory\n");
		exit(1);
	}
}


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


// need free(grad) in caller
double *numeriacal_gradient(double (*function)(double *), int n, double x[n])
{
	double h = 1e-4;

	double *grad = malloc(sizeof(double) * n);
	check_malloc(grad);

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


// need free(x) in caller
double *gradient_descent(double (*function)(double *), int n, double init_x[n], double lr, int step_num)
{
	double *x = malloc(sizeof(double) * n);
	check_malloc(x);

	int i;
	for (i=0; i<n; i++) x[i] = init_x[i];

	for (i=0; i<step_num; i++) {
		printf("x[0]: %f\tx[1]:%f\n", x[0], x[1]);
		double *grad = numeriacal_gradient(function, n, x);
		int j;
		for (j=0; j<n; j++) {
			x[j] -= lr * grad[j];
		}
		free(grad);
	}

	return x;
}


int main(void)
{
	// differetiation
	double x1[] = {10};
	numerical_diff(function_1, 1, x1);
	printf("%f\n", x1[0]);
	
	// gradient
	double array[2] = {3.0, 0.0};
	double *p = numeriacal_gradient(function_2, 2, array);
	printf("array([%0.1f, %0.1f])\n", p[0], p[1]);
	free(p);

	// gradient descent
	double init_x[] = {-3.0, 4.0};
	double *x = gradient_descent(function_2, 2, init_x, 0.1, 100);
	printf("array([%f, %f])\n", x[0], x[1]);
	free(x);

	return 0;
}