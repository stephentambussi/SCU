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
    int i = 0;
    while (printf("enter file to open$ "), fgets(line, 255, stdin) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        printf("%s", line);
        printf("\n");
        flist[i] = open(line, O_RDWR | O_EXCL);
        flck[i] = flock(flist[i], LOCK_EX);
        printf("open() returned=%d\n", flist[i]);
        printf("flock() returned=%d\n", flck[i]);
        i++;
    }
    return 0;
}