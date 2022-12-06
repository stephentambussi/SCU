#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
/*
  This program takes input of the form:

  process_id1 file1 file2 ... *file10 *file11  ...
  process_id2 file4 file5 ... *file12 *file13  ...
  process_id3 file7 file8 ... *file14 *file15  ...

  First line says process_id1 has locks on file1 file2, etc, and is waiting to lock file10, file11 etc
  with file10, file11 being held by another process.

  An adjacency list is created for the process and its waited on files.

  [process_id1]->[file10]->[file11]
  [process_id2]->[file12]->[file13]
  [process_id3]->[file14]->[file15]

  Then a depth first search cycle detection algorithm is used to go through all the processes
  to determine if any one of them result in a circular wait, such as:

  process_id1 holding on file1 waiting for file10
  process_id7 holding on file10 waiting for file1

  process_id1 holding on file1 waiting for file10
  process_id7 holding on file10 waiting for file20
  process_id9 holding on file20 waiting for file1
*/

std::unordered_map<std::string, int> resource2pid;
std::unordered_map<int, int> pid2idx;
struct process_resource
{
    char *resource;
    struct process_resource *next;
};
struct process_info
{
    int pid;
	int in_deadlock;
    struct process_resource *locked;
    struct process_resource *waiting;
    char mark;
};
struct process_info process[8];
int resource_locked_by[8];
int append_list(struct process_resource **head, char *resource)
{
    struct process_resource *current;
    struct process_resource *previous;
    // printf("append_list resource=%s\n",resource);
    if (*head == NULL)
    {
        *head = (process_resource *)malloc(sizeof(struct process_resource));
        (*head)->resource = resource;
        (*head)->next = NULL;
        return 1;
    }
    previous = *head;
    current = (*head)->next;
    while (current != NULL)
    {
        previous = current;
        current = current->next;
    }
    previous->next = (process_resource *)malloc(sizeof(struct process_resource));
    previous->next->resource = resource;
    previous->next->next = NULL;
    return 1;
}
int dfs(int idx)
{
    static int in_deadlock_chain = 0;
    int deadlock = 0;
	process[idx].in_deadlock = 0;
    struct process_resource *current;
    struct process_resource *tmp;
    printf("dfs (%d)\n", process[idx].pid);
    if (process[idx].mark)
    {
        printf("Deadlock detected, pid=%d\n", process[idx].pid);
        process[idx].in_deadlock = -process[idx].pid;
        in_deadlock_chain = 1;
        return 1;
    }
    process[idx].mark = 1;
    current = process[idx].waiting;
    while (current != NULL)
    {
        printf("proc %d has ", process[idx].pid);
        tmp = process[idx].locked;
        while(tmp != NULL)
        {
            printf("%s ", tmp->resource);
            tmp = tmp->next;
        }
        printf("and waits for resource: %s held by proc %d\n", current->resource, resource2pid[current->resource]);
        if (dfs(pid2idx[resource2pid[current->resource]]))
        {
            if (in_deadlock_chain)
                printf("Deadlock pid: %d\n", abs(process[idx].pid));
            if (process[idx].in_deadlock < 0)
                in_deadlock_chain = 0;
            return 1;
        }
        current = current->next;
    }
    process[idx].mark = 0;
    return 0;
}
void check_deadlock()
{
    int i;
    for (i = 0; i < 8; i++)
        process[i].mark = 0;
    i = 0;
    while (i < 8)
    {
        if (process[i].mark == 0)
			if (!dfs(i))
        		exit(0);
        i++;
    }
}
int main(void)
{
    char line[8][256];
    char cmd[256];
    int pid, rid;
    int i, n;
    char *token;
    struct process_resource *current;
    for (i = 0; i < 8; i++)
        resource_locked_by[i] = -1;
    for (i = 0; i < 8; i++)
    {
        process[i].locked = process[i].waiting = NULL;
    }
    n = 0;
    while (printf("enter process action$ "), fgets(line[n], 255, stdin) != NULL)
    {
        line[n][strlen(line[n]) - 1] = '\0';
        token = strtok(line[n], " ");
        process[n].pid = atoi(token);
        pid2idx[process[n].pid] = n;
        while (token != NULL)
        {
            // printf( " %s\n", token );
            token = strtok(NULL, " ");
            if (token != NULL)
                if (token[0] != '*')
                {
                    resource2pid[token] = process[n].pid;
                    append_list(&process[n].locked, token);
                }
                else
                {
                    append_list(&process[n].waiting, token + 1);
                }
        }
        n++;
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("pid:%d has lock on: ", process[i].pid);
        current = process[i].locked;
        while (current != NULL)
        {
            printf("%s ", current->resource);
            current = current->next;
        }
        printf("waiting for: ");
        current = process[i].waiting;
        while (current != NULL)
        {
            printf("%s ", current->resource);
            current = current->next;
        }
        printf("\n");
    }
    check_deadlock();
    return 0;
}
