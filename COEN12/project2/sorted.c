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
//*****
void addElement(SET *sp, char *elt)//adds element -- O(n)
{
    assert(sp!=NULL);
    bool f = false;
    if(sp->count < sp->length) //makes sure array is not full
    {
        int index = search(sp, elt, &f);//checks if there are duplicates 
        if(f==false)//only adds element if there are no duplicates
        {
            for(int i=sp->count; i>index; i--)//shifts up elements to make space for new element
            {
                sp->data[i] = sp->data[i-1];
            }
            sp->data[index] = strdup(elt);
            sp->count++;
            return;
        }
    }
    else
        printf("Array is full! Element not added.\n");
}
//*****
void removeElement(SET *sp, char *elt)//self explanatory -- O(n)
{
    assert(sp!=NULL);
    bool f = false;
    int index = search(sp, elt, &f);
    if(f==false)//checks if element in array even exists --> if not do not do anything
        return;
    free(sp->data[index]);//clears memory allocation
    for(int i=index+1; i<sp->count; i++)
    {
        sp->data[i-1] = sp->data[i];
    }
    sp->count--;
    return;
}
char *findElement(SET *sp, char *elt)//returns element found by search function -- O(logn)
{
    assert(sp!=NULL);
    bool f = true;
    int i = search(sp, elt, &f);
    if(f==true)
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
static int search(SET *sp, char *elt, bool *found)//binary search function - array is alphabetically sorted -- O(logn)
{
    assert(sp!=NULL);
    int low, mid, high;
    low = 0;//first element
    high = sp->count-1;//last element
    while(low<=high)
    {
        mid = (low+high)/2;//middle of array
        if(strcmp(sp->data[mid],elt)==0)//if element is found in middle of array
        {
            *found = true;
            return mid;//return index of where element is
        }
        if(strcmp(sp->data[mid],elt)>0)//element is in upper half
        {
            low = mid+1;
        }
        else//--> if(strcmp(sp->data[mid],elt)<0) ==> element is in lower half
        {
            high = mid-1;
        }
    }
    *found = false;
    return low;//will return 0 if element not found
}