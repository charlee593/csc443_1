/*
 ============================================================================
 Name        : create_random_file.c
 Author      : Carlos Lee
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

/* Function prototypes  */
void random_array(char *array, long bytes);

/**
 * populate a random array (which is already
 * allocated with enough memory to hold n bytes.)
 *
 */
void random_array(char *array, long bytes)
{
	int i;
	for(i = 0; i < bytes; i++)
	{
		char c = 'A' + (rand() % 26);
		array[i] = c;
	}
}

int main(int argc, char **argv) {

	//Arguments
	char* filename = argv[1];
	long total_bytes= atol(argv[2]);
	long block_size= atol(argv[3]);

	char buffer[block_size];

	//Count time - start
	struct timeb t;
	ftime(&t);
	long before_in_ms = t.time * 1000 + t.millitm;
	printf("Start time mm: %ld \n", before_in_ms);

	//Write to file
	FILE *fp = fopen(filename, "w");
	while(total_bytes >= block_size)
	{
		total_bytes -= block_size;
		random_array(buffer, block_size);
		fwrite(buffer, sizeof(char), block_size, fp);
		fflush(fp);
	}
	if(total_bytes > 0)
	{
		random_array(buffer, total_bytes);
		fwrite(buffer, sizeof(char), total_bytes, fp);
		fflush(fp);
	}
	fclose(fp);

	//Count time - end
	ftime(&t);
	long after_in_ms = t.time * 1000 + t.millitm;
	printf("Stop time mm: %ld \n", after_in_ms);
	printf("Difference mm: %ld \n", after_in_ms - before_in_ms);

	return EXIT_SUCCESS;
}
