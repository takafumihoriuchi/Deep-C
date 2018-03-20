#include <stdio.h>
#include "mnist/mnist.h"
#include "./utils.h"
#include "./neural_net.h"
#include "./activation.h"
#include "./loss_function.h"


typedef struct Network {
	int input_size;
	int hidden_size;
	int output_size;
	double weight_init_std;
	double **W1;
	double **W2;
	double *b1;
	double *b2;
} Network;


Network init(int input_size, int hidden_size, int output_size, double weight_init_std)
{
	Network net;

	net.input_size = input_size;
	net.hidden_size = hidden_size;
	net.output_size = output_size;
	net.weight_init_std = weight_init_std;

	net.W1 = (double **)malloc(sizeof(double *) * net.input_size);
	check_malloc_double_p(net.W1);
	int i;
	for (i=0; i<net.input_size; i++) {
		double *inner = (double *)malloc(sizeof(double) * net.hidden_size);
		check_malloc_double(inner);
		net.W1[i] = inner;
	}
	net.W2 = (double **)malloc(sizeof(double *) * net.hidden_size);
	check_malloc_double_p(net.W2);
	for (i=0; i<net.hidden_size; i++) {
		double *inner = (double *)malloc(sizeof(double) * net.output_size);
		check_malloc_double(inner);
		net.W2[i] = inner;
	}

	net.b1 = (double *)malloc(sizeof(double) * net.hidden_size);
	check_malloc_double(net.b1);
	net.b2 = (double *)malloc(sizeof(double) * net.output_size);
	check_malloc_double(net.b2);

	randn(net.input_size, net.output_size, net.W1);
	zeros(net.hidden_size, net.b1);
	randn(net.hidden_size, net.output_size, net.W2);
	zeros(net.output_size, net.b2);

	return net;
}


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


void release_network(Network net)
{
	free(net.W1);
	free(net.b1);
	free(net.W2);
	free(net.b2);
}


void two_layer_net()
{
	int input_size = 784;
	int hidden_size = 100;
	int output_size = 10;
	double weight_init_std = 0.01;
	
	double x[input_size];
	double t[output_size];
	
	// set up mnist input and mnist label
	load_mnist();
	int i;
	for (i=0; i<input_size; i++) {
		x[i] = test_image[0][i];
	}
	zeros(output_size, t);
	t[test_label[0]] = 1.0;

	Network net = init(input_size, hidden_size, output_size, weight_init_std);
	double loss_amt = loss(net, x, t);
	printf("loss_amt: %f\n", loss_amt);

	release_network(net);
}


int main(void)
{
	two_layer_net();
	return 0;
}
