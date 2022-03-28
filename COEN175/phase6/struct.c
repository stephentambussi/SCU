struct data {
    int a, b;
};

struct node {
    int x, y;
    struct data d;
};

struct node n;

int f(void)
{
    struct node p;
    p.d.b = n.y;
}