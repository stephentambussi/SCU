#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dataset.c"
int maxstudents = 3000;
int main(int argc, int *argv[])
{
    //declarations
    int id, age;
	int maxb;
	int option;
	int check;
	DS chk;//struct
	while(1)//O(n)
    {
		printf("Press\n1: create data set\n2: destroy data set\n3: to insert\n4: to delete an entry\n5: for max age gap\n6: to search for age group\n7: to quit\n");
		scanf("%d",&option);
		if(option==1)
            createDataSet(maxstudents);//Generate 1000 students
		else if(option==2)
        {
			check=destroyDataSet();
			printf("Records destroyed, number of students enrolled %d\n",check);
        }
        else if(option==3)
        {
			printf("Enter age\n");
			scanf("%d",&age);
			chk=insertion(age);
			if(chk.count == -1)
				printf("Too old to enroll\n");
			if (chk.count == 0)
				printf("Classes full, try again in the fall\n");
			if(chk.count != -1 && chk.count != 0)
				printf("Success! Your ID number is %d, and the current amount = %d.\n",chk.id,chk.count);
        }
		else if(option==6)
        {
			printf("Enter age to search\n");
			scanf("%d",&age);
			searchAge(age);
        }
		else if(option==5)
        {
			maxb=maxAgeGap();//Prints max age gap
			printf("Max age gap = %d years.\n",maxb);
        }
		else if(option==4)
        {
			printf("Enter age set for removal\n");//Removes all ID's with given age
			scanf("%d",&age);
			check=deletion(age);
			if (check==count)
				printf("Nothing to delete\n");
			else
				printf("Success.%d students enrolled now\n",count);
        }
		else if(option==7)
			return 1;
		else
			printf("Invalid Entry\n");
	}
}
