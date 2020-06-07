#include "set.h"
#include "list.h"
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
int avg = 20;
struct node
{
    void *data;
    struct node *next;//next pointer
    struct node *prev;//prev pointer
};
struct list
{
    int count;
    struct node *head;//the pointer that points to the dummy node
    int(*compare)();
};
struct set
{
    LIST **lists;
    int count;
    int length;
    int(*compare)();
    unsigned(*hash)();
};
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)())//O(n)
{
    SET *sp;
    sp = malloc(sizeof(SET));
    sp->count = 0;
    sp->length = maxElts/avg;
    sp->compare = compare;
    sp->hash = hash;
    sp->lists = malloc(sizeof(LIST*)*sp->length);
    for(int i = 0; i<sp->length; i++)
        sp->lists[i]=createList(compare);//calls list.c function
    return sp;
}
void destroySet(SET *sp)//O(n)
{
    for(int i = 0; i<sp->length; i++)
        free(sp->lists[i]);//removes elements 
    free(sp->lists);//removes list
    free(sp);//removes memory allocation for set
}
int numElements(SET *sp)//O(1)
{
    assert(sp!=NULL);
    return(sp->count);
}
void addElement(SET *sp, void *elt)//O(n)
{
    assert(sp!=NULL && elt!=NULL);
    int pos = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->lists[pos], elt)==NULL)//if element doesn't already exist
    {
        addFirst(sp->lists[pos], elt);//adds element to the front of the list
        sp->count++;
    }
}
void removeElement(SET *sp, void *elt)//O(n^2)
{
    assert(sp!=NULL);
    int pos = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->lists[pos], elt)!=NULL)//if it finds element
    {
        removeItem(sp->lists[pos], elt);
        sp->count--;
    }
}
void *findElement(SET *sp, void *elt)//O(n)
{
    assert(sp!=NULL);
    int pos = (*sp->hash)(elt) % sp->length;//gets position
    return findItem(sp->lists[pos], elt);
}
void *getElements(SET *sp)//O(n^2)
{
    assert(sp!=NULL);
    void **copy;
    copy = malloc(sizeof(void*)*sp->count);
    int j = 0;
    struct node *temp;
    for(int i=0; i<sp->length; i++)
    {
        int cnt = numItems(sp->lists[i]);
        if(cnt!=0)
        {
            temp = sp->lists[i]->head->next;
            while(temp != sp->lists[i]->head)
            {
                copy[j] = temp->data;
                j++;
                temp = temp->next;
            }
        }
    }
    return copy;
}