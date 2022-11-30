#include <string.h>
#include <stdio.h>
int main()
{
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
}