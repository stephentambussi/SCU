#include<stdio.h>
#include<stdlib.h>
#include"dataset.h"
//rest of them
int tracker;
int count;
struct set
{
    int count;//amount of items in array
    int id;//size of the array
};
struct data
{
    int ID;
    int age;
};
Data students[3000];//array of structs to contain students and their ids --sorted by ID now
void createDataSet(int maxStudents)//O(n)
{
    srand(0);
    int tempage;
    for(int i=0;i<maxStudents;i++)//initializes them to negative -1
		students[i].ID=-1;
	for (int i=0;i<1000;i++)
    {
		tempage= rand() % (30+1-18)+18;
		insertion(tempage);
	}
    printf("Random set of %d generated\n", count);
}
int destroyDataSet()//O(n)
{
	int top=count;
	for (int i=0;i<tracker+2;i++)//destroys by setting data equal to null
	{
		if(students[i].ID!=-1)
        {
			students[i].ID=-1;
			students[i].age=-1;
			count--;
		}
	}
	return count;//Verify success
}
int searchID(int id)//O(1)
{
	int h=(id%2003);
	printf("%d\n",h);
	printf("%d\n",id);
	if(students[h].ID==id)
		return h;
	return 0;
}
DS insertion(int age)//O(1)
{
    DS temp;
	if(count==1001)
    {
			temp.count=0;
			temp.id=0;
			return temp;
	}
	tracker=(tracker+rand()%(2+1-1)+1);
	int h=(tracker%2003);
	students[h].age=age;
	students[h].ID=h;
	count++;
	temp.id=students[h].ID;
	temp.count=count;
	return temp;
}
int deletion(int id)//O(n) -- deletes a specific instance of id
{
	int h = (id%2003);
	if(students[h].ID==id)
    {
		if(h==tracker%2003)
        {
			h--;
			while(students[h].ID==-1)
				h--;
			tracker=students[h].ID;
			count--;
		}
		students[h]=students[tracker%2003];
		count--;
		return count;
	}
return 0;
}
