#include <stdio.h>
#include <stdlib.h>
#include "activation.h"


void check_malloc_double(double *p)
{
	if (p == NULL) {
		fprintf(stderr, "failed to allocate memory\n");
		exit(-1);
	}
}


// implement dot(), use malloc and return pointer
double *dot(double *x, double *w)
{
	int dim_in = sizeof(x) / sizeof(double);
	int dim_out = sizeof(w) / sizeof(double) / dim_in;
	double *a = malloc(sizeof(double) * dim_out);
	check_malloc_double(a);
	int i;
	for (i=0; i<dim_out; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<dim_in; j++) {
			a_tmp += x[j] * w[j*dim_out+i];
		}
		a[i] = a_tmp;
	}
	return a;
}


int main(void)
{
	double x[2] = {1.0, 0.5};
	
	double W1[2][3] = {{0.1, 0.3, 0.5}, {0.2, 0.4, 0.6}};
	double b1[3] = {0.1, 0.2, 0.3};
	double *a1;
	double z1[3];

	a1 = dot(x, W1);
	int i;
	/*
	for (i=0; i<3; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<2; j++) {
			a_tmp += x[j] * W1[j][i];
		}
		a1[i] = a_tmp;
	}
	*/

	for (i=0; i<3; i++) {
		a1[i] += b1[i];
		printf("a1[%d] = %f\n", i, a1[i]);
	}

	for (i=0; i<3; i++) {
		z1[i] = sigmoid(a1[i]);
		printf("z1[%d] = %f\n", i, z1[i]);
	}

	double W2[3][2] = {{0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6}};
	double b2[2] = {0.1, 0.2};
	double a2[2];
	double z2[2];

	for (i=0; i<2; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<3; j++) {
			a_tmp += z1[j] * W2[j][i];
		}
		a2[i] = a_tmp;
	}

	for (i=0; i<2; i++) {
		a2[i] += b2[i];
		printf("a2[%d] = %f\n", i, a2[i]);
	}

	for (i=0; i<3; i++) {
		z2[i] = sigmoid(a2[i]);
		printf("z2[%d] = %f\n", i, z2[i]);
	}

	double W3[2][2] = {{0.1, 0.3}, {0.2, 0.4}};
	double b3[2] = {0.1, 0.2};
	double a3[2];
	double y[2];

	for (i=0; i<2; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<2; j++) {
			a_tmp += z2[j] * W3[j][i];
		}
		a3[i] = a_tmp;
	}

	for (i=0; i<2; i++) {
		a3[i] += b3[i];
		printf("a3[%d] = %f\n", i, a3[i]);
	}

	for (i=0; i<2; i++) {
		y[i] = identity(a3[i]);
		printf("y[%d] = %f\n", i, y[i]);
	}

	return 0;
}


/*
int main(void)
{
	double x[2] = {1.0, 0.5};
	
	double W1[2][3] = {{0.1, 0.3, 0.5}, {0.2, 0.4, 0.6}};
	double b1[3] = {0.1, 0.2, 0.3};
	double a1[3];
	double z1[3];

	int i;
	for (i=0; i<3; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<2; j++) {
			a_tmp += x[j] * W1[j][i];
		}
		a1[i] = a_tmp;
	}

	for (i=0; i<3; i++) {
		a1[i] += b1[i];
		printf("a1[%d] = %f\n", i, a1[i]);
	}

	for (i=0; i<3; i++) {
		z1[i] = sigmoid(a1[i]);
		printf("z1[%d] = %f\n", i, z1[i]);
	}

	double W2[3][2] = {{0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6}};
	double b2[2] = {0.1, 0.2};
	double a2[2];
	double z2[2];

	for (i=0; i<2; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<3; j++) {
			a_tmp += z1[j] * W2[j][i];
		}
		a2[i] = a_tmp;
	}

	for (i=0; i<2; i++) {
		a2[i] += b2[i];
		printf("a2[%d] = %f\n", i, a2[i]);
	}

	for (i=0; i<3; i++) {
		z2[i] = sigmoid(a2[i]);
		printf("z2[%d] = %f\n", i, z2[i]);
	}

	double W3[2][2] = {{0.1, 0.3}, {0.2, 0.4}};
	double b3[2] = {0.1, 0.2};
	double a3[2];
	double y[2];

	for (i=0; i<2; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<2; j++) {
			a_tmp += z2[j] * W3[j][i];
		}
		a3[i] = a_tmp;
	}

	for (i=0; i<2; i++) {
		a3[i] += b3[i];
		printf("a3[%d] = %f\n", i, a3[i]);
	}

	for (i=0; i<2; i++) {
		y[i] = identity(a3[i]);
		printf("y[%d] = %f\n", i, y[i]);
	}

	return 0;
}
*/