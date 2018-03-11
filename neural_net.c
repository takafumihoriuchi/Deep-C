#include <stdio.h>
#include <stdlib.h>
#include "activation.h"


void dot(int dim_in, int dim_out, double x[dim_out], double W[dim_in][dim_out], double a[dim_out])
{
	int i;
	for (i=0; i<dim_out; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<dim_in; j++) {
			a_tmp += x[j] * W[j][i];
		}
		a[i] = a_tmp;
	}
	return;
}


void add_bias(int dim, double a[dim], double b[dim])
{
	int i;
	for (i=0; i<dim; i++) a[i] += b[i];
	return;
}


void call_activation(int dim, double a[dim], double z[dim], double (*activation)(double))
{
	int i;
	for (i=0; i<dim; i++) z[i] = activation(a[i]);
	return;
}


int main(void)
{
	double x[2] = {1.0, 0.5};

	double W1[2][3] = {{0.1, 0.3, 0.5}, {0.2, 0.4, 0.6}};
	double b1[3] = {0.1, 0.2, 0.3};
	double a1[3];
	double z1[3];

	dot(2, 3, x, W1, a1);
	add_bias(3, a1, b1);
	call_activation(3, a1, z1, sigmoid);

	double W2[3][2] = {{0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6}};
	double b2[2] = {0.1, 0.2};
	double a2[2];
	double z2[2];

	dot(3, 2, z1, W2, a2);
	add_bias(2, a2, b2);
	call_activation(2, a2, z2, sigmoid);

	double W3[2][2] = {{0.1, 0.3}, {0.2, 0.4}};
	double b3[2] = {0.1, 0.2};
	double a3[2];
	double y[2];

	dot(2, 2, z2, W3, a3);
	add_bias(2, a3, b3);
	call_activation(2, a3, y, identity);

	int i;
	for (i=0; i<2; i++) {
		printf("y[%d] = %f\n", i, y[i]);
	}

	return 0;
}
