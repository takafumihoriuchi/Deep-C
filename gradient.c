#include "./utils.h"
#include "./gradient.h"


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
    free(p);
    double t[3] = {0.0, 0.0, 1.0};
    double loss_amt = loss(2, 3, x, t, W);
    printf("loss_amt: %f\n", loss_amt);

    return 0;
}
