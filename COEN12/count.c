#include<stdio.h>
#include<string.h>
#define MAX_WORD_LENGTH 30 //constant declaration
int main(int argc, char *argv[])
{
    if(argc==1)
	{
		printf("The name of the file is missing\n");
		return 1;
	}
    FILE *labfile; //declares file pointer
    labfile=fopen(argv[1], "r");
    if(labfile==NULL)
	{
		printf("No File.\n");
		return 0;
	}
    int count = 0;//counts the number of words
    char buff[MAX_WORD_LENGTH];//stores the words
    while(fscanf(labfile, "%s",buff)==1) //if it is a string then increment count
    {
        count++;
    }
    printf("Total number of words: %d", count);//outputs number of words
    fclose(labfile);
    return count;
}