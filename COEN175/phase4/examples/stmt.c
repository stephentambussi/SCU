struct node {
    int x, y;
};

struct node n;

int **f(void)
{
    int *p;
    return p;			/* invalid return type */
}

int main(void)
{
    if (n) main();		/* invalid type for test expression */
    if (main) main();
}
