#include <stdio.h>


int one_zero(int x)
{
	if (x) return 1;
	else return 0;
}


int and(int x1, int x2)
{
	x1 = one_zero(x1);
	x2 = one_zero(x2);
	int w1 = 1, w2 = 1, b = -1;
	int y = b + x1*w1 + x2*w2;
	if (y > 0) return 1;
	else return 0;
}


int nand(int x1, int x2)
{
	return (1- and(x1, x2));
}


int or(int x1, int x2)
{
	x1 = one_zero(x1);
	x2 = one_zero(x2);
	int w1 = 2, w2 = 2, b = -1;
	int y = b + x1*w1 + x2*w2;
	if (y > 0) return 1;
	else return 0;
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

	return 0;
}
