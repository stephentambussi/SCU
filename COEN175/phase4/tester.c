/*
struct foo {
    int x;
};
*/

struct bar {
    int x, *p, a[10];
};

struct foo psf, **asf[10], **y;
struct bar sb, *psb, *arr[10], f[5];
struct node *np, **npp;
int x[10];
int b;
char r;
char ***test;
int (*g)();
int g2();

int main(void)
{
    f[0].x;
    /*indirect struct ref with array of ptrs to structs */
    arr[1]->x; /*a[i] = *(a + i) */
    /*vs*/
    /*direct struct ref with array of ptrs to structs */
    (*arr[1]).x;
    /* sizeof test */
    sizeof(psf);
}