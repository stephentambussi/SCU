#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Queue implementation
Node *createNode(void *value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Queue *createQueue()
{
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->size = 0;
    return newQueue;
}

void enqueue(Queue *q, void *value)
{
    Node *newNode = createNode(value);

    newNode->prev = q->tail;
    if(q->tail == NULL)
    {   //Empty queue
        q->tail = newNode;
        q->head = newNode;
    }
    else
    {   //Queue has elements in it
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size++;
}

void *dequeue(Queue *q)
{
    if(q->head != NULL)
    {
        Node *curNode = q->head;
        void *value = curNode->value;
        Node *nextNode = q->head->next;

        if(nextNode != NULL)
            nextNode->prev = NULL;
        
        q->head = nextNode;

        if(q->tail == curNode)
            q->tail = NULL;
        
        q->size--;
        free(curNode);
        return value;
    }
}

void sort(Queue *q, int (*cmp)(void *val1, void *val2))
{
    Node *i = q->head;
    while(i != NULL)
    {
        Node *j = i->next;
        while(j != NULL)
        {
            void *p1 = i->value;
            void *p2 = j->value;
            if((*cmp)(p1, p2) > 0)
                swapNodes(i, j);
            j = j->next;
        }
        i = i->next;
    }
}

void swapNodes(Node *a, Node *b)
{
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}