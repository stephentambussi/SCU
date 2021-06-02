/* Name: Stephen Tambussi
 * Date: 5/27/2021
 * Title: Lab 9 - File Performance Measurement
 * Description: This program evaluates file system performance during sequential I/O requests
 * by reading and writing to the disk. Step 4 of lab. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if(argc < 4) //error checking
	{
		printf("Error: not enough command line arguments. \n");
		return 0;
	}
	int buf_size = atoi(argv[2]); //converts the cmd line argument to an int
	size_t bytes; 
	char buffer[buf_size];
	FILE *fp, *fp2;
	fp = fopen(argv[1], "rb"); //open file for reading
	fp2 = fopen(argv[3], "wb"); //create file for writing
	while((bytes = fread(buffer, 1, sizeof(buffer), fp)) != 0) //keeps reading the file until the number of elements read is 0 (end of file)
	{
		if(fwrite(buffer, 1, bytes, fp2) != bytes) //error check - elements read should equal elements written
			return 1;
	}
	fclose(fp); //close file
	fclose(fp2);
	return 0;
}
