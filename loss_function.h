#ifndef LOSS_FUNCTION_H
#define LOSS_FUNCTION_H

#include <math.h>


// takes two arrays (y:prediction, t:label) of size n
// returns mse of two arrays
double mean_squared_error(int n, double y[n], double t[n])
{
	double sum = 0;

	int i;
	for (i=0; i<n; i++) {
		sum += pow((y[i] - t[i]), 2);
	}

	return sum / 2.0;
}


// t: one-hot label
double cross_entropy_error(int n, double y[n], double t[n])
{
	double sum = 0;
	double delta = 1e-7;

	int i;
	for (i=0; i<n; i++) {
		sum += t[i] * log(y[i] + delta);
	}

	return sum * (-1);
}


#endif