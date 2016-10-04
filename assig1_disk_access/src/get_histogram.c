///*
// ============================================================================
// Name        : get_histogram.c
// Author      : Carlos Lee
// ============================================================================
// */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

/* Function prototypes */
int get_histogram(
    FILE *file_ptr,
    long hist[],
    int block_size,
    long *milliseconds,
    long *total_bytes_read);


/**
 * file_ptr : the file pointer, ready to be read from.
 * hist: an array to hold 26 long integers.  hist[0] is the
 *       number of 'A', and hist[1] is the number of 'B', etc.
 * block_size: the buffer size to be used.
 * milliseconds: time it took to complete the file scan
 * total_bytes_read: the amount data in bytes read
 *
 * returns: -1 if there is an error.
 */
#include <sys/stat.h>

int get_histogram(FILE *file_ptr, long hist[], int block_size, long *milliseconds, long *total_bytes_read)
{
	//Init buffer
	char buffer[block_size];
	memset(buffer, 0, sizeof(buffer));
	*total_bytes_read = 0;

	// init time
	struct timeb t;
	long before_in_ms = 0;
	long current_in_ms = 0;

	int current_byte_read = -1;
	while(current_byte_read != 0)
	{
		ftime(&t);
		before_in_ms = t.time * 1000 + t.millitm;
		current_byte_read = fread(buffer, sizeof(char), block_size, file_ptr);
		ftime(&t);
		current_in_ms = t.time * 1000 + t.millitm;
		*milliseconds += (current_in_ms - before_in_ms);

		int i;
		for(i = 0; i < block_size; i++)
		{
			hist[buffer[i] - 'A'] ++;
		}
		memset(buffer, 0, sizeof(buffer));

		*total_bytes_read += current_byte_read;
	}


	return -1;
}

int main(int argc, char **argv) {
	long hist[26];
	long milliseconds = 0;
	long filelen;

	//Arguments
	char* filename = argv[1];
	long block_size= atol(argv[2]);

	//Read file
	FILE *fp = fopen(filename, "r");

	//Init variable
	memset(hist, 0, sizeof(hist));

	/**
	 * Compute the histogram using 2K buffers
	 */
	get_histogram(fp, hist, block_size, &milliseconds, &filelen);


	printf("Computed the histogram in %ld ms.\n", milliseconds);
	for(int i=0; i < 26; i++) {
	    printf("%c : %ld\n", 'A' + i, hist[i]);
	}
	printf("Data rate: %f Bps\n", (double)filelen/milliseconds * 1000);

	fclose(fp);

	return EXIT_SUCCESS;
}
