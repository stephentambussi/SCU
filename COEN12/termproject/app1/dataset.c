#include<stdio.h>
#include<stdlib.h>
#include"dataset.h"
//rest of them
int maxa = 0;//Max age
int mina = 0;//Min age
int tracker;
int count;
struct set
{
    int count;//amount of items in array
    int id;//size of the array
};
int students[32][3000];//2d array to contain students and their ids --sorted by age
void createDataSet(int maxStudents)//O(n)
{
    srand(0);
    int tempage;
    for(int i=18; i<31; i++)
    {
        students[i][0] = i;//creates age categories in 2d array
        for(int j=1; j<maxStudents; j++)
            students[i][j] = -1;//just sets it equal to something
    }
    for(int k=0;k<1000;k++)
    {
        tempage = rand() % (30+1-18)+18;
        if(k==0)
        {
            maxa = tempage;
            mina = tempage;
        }
        insertion(tempage);
    }
    printf("Random set of %d generated\n", count);
}
int destroyDataSet()//O(n)
{
	for(int i=18; i<31; i++)
	{
		int j=1;
		while(students[i][j]!=-1)
        {
		    students[i][j]=-1;
			j++;
			count--;
		}
	}
	return count;
}
void searchAge(int age)//O(n)
{
    int i=0;
	int ck=0;
	while(students[age][i]!=-1)
    {
		if (ck==0)
        {
			printf("ID's in age group:\n");
			ck++;
        }
		printf("%d\t",students[age][i]);
		i++;
	}
	if(ck==0)
		printf("No age matches\n");
}
DS insertion(int age)//O(n)
{
    DS temp;
	int j=0;
	if (age>31)
    {
		temp.count = -1;
		temp.id = -1;
		return temp;
	}
	if (count==3000)
    {
			temp.count = 0;
			temp.id = 0;
			return temp;
	}
	while(students[age][j]!=-1)
		j++;
	if (count==0)
    {
		students[age][j]=rand()%(2+1-1);//random id num -- follows method
		tracker = students[age][j];
	}
	else
    {
		students[age][j]=(tracker + rand()%(2+1-1)+1);//random id num -- follows method
		tracker = students[age][j];
	}
	if(age > maxa)
		maxa = age;
	if(age < mina)
		mina = age;
	count++;
	temp.id = tracker;
	temp.count = count;
	return temp;
}
int deletion(int age)//O(n)
{
    if(age>30)
		return count;
	if(age<18)
		return count;
	int i=1;
	int newcount;
	if(age==maxa)//reduces max age bc of removal
		maxa--;
	if(age==mina)//increases min age bc of removal
		mina++;
	newcount=count;
	while(students[age][i]!=-1)
    {
		students[age][i]=-1;
		i++;
		count--;
	}
	return newcount;
}
int maxAgeGap()//O(1)
{
    return(maxa-mina);
}