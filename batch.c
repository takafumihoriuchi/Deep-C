#include <stdio.h>
#include "./batch.h"


int main(void)
{
	int *batch = random_arrary();

	int i;
	for (i=0; i<BATCH_SIZE; i++) {
		printf("%d ", batch[i]);
	}
	putchar('\n');

	return 0;
}
