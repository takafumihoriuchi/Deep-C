#include <stdio.h>
#include "perceptron.h"


int main(void)
{
	printf("AND(0,0)  = %d\n", and(0,0));
	printf("AND(1,0)  = %d\n", and(1,0));
	printf("AND(0,1)  = %d\n", and(0,1));
	printf("AND(1,1)  = %d\n", and(1,1));

	printf("NAND(0,0) = %d\n", nand(0,0));
	printf("NAND(1,0) = %d\n", nand(1,0));
	printf("NAND(0,1) = %d\n", nand(0,1));
	printf("NAND(1,1) = %d\n", nand(1,1));

	printf("OR(0,0)   = %d\n", or(0,0));
	printf("OR(1,0)   = %d\n", or(1,0));
	printf("OR(0,1)   = %d\n", or(0,1));
	printf("OR(1,1)   = %d\n", or(1,1));

	printf("NOR(0,0)  = %d\n", nor(0,0));
	printf("NOR(1,0)  = %d\n", nor(1,0));
	printf("NOR(0,1)  = %d\n", nor(0,1));
	printf("NOR(1,1)  = %d\n", nor(1,1));

	printf("XOR(0,0)  = %d\n", xor(0,0));
	printf("XOR(1,0)  = %d\n", xor(1,0));
	printf("XOR(0,1)  = %d\n", xor(0,1));
	printf("XOR(1,1)  = %d\n", xor(1,1));

	return 0;
}
