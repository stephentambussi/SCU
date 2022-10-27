/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 3 - Extra Credit
*   11/1/22
*/
#include <stdio.h>
#include <stdlib.h>

struct linkrecord {
    int data;
    struct linkrecord *next;
};

struct linkrecord *head;
struct linkrecord *p;

//EXTRA CREDIT SOLUTION
void delete(struct linkrecord *p)
{
    //Move/copy node with data=3 to node to be deleted and
    //then delete and remove data=3
    struct linkrecord *cursor = p->next;
    if(cursor != NULL) //do some stuff
    {
        //overwrite the node to be deleted with the node after it
        p->data = cursor->data;
        p->next = cursor->next;

        //Delete the node currently pointed to by cursor
        free(cursor);
    }
    return;
}

/* Utility Functions for Testing */
struct linkrecord *create_node(int data)
{
    struct linkrecord *node = (struct linkrecord *)malloc(sizeof(struct linkrecord));
    node->data = data;
    return node;
}

struct linkrecord *create_list(int size)
{
    //This function will create a basic linkedlist
    struct linkrecord *head = create_node(1);
    int i = 2; //iterator
    struct linkrecord *cur = head;
    while(i < size + 1)
    {
        cur->next = create_node(i);
        cur = cur->next;
        i++;
    }
    cur->next = NULL; //Last node in list points to NULL
    return head;
}

void print_list(struct linkrecord *head)
{
    struct linkrecord *cur = head;
    while(cur != NULL)
    {
        printf("[data=%d,next", cur->data);
        if(cur->next != NULL)
        {
            printf("]->");
        }
        else
        {
            printf("=NULL]");
        }
        cur = cur->next;
    }
    printf("\n");
}

int main(void)
{
    head = create_list(3);
    printf("Before deletion: \n");
    print_list(head);

    p = head->next;
    delete(p);

    printf("After deletion: \n");
    print_list(head);
    return 0;
}

/*
*   Given the following linked list:
*   head             p              cur
*   |                |               |
*   v                v               v
*   [data=1,next]->[data=2,next]->[data=3,next=NULL]
*
*   Write the function delete resulting in the above list becoming:
*   [data=1,next]->[data=3,next=NULL]
*
*   You are given pointer p, NOT pointer head, to call function delete() like:
*   delete(p);
*/