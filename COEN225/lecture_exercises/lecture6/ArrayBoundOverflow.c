#include <stdio.h>
#include <string.h>
struct item
{
    char name[16];
    int cost;
    int count;
};
struct item itemlist[5] = {
    {"milk ", 5, 0},
    {"eggs ", 8, 0},
    {"juice", 6, 0},
    {"bread", 4, 0},
    {"ham  ", 7, 0},
};
char *label[4] = {"no", "description", "cost", "count"};
int balance = 0;
int main(int argc, char *argv[])
{
    int i, choice, number;
    char buf[80];

    for (i = 0; i < 4; i++)
        printf("%s ", label[i]);
    printf("\n");
    for (i = 0; i < 5; i++)
        printf("%d:%s        $%d       %d\n", i, itemlist[i].name, itemlist[i].cost, itemlist[i].count);

    while (1)
    {
        puts("choose item and count");
        scanf("%d %d", &choice, &number);
        itemlist[choice].count = number;
        balance += itemlist[choice].count * itemlist[choice].cost;
        for (i = 0; i < 4; i++)
            printf("%s ", label[i]);
        printf("\n");
        for (i = 0; i < 5; i++)
            printf("%d:%s        $%d       %d\n", i, itemlist[i].name, itemlist[i].cost, itemlist[i].count);
        printf("balance:$%d\n", balance);
    }
    return 0;
}