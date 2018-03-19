#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "./loss_function.h"


void check_malloc(double *p) {
    if (p == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        exit(1);
    }
}


double function_1(double x)
{
    return 0.01 * pow(x, 2) + 0.1 * x;
}


double function_2(double x[2])
{
    return pow(x[0], 2) + pow(x[1], 2);
}


void numerical_diff(double (*function)(double), int n, double x[n])
{
    double h = 1e-4;
    int i;
    for (i=0; i<n; i++) {
        x[i] = (function(x[i] + h) - function(x[i] - h)) / (h * 2.0);
    }
}


// need free(grad) in caller
double *numeriacal_gradient(double (*function)(double *), int n, double x[n])
{
    double h = 1e-4;

    double *grad = malloc(sizeof(double) * n);
    check_malloc(grad);

    int i;
    for (i=0; i<n; i++) {
        
        double tmp_val = x[i];
        
        x[i] = tmp_val + h;
        double fxh1 = function(x);

        x[i] = tmp_val - h;
        double fxh2 = function(x);

        grad[i] = (fxh1 - fxh2) / (h * 2.0);
        x[i] = tmp_val;
    }

    return grad;
}


// need free(x) in caller
double *gradient_descent(double (*function)(double *), int n, double init_x[n], double lr, int step_num)
{
    double *x = malloc(sizeof(double) * n);
    check_malloc(x);

    int i;
    for (i=0; i<n; i++) x[i] = init_x[i];

    for (i=0; i<step_num; i++) {
        printf("x[0]: %f\tx[1]:%f\n", x[0], x[1]);
        double *grad = numeriacal_gradient(function, n, x);
        int j;
        for (j=0; j<n; j++) {
            x[j] -= lr * grad[j];
        }
        free(grad);
    }

    return x;
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


// expects free(a) in caller
double *dot(int nin, int nout, double x[nin], double W[nin][nout])
{
    double *a = malloc(sizeof(double) * nout);
    check_malloc(a);

    int i, j;
    for (i=0; i<nout; i++) {
        double a_tmp = 0;
        for (j=0; j<nin; j++) {
            a_tmp += x[j] * W[j][i];
        }
        a[i] = a_tmp;
    }

    return a;
}


// expects free(a) in caller
double *predict(int nin, int nout, double x[nin], double W[nin][nout])
{
    return dot(nin, nout, x, W);
}


// expects free(z) in caller
double *softmax(int n, double a[n])
{
    double *z = malloc(sizeof(double) * n);
    check_malloc(z);

    int i;

    double max = a[0];
    for (i=1; i<n; i++)
        if (a[i] > max)
            max = a[i];

    for (i=0; i<n; i++)
        a[i] -= max;

    double sum_exp = 0;
    for (i=0; i<n; i++)
        sum_exp += exp(a[i]);

    for (i=0; i<n; i++)
        z[i] = exp(a[i]) / sum_exp;

    return z;
}


double loss(int nin, int nout, double x[nin], double t[nin], double W[nin][nout])
{
    double *z = predict(nin, nout, x, W);
    double *y = softmax(nout, z);
    double loss = cross_entropy_error(nout, y, t);
    return loss;
}


int main(void)
{
    // differetiation
    double x1[] = {10};
    numerical_diff(function_1, 1, x1);
    printf("%f\n", x1[0]);
    
    // gradient
    double array[2] = {3.0, 0.0};
    double *p1 = numeriacal_gradient(function_2, 2, array);
    printf("array([%0.1f, %0.1f])\n", p1[0], p1[1]);
    free(p1);

    // gradient descent
    double init_x[] = {-3.0, 4.0};
    double *x2 = gradient_descent(function_2, 2, init_x, 0.1, 100);
    printf("array([%f, %f])\n", x2[0], x2[1]);
    free(x2);

    // simple neural network
    double W[2][3];
    // double W[2][3] = {{0.47355232, 0.9977393, 0.84668094}, {0.85557411, 0.03563661, 0.69422093}};
    randn(2, 3, W);
    int i, j;
    for (i=0; i<2; i++) {
        for (j=0; j<3; j++) {
            printf("W[%d][%d]: %f\n", i, j, W[i][j]);
        }
    }
    double x[2] = {0.6, 0.9};
    double *p = predict(2, 3, x, W);
    printf("p[0]: %f\n", p[0]);
    printf("p[1]: %f\n", p[1]);
    printf("p[2]: %f\n", p[2]);
    double t[3] = {0.0, 0.0, 1.0};
    double loss_amt = loss(2, 3, x, t, W);
    printf("loss_amt: %f\n", loss_amt);
    free(p);

    return 0;
}