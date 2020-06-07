#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "set.h"
#define E 1//empty
#define F 2//filled
#define D 3//deleted
static int search();
//unsigned = integer that can't be negative
typedef struct set 
{
    int count;//number of elements in array
    int length;//size of array
    void **data;
    char *flags;//array to check if element in **data index is filled/deleted/empty
    int(*compare)();
    unsigned(*hash)();
}SET;
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)())//O(n)
{
    SET *sp;
    sp=malloc(sizeof(SET));//allocates memory
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(sizeof(void*)*maxElts);
    assert(sp->data!=NULL);
    sp->flags=malloc(sizeof(char*)*maxElts);
    assert(sp->flags!=NULL);
    for(int i=0; i<maxElts; i++)
        sp->flags[i] = E; //sets all flags to empty
    sp->compare = compare;//functions to be called later in program
    sp->hash = hash;
    return sp;
}
void destroySet(SET *sp)//O(1)
{
    assert(sp!=NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
    return;
}
int numElements(SET *sp)//return number of elements in array -- O(1)
{
    return sp->count;
}
void addElement(SET *sp, void *elt)//adds element -- O(n)
{
    assert(sp != NULL);
    assert(elt != NULL);
    if(sp->count == sp->length)
        return;
    bool f = false;
    int i = search(sp, elt, &f);//finds index to add element
    if(f==true || i==-1)//if it already exists -- don't add it 
        return;
    sp->data[i] = elt;
    sp->count++;
    sp->flags[i] = F;
    return;// end function
}
void removeElement(SET *sp, void *elt)//self explanatory -- O(n)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    bool f = false;
    int i = search(sp, elt, &f);
    if(f==false)
        return;
    sp->data[i] = NULL;
    sp->flags[i] = D;
    sp->count--;
    return;
}
void *findElement(SET *sp, void *elt)//returns element found by search function -- O(n)
{
    assert(sp!=NULL);
    bool f = false;
    int i = search(sp, elt, &f);
    if(f == true)
        return(sp->data[i]);
    return NULL;
}
void *getElements(SET *sp)//copy information in array to new array -- O(n)
{
    int i,j;
    assert(sp!=NULL);
    void **elts = malloc(sizeof(void*) * sp->count);
    assert(elts!=NULL);
    j = 0;
    for(i = 0; i<sp->length; i++)
    {
        if(sp->flags[i]==F)
        {
            elts[j] = sp->data[i];
            j++;
        }
    }
    return elts;
}
static int search(SET *sp, void *elt, bool *found)//binary search function - array is alphabetically sorted -- O(n)
{
    assert(sp!=NULL);
    int position;//variable used for hash f()
    unsigned key = sp->hash(elt);//initializes key variable from returned hash f() value 
    int firstdelete=0;
    int mem;
    *found = false;
    for(int i=0; i<sp->length; i++)
    {
        position = (key+i)%(sp->length);//linear probing
        if(sp->flags[position]==F)
        {
            if(sp->compare(elt, sp->data[position])==0)//if key is found in filled position | else is not found
            {
                *found = true;
                return(position);
            }
        }
        if(sp->flags[position]==D)
            if(firstdelete==0)
            {
                mem = position;
                firstdelete = 1;
            }
        if(sp->flags[position]==E)
        {
            if(firstdelete==1)
            {
                return(mem);
            }
            return(position);
        }
    }
    return -1;
}