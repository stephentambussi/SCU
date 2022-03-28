int (*f)(), (*h)();
int *(*g)();

int printf();
char *malloc();

int main(void)
{
    f = printf;
    g = malloc;				/* invalid operands to binary = */
    printf = f;				/* lvalue required in expression */
    h = f;
    h == g;				/* invalid operands to binary == */
    h != f;
    f("hello");
}
