#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // read()
#include <fcntl.h>  // open()

#define IMAGE_FILE "./train-images.idx3-ubyte"
#define NUM_IMAGES 60000
#define SIZE 784
#define LEN_DESC 4

static int num[LEN_DESC];
static unsigned char image_char[NUM_IMAGES][SIZE];
static double image[NUM_IMAGES][SIZE];


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


void read_images()
{
    int i, j, k, fd;
    float f;
    unsigned char *ptr; 
    
    if ((fd = open(IMAGE_FILE, O_RDONLY)) == -1) {
        fprintf(stderr, "couldn't open image file");
        exit(-1);
    }
    
    read(fd, num, LEN_DESC*sizeof(int));

    // read-in description
    for (i=0; i<LEN_DESC; i++) { 
        ptr = (unsigned char *)(num + i);
        FlipLong(ptr);
        printf("%d\n", num[i]);
        ptr = ptr + sizeof(int);
    }

    // read-in mnist numbers
    for (i=0; i<NUM_IMAGES; i++) {
        read(fd, image_char[i], SIZE*sizeof(unsigned char));
    }

    close(fd);
}


void print_images()
{
    int i, j;
    for (i=0; i<NUM_IMAGES; i++) {
        printf("# image %d/%d\n", i+1, NUM_IMAGES);
        for (j=0; j<SIZE; j++) {
            image[i][j] = (double)image_char[i][j] / 255.0;
            printf("%1.1f ", image[i][j]);
            if ((j+1) % 28 == 0) putchar('\n');
        }
        putchar('\n');
    }
}


int main(void)
{
    read_images();
    print_images();  
}

/*  
 *  MNIST Data file from http://yann.lecun.com/exdb/mnist/
 *  2006.10.25 A.Date 
 */
