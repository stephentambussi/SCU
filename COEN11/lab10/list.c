#include "main.h"
void insert(char x[],int y,union patientinfo u)//inserts name and department to list
{
	int check = check_duplicate(x);
	if(check==0)//checks for existing name
	{
		struct Node *tempor = (struct Node*)malloc(sizeof(struct Node));
		if(arr[y].head==NULL)
		{
			arr[y].head=tempor;
			arr[y].tail=tempor;
			tempor->prev=NULL;
			tempor->next=NULL;
		}
		else 
		{
			tempor->prev=arr[y].tail;
			tempor->next=NULL;
			arr[y].tail->next=tempor;
			arr[y].tail=tempor;
		}
		tempor->person.fever=u.fever;
		strcpy(tempor->person.paintype,u.paintype);
		tempor->person.daysick=u.daysick;
		tempor->department = y;
		strcpy(tempor->name,x);
		printf("Added entry!\n");
	}
	else//throws error if name exists
	{
		printf("Error. Name already exists.\n");
	}
}
void show()//lists the names and departments
{
	struct Node *tempor;
	int i;
	for(i=1;i<5;i++)
	{
		tempor = arr[i].head;
		while(tempor != NULL)
		{
			if(i==1)
				printf("Name--Department--Info: %s -- %d -- %f Degrees\n",tempor->name,tempor->department,tempor->person.fever);//this works-use as example
			else if(i==2)
				printf("Name--Department--Info: %s -- %d -- %s Pain\n",tempor->name,tempor->department,tempor->person.paintype);
			else if(i==3||i==4)
				printf("Name--Department--Info: %s -- %d -- %i Days\n",tempor->name,tempor->department,tempor->person.daysick);
			tempor=tempor->next;
		}
	}
}
void Remove()//removes oldest item on list with department
{
	printf("Remove entry on list with given department: ");
	int removenum;
	scanf("%d",&removenum);
	struct Node *current = arr[removenum].head;
	if(removenum>0 && removenum<5)
	{
		while(current!=NULL)
		{
			if(current->department==removenum)
			{
				if(arr[removenum].head==arr[removenum].tail)
					arr[removenum].head=arr[removenum].tail=NULL;//if only one entry is in list
				else if(current==arr[removenum].head)//if entry is at the front of the list
				{
					arr[removenum].head=arr[removenum].head->next;
					arr[removenum].head->prev=NULL;
				}
				else if(current==arr[removenum].tail)//if entry is at the end of the list
				{
					arr[removenum].tail=arr[removenum].tail->prev;
					arr[removenum].tail->next=NULL;
				}
				else //this breaks the 'link' in a chain, removes the link and then reattaches the chain
				{
					current->prev->next=current->next; 
					current->next->prev=current->prev;
					free(current);
				}
				return;
			}
			current = current->next;//make sure this is at the end so it does not cause segmentation fault
		}
	}
	else
	{
		printf("Department does not exist. Try again.\n");
	}	
}
void show_dept()//shows all the items with given department
{
	printf("Enter department number you wish to see entries for: ");
	int tempd;
	scanf("%d",&tempd);
	struct Node *current = arr[tempd].head;//the pointer for the struct
	if(TRUEDEPT(tempd))
	{
		while(current != NULL)//do not need ->next 
		{
			printf("Name & Department: %s -- %d\n",current->name,current->department);
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
	int flag = 0;
	int i;
	for(i=1;i<5;i++)
	{
		struct Node *tempor = arr[i].head;
		while(tempor != NULL)
		{
			if(strcmp(tempor->name,b)==0)
			{
				flag=1;
			}
			tempor = tempor->next;
		}
	}
	return(flag);
}
void show_info(char pname[])//displays patient medical info
{
	int flag=0;
	struct Node *current;
	for(int i=1;i<5;i++)
	{
		current = arr[i].head;
		while(current!=NULL)//do not need -> next
		{
			if(strcmp(current->name,pname)==0)
			{
				flag=0;
				if(current->department==1)
				{
					printf("Patient: %s --Department: %i --Fever Temperature: %f degrees.\n",current->name,current->department,current->person.fever);
					break;
				}
				else if(current->department==2)
				{
					printf("Patient: %s --Department: %i --Pain Type: %s.\n",current->name,current->department,current->person.paintype);
					break;
				}
				else if(current->department==3||current->department==4)
				{
					printf("Patient: %s --Department: %i --Days Sick: %i days.\n",current->name,current->department,current->person.daysick);
					break;
				}
			}
			else
			{
				flag=1;
			}
			current = current->next;
		}
	}
	if(flag==1)
	{
		printf("Name not found.\n");
	}
	return;
}
void deletenodes()//removes the allocated memory
{
	struct Node *deleter,*temp;
	int i;
	for(i=1;i<5;i++)
	{
		deleter=arr[i].head;
		while(deleter!=NULL)
		{
			temp=deleter;//need this to be able to iterate through the list
			free(temp);
			deleter=deleter->next;
		}
	}
}
