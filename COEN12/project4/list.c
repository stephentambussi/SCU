#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
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
LIST *createList(int (*compare)())
{
    struct list *lp;
    lp = malloc(sizeof(struct list));
    assert(lp!=NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(struct node));
    assert(lp->head != NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}
void destroyList(LIST *lp)
{
    NODE *pDel, *pNext;
    assert(lp!=NULL);
    pDel = lp->head;//pDel points to head node
    do{
        pNext = pDel->next;//pNext points to node after head(pDel)
        free(pDel);//remove memory allocation of node pointed to by pDel
        pDel = pNext;//pDel points to pNext
    } while(pDel != lp->head);
    free(lp);
}
int numItems(LIST *lp) //O(1)
{
    return(lp->count);
}
void addFirst(LIST *lp, void *item) //O(1)
{
    assert(lp!=NULL);
    NODE *temp = malloc(sizeof(NODE));
    temp->data = item;//sets temp node data to parameter variable
    //inserts temp in front of dummy node
    temp->next = lp->head->next;//sets temp node to point to node that was after head
    temp->prev = lp->head;//head node is now before temp node
    //rearrangement
    lp->head->next->prev = temp;//sets node that was after head to point back to temp
    lp->head->next = temp;//head node now points to temp
    lp->count++;
}
void addLast(LIST *lp, void *item) //O(1)
{
    assert(lp!=NULL);
    NODE *temp = malloc(sizeof(NODE));
    temp->data = item;//sets temp node data to parameter variable
    temp->prev = lp->head->prev;//temp points back to last node in list bc list is circular
    temp->next = lp->head;//temp points back to head node(at front of list)
    lp->head->prev->next = temp;
    lp->head->prev = temp;
    lp->count++;
}
void *removeFirst(LIST *lp) //O(1)
{
    assert(lp!=NULL);
    NODE *temp = lp->head->next;//points to first actual node(non dummy one)
    lp->head->next = temp->next;//sets head to point to node after temp
    lp->head->next->prev = lp->head;//node after temp points back to head
    void *value = temp->data;
    free(temp);//clears memory
    lp->count--;
    return value;
}
void *removeLast(LIST *lp) //O(1)
{
    assert(lp!=NULL);
    NODE *temp = lp->head->prev;//points to last node in list
    lp->head->prev = temp->prev;//head points to node before temp
    lp->head->prev->next = lp->head;//points back to head
    void *value = temp->data;
    free(temp);
    lp->count--;
    return value;
}
void *getFirst(LIST *lp) //O(1)
{
    assert(lp!=NULL);
    return(lp->head->next->data);
}
void *getLast(LIST *lp) //O(1)
{
    assert(lp!=NULL);
    return(lp->head->prev->data);
}
void removeItem(LIST *lp, void *item)//O(n)
{
    assert(lp->compare != NULL);
    NODE *pDel, *pTemp;
    pTemp = lp->head;
    do{
        pDel = pTemp->next;//pDel points to first actual node(skips dummy head node)
        if(lp->compare(item,pDel->data)==0)
        {
            pTemp->next = pDel->next;//pTemp now points to node after pDel
            pDel->next->prev = pTemp;//node after pDel points back to pTemp
            free(pDel);
            lp->count--;
            return;
        }
        pTemp = pDel;
    } while(pTemp != lp->head);
}
void *findItem(LIST *lp, void *item)//O(n)
{
    assert(lp->compare != NULL);
    NODE *pTemp = lp->head;//sets temp equal to dummy node
    while(pTemp->next != lp->head)
    {
        pTemp = pTemp->next;
        if((*lp->compare)(item,pTemp->data)==0)
        {
            return(pTemp->data);
        }
    }
    return NULL;
}
void *getItems(LIST *lp)//O(n)
{
    void **copy = malloc(sizeof(void*)*lp->count);
    NODE *temp = lp->head->next;
    for(int i=0;i<lp->count;i++)//iterates through and copies to new array
    {
        copy[i] = temp->data;
        temp = temp->next;
    }
    return copy;
}