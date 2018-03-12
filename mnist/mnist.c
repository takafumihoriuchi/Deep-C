#include "mnist.h"
#include "pgmlib.h"


int main(void)
{
    read_mnist();
    print_mnist();

    pack_mnist(0);
    save_image(0, "");
}
