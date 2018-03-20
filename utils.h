#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


void check_malloc_double(double *p) {
    if (p == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        exit(1);
    }
}


int to_one_zero(int x)
{
	if (x) return 1;
	else return 0;
}


// initialize array W[n1][n2] with random numbers of standardized normal distribution
void randn(int n1, int n2, double W[n1][n2])
{
    srand((unsigned)time(NULL));
    double x, y, z1, z2;
    bool stock = false;
    int i, j;
    for (i=0; i<n1; i++) {
        for (j=0; j<n2; j++) {
            // HACK: necessary to use both in pair ??
            if (stock) {
                W[i][j] = z2;
                stock = false;
            } else {
                // generate standardized normal distribution by Box–Muller transform
                x  = (double)rand() / RAND_MAX;
                y  = (double)rand() / RAND_MAX;
                z1 = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
                z2 = sqrt(-2 * log(x)) * sin(2 * M_PI * y);
                W[i][j] = z1;
                stock = true;
            }
        }
    }
}


// initialize array b[n] with zeros
void zeros(int n, double b[n])
{
	int i;
	for (i=0; i<n; i++) {
		b[i] = 0.0;
	}
}