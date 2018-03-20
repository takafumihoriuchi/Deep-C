#include <stdio.h>
#include "./utils.h"
#include "./neural_net.h"
#include "./activation.h"
#include "./loss_function.h"


typedef struct Network {

	int input_size;
	int hidden_size;
	int output_size;
	double weight_init_std;
	
	double W1[input_size][hidden_size];
	double b1[hidden_size];
	double W2[hidden_size][output_size];
	double b2[output_size];

} Network;


// expects free(y) in caller function
double *predict(Network net, double x[net.input_size])
{
	double a1[net.hidden_size];
	dot_xw(net.input_size, net.hidden_size, x, net.W1, a1);
	add_bias(net.hidden_size, a1, net.b1);

	double z1[net.hidden_size];
	sigmoid_arr(net.hidden_size, z1);

	double a2[net.output_size];
	dot_xw(net.hidden_size, net.output_size, z1, net.W2, a2);
	add_bias(net.output_size, a2, net.b2);

	double *y = malloc(sizeof(double) * net.output_size);
	check_malloc_double(y);
	softmax(net.output_size, a2, y);

	return y;
}


double loss(Network net, double x[net.input_size], double t[net.output_size])
{
	double *y = predict(net, x);
	double cee = cross_entropy_error(net.output_size, y, t);
	free(y);
	return cee;
}


Network init(int input_size, int hidden_size, int output_size, double weight_init_std)
{
	Network net;

	net.input_size = input_size;
	net.hidden_size = hidden_size;
	net.output_size = output_size;
	net.weight_init_std = weight_init_std;

	randn(net.input_size, net.output_size, net.W1);
	zeros(net.hidden_size, net.b1);
	randn(net.hidden_size, net.output_size, net.W2);
	zeros(net.output_size, net.b2);

	return net;
}


void two_layer_net()
{
	int input_size = 784;
	int hidden_size = 100;
	int output_size = 10;
	double weight_init_std = 0.01;

	double x[input_size];
	double t[output_size];

	Network net = init(784, 100, 10, 0.01);
	double loss_amt = loss(net, x, t);

	printf("loss_amt: %f\n", loss_amt);
}


int main(void)
{
	two_layer_net();
	return 0;
}