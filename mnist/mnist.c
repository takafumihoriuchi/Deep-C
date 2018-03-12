#include "mnist.h"

int main(void)
{
    read_mnist();
    // print_mnist();

    // pack_mnist(0);
    
    //printf("train_label[0]: %d\n", train_label[0]);
    int i;
    for (i=0; i<60000; i++) {
    	printf("train_label[%d]: %d\n", i, train_label[i][0]);
    }

    // save_image(0, "");
}
