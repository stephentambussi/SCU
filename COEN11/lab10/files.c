#include "main.h"
void readfile(char fileName[], int key)//double check to see if this works correctly
{
	FILE *labfile; //file declaration for IO
	labfile=fopen(fileName,"r");
	if(labfile==NULL)
	{
		printf("No File.\n");
		return;
	}
	char buffer[256];
	char name[20];
	int tempDept;
	union patientinfo tempu;
	while(fgets(buffer, 256, labfile) != NULL)
	{
		for(int i=0;i<256;i++)
			buffer[i]=buffer[i]^key;//decrypts
		sscanf(buffer,"%s %i",name,&tempDept);
		if(tempDept==1)
		{
			sscanf(buffer,"%s %i %f",name,&tempDept,&tempu.fever);
			insert(name, tempDept, tempu);
		}
		else if(tempDept==2)
		{
			sscanf(buffer,"%s %i %s",name,&tempDept,tempu.paintype);
			insert(name, tempDept, tempu);
		}
		else
		{
			sscanf(buffer,"%s %i %i",name,&tempDept,&tempu.daysick);
			insert(name, tempDept, tempu);
		}
	}
	fclose(labfile);
	return;
}
void savefile(char fileName[], int key)
{
	FILE *labfile; //pointer declaration for file
	labfile=fopen(fileName,"w");
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
			if(i==1)
			{
				char buffer[50];
				sprintf(buffer,"%s %d %f",current->name,current->department,current->person.fever);
				for(int i=0;i<50;i++)
				{
					buffer[i]=((buffer[i])^(key));
				}
				fprintf(labfile,"%s",buffer);
				fprintf(labfile,"\n");
			}
			else if(i==2)
			{
				char buffer[50];
				sprintf(buffer,"%s %d %s",current->name,current->department,current->person.paintype);
				for(int i=0;i<50;i++)
				{
					buffer[i]=((buffer[i])^(key));
				}
				fprintf(labfile,"%s",buffer);
				fprintf(labfile,"\n");
			}
			else if(i==3||i==4)
			{
				char buffer[50];
				sprintf(buffer,"%s %d %i",current->name,current->department,current->person.daysick);
				for(int i=0;i<50;i++)
				{
					buffer[i]=((buffer[i])^(key));
				}
				fprintf(labfile,"%s",buffer);
				fprintf(labfile,"\n");
			}
			current=current->next;
		}
	}
	fclose(labfile);
	return;
}
void read_auto_save(char fileName[])
{
	FILE *labfile; //file declaration for IO
	struct Node temp;
	labfile=fopen(fileName,"rb");
	if(labfile==NULL)
	{
		printf("No File.\n");
		return;
	}
	printf("Auto Save Binary File: \n");
	pthread_mutex_lock(&mutex);
	while((fread(&temp,sizeof(struct Node),1,labfile))==1)//iterates through file
	{
		if(temp.department==1)
		{
			printf("Patient: %s --Department: %i --Fever Temperature: %f degrees.\n",temp.name,temp.department,temp.person.fever);
		}
		else if(temp.department==2)
		{
			printf("Patient: %s --Department: %i --Pain Type: %s.\n",temp.name,temp.department,temp.person.paintype);
		}
		else if(temp.department==3||temp.department==4)
		{
			printf("Patient: %s --Department: %i --Days Sick: %i days.\n",temp.name,temp.department,temp.person.daysick);
		}

	}
	pthread_mutex_unlock(&mutex);
	fclose(labfile);
	return;
}
void *autosaveThread(void *arg)
{
	int i=1;
	FILE *labfile;
	while(i==1)
	{
		sleep(15);
		labfile=fopen(arg,"wb");
		struct Node *current;
		for(int i=1;i<5;i++)
		{
			pthread_mutex_lock(&mutex);
			current=arr[i].head;
			pthread_mutex_unlock(&mutex);
			while(current!=NULL)
			{
				pthread_mutex_lock(&mutex);
				fwrite(current,sizeof(struct Node),1,labfile);//writes to the binary file
				current=current->next;
				pthread_mutex_unlock(&mutex);
			}
		}
		fclose(labfile);
	}
}