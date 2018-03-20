#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <math.h>


double step(double x)
{
	return (x > 0);
}


double sigmoid(double x)
{
	return (1 / (1 + exp(x*(-1))));
}


void sigmoid_arr(int n, double x[n])
{
	int i;
	for (i=0; i<n; i++) {
		x[i] = (1 / (1 + exp(x[i]*(-1))));
	}
}


double relu(double x)
{
	return fmax(0, x);
}


double identity(double x)
{
	return x;
}


// n: length of array
// a: input array
// z: output array (elements of 'a' after softmax activation)
void softmax(int n, double a[n], double z[n])
{
	int i;

	double max = a[0];
	for (i=1; i<n; i++)
		if (a[i] > max)
			max = a[i];

	for (i=0; i<n; i++)
		a[i] -= max;

	double sum_exp = 0;
	for (i=0; i<n; i++)
		sum_exp += exp(a[i]);

	for (i=0; i<n; i++)
		z[i] = exp(a[i]) / sum_exp;

	return;
}


#endif