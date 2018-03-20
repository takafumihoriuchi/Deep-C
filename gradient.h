#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./utils.h"
#include "./loss_function.h"


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


double loss(int nin, int nout, double x[nin], double t[nout], double W[nin][nout])
{
    double *z = predict(nin, nout, x, W);
    double *y = softmax(nout, z);
    double loss = cross_entropy_error(nout, y, t);
    return loss;
}
