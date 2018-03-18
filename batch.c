#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_SIZE 60000
#define BATCH_SIZE 1000

int *random_arrary()
{
	static int batch[BATCH_SIZE];
	
	srand((unsigned)time(NULL));

	int i;
	for (i=0; i<BATCH_SIZE; i++) {
		batch[i] = rand() % TOTAL_SIZE;
	}

	return batch;
}


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