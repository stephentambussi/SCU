#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	int divisor, quotient, dividend, score, answer;//initialize variables
	score = 0;//set score to zero
	srand((int)time(NULL));//do not know what this does
	for(int i=0; i<10; i++)//for loop - ten times
	{
	divisor=rand()%12+1;
	quotient=rand()%13;
	dividend=divisor*quotient;
	//both give output
	printf("Dividend=%d\n",dividend);
	printf("Divisor=%d\n",divisor);
	scanf("%d",&answer);//takes input
	if(answer==quotient)//checks if answer is right
	{
		printf("Correct\n");
		score++;

	}
	else//if not - does this
	{
		printf("Incorrect. Correct Answer=%d\n",quotient);
	}
	}
	printf("Correct out of 10 = %d\n",score);//final score
	return 0;
}	
	
