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
	struct Node *prev;
};
struct LIST
{
	struct Node *head;
	struct Node *tail;
}LIST;
struct LIST arr[5]; // declare the array of lists
void insert();
void show();
void Remove();
void show_dept(); 
int check_duplicate();
void show_info();//function that displays info for given name
void change_dept();//XC
void readfile();
void savefile();
void deletenodes();
int main(int argc, char *argv[])
{
	if(argc==1)
	{
		printf("The name of the file is missing\n");
		return 1;
	}
	//initialize node pointers - have to initialize in a function
	for(int i=1;i<5;i++)
	{
		arr[i].head=NULL;
		arr[i].tail=NULL;
	}
	int state=1;
	readfile(argv[1]);
	while(state!=0) 
	{
		printf("\nPress 1 to add name & department. Departments: 1,2,3,4 \n");
		printf("Press 2 to show the current list of names.\n");
		printf("Press 3 to remove the oldest item on list with the given department.\n");
		printf("Press 4 to display the items on list with given department.\n");
		printf("Press 5 to display the patient's medical info with the given name.\n");
		printf("Press 6 to change an entry to a different department. -- Extra Credit\n");
		printf("Press 0 to quit.\n");
		scanf("%d",&state);
		if(state==1)//insert
		{
			union patientinfo u;
			printf("Enter name:");
			char temp[20];
			scanf("%s",temp);
			printf("Enter department:");
			int temp2 = 0;
			scanf("%d",&temp2);
			if(temp2>0 && temp2<5)
			{
				printf("Enter info of illness.\n");
				if(temp2==1)//adds info of illness
				{
					printf("D1=Fever temperature: ");
					scanf("%f",&u.fever);
				}
				else if(temp2==2)
				{
					printf("D2=Type of pain: ");
					scanf("%s",u.paintype);
				}
				else if(temp2==3||temp2==4)
				{
					printf("D3&D4=Days sick: ");
					scanf("%i",&u.daysick);
				}
				insert(temp,temp2,u);
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
		else if(state==6)
			change_dept();
	}
	savefile(argv[1]);
	for(int i=1;i<5;i++)
	{
		deletenodes(arr[i].head);//goes through whole list
	}
	return 0;
}	
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
	if(tempd>0 && tempd<5)
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
void readfile(char fileName[])
{
	FILE *labfile; //file declaration for IO
	struct Node temp;
	labfile=fopen(fileName,"rb");
	if(labfile==NULL)
	{
		printf("No File.\n");
		return;
	}
	while((fread(&temp,sizeof(struct Node),1,labfile))==1)//iterates through file
	{
		insert(temp.name, temp.department, temp.person);
	}
	fclose(labfile);
	return;
}
void savefile(char fileName[])
{
	FILE *labfile; //pointer declaration for file
	labfile=fopen(fileName,"wb");
	if(labfile==NULL)
	{
		printf("File does not exist. Creating new file.\n");//creates file if it does not exist
		return;
	}
	struct Node *current;
	int i;
	for(i=1;i<5;i++)
	{
		current = arr[i].head;
		while(current != NULL)
		{
			fwrite(current,sizeof(struct Node),1,labfile);
			current=current->next;
		}
	}
	fclose(labfile);
	return;
}
void deletenodes(struct Node *p)//removes the allocated memory
{
	struct Node *deleter;
	if(p==NULL)//if it is empty
		return;
	else
	{
		deleter=p;//pointer to p
		free(deleter);//removes memory allocation
		deletenodes(p->next);//recursive call
	}
}
void change_dept()//Extra Credit function
{	
	char name[20];
	printf("Enter name to change department number: ");
	scanf("%s", name);
	if(check_duplicate(name)==0)
	{
		printf("The name: %s does not exist", name);
		return;
	}
	printf("Old Department: \n");
	int olddept;
	scanf("%d", &olddept);
	printf("New Department: \n");
	int newdept;
	scanf("%d", &newdept);
	union patientinfo u;
	struct Node *current = arr[olddept].head;
	int nd = 0;
	struct Node *temp = arr[olddept].head;
	while(temp != NULL)
	{
	        if(strcmp(temp->name,name)==0)
                {	
			if(newdept==1)
                        {
                                printf("Fever temperature: \n");
                                scanf("%f",&u.fever);
                        }
			if(newdept==2)
                        {
                                printf("Pain type: \n");
                                scanf("%s",u.paintype);
                        }
			if(newdept==3 || newdept==4)
                        {
                                printf("Days sick: \n");
                                scanf("%d",&u.daysick);
                        }
			if(arr[olddept].head == arr[olddept].tail)
			{
				arr[olddept].head = arr[olddept].tail = NULL;
				nd++;
			}	
			else if(temp == arr[olddept].head)
			{
				arr[olddept].head = arr[olddept].head->next;
				arr[olddept].head->prev = NULL;
				nd++;
			}
			else if(current == arr[olddept].tail)
			{
				arr[olddept].tail = arr[olddept].tail->prev;
				arr[olddept].tail->next = NULL;
				nd++;
			}
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
				nd++;
			}
				
                }
                current = current->next;
		temp = temp->next;
	}
	if(nd==0)
        {
                printf("Error. There is no one named %s in department #%d", name, olddept);
                return;
        }
	insert(name, newdept, u);
	return;
}
