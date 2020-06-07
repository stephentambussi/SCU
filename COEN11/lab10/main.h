#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#define TRUEDEPT(a) (((a)>=1 && (a)<=4) ? (a) : (a=0)) //macro declaration
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
//function declarations
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
pthread_mutex_t mutex;//used for locking