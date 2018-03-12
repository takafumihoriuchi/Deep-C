#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for read(), etc.
#include <fcntl.h>  // for open(), etc.
#include "pgmlib.h"

#define TRAIN_IMAGE "./data/train-images.idx3-ubyte"
#define TRAIN_LABEL "./data/train-labels.idx1-ubyte"
#define TEST_IMAGE "./data/t10k-images.idx3-ubyte"
#define TEST_LABEL "./data/t10k-labels.idx1-ubyte"

#define NUM_IMAGES 60000
#define SIZE 784
#define LEN_INFO 4

int info[LEN_INFO];
unsigned char train_image[NUM_IMAGES][SIZE];


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


void read_mnist()
{
    int i, j, k, fd;
    float f;
    unsigned char *ptr; 
    
    if ((fd = open(TRAIN_IMAGE, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open image file");
        exit(-1);
    }
    
    read(fd, info, LEN_INFO*sizeof(int));

    // read-in information about size of data
    for (i=0; i<LEN_INFO; i++) { 
        ptr = (unsigned char *)(info + i);
        FlipLong(ptr);
        printf("%d\n", info[i]);
        ptr = ptr + sizeof(int);
    }

    // read-in mnist numbers
    for (i=0; i<NUM_IMAGES; i++) {
        read(fd, train_image[i], SIZE*sizeof(unsigned char));
    }

    close(fd);
}


void print_mnist()
{
    int i, j;
    for (i=0; i<NUM_IMAGES; i++) {
        printf("# image %d/%d\n", i+1, NUM_IMAGES);
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
            image[n][x][y] = train_image[1][y * width[n] + x];
        }
    }
}


/*  
MNIST Data file from http://yann.lecun.com/exdb/mnist/
2006.10.25 A.Date 
*/