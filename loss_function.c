#include <stdio.h>
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