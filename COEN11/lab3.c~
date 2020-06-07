#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int counter=0;
struct urgentcare//struct declaration
{
	int department;
	char name[20];
};
struct urgentcare apptmnt[10]; //array of structs-creates ten structs
int insert();//do not need pointers
int show();
int Remove();
int show_dept(); 
int check_duplicate();
int main(void)
{
	int state=1;
	while(state!=0 && counter<10) 
	{
		printf("\nPress 1 to add name & department. Departments: 1,2,3,4 \n");
		printf("Press 2 to show the current list of names.\n");
		printf("Press 3 to remove the oldest item on list with the given department.\n");
		printf("Press 4 to display the items on list with given department.\n");
		printf("Press 0 to quit.\n");
		scanf("%d",&state);
		if(state==1)//insert
		{
			printf("Enter name:");
			char temp[10];
			scanf("%s",temp);
			printf("Enter department:");
			int temp2 = 0;
			scanf("%d",&temp2);
			if(temp2>0 && temp2<5)
			{
				insert(temp,temp2);
			}
			else
			{
				printf("Wrong department number. Try again.\n");
			}
		}
		else if(state==2)//show list
		{
			show();
		}
		else if(state==3)//remove
		{
			Remove();
		}
		else if(state==4)//show list with department
		{
			show_dept();
		}

	}
	if(counter==10)
	{
		printf("List full.\n");
	}
	return 0;
}	
int insert(char x[],int y)//inserts name and department to list
{
	int check = check_duplicate(x);
	if(check==0)//checks for existing name
	{
		apptmnt[counter].department = y;
		strcpy(apptmnt[counter].name,x);
		counter++;
		printf("Added name!\n");
	}
	else//throws error if name exists
	{
		printf("Error. Name already exists.\n");
	}
}
int show()//lists the names and departments
{
	struct urgentcare *p;//the pointer for the struct
	p = apptmnt;
	for(int i=0;i<10;i++,p++)
	{
		printf("Name & Department: %s || %d\n",p->name,p->department);//this works-use as example
	}
}
int Remove()//removes oldest item on list with department
{
	struct urgentcare *p1,*p2;//pointers for the struct
	p1 = apptmnt;
	p2 = apptmnt;
	printf("Remove entry on list with given department: ");
	int removenum;
	scanf("%d",&removenum);
	if(removenum>0 && removenum<5)
	{
		int i;
		for(i=0;i<counter;i++,p1++)
		{
			if(p1->department==removenum)
			{
				int tempcnt2 = i+1;
				p2++;//increments pointer position in memory
				while(tempcnt2<=counter)
				{
					strcpy(p1->name,p2->name);
					strcpy(p2->name,"");
					p1->department=p2->department;
					p2->department=0;
					p1++;//increments pointer position in memory
					p2++;//increments pointer position in memory
					tempcnt2++;
				}
				counter--;
				break;
			}
		}
	}
	else
	{
		printf("Department does not exist. Try again.\n");
	}	
}
int show_dept()//shows all the items with given department
{
	struct urgentcare *p;//the pointer for the struct
	p = apptmnt;
	printf("Enter department number you wish to see entries for: ");
	int tempd;
	scanf("%d",&tempd);
	if(tempd>1 && tempd<5)
	{
		for(int i=0;i<counter;i++,p++)
		{
			if(p->department==tempd)
			{
				printf("Name & Department: %s || %d\n",p->name,p->department);
			}
		}
	}	
	else
	{
		printf("Department does not exist. Try again.\n");
	}
}
int check_duplicate(char b[])//checks for duplicate items
{
	struct urgentcare *p;//the pointer for the struct
	p = apptmnt;
	int flag = 0;
	for(int i=0;i<10;i++,p++)
	{
		if(strcmp(p->name,b)==0)
		{
			flag=1;
		}
	}
	return(flag);
}
