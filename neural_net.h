void dot_xw(int dim_in, int dim_out, double x[dim_out], double W[dim_in][dim_out], double a[dim_out])
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