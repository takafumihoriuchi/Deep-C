#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for read(), etc.
#include <fcntl.h>  // for open(), etc.
#include "pgmlib.h"

#define TRAIN_IMAGE "./data/train-images.idx3-ubyte"
#define TRAIN_LABEL "./data/train-labels.idx1-ubyte"
#define TEST_IMAGE "./data/t10k-images.idx3-ubyte"
#define TEST_LABEL "./data/t10k-labels.idx1-ubyte"

#define NUM_TRAIN 60000
#define NUM_TEST 10000
#define SIZE 784 // 28 * 28
#define LEN_INFO_IMG 4
#define LEN_INFO_LBL 2

int info_img[LEN_INFO_IMG];
int info_lbl[LEN_INFO_LBL];

unsigned char train_image_char[NUM_TRAIN][SIZE];
unsigned char train_label_char[NUM_TRAIN][1];
unsigned char test_image_char[NUM_TEST][SIZE];
unsigned char test_label_char[NUM_TEST][1];

double train_image[NUM_TRAIN][SIZE];
int  train_label[NUM_TRAIN];
double test_image[NUM_TEST][SIZE];
int test_label[NUM_TEST];


void FlipLong(unsigned char * ptr)
{
    register unsigned char val;
    
    // Swap 1st and 4th bytes
    val = *(ptr);
    *(ptr) = *(ptr+3);
    *(ptr+3) = val;
    
    // Swap 2nd and 3rd bytes
    ptr += 1;
    val = *(ptr);
    *(ptr) = *(ptr+1);
    *(ptr+1) = val;
}


void read_mnist_char(char *file_path, int num_data, int len_info, int arr_n, unsigned char data_char[][arr_n], int info_arr[])
{
    int i, j, k, fd;
    unsigned char *ptr;

    if ((fd = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open image file");
        exit(-1);
    }
    
    read(fd, info_arr, len_info * sizeof(int));
    
    // read-in information about size of data
    for (i=0; i<len_info; i++) { 
        ptr = (unsigned char *)(info_arr + i);
        FlipLong(ptr);
        printf("%d\n", info_arr[i]);
        ptr = ptr + sizeof(int);
    }
    
    // read-in mnist numbers
    for (i=0; i<num_data; i++) {
        read(fd, data_char[i], arr_n * sizeof(unsigned char));   
    }

    close(fd);
}


void image_char2double(int num_data, unsigned char data_image_char[][SIZE], double data_image[][SIZE])
{
    int i, j;
    for (i=0; i<num_data; i++)
        for (j=0; j<SIZE; j++)
            data_image[i][j]  = (double)data_image_char[i][j];// / 255.0;
}

void label_char2int(int num_data, unsigned char data_label_char[][1], int data_label[])
{
    int i;
    for (i=0; i<num_data; i++)
        data_label[i]  = (int)data_label_char[i][0];
}

// postcondition: mnist data will be stored in following array
// train image -> train_image[][] (type: double, each image of flat array)
// train label -> train_label[] (type: int)
// test image  -> test_image[][] (type: double, each image of flat array)
// test label  -> test_label[] (type: int)
void read_mnist()
{
    // printf("\ntrain image\n");
    read_mnist_char(TRAIN_IMAGE, NUM_TRAIN, LEN_INFO_IMG, SIZE, train_image_char, info_img);
    image_char2double(NUM_TRAIN, train_image_char, train_image);

    // printf("\ntest image\n");
    read_mnist_char(TEST_IMAGE, NUM_TEST, LEN_INFO_IMG, SIZE, test_image_char, info_img);
    image_char2double(NUM_TEST, test_image_char, test_image);
    
    // printf("\ntrain label\n");
    read_mnist_char(TRAIN_LABEL, NUM_TRAIN, LEN_INFO_LBL, 1, train_label_char, info_lbl);
    label_char2int(NUM_TRAIN, train_label_char, train_label);
    
    // printf("\ntest label\n");
    read_mnist_char(TEST_LABEL, NUM_TEST, LEN_INFO_LBL, 1, test_label_char, info_lbl);
    label_char2int(NUM_TEST, test_label_char, test_label);
}


void print_mnist()
{
    int i, j;
    for (i=0; i<NUM_TRAIN; i++) {
        printf("# image %d/%d\n", i+1, NUM_TRAIN);
        for (j=0; j<SIZE; j++) {
            printf("%1.1f ", train_image[i][j]);
            if ((j+1) % 28 == 0) putchar('\n');
        }
        putchar('\n');
    }
}


// call before pgmlib.h/save_image() when saving mnist image
// store train_image[][] into image[][][]
void pack_mnist(int n)
{
    int x, y;

    width[n] = 28;
    height[n] = 28;

    for (y=0; y<height[n]; y++) {
        for (x=0; x<width[n]; x++) {
            image[n][x][y] = train_image[59999][y * width[n] + x];
        }
    }
}


/*  
MNIST Data file from http://yann.lecun.com/exdb/mnist/
2006.10.25 A.Date 
*/