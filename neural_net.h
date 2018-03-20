#ifndef NEURAL_NET_H
#define NEURAL_NET_H


/*
// calculate inner product of x[n_in] and W[n_in][n_out]
// resulting array in form of a[n_out]
void dot_xw(int n_in, int n_out, double x[n_in], double W[n_in][n_out], double a[n_out])
{
	int i;
	for (i=0; i<n_out; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<n_in; j++) {
			a_tmp += x[j] * W[j][i];
		}
		a[i] = a_tmp;
	}
	return;
}
*/
// calculate inner product of x[n_in] and W[n_in][n_out]
// resulting array in form of a[n_out]
void dot_xw(int n_in, int n_out, double x[n_in], double **W, double a[n_out])
{
	int i;
	for (i=0; i<n_out; i++) {
		double a_tmp = 0;
		int j;
		for (j=0; j<n_in; j++) {
			a_tmp += x[j] * W[j][i];
		}
		a[i] = a_tmp;
	}
	return;
}


// n: length of array
// a: input array
// b: array of bias
void add_bias(int n, double a[n], double b[n])
{
	int i;
	for (i=0; i<n; i++) a[i] += b[i];
	return;
}


// n: length of array
// a: input array
// z: output array
void call_activation(int n, double a[n], double z[n], double (*activation)(double))
{
	int i;
	for (i=0; i<n; i++) z[i] = activation(a[i]);
	return;
}


#endif