#include<stdio.h>
#include<stdlib.h>
#include<string.h>
union patientinfo//union declaration
{
	float fever;
	char paintype[20];
	int daysick;
};
struct Node//node declaration
{
	char name[20];
	int department;
	union patientinfo person;
	struct Node *next;
};
struct Node *head = NULL;//declare node pointers
struct Node *tail = NULL;
int insert();//do not need pointers
int show();
int Remove();
int show_dept(); 
int check_duplicate();
int show_info();//new function that displays info for given name
int main(void)
{
	head = (struct Node*)malloc(sizeof(struct Node)); //initialize node pointers - have to initialize in a function
	tail = (struct Node*)malloc(sizeof(struct Node));
	int state=1;
	while(state!=0) 
	{
		printf("\nPress 1 to add name & department. Departments: 1,2,3,4 \n");
		printf("Press 2 to show the current list of names.\n");
		printf("Press 3 to remove the oldest item on list with the given department.\n");
		printf("Press 4 to display the items on list with given department.\n");
		printf("Press 5 to display the patient's medical info with the given name.\n");
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
		else if(state==5)
		{
			printf("Enter name of patient:");
			char temp[10];
			scanf("%s",temp);
			show_info(temp);
		}
	}
	return 0;
}	
int insert(char x[],int y)//inserts name and department to list
{
	int check = check_duplicate(x);
	if(check==0)//checks for existing name
	{
		struct Node *tempor = head;
		while(tempor->next != NULL)
		{
			tempor = tempor->next;
		}
		tempor->next = (struct Node*)malloc(sizeof(struct Node));
		printf("Enter info of illness.\n");
		if(y==1)//adds info of illness
		{
			printf("D1=Fever temperature: ");
			float temp1;
			scanf("%f",&temp1);
			tempor->next->person.fever=temp1;
		}
		else if(y==2)
		{
			printf("D2=Type of pain: ");
			char type[10];
			scanf("%s",type);
			strcpy(tempor->next->person.paintype,type);
		}
		else if(y==3||y==4)
		{
			printf("D3&D4=Days sick: ");
			int temp2;
			scanf("%i",&temp2);
			tempor->next->person.daysick=temp2;
		}
		tempor->next->department = y;
		strcpy(tempor->next->name,x);
		tempor->next->next = NULL;
		tail = tempor->next->next;//tail is equal to last element on list
		printf("Added entry!\n");
	}
	else//throws error if name exists
	{
		printf("Error. Name already exists.\n");
	}
}
int show()//lists the names and departments
{
	struct Node *tempor = head->next;//do this so it does not print out first empty node in list
	while(tempor != NULL)
	{
		printf("Name & Department: %s || %d\n",tempor->name,tempor->department);//this works-use as example
		tempor = tempor->next;
	}
}
int Remove()//removes oldest item on list with department
{
	struct Node *current = head;
	struct Node *temp = NULL;
	printf("Remove entry on list with given department: ");
	int removenum;
	scanf("%d",&removenum);
	if(removenum>0 && removenum<5)
	{
		while(current->next != NULL)
		{
			if(current->next->department==removenum)
			{
				if(current->next==head)
				{
					tail=head;
					free(tail);
					break;
				}
				temp = current->next;
				current->next = temp->next;
				free(temp);//frees previously allocated memory
				break;
			}
			current = current->next;//make sure this is at the end so it does not cause segmentation fault
		}
	}
	else
	{
		printf("Department does not exist. Try again.\n");
	}	
}
int show_dept()//shows all the items with given department
{
	struct Node *current = head;//the pointer for the struct
	printf("Enter department number you wish to see entries for: ");
	int tempd;
	scanf("%d",&tempd);
	if(tempd>0 && tempd<5)
	{
		while(current != NULL)//do not need ->next 
		{
			if(current->department==tempd)
			{
				printf("Name & Department: %s || %d\n",current->name,current->department);
			}
			current = current->next;
		}
	}	
	else
	{
		printf("Department does not exist. Try again.\n");
	}
}

int check_duplicate(char b[])//checks for duplicate items
{
	struct Node *tempor = head;
	int flag = 0;
	while(tempor != NULL)
	{
		if(strcmp(tempor->name,b)==0)
		{
			flag=1;
		}
		tempor = tempor->next;
	}
	return(flag);
}
int show_info(char pname[])//displays patient medical info
{
	struct Node *current = head;
	int flag=0;
	while(current != NULL)//do not need -> next
	{
		if(strcmp(current->name,pname)==0)
		{
			flag=0;
			if(current->department==1)
			{
				printf("Patient: %s  |Department: %i  |Fever Temperature: %f degrees.\n",current->name,current->department,current->person.fever);
				break;
			}
			else if(current->department==2)
			{
				printf("Patient: %s  |Department: %i  |Pain Type: %s.\n",current->name,current->department,current->person.paintype);
				break;
			}
			else if(current->department==3||current->department==4)
			{
				printf("Patient: %s  |Department: %i  |Days Sick: %i days.\n",current->name,current->department,current->person.daysick);
				break;
			}
		}
		else
		{
			flag=1;
		}
		current = current->next;
	}
	if(flag==1)
	{
		printf("Name not found.\n");
	}
	return 0;
}
