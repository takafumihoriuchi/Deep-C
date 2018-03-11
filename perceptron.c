#include <stdio.h>


int to_one_zero(int x)
{
	if (x) return 1;
	else return 0;
}


int step(int x)
{
	if (x > 0) return 1;
	else return 0;
}


int and(int x1, int x2)
{
	x1 = to_one_zero(x1);
	x2 = to_one_zero(x2);
	int w1 = 1, w2 = 1, b = -1;
	int y = b + x1*w1 + x2*w2;
	return step(y);
}


int nand(int x1, int x2)
{
	return (1 - and(x1, x2));
}


int or(int x1, int x2)
{
	x1 = to_one_zero(x1);
	x2 = to_one_zero(x2);
	int w1 = 2, w2 = 2, b = -1;
	int y = b + x1*w1 + x2*w2;
	return step(y);
}


int nor(int x1, int x2)
{
	return (1 - or(x1, x2));
}


int xor(int x1, int x2)
{
	x1 = to_one_zero(x1);
	x2 = to_one_zero(x2);
	int s1 = nand(x1, x2);
	int s2 = or(x1, x2);
	int y = and(s1, s2);
	return step(y);
}


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
