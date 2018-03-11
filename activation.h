#include <math.h>


double step(double x)
{
	return (x > 0);
}


double sigmoid(double x)
{
	return (1 / (1 + exp(x*(-1))));
}


double relu(double x)
{
	return fmax(0, x);
}

double identity(double x)
{
	return x;
}