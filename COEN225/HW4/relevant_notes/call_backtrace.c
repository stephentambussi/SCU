/*
 *   This program is used to display the runtime stack programmatically
 */
#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>
void print_trace(void)
{
    char **strings;
    size_t i, size;
    enum Constexpr
    {
        MAX_SIZE = 1024
    };
    void *array[MAX_SIZE];
    size = backtrace(array, MAX_SIZE);
    strings = backtrace_symbols(array, size);
    for (i = 0; i < size; i++)
        printf("%s\n", strings[i]);
    puts("");
    free(strings);
}
int bar()
{
    int z = 3;
    print_trace();
    return z;
}
int foo()
{
    int y = 2;
    y = bar();
    return y;
}
int main()
{
    int x = 1;
    x = foo();
}