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

void delete(struct linkrecord *p)
{
    //TODO: implementation
    return;
}

int main(void)
{
    return 0;
}

/*
*   Given the following linked list:
*   head             p
*   |                |
*   v                v
*   [data=1,next]->[data=2,next]->[data=3,next=NULL]
*
*   Write the function delete resulting in the above list becoming:
*   [data=1,next]->[data=3,next=NULL]
*
*   You are given pointer p, NOT pointer head, to call function delete() like:
*   delete(p);
*/