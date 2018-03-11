#include "utils.h"


int step(int x)
{
	return (x > 0);
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
