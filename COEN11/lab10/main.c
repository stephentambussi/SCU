#include "main.h"
void insert();
void show();
void Remove();
void show_dept(); 
int check_duplicate();
void show_info();//function that displays info for given name
void readfile();
void savefile();
void read_auto_save();//reads autosaved binary file
void *autosaveThread();//
void deletenodes();
extern pthread_mutex_t mutex;//used for locking
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
	int key = atoi(argv[3]);//converts string to int
	readfile(argv[1], key);
	pthread_t mythread;//sets thread name
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&mythread, NULL, autosaveThread, argv[2]);//argument is binary file name
	while(state!=0) 
	{
		printf("\nPress 1 to add name & department. Departments: 1,2,3,4 \n");
		printf("Press 2 to show the current list of names.\n");
		printf("Press 3 to remove the oldest item on list with the given department.\n");
		printf("Press 4 to display the items on list with given department.\n");
		printf("Press 5 to display the patient's medical info with the given name.\n");
		printf("Press 6 to display the contents of the binary file.\n");
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
			if(TRUEDEPT(temp2))
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
			read_auto_save(argv[2]);
			
	}
	pthread_mutex_lock(&mutex);
	pthread_cancel(mythread);
	savefile(argv[1], key);
	deletenodes();
	return 0;
}