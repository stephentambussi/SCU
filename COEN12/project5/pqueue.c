#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define p(i) (((i)-1)/2)//parent index
#define l(i) (((i)*2)+1)//left child index
#define r(i) (((i)*2)+2)//right child index
struct pqueue
{
    int count;//amount of items in array
    int length;//size of the array
    void **data;//the array
    int (*compare)();
};
PQ *createQueue(int(*compare)()) //O(1)
{
    PQ *pq;
    pq = malloc(sizeof(PQ));
    pq->compare = compare;
    pq->count = 0;
    pq->length = 10;//initial length
    pq->data = malloc(sizeof(void*)*pq->length);
    return pq;
}
void destroyQueue(PQ *pq) //O(1)
{
    assert(pq!=NULL);
    free(pq->data);
    free(pq);
}
int numEntries(PQ *pq) //O(1)
{
    assert(pq!=NULL);
    return(pq->count);
}
void addEntry(PQ *pq, void *entry) //O(n)
{
    assert(pq!=NULL);
    if(pq->count+1 > pq->length)
    {
        pq->data = realloc(pq->data, sizeof(void*)*pq->length*2);
        pq->length = pq->length*2;
    }
    int i = pq->count;
    pq->data[i] = entry;//adds new entry to end of the array
    int parent = p(i);//prepares for reshuffling
    while(parent >= 0)
    {
        if((*pq->compare)(pq->data[parent], pq->data[i]) > 0)
        {
            void *temp = pq->data[i];
            pq->data[i] = pq->data[parent];
            pq->data[parent] = temp;
        }
        else
        {
            break;
        }
        i = parent;
        parent = p(parent);
    }
    pq->count++;
}
void *removeEntry(PQ *pq) //O(n)
{
    assert(pq!=NULL);
    int cp1;
    int i = 0;
    void *child;
    void *temp;
    int min = 0;
    child = pq->data[i];
    pq->data[i] = pq->data[pq->count-1];
    pq->count--;
    while(l(i) < pq->count)
    {
        if(r(i) < pq->count)
        {
            cp1 = (*pq->compare)(pq->data[l(i)], pq->data[r(i)]);
            if(cp1 < 0)
                min = l(i);
            else
                min = r(i);
        }
        else
            min = l(i);
        if(((*pq->compare)(pq->data[i], pq->data[min])) > 0)
        {
            temp = pq->data[i];
            pq->data[i] = pq->data[min];
            pq->data[min] = temp;
        }
        else 
            break;
        i = min;
    }
    return child;
}