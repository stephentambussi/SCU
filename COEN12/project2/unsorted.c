#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "set.h"
static int search();
typedef struct set 
{
    int count;//number of elements in array
    int length;//size of array
    char **data;
}SET;
SET *createSet(int maxElts)//O(1)
{
    SET *sp;
    sp=malloc(sizeof(SET));//allocates memory
    assert(sp!=NULL);
    sp->data=malloc(sizeof(char*)*maxElts);
    sp->count=0;
    sp->length=maxElts;
    assert(sp->data!=NULL);
    return sp;
}
void destroySet(SET *sp)//O(n)
{
    assert(sp!=NULL);
    for(int i=0; i<sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp);
    return;
}
int numElements(SET *sp)//return number of elements in array -- O(1)
{
    assert(sp!=NULL);
    return sp->count;
}
void addElement(SET *sp, char *elt)//adds element -- O(n)
{
    assert(sp!=NULL);
    bool f = false;
    if(sp->count < sp->length)
    {
        int flag = search(sp, elt, &f);//checks if there are duplicates
        if(flag==-1)//only adds element if there are no duplicates
        {
            sp->data[sp->count] = strdup(elt);//strdup = allocates memory and copies the string
            sp->count++;
            return;
        }
    }
    else
        printf("Array is full! Element not added.\n");
}
void removeElement(SET *sp, char *elt)//O(n)
{
    assert(sp!=NULL);
    bool f = false;
    int index = search(sp, elt, &f);
    if(index == -1)//checks if element in array even exists --> if not do not do anything
        return;
    //this frees element in array, then replaces it with last element in array
    sp->data[index] = strdup(sp->data[sp->count-1]);//overwrites element to remove with last element in array
    free(sp->data[sp->count-1]);//deletes last element
    sp->count--;
    return;
}
char *findElement(SET *sp, char *elt)//returns element found by search function -- O(n)
{
    assert(sp!=NULL);
    bool f = true;
    int i = search(sp, elt, &f);
    if(i!=-1)
    {
        return(sp->data[i]);
    }
    return NULL;
}
char **getElements(SET *sp)//copy information in array to new array -- O(n)
{
    assert(sp!=NULL);
    char **copy=malloc(sizeof(char*)*sp->length);//allocates memory for array
    for(int i=0; i<sp->count; i++)
    {
        strcpy(copy[i], sp->data[i]);
    }
    return copy;//returns array
}
static int search(SET *sp, char *elt, bool *found)//sequential search function -- O(n)
{
    assert(sp!=NULL);
    for(int i=0; i<sp->count; i++)
    {
        if(strcmp(sp->data[i],elt)==0)
        {
            *found = true;
            return i;//return index of where element is
        }
    }
    *found = false;
    return -1;
}