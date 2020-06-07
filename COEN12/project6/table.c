# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"
# define EMPTY   0
# define FILLED  1
# define DELETED 2

struct set 
{
    int count;//amount of elements in array     
    int length;//length of array -- how many elements it can hold                 
    void **data;//the array itself                
    char *flags;//parallel array that holds data about each indexes' state(Filled, Empty, or deleted)               
    int (*compare)();//compare function		
    unsigned (*hash)();//hash function		
};
static int partition(void **elts, int low, int high, int(*compare)())//works in conjuction with quick sort --O(n)
{//reorders around the pivot so that elements less than pivot go before it and values greater go after
	int sep;
	void *x, *temp;
	x=elts[high];
	sep=low;
	for(int i=low; i<high; i++)
	{
		if((*compare)(elts[i],x)<0)
		{
			temp=elts[i];
			elts[i]=elts[sep];
			elts[sep++]=temp;
		}
	}
	temp=elts[high];
	elts[high]=elts[sep];
	elts[sep]=temp;
	return sep;//pivoting
}
static void quicksort(void **elts, int low, int high, int(*compare)())//quicksort function --recursive--O(n^2)--worst
{
	if(low<high)
	{
		int ploc=partition(elts, low, high, compare);
		quicksort(elts, low, ploc-1, compare);//recursion
		quicksort(elts, ploc+1, high, compare);
	}
}
static int search(SET *sp, void *elt, bool *found)//O(n)
{
    int available, i, locn, start;


    available = -1;
    start = (*sp->hash)(elt) % sp->length;

    for (i = 0; i < sp->length; i ++) {
        locn = (start + i) % sp->length;

        if (sp->flags[locn] == EMPTY) {
            *found = false;
            return available != -1 ? available : locn;

        } else if (sp->flags[locn] == DELETED) {
            if (available == -1)
		available = locn;

        } else if ((*sp->compare)(sp->data[locn], elt) == 0) {
            *found = true;
            return locn;
        }
    }

    *found = false;
    return available;
}
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())//O(n)
{
    int i;
    SET *sp;
    assert(compare != NULL && hash != NULL);

    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(char *) * maxElts);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (i = 0; i < maxElts; i ++)
        sp->flags[i] = EMPTY;

    return sp;
}
void destroySet(SET *sp)//O(1)
{
    assert(sp != NULL);

    free(sp->flags);
    free(sp->data);
    free(sp);
}
int numElements(SET *sp)//O(1)
{
    assert(sp != NULL);
    return sp->count;
}
void addElement(SET *sp, void *elt)//O(n)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if(!found) 
    {
	    assert(sp->count < sp->length);
	    sp->data[locn] = elt;
	    sp->flags[locn] = FILLED;
	    sp->count ++;
    }
}
void removeElement(SET *sp, void *elt)//O(n)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if(found) 
    {
	    sp->flags[locn] = DELETED;
	    sp->count --;
    }
}
void *findElement(SET *sp, void *elt)//O(n)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);

    locn = search(sp, elt, &found);
    return found ? sp->data[locn] : NULL;
}
void *getElements(SET *sp)//added this function --O(n^2)
{
    void **elts;
    assert(sp != NULL);
    elts = malloc(sizeof(void *)* sp->count);
    assert(elts!=NULL);
    int j=0;
    for(int i=0; i<sp->length; i++)
    {
	    if (sp->flags[i] == FILLED)
	        elts[j++] = sp->data[i];
    }
	quicksort(elts, 0, j-1, sp->compare);//calls the new quick sort function
    return elts;
}
