/*
* Given a program, identify the vulnerabilities, and which analysis solution is used to detect the vulnerabilities.
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// These vulnerabilities are detected through static analysis
void static_vul()
{
    char formatstr[16]; // Need to perform bounds checking to prevent overflow
    char str[16];
    
    printf("enter password:");
    scanf("%s",formatstr); // Scanf without a limit, permits buffer overflows
    scanf(formatstr,str);


    char fn[]="./temp.file";
    FILE *stream;
    struct stat info;

    if ((stream = fopen(fn, "w")) == NULL) // fopen can allow attackers to redirect via symlink
        perror("fopen() error");
    else {
        fclose(stream);
        stat(fn, &info);
        printf("original owner was %d and group was %d\n", info.st_uid,
                info.st_gid);
        if (chown(fn, 25, 0) != 0)  // Attacker can move files to cause race condition
            perror("chown() error");
        else {
            stat(fn, &info);
            printf("after chown(), owner is %d and group is %d\n",
                    info.st_uid, info.st_gid);
        }
        unlink(fn);
    }

    char filename[64];
    char address[64];
    char cmd[256];
    // gdb -batch -ex "file a.out" -ex "info line * 0x80484a6"
    printf("enter filename:");
    scanf("%s", filename);  // TAINTED --> example payload: ';date > /tmp/date.txt;'
    
    // gdb -batch -ex 'file ';date > /tmp/date.txt;'' -ex 'info line * %s' > /tmp/gdb.out
    // The above command would only execute the 'date > /tmp/date.txt' portion and ignore the rest (due to the semicolons)

    printf("enter address:");
    scanf("%s", address);   // TAINTED

    sprintf(cmd, "gdb -batch -ex 'file %s' -ex 'info line * %s' > /tmp/gdb.out", filename, address);
    printf("cmd=%s\n", cmd);
    system(cmd);

    return;
}

// These vulnerabilities are detected through dynamic analysis
char passwd[20] = "california";
char input[16] = "";
int matched = 0;
void dynamic_vul()
{
    // Variable overflow
    printf("enter password:");
    scanf("%s", input);

    if (strcmp(passwd, input) == 0)
        matched = 1;

    if (matched)
        printf("you guessed right!\n");
    else
        printf("you guessed wrong!\n");

    // Uninitialized memory
    int a[2];
    int b = a[0];

    // Memory leaks
    void *p = malloc(10);
    
    return;
}

int main()
{
    static_vul();
    dynamic_vul();
    return 0;
}