//text file data compression
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"
typedef struct node NODE;
int numhops(struct node *leaf) //O(n)
{
	int cnt = 0;
	while(leaf->parent!=NULL) 
    {
		leaf = leaf->parent;
		cnt++;
	}
	return cnt;
}
int compare(struct node *one, struct node *two) 
{
	return (one->count < two->count) ? -1 : (one->count > two->count);
}
int main(int argc, char *argv[])
{
	
	FILE *fp = fopen(argv[1],"r");		
	if (fp == NULL) 
    {				
  		return 0;
	}
    //part1 -- counts the occurrences of letters in txt file -- O(n)
	int occur[257] = {0};			
	do {						
	  int c;
      c = fgetc(fp);
      occur[c]++;
    } while(!(feof(fp)));
    //part2
    PQ *pq = createQueue(compare);
    struct node* leaves[257] = {0};			
    for (int i=0; i<257; i++) 
    {			
    	leaves[i] = NULL;
    }
    for (int i=0; i<256; i++) //O(n)
    {	
    	if (occur[i]>0) //if specific letter actually occurs
    	{
    		NODE *node=malloc(sizeof(struct node));
    		node->count = occur[i];
    		node->parent = NULL;
    		addEntry(pq,node);
    		leaves[i]= node;
    	}
    }

    NODE *zeroCount = malloc(sizeof(struct node));
    zeroCount->count = 0;
    zeroCount->parent = NULL;
    addEntry(pq,zeroCount);
    leaves[256] = zeroCount;

    //part3 -- removes trees 
    while(numEntries(pq)>1) //O(n)
    {
    	NODE *first = removeEntry(pq);	
    	NODE *second = removeEntry(pq);				
    	NODE *third = malloc(sizeof(struct node));		
    	third->count = first->count + second->count;
    	third->parent = NULL;
    	first->parent = third;
    	second->parent = third;
    	addEntry(pq, third);					
    }
    //part5
    for (int i=0; i<257; i++) //O(n)
    {
    	if (leaves[i]!=NULL) 
        {
    		int numOfHops;
    		numOfHops = numhops(leaves[i]);
            int total = occur[i]*numOfHops;
    		if (isprint(i))								
    			printf("%c: %d x %d bits = %d\n", i, occur[i], numOfHops, total);//if its an actual character
    		else 
    			printf("%03o: %d x %d bits = %d\n", i, occur[i], numOfHops, total);
    	}
    }
    pack(argv[1],argv[2],leaves);//actually compresses the file
}