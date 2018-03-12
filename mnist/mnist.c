#include "mnist.h"
#include "pgmlib.h"


void load_mnist(int n)
{
	int x, y;

	width[n] = 28;
	height[n] = 28;

	for (y=0; y<height[n]; y++) {
		for (x=0; x<width[n]; x++) {
			image[n][x][y] = image_char[1][y * width[n] + x];
		}
	}
}


int main(void)
{
    read_images();
    // print_images();

    load_mnist(0);
    save_image(0, "");
}
