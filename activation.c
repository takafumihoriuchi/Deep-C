#include <stdio.h>
#include "activation.h"


int main(void)
{
	printf("sigmoid(-1.) = %f\n", sigmoid(-1.));
	printf("sigmoid(1)   = %f\n", sigmoid(1));
	printf("sigmoid(6.4) = %f\n", sigmoid(6.4));

	printf("relu(1.2)    = %f\n", relu(1.2));
	printf("relu(-1)     = %f\n", relu(-1));

	return 0;
}
