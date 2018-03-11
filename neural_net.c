#include <stdio.h>
#include "activation.h"
#include "neural_net.h"


int main(void)
{
	double x[2] = {1.0, 0.5};

	double W1[2][3] = {{0.1, 0.3, 0.5}, {0.2, 0.4, 0.6}};
	double b1[3] = {0.1, 0.2, 0.3};
	double a1[3];
	double z1[3];

	dot_xw(2, 3, x, W1, a1);
	add_bias(3, a1, b1);
	call_activation(3, a1, z1, sigmoid);

	double W2[3][2] = {{0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6}};
	double b2[2] = {0.1, 0.2};
	double a2[2];
	double z2[2];

	dot_xw(3, 2, z1, W2, a2);
	add_bias(2, a2, b2);
	call_activation(2, a2, z2, sigmoid);

	double W3[2][2] = {{0.1, 0.3}, {0.2, 0.4}};
	double b3[2] = {0.1, 0.2};
	double a3[2];
	double y[2];

	dot_xw(2, 2, z2, W3, a3);
	add_bias(2, a3, b3);
	call_activation(2, a3, y, identity);

	int i;
	for (i=0; i<2; i++) {
		printf("y[%d] = %f\n", i, y[i]);
	}

	return 0;
}
