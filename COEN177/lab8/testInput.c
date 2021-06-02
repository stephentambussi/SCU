/* Name: Stephen Tambussi
 * Date: 5/20/2021
 * Title: Lab8 - Memory management
 * Description: This program creates the testInput.txt file.
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char buffer[sizeof(int)];
	int i;
	fp = fopen("testInput10K.txt", "w");
	for(i = 0; i < 10000; i++)
	{
		sprintf(buffer, "%d\n", rand() % 1000);
		fputs(buffer, fp);
	}
	fclose(fp);
	return 0;
}
