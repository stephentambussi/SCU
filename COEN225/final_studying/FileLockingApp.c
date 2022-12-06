#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char line[256];
    int flist[8];
    int flck[8];
    char *token;
    int i = 0;
    while (printf("enter file to open$ "), fgets(line, 255, stdin) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        printf("%s\n", line);
        token = strtok(line, " ");
        printf("%s\n", token);
        flist[i] = open(token, O_RDWR | O_EXCL);
        flck[i] = flock(flist[i], LOCK_EX);
        printf("open() returned=%d\n", flist[i]);
        printf("flock() returned=%d\n", flck[i]);
        while(token != NULL)
        {
            token = strtok(NULL, " ");
            if(token != NULL)
            {
                printf("%s\n", token);
                flist[i] = open(token, O_RDWR | O_EXCL);
                flck[i] = flock(flist[i], LOCK_EX);
                printf("open() returned=%d\n", flist[i]);
                printf("flock() returned=%d\n", flck[i]);
            }
        }
        printf("\n");
        i++;
    }
    return 0;
}