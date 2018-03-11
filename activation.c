#include <stdio.h>
#include <math.h>


double step(double x)
{
	return (x > 0);
}


double sigmoid(double x)
{
	return (1 / (1 + exp(x*(-1))));
}


int main(void)
{
	printf("sigmoid(-1.1) = %f\n", sigmoid(-1.1));
	printf("sigmoid(1) = %f\n", sigmoid(1));
	printf("sigmoid(2.4) = %f\n", sigmoid(2.4));
	printf("sigmoid(5.6) = %f\n", sigmoid(5.6));
	return 0;
}
