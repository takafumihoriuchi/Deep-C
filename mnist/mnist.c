#include "mnist.h"

int main(void)
{
    read_mnist();
    // print_mnist();

    pack_mnist(0);
    
    int i;
    for (i=0; i<60000; i++) {
    	printf("train_label[%d]: %d\n", i, train_label[i]);
    }

    save_image(0, "");
}

/*

train_label[59992]: 0
train_label[59993]: 0
train_label[59994]: 0
train_label[59995]: 0
train_label[59996]: 0
train_label[59997]: 0
train_label[59998]: 0
train_label[59999]: 0

が正しく読み込めていない。

*/