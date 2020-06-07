#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dataset.c"
int maxstudents = 3000;
int main(int argc, int *argv[])
{
    //declarations
    int id, ID;
	int maxb;
	int option;
	int check;
	DS chk;//struct
	while(1)//O(n)
    {
		printf("Press\n1: create data set\n2: destroy data set\n3: to delete an entry\n4: to search for an ID\n5: to quit\n");
		scanf("%d",&option);
		if(option==1)
            createDataSet(maxstudents);//Generate 1000 students
		else if(option==2)
        {
			check=destroyDataSet();
			printf("Records destroyed, number of students enrolled %d\n",check);
        }
		else if(option==4)//searches for ID
        {
			printf("Enter ID to search\n");
			scanf("%d",&ID);
			searchID(ID);
        }
		else if(option==3)
        {
			printf("Enter ID for removal\n");//Removes by ID
			scanf("%d",&ID);
			check=deletion(ID);
			if (check==count)
				printf("Nothing to delete\n");
			else
				printf("Success. %d students enrolled now\n",count);
        }
		else if(option==5)
			return 1;
		else
			printf("Invalid Entry\n");
	}
}
