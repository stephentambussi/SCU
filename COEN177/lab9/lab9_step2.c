/* Name: Stephen Tambussi
 * Date: 5/27/2021
 * Title: Lab 9 - File Performance Measurement
 * Description: This program evaluates file system performance during sequential I/O requests
 * by reading and writing to the disk. Step 2 of lab. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 10000

int main(int argc, char *argv[])
{
	if(argc < 2) //error checking
	{
		printf("Error: not enough command line arguments. \n");
		return 0;
	}
	char buffer[BUF_SIZE];
	FILE *fp;
	fp = fopen(argv[1], "rb"); //open file
	while(fread(buffer, sizeof(buffer), 1, fp)) //keeps reading the file until the number of elements read is 0 (end of file)
	{
	}
	fclose(fp); //close file
	return 0;
}
