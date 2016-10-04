///*
// ============================================================================
// Name        : create_random_file.c
// Author      : Carlos Lee
// ============================================================================
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/timeb.h>
//#include <string.h>
//
///* Function prototypes  */
//void random_array(char *array, long bytes);
//
///**
// * populate a random array (which is already
// * allocated with enough memory to hold n bytes.)
// *
// */
//void random_array(char *array, long bytes)
//{
//	int i;
//	for(i = 0; i < bytes; i++)
//	{
//		char c = 'A' + (rand() % 26);
//		array[i] = c;
//	}
//}
//
//int main(int argc, char **argv) {
//
//	//Arguments
//	char* filename = argv[1];
//	long total_bytes= atol(argv[2]);
//	long block_size= atol(argv[3]);
//	long total_time = 0;
//	long before_in_ms = 0;
//	long current_in_ms = 0;
//	struct timeb t;
//
//	//init buffer
//	char buffer[block_size];
//	memset(buffer, 0, sizeof(buffer));
//
//	//Write to file
//	FILE *fp = fopen(filename, "w");
//
//	while(total_bytes >= block_size)
//	{
//		total_bytes -= block_size;
//		random_array(buffer, block_size);
//
//		//Count time
//		ftime(&t);
//		before_in_ms = t.time * 1000 + t.millitm;
//		fwrite(buffer, sizeof(char), block_size, fp);
//		ftime(&t);
//		current_in_ms = t.time * 1000 + t.millitm;
//		total_time += (current_in_ms - before_in_ms);
//
//		fflush(fp);
//		memset(buffer, 0, sizeof(buffer));
//	}
//	if(total_bytes > 0)
//	{
//		random_array(buffer, total_bytes);
//
//		//Count time
//		ftime(&t);
//		before_in_ms = t.time * 1000 + t.millitm;
//		fwrite(buffer, sizeof(char), block_size, fp);
//		ftime(&t);
//		current_in_ms = t.time * 1000 + t.millitm;
//		total_time += (current_in_ms - before_in_ms);
//
//		fflush(fp);
//	}
//
//	fclose(fp);
//
//	printf("Total time milliseconds: %ld \n", total_time);
//
//	return EXIT_SUCCESS;
//}
