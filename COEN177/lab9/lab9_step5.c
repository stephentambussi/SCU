/* Name: Stephen Tambussi
 * Date: 5/27/2021
 * Title: Lab 9 - File Performance Measurement
 * Description: This program evaluates file system performance during sequential I/O requests
 * by reading and writing to the disk. Step 5 of lab. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct arg_struct //struct to hold the arguments to pass to thread function copy
{
	int buf_size;
	char *source;
	char *target;
};

void *copy(void *args)
{
	struct arg_struct *a = args;
	FILE *fp, *fp2;
	char buffer[a->buf_size];
	size_t bytes;
	fp = fopen(a->source, "rb"); //opens file for reading
	fp2 = fopen(a->target, "wb"); //creates file for writing
	while((bytes = fread(buffer, 1, sizeof(buffer), fp)) != 0) //keeps reading from file until the number of elements read is 0 (end of file)
	{
		if(fwrite(buffer, 1, bytes, fp2) != bytes) //error check - elements read should equal elements written
			return NULL;
	}
	fclose(fp);
	fclose(fp2);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if(argc < 5) //error checking
	{
		printf("Error: not enough command line arguments. \n");
		return 0;
	}
	struct arg_struct args;
	args.buf_size = atoi(argv[2]); //converts the cmd line argument to an int
	args.source = argv[1];
	args.target = argv[3];
	char temp[20];
	sprintf(temp, "%s", argv[3]);
	int num_threads = atoi(argv[4]);
	pthread_t t;
	int i;
	char num[5];
	for(i = 0; i < num_threads; i++)
	{
		memset(num, '\0', sizeof(char)*5);
		memset(args.target, 0, sizeof(args.target));
		sprintf(args.target, "%s", temp);
		sprintf(num, "%d", i);
		strcat(args.target, num);
		pthread_create(&t, NULL, copy, (void *)&args);
		pthread_join(t, NULL);
	}
	return 0;
}
