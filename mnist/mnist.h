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
unsigned char train_image[NUM_TRAIN][SIZE];
unsigned char train_label[NUM_TRAIN][1];
unsigned char test_image[NUM_TEST][SIZE];
unsigned char test_label[NUM_TEST][1];


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


void read_mnist_image(char *file_path, int num_data, unsigned char data_image[][SIZE])
{
    int i, j, k, fd;
    unsigned char *ptr; 

    if ((fd = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open image file");
        exit(-1);
    }
    
    read(fd, info_img, LEN_INFO_IMG*sizeof(int));
    
    // read-in information about size of data
    for (i=0; i<LEN_INFO_IMG; i++) { 
        ptr = (unsigned char *)(info_img + i);
        FlipLong(ptr);
        printf("%d\n", info_img[i]);
        ptr = ptr + sizeof(int);
    }
    
    // read-in mnist numbers
    for (i=0; i<num_data; i++) {
        read(fd, data_image[i], SIZE*sizeof(unsigned char));
    }
    
    close(fd);
}


void read_mnist_label(char *file_path, int num_data, unsigned char data_label[][1])
{
    int i, j, k, fd;
    unsigned char *ptr; 

    if ((fd = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open image file");
        exit(-1);
    }
    
    read(fd, info_lbl, LEN_INFO_LBL*sizeof(int));
    
    // read-in information about size of data
    for (i=0; i<LEN_INFO_LBL; i++) { 
        ptr = (unsigned char *)(info_lbl + i);
        FlipLong(ptr);
        printf("%d\n", info_lbl[i]);
        ptr = ptr + sizeof(int);
    }
    
    // read-in mnist numbers
    for (i=0; i<num_data; i++) {
        read(fd, data_label[i], sizeof(unsigned char));
    }
    
    close(fd);
}


// postcondition: mnist data will be stored in following array
// train image -> train_image[][]
// train label -> train_label[][]
// test image  -> test_image[][]
// test label  -> test_label[][]
void read_mnist()
{
    printf("\ntrain image\n");
    read_mnist_image(TRAIN_IMAGE, NUM_TRAIN, train_image);
    printf("\ntest image\n");
    read_mnist_image(TEST_IMAGE, NUM_TEST, test_image);
    printf("\ntrain label\n");
    read_mnist_label(TRAIN_LABEL, NUM_TRAIN, train_label);
    printf("\ntest label\n");
    read_mnist_label(TEST_LABEL, NUM_TEST, test_label);
}


void print_mnist()
{
    int i, j;
    for (i=0; i<NUM_TRAIN; i++) {
        printf("# image %d/%d\n", i+1, NUM_TRAIN);
        for (j=0; j<SIZE; j++) {
            printf("%1.1f ", train_image[i][j] / 255.0);
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
            image[n][x][y] = train_image[0][y * width[n] + x];
        }
    }
}


/*  
MNIST Data file from http://yann.lecun.com/exdb/mnist/
2006.10.25 A.Date 
*/