#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int counter=0;
char names[10][20]; //array of strings for names
char name[10]; // string to be rewritten
int department[10]; //array of numbers for departments 1-4 - linked with names
int insert();
int list();
int main(void)
{
	int state=1;
	while(state!=0 && counter<10) 
	{
		printf("\nPress 1 to add name & department.\n");
		printf("Press 2 to show the current list of names.\n");
		printf("Press 0 to quit.\n");
		scanf("%d",&state);
		if(state==1)//insert
		{
			printf("Enter name:");
			char temp[10];
			scanf("%s",temp);
			strcpy(name,temp);
			printf("Enter department:");
			int temp2 = 0;
			scanf("%d",&temp2);
			department[counter] = temp2;
			insert();
		}
		else//list
		{
			list();
		}

	}
	if(counter==10)
	{
		printf("List full.\n");
	}
	return 0;
}	
int insert()//inserts name and department to list
{
	int flag = 0;
	for(int i=0;i<10;i++)
	{
		if(strcmp(names[i],name)==0)
		{
			flag=1;
		}
	}
	if(flag==0)//checks for existing name
	{
		strcpy(names[counter],name);
		counter++;
		printf("Added name!\n");
	}
	else//throws error if name exists
	{
		printf("Error. Name already exists.\n");
	}
}
int list()//lists the names and departments
{
	for(int i=0;i<10;i++)
	{
		printf("Name & Department: %s || %d\n",names[i],department[i]);
	}
}

