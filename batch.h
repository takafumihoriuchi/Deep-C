#include <stdlib.h>
#include <time.h>

#define TOTAL_SIZE 60000
#define BATCH_SIZE 30

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
