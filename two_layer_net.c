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
	// parameters:
	double **W1;
	double **W2;
	double *b1;
	double *b2;
	// gradients:
	double **grad_W1;
	double **grad_W2;
	double *grad_b1;
	double *grad_b2;
} Network;


Network init(int input_size, int hidden_size, int output_size, double weight_init_std)
{
	Network net;

	net.input_size = input_size;
	net.hidden_size = hidden_size;
	net.output_size = output_size;
	net.weight_init_std = weight_init_std;

	net.W1 = two_dim_double_malloc(net.input_size, net.hidden_size);
	net.W2 = two_dim_double_malloc(net.hidden_size, net.output_size);
	net.b1 = one_dim_double_malloc(net.hidden_size);
	net.b2 = one_dim_double_malloc(net.output_size);

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


int max_index(int n, double arr[n])
{
	double max = arr[0];
	int max_idx = 0;
	int i;
	for (i=1; i<n; i++) {
		if (arr[i] > max) {
			max = arr[i];
			max_idx = i;
		}
	}
	return max_idx;
}


double calc_accuracy(Network net)
{
	// train_image[NUM_TRAIN][SIZE]
	// train_label[NUM_TRAIN]

	// double one_hot_encoding[NUM_TRAIN][net.output_size];
	
	int num_correct = 0;

	int i;
	for (i=0; i<NUM_TRAIN; i++) {
		// set label to one-hot-encoding
		// zeros(net.output_size, one_hot_label[i]);
		// one_hot_encoding[i][train_label[i]] = 1.0;
		// predict
		double *y = predict(net, train_image[i]);
		int pred_label = max_index(net.output_size, y);
		free(y);
		if (pred_label == train_label[i]) num_correct++;
	}

	double accuracy = (double)num_correct / NUM_TRAIN;
	return accuracy;
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
	// convert to one-hot-encoding
	zeros(output_size, t);
	t[test_label[0]] = 1.0;

	Network net = init(input_size, hidden_size, output_size, weight_init_std);
	double loss_amt = loss(net, x, t);
	printf("loss amount of train_image[0]: %f\n", loss_amt);

	double accuracy = calc_accuracy(net);
	printf("train accuracy: %f\n", accuracy);

	release_network(net);
}


int main(void)
{
	two_layer_net();
	return 0;
}
