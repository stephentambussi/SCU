/* Stephen Tambussi
 * 1/14/21
 * Lab 2 - Multithreading in C - Copying files
 * Description: This program uses multithreading, system calls, and c library functions
 * to read/write and copy files
 */
#include <stdio.h> //printf, stderr
#include <sys/types.h> //pid_t
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h> //atoi
#include <pthread.h> //threading
#include <string.h>
#define BUF_SIZE 256

void *copy_sys(void *n)
{	
	char w[10], cp[50];
	int src, tar;
	char buffer[BUF_SIZE];
	ssize_t read_num;
	strcpy(w, "-copy"); //adds '-copy' string to the end of each copied file
	strcpy(cp, n);
	strcat(cp, w);
	src = open(n, O_RDWR);
        if(src == -1)
        {
		printf("Error opening source file. \n");
                return;
	}
	tar = open(cp, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if(tar == -1)
        {
		printf("Error creating copy file. \n");
                return;
        }
        while((read_num = read(src, buffer, BUF_SIZE)) > 0)
		if(write(tar, buffer, read_num) != read_num)
			return;
        if(close(src) == -1)
        {
		printf("Error closing source file. \n");
                return;
        }
        if(close(tar) == -1)
        {
		printf("Error closing target file. \n");
                return;
	}
	printf("Successfully copied file %s \n", n);
	pthread_exit((void *)n);
}

void *copy_fn(void *n)
{
	char w[10], cp[50];
	FILE *source, *target;
	char buffer[BUF_SIZE];
	size_t bytes;
	strcpy(w, "-copy");
	strcpy(cp, n);
	strcat(cp, w);
	source = fopen(n, "r");
	if(source == NULL)
		return;
	target = fopen(cp, "w");
	if(target == NULL)
		return;
	while((bytes = fread(buffer, 1, BUF_SIZE, source)) != 0)
        {
		if(fwrite(buffer, 1, bytes, target) != bytes)
                	return;
        }
	if(fclose(source) != 0)
	{
		printf("Error closing source file. \n");
		return;
	}
	if(fclose(target) != 0)
	{
		printf("Error closing target file. \n");
		return;
	}
	printf("Successfully copied file %s \n", n);
	pthread_exit((void *)n); 
}

int main(int argc, char *argv[]) 
{	//declarations
	pthread_t t;
	FILE *source, *target;
	char buffer[BUF_SIZE];
	size_t bytes;
	clock_t start, end;
	double cpu_time_used;
	printf("Enter 1 to copy a single file using functions \n");
	printf("Enter 2 to copy a single file using system calls \n");
	printf("Enter 3 to copy multiple files \n");
	int dec;//decision variable to decide what to do
	scanf("%d", &dec);
	if(dec == 1)
	{	//copy file with library functions
		start = clock(); //start calculating processing time of File IO using functions
		source = fopen(argv[1], "r");//opens file with name from 1st command line argument
		if(source == NULL)
		{
			printf("Error opening source file. \n");
			return 1;
		}
		target = fopen(argv[2], "w");//creates file with name from 2nd command line argument
		if(target == NULL)
		{
			fclose(source);
			printf("Error creating copy file. \n");
			return 1;
		}
		while((bytes = fread(buffer, 1, BUF_SIZE, source)) != 0)//bytes is equal to number of elements read
		{ //while loop continues until there are no more elements to be read
			if(fwrite(buffer, 1, bytes, target) != bytes) //error check - elements read should equal elements written
				return 1;
		}
		if(fclose(source) != 0)
		{
			printf("Error closing source file. \n");
			return 1;
		}
		if(fclose(target) != 0)
		{
			printf("Error closing target file. \n");
			return 1;
		}
		printf("Successfully copied files. \n");
		end = clock();//get clock ticks
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; //seconds
		printf("Processing time of File IO using functions: %f \n", cpu_time_used);
	}
	else if(dec == 2)
	{	//copy file with system calls
		start = clock(); //start calculating processing time of File IO using system calls
		ssize_t read_num;//variable for storing number of bytes read/written
		int src = open(argv[1], O_RDWR);//opens file to be copied with read and write capabilities
		if(src == -1)
		{
			printf("Error opening source file. \n");
			return 1;
		}
		int tar = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);//creates file to write to
		if(tar == -1)
		{
			printf("Error creating copy file. \n");
			return 1;
		}
		while((read_num = read(src, buffer, BUF_SIZE)) > 0)//continues until there are no more bytes to be read
			if(write(tar, buffer, read_num) != read_num)//error check - number of bytes read needs to equal number of bytes written
				return 1;
		if(close(src) == -1)
		{
			printf("Error closing source file. \n");
			return 1;
		}
		if(close(tar) == -1)
		{
			printf("Error closing target file. \n");
			return 1;
		}
		printf("Successfully copied files. \n");
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("Processing time of File IO using system calls: %f \n", cpu_time_used); //seconds
	}
	else if(dec == 3)
	{	//copy multiple files	
		int s, i;
		printf("Multi-file copy using system calls(1) or functions(2)? \n");//option to use system calls or library functions
		scanf("%d", &s);
		if(s == 1)
		{
			//copies files using system calls
			if(argc > 1)
			{
				start = clock();
				for(i = 1; i < argc; i++)
				{
					pthread_create(&t, NULL, copy_sys, argv[i]); //creates thread that calls copy_sys function with argument from cmd line
					pthread_join(t, (void **)argv[i]); //waits for previous thread to finish
				}
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printf("Processing time to copy %d files (%d threads) using system calls: %f \n", argc-1, argc-1, cpu_time_used);
			}
		}
		else if(s == 2)
		{
			//copies files using library functions
			if(argc > 1)
			{
				start = clock();
				for(i = 1; i < argc; i++)
				{
					pthread_create(&t, NULL, copy_fn, argv[i]);//calls copy_fn function
					pthread_join(t, (void **)argv[i]);
				}
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printf("Processing time to copy %d files (%d threads) using library functions: %f \n", argc-1, argc-1, cpu_time_used);
			}	
		}
	}
	else
		printf("Enter valid option. \n");
	return 0;
}
